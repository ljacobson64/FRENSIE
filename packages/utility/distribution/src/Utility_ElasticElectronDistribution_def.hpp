//---------------------------------------------------------------------------//
//!
//! \file   Utility_ElasticElectronDistribution_def.hpp
//! \author Luke Kersting
//! \brief  Tabular distribution for elastic electron scattering class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ELASTIC_ELECTRONDISTRIBUTION_DEF_HPP
#define UTILITY_ELASTIC_ELECTRONDISTRIBUTION_DEF_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_DataProcessor.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_KinematicHelpers.hpp"

namespace Utility{

// Default constructor
template<typename InterpolationPolicy>
ElasticElectronDistribution<InterpolationPolicy>::ElasticElectronDistribution()
{ /* ... */ }

// Constructor
/*! \details The independent values are assumed to be sorted (lowest to 
 * highest).
 */ 
template<typename InterpolationPolicy>
ElasticElectronDistribution<InterpolationPolicy>::ElasticElectronDistribution( 
			      const Teuchos::Array<double>& independent_values,
			      const Teuchos::Array<double>& dependent_values,
                  const double energy,
                  const unsigned atomic_number,
                  const bool interpret_dependent_values_as_cdf )
  : d_energy( energy ),
    d_atomic_number( atomic_number ),
    d_Z_two_thirds_power( pow( atomic_number, 2.0/3.0 ) ),
    d_distribution( independent_values.size() ),
    d_norm_constant( 0.0 )
{
  if( interpret_dependent_values_as_cdf )
  {
    // Make sure the energy is valid
    testPrecondition( energy > 0 );
    // Make sure the atomic number is valid
    testPrecondition( atomic_number > 0u );
    testPrecondition( atomic_number <= 100u );
    // Make sure that at least two points of the distribution are specified
    testPrecondition( independent_values.size() > 1 );
    // Make sure that at least two points of the distribution are specified
    testPrecondition( independent_values.size() > 1 );
    // Make sure that for n bin boundaries there are n bin values
    testPrecondition( independent_values.size() == dependent_values.size() );
    // Make sure that the bins are sorted
    testPrecondition( Sort::isSortedAscending( independent_values.begin(),
					       independent_values.end() ) );
    // Make sure that the bin values are sorted
    testPrecondition( Sort::isSortedAscending( dependent_values.begin(), 
					       dependent_values.end() ) );

    unsigned size = independent_values.size();

    // Set the last two data bins
    d_distribution[size-1].first = independent_values[size-1];
    d_distribution[size-1].second = dependent_values[size-1];
    d_distribution[size-2].first = independent_values[size-2];
    d_distribution[size-2].second = dependent_values[size-2];
    setLastTwoPDFs( dependent_values[size-1], 
                    dependent_values[size-2] );

    // Assign the distribution
    for( int i = size-3; i >= 0; --i )
    {
      d_distribution[i].first = independent_values[i];
      d_distribution[i].second = dependent_values[i];

      // Use Lin-Lin interpolation for the pdf and quadratic for the cdf
      if ( d_distribution[i+1].second != d_distribution[i].second )
      {
        // Calculate the pdf from the cdf
        d_distribution[i].third = -d_distribution[i+1].third + 2.0 *
          (d_distribution[i+1].second - d_distribution[i].second)/
          (d_distribution[i+1].first - d_distribution[i].first);
      }
      else // If the cdf does not change inbetween angular bins, set the pdf to zero
      {
        d_distribution[i].third = 0.0; 
      }
    }

    // Set normalization constant
    d_norm_constant = d_distribution.back().second;
 
    // Verify that the CDF is normalized (in event of round-off errors)
    if( dependent_values.back() != 1.0 )
    {
      for( unsigned j = 0; j < d_distribution.size(); ++j )
      {
        d_distribution[j].second /= d_norm_constant;
        d_distribution[j].third /= d_norm_constant;
      }
    }

    // Calculate the slopes of the PDF
    DataProcessor::calculateSlopes<FIRST,THIRD,FOURTH>( d_distribution );
  }
  else
  {
    initializeDistribution( independent_values, dependent_values );
  }
}

// Copy constructor
template<typename InterpolationPolicy>
ElasticElectronDistribution<InterpolationPolicy>::ElasticElectronDistribution(
		const ElasticElectronDistribution<InterpolationPolicy>& dist_instance )
  : d_distribution( dist_instance.d_distribution ),
    d_norm_constant( dist_instance.d_norm_constant )
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );
}

// Assignment operator
template<typename InterpolationPolicy>
ElasticElectronDistribution<InterpolationPolicy>& 
ElasticElectronDistribution<InterpolationPolicy>::operator=(
		const ElasticElectronDistribution<InterpolationPolicy>& dist_instance )
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );

  if( this != &dist_instance )
  {
    d_distribution = dist_instance.d_distribution;
    d_norm_constant = dist_instance.d_norm_constant;
  }
  
  return *this;
}

// Evaluate the distribution
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::evaluate( 
					   const double indep_var_value ) const
{
  return evaluatePDF( indep_var_value )*d_norm_constant;
}

// Evaluate the PDF
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::evaluatePDF( 
					   const double indep_var_value ) const
{
  if( indep_var_value < d_distribution.front().first )
    return 0.0;
  else if( indep_var_value > d_distribution.back().first )
    return 0.0;
  else if( indep_var_value == d_distribution.back().first )
    return d_distribution.back().third;
  else
  {
    DistributionArray::const_iterator start, end, lower_bin_boundary,
      upper_bin_boundary;
    start = d_distribution.begin();
    end = d_distribution.end();

    lower_bin_boundary = Search::binaryLowerBound<FIRST>( start,
							  end,
							  indep_var_value );

    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;
    
    double lower_indep_value = lower_bin_boundary->first;
    double lower_pdf_value = lower_bin_boundary->third;
    double upper_indep_value = upper_bin_boundary->first;
    double upper_pdf_value = upper_bin_boundary->third;
    
    return InterpolationPolicy::interpolate( lower_indep_value,
					     upper_indep_value,
					     indep_var_value,
					     lower_pdf_value,
					     upper_pdf_value );
  }
}

// Evaluate the CDF
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::evaluateCDF( 
					   const double indep_var_value ) const
{
  if( indep_var_value < d_distribution.front().first )
    return 0.0;
  else if( indep_var_value >= d_distribution.back().first )
    return 1.0;
  else
  {
    DistributionArray::const_iterator start, end, lower_bin_boundary;
    start = d_distribution.begin();
    end = d_distribution.end();

    lower_bin_boundary = Search::binaryLowerBound<FIRST>( start,
							  end,
							  indep_var_value );

    double indep_diff = indep_var_value - lower_bin_boundary->first;

    return lower_bin_boundary->second + indep_diff*lower_bin_boundary->third +
           indep_diff*indep_diff/2.0 * lower_bin_boundary->fourth;
  }
}

// Return a random sample from the distribution
template<typename InterpolationPolicy>
inline double ElasticElectronDistribution<InterpolationPolicy>::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();
  
  unsigned dummy_index;
  
  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample and record the number of trials
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::sampleAndRecordTrials( 
						       unsigned& trials ) const
{
  ++trials;

  return this->sample();
}

// Return a random sample and bin index from the distribution
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::sampleAndRecordBinIndex( 
					    unsigned& sampled_bin_index ) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleImplementation( random_number, sampled_bin_index );
}

// Return a sample from the distribution at the given CDF value
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::sampleWithRandomNumber( 
					     const double random_number ) const
{
  unsigned dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample from the corresponding CDF in a subrange
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::sampleInSubrange( 
					     const double max_indep_var ) const
{
  // Make sure the maximum indep var is valid
  testPrecondition( max_indep_var >= this->getLowerBoundOfIndepVar() );
    
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleWithRandomNumberInSubrange( random_number,
						 max_indep_var );
}

// Return a random sample from the distribution at the given CDF value in a subrange
template<typename InterpolationPolicy>
inline double ElasticElectronDistribution<InterpolationPolicy>::sampleWithRandomNumberInSubrange( 
					     const double random_number,
					     const double max_indep_var ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the maximum indep var is valid
  testPrecondition( max_indep_var >= this->getLowerBoundOfIndepVar() );
  
  // Calculate a scaled random number
  double scaled_random_number = 
    random_number*this->evaluateCDF( max_indep_var );
    
  unsigned dummy_index;

  return this->sampleImplementation( scaled_random_number, dummy_index );
}

// Return a random sample using the random number and record the bin index
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::sampleImplementation( 
					    double random_number,
					    unsigned& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  DistributionArray::const_iterator start, end, lower_bin_boundary;
  start = d_distribution.begin();
  end = d_distribution.end();

  lower_bin_boundary = Search::binaryLowerBound<SECOND>( start,
							 end,
							 random_number );

  // Calculate the sampled bin index
  sampled_bin_index = std::distance(d_distribution.begin(),lower_bin_boundary);

  // Calculate the sampled independent value
  double sample;
  
  double indep_value = lower_bin_boundary->first;
  double cdf_diff = random_number - lower_bin_boundary->second;
  double pdf_value = lower_bin_boundary->third;
  double slope = lower_bin_boundary->fourth;

  // x = x0 + [sqrt(pdf(x0)^2 + 2m[cdf(x)-cdf(x0)]) - pdf(x0)]/m 
  if( slope != 0.0 )
  {
    sample = indep_value + 
      (sqrt( pdf_value*pdf_value + 2*slope*cdf_diff ) - pdf_value)/slope;
  }
  // x = x0 + [cdf(x)-cdf(x0)]/pdf(x0) => L'Hopital's rule
  else
    sample =  indep_value + cdf_diff/pdf_value;

  // Make sure the sample is valid
  testPostcondition( !Teuchos::ScalarTraits<double>::isnaninf( sample ) );

  return sample;
}

// Return the upper bound of the distribution independent variable
template<typename InterpolationPolicy>
double 
ElasticElectronDistribution<InterpolationPolicy>::getUpperBoundOfIndepVar() const
{
  return d_distribution.back().first;
}

// Return the lower bound of the distribution independent variable
template<typename InterpolationPolicy>
double 
ElasticElectronDistribution<InterpolationPolicy>::getLowerBoundOfIndepVar() const
{
  return d_distribution.front().first;
}

// Return the distribution type
template<typename InterpolationPolicy>
OneDDistributionType 
ElasticElectronDistribution<InterpolationPolicy>::getDistributionType() const
{
  return ElasticElectronDistribution<InterpolationPolicy>::distribution_type;
}

// Test if the distribution is continuous
template<typename InterpolationPolicy>
bool ElasticElectronDistribution<InterpolationPolicy>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::toStream( 
						       std::ostream& os ) const
{
  Teuchos::Array<double> independent_values( d_distribution.size() );
  Teuchos::Array<double> dependent_values( d_distribution.size() );

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
  {
    independent_values[i] = d_distribution[i].first;
    
    dependent_values[i] = d_distribution[i].third*d_norm_constant;
  }

  os << "{" << independent_values << "," << dependent_values << "}";
}

// Method for initializing the object from an input stream
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::fromStream( std::istream& is )
{
  // Read the initial '{'
  std::string start_bracket;
  std::getline( is, start_bracket, '{' );
  start_bracket = Teuchos::Utils::trimWhiteSpace( start_bracket );
  
  TEST_FOR_EXCEPTION( start_bracket.size() != 0, 
		      InvalidDistributionStringRepresentation, 
		      "Error: the input stream is not a valid elastic electron "
		      "distribution representation!" );

  std::string independent_values_rep;
  std::getline( is, independent_values_rep, '}' );
  independent_values_rep += "}";

  // Parse special characters
  try{
    ArrayString::locateAndReplacePi( independent_values_rep );
    ArrayString::locateAndReplaceIntervalOperator( independent_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
			      InvalidDistributionStringRepresentation,
			      "Error: the elastic electron distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );
  
  Teuchos::Array<double> independent_values;
  try{ 
    independent_values = 
      Teuchos::fromStringToArray<double>( independent_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the elastic electron distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );
    
  TEST_FOR_EXCEPTION( !Sort::isSortedAscending( independent_values.begin(),
						independent_values.end() ),
		      InvalidDistributionStringRepresentation, 
		      "Error: the elastic electron distribution cannot be constructed "
		      "because the bin boundaries "
		      << independent_values_rep << " are not sorted!" );
  
  // Read the ","
  std::string separator;
  std::getline( is, separator, ',' );

  std::string dependent_values_rep;
  std::getline( is, dependent_values_rep, '}' );
  dependent_values_rep += "}";

  // Parse special characters
  try{
    ArrayString::locateAndReplacePi( dependent_values_rep );
    ArrayString::locateAndReplaceIntervalOperator( dependent_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
			      InvalidDistributionStringRepresentation,
			      "Error: the elastic electron distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );
  
  Teuchos::Array<double> dependent_values;
  try{
    dependent_values = 
      Teuchos::fromStringToArray<double>( dependent_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the elastic electron distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );
			      
  TEST_FOR_EXCEPTION( independent_values.size() != dependent_values.size(),
		      InvalidDistributionStringRepresentation, 
		      "Error: the elastic electron distribution "
		      "{" << independent_values_rep << "},{"
		      << dependent_values_rep << "} "
		      "cannot be constructed because the number of "
		      "independent values does not equal the number of "
		      "dependent values" );
		        
  initializeDistribution( independent_values, dependent_values );
}

// Method for testing if two objects are equivalent
template<typename InterpolationPolicy>
bool ElasticElectronDistribution<InterpolationPolicy>::isEqual( 
		  const ElasticElectronDistribution<InterpolationPolicy>& other ) const
{
  return d_distribution == other.d_distribution && 
    d_norm_constant == other.d_norm_constant;
}

// Initialize the distribution
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::initializeDistribution(
			      const Teuchos::Array<double>& independent_values,
			      const Teuchos::Array<double>& dependent_values )
{
  // Make sure that at least two points of the distribution are specified
  testPrecondition( independent_values.size() > 1 );
  // Make sure that the independent values are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
					     independent_values.end() ) );
  // Make sure that every independent value has a dependent value
  testPrecondition( independent_values.size() == dependent_values.size() );

  // Resize the distribution
  d_distribution.resize( independent_values.size() );
  
  // Assign the raw distribution data
  for( unsigned i = 0; i < independent_values.size(); ++i )
  {
    d_distribution[i].first = independent_values[i];
    d_distribution[i].third = dependent_values[i];
  }

  // Create a CDF from the raw distribution data
  d_norm_constant = 
    DataProcessor::calculateContinuousCDF<FIRST,THIRD,SECOND>(d_distribution);

  // Calculate the slopes of the PDF
  DataProcessor::calculateSlopes<FIRST,THIRD,FOURTH>( d_distribution );
}

// Set the last two PDF values
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::setLastTwoPDFs( 
        const double& last_cdf,
        const double& second_to_last_cdf )
{
  // get size of array
  unsigned size = d_distribution.size();

  // get the momentum**2 of the electron in units of electron_rest_mass_energy
  double electron_momentum_squared = 
           Utility::calculateDimensionlessRelativisticMomentumSquared( 
                          Utility::PhysicalConstants::electron_rest_mass_energy,
                          d_energy );

  // get the velocity of the electron divided by the speed of light beta = v/c
  double beta_squared = Utility::calculateDimensionlessRelativisticSpeedSquared( 
           Utility::PhysicalConstants::electron_rest_mass_energy,
           d_energy );

  // The fine structure constant squared
  double fine_structure_const_squared=
        Utility::PhysicalConstants::fine_structure_constant*
        Utility::PhysicalConstants::fine_structure_constant;

  double screening_param1 = fine_structure_const_squared/( 2.0*0.885*0.885 );

  double screening_param2 = 3.76*fine_structure_const_squared*
                            d_atomic_number*d_atomic_number;

  double screening_param3 = 1.0/beta_squared*sqrt( d_energy/
          ( d_energy + Utility::PhysicalConstants::electron_rest_mass_energy) );

  // Calculate Moliere's atomic screening constant
  double eta = screening_param1 * 1.0/electron_momentum_squared * 
          d_Z_two_thirds_power * ( 1.13 + screening_param2*screening_param3 );
 
  double var = (0.000001 + eta);

  // Calculate the normalization constant
  double norm_const = (last_cdf - second_to_last_cdf)*
                        eta*var/0.000001;


  d_distribution[size-2].third = norm_const/( var*var );
  d_distribution[size-1].third = norm_const/( eta*eta );
}
				       			    
} // end Utility namespace

#endif // end Utility_ElasticElectronDistribution_def.hpp

//---------------------------------------------------------------------------//
// end Utility_ElasticElectronDistribution_def.hpp
//---------------------------------------------------------------------------//
