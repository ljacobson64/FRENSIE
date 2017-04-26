//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MomentPreservingElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The moment preserving electron elastic scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_MomentPreservingElasticElectronScatteringDistribution.hpp"

namespace MonteCarlo{

// Constructor
MomentPreservingElasticElectronScatteringDistribution::MomentPreservingElasticElectronScatteringDistribution(
    const std::shared_ptr<TwoDDist>& discrete_scattering_distribution,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on )
  : d_discrete_scattering_distribution( discrete_scattering_distribution ),
    d_cutoff_angle_cosine( cutoff_angle_cosine )
{
  // Make sure the array is valid
  testPrecondition( d_discrete_scattering_distribution.use_count() > 0 );
  // Make sure the cutoff angle cosine is valid
  testPostcondition( d_cutoff_angle_cosine >= -1.0 );
  testPostcondition( d_cutoff_angle_cosine < 1.0 );
  // Make sure the bool is valid
  testPrecondition( correlated_sampling_mode_on == 0 ||
                    correlated_sampling_mode_on == 1 )

  if( correlated_sampling_mode_on )
  {
    // Set the correlated unit based sample routine
    d_sample_func = std::bind<double>(
         &TwoDDist::sampleSecondaryConditionalExact,
         std::cref( *d_discrete_scattering_distribution ),
         std::placeholders::_1 );
  }
  else
  {
    // Set the stochastic unit based sample routine
    d_sample_func = std::bind<double>(
         &TwoDDist::sampleSecondaryConditional,
         std::cref( *d_discrete_scattering_distribution ),
         std::placeholders::_1 );
  }
}


// Evaluate the distribution
double MomentPreservingElasticElectronScatteringDistribution::evaluate(
    const double incoming_energy,
    const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // evaluate the distribution at the incoming energy and scattering_angle_cosine
  return d_discrete_scattering_distribution->evaluateExact(
                        incoming_energy,
                        scattering_angle_cosine );
}

// Evaluate the PDF
double MomentPreservingElasticElectronScatteringDistribution::evaluatePDF(
                            const double incoming_energy,
                            const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // evaluate the PDF at the incoming energy and scattering_angle_cosine
  return d_discrete_scattering_distribution->evaluateSecondaryConditionalPDFExact(
                        incoming_energy,
                        scattering_angle_cosine );
}

// Evaluate the CDF
double MomentPreservingElasticElectronScatteringDistribution::evaluateCDF(
                            const double incoming_energy,
                            const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // evaluate the CDF at the incoming energy and scattering_angle_cosine
  return d_discrete_scattering_distribution->evaluateSecondaryConditionalCDFExact(
                        incoming_energy,
                        scattering_angle_cosine );
}

// Sample an outgoing energy and direction from the distribution
void MomentPreservingElasticElectronScatteringDistribution::sample(
               const double incoming_energy,
               double& outgoing_energy,
               double& scattering_angle_cosine ) const
{
  // The outgoing energy is always equal to the incoming energy
  outgoing_energy = incoming_energy;

  unsigned trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( incoming_energy,
                                   scattering_angle_cosine,
                                   trial_dummy );
}

// Sample an outgoing energy and direction and record the number of trials
void MomentPreservingElasticElectronScatteringDistribution::sampleAndRecordTrials(
                const double incoming_energy,
                double& outgoing_energy,
                double& scattering_angle_cosine,
                unsigned& trials ) const
{
  // The outgoing energy is always equal to the incoming energy
  outgoing_energy = incoming_energy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( incoming_energy,
                                   scattering_angle_cosine,
                                   trials );
}

// Randomly scatter the electron
void MomentPreservingElasticElectronScatteringDistribution::scatterElectron(
                ElectronState& electron,
                ParticleBank& bank,
                Data::SubshellType& shell_of_interaction ) const
{
  double scattering_angle_cosine;

  unsigned trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( electron.getEnergy(),
                                   scattering_angle_cosine,
                                   trial_dummy );

  shell_of_interaction = Data::UNKNOWN_SUBSHELL;

  // Set the new direction
  electron.rotateDirection( scattering_angle_cosine,
                            this->sampleAzimuthalAngle() );
}

// Randomly scatter the adjoint electron
void MomentPreservingElasticElectronScatteringDistribution::scatterAdjointElectron(
                AdjointElectronState& adjoint_electron,
                ParticleBank& bank,
                Data::SubshellType& shell_of_interaction ) const
{
  double scattering_angle_cosine;

  unsigned trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( adjoint_electron.getEnergy(),
                                   scattering_angle_cosine,
                                   trial_dummy );

  shell_of_interaction = Data::UNKNOWN_SUBSHELL;

  // Set the new direction
  adjoint_electron.rotateDirection( scattering_angle_cosine,
                                    this->sampleAzimuthalAngle() );
}

// Sample an outgoing direction from the distribution
void MomentPreservingElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl(
                const double incoming_energy,
                double& scattering_angle_cosine,
                unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // Increment the number of trials
  ++trials;

  scattering_angle_cosine =
    d_discrete_scattering_distribution->sampleSecondaryConditionalExact(
        incoming_energy );

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= d_cutoff_angle_cosine );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//