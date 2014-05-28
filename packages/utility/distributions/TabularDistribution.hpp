//---------------------------------------------------------------------------//
//!
//! \file   TabularDistribution.hpp
//! \author Alex Robinson
//! \brief  Tabular distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef TABULAR_DISTRIBUTION_HPP
#define TABULAR_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FACEMC Includes
#include "OneDDistribution.hpp"
#include "InterpolationPolicy.hpp"
#include "Tuple.hpp"

namespace FACEMC{

//! The interpolated distribution class declaration
template<typename InterplationPolicy>
class TabularDistribution : public OneDDistribution
{

public:

  //! Constructor
  TabularDistribution( const Teuchos::Array<double>& independent_values,
		       const Teuchos::Array<double>& dependent_values );

  //! Evaluate the distribution
  double evaluate( const double indep_var_value ) const;
  
  //! Evaluate the PDF
  double evaluatePDF( const double indep_var_value ) const;

  //! Return a random sample from the distribution
  double sample();

  //! Return a random sample from the distribution
  double sample() const;

  //! Return the sampling efficiency from the distribution
  double getSamplingEfficiency() const;

  //! Return the upper bound of the distribution independent variable
  double getUpperBoundOfIndepVar() const;
  
  //! Return the lower bound of the distribution independent variable
  double getLowerBoundOfIndepVar() const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

private:

  // The distribution type
  static const OneDDistributionType distribution_type = TABULAR_DISTRIBUTION;

  // The distribution (first = indep_var, second = cdf, third = pdf, 
  // fourth = slope)
  typedef Teuchos::Array<Quad<double,double,double,double> > DistributionArray;
  DistributionArray d_distribution;

  // The normalization constant
  double d_norm_constant;
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template inludes.
//---------------------------------------------------------------------------//

#include "TabularDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end TABULAR_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end TabularDistribution.hpp
//---------------------------------------------------------------------------//