//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationAdjointElectronProperties.hpp
//! \author Luke Kersting
//! \brief  Simulation adjoint electron properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SimulationAdjointElectronProperties.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// The absolute mimimum adjoint electron energy (MeV)
const double SimulationAdjointElectronProperties::s_absolute_min_adjoint_electron_energy = 1e-5;

// The absolume maximum adjoint electron energy (MeV)
const double SimulationAdjointElectronProperties::s_absolute_max_adjoint_electron_energy = 20.0;

// Constructor
SimulationAdjointElectronProperties::SimulationAdjointElectronProperties()
  : d_min_adjoint_electron_energy( s_absolute_min_adjoint_electron_energy ),
    d_max_adjoint_electron_energy( s_absolute_max_adjoint_electron_energy ),
    d_adjoint_elastic_mode_on( true ),
    d_adjoint_bremsstrahlung_mode_on( true ),
    d_adjoint_electroionization_mode_on( true ),
    d_adjoint_atomic_excitation_mode_on( true ),
    d_adjoint_evaluation_tol( 1e-7 ),
    d_adjoint_correlated_sampling_mode_on( true ),
    d_adjoint_unit_based_interpolation_mode_on( true ),
    d_adjoint_bremsstrahlung_angular_distribution_function( TWOBS_DISTRIBUTION ),
    d_adjoint_elastic_cutoff_angle_cosine( 1.0 ),
    d_num_adjoint_electron_hash_grid_bins( 500 )
{ /* ... */ }
  
// Set the minimum adjoint electron energy (MeV)
void SimulationAdjointElectronProperties::setMinAdjointElectronEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition( energy >= s_absolute_min_adjoint_electron_energy );
  testPrecondition( energy < d_max_adjoint_electron_energy );

  d_min_adjoint_electron_energy = energy;
}

// Return the minimum adjoint electron energy (MeV)
double SimulationAdjointElectronProperties::getMinAdjointElectronEnergy() const
{
  return d_min_adjoint_electron_energy;
}

// Return the absolute minimum adjoint electron energy (MeV)
double SimulationAdjointElectronProperties::getAbsoluteMinAdjointElectronEnergy()
{
  return s_absolute_min_adjoint_electron_energy;
}

// Set the maximum adjoint electron energy (MeV)
void SimulationAdjointElectronProperties::setMaxAdjointElectronEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition( energy > d_min_adjoint_electron_energy );
  testPrecondition( energy <= s_absolute_max_adjoint_electron_energy );

  d_max_adjoint_electron_energy = energy;
}

// Return the maximum adjoint electron energy (MeV)
double SimulationAdjointElectronProperties::getMaxAdjointElectronEnergy() const
{
  return d_max_adjoint_electron_energy;
}

// Return the absolute maximum adjoint electron energy (MeV)
double SimulationAdjointElectronProperties::getAbsoluteMaxAdjointElectronEnergy()
{
  return s_absolute_max_adjoint_electron_energy;
}

// Set adjoint elastic mode to off (on by default)
void SimulationAdjointElectronProperties::setAdjointElasticModeOff()
{
  d_adjoint_elastic_mode_on = false;
}

// Set adjoint elastic mode to on (on by default)
void SimulationAdjointElectronProperties::setAdjointElasticModeOn()
{
  d_adjoint_elastic_mode_on = true;
}

// Return if adjoint elastic mode is on
bool SimulationAdjointElectronProperties::isAdjointElasticModeOn() const
{
  return d_adjoint_elastic_mode_on;
}

// Set adjoint electroionization mode to off (on by default)
void SimulationAdjointElectronProperties::setAdjointElectroionizationModeOff()
{
  d_adjoint_electroionization_mode_on = false;
}

// Set adjoint electroionization mode to on (on by default)
void SimulationAdjointElectronProperties::setAdjointElectroionizationModeOn()
{
  d_adjoint_electroionization_mode_on = true;
}

// Return if adjoint electroionization mode is on
bool SimulationAdjointElectronProperties::isAdjointElectroionizationModeOn() const
{
  return d_adjoint_electroionization_mode_on;
}

// Set adjoint bremsstrahlung mode to off (on by default)
void SimulationAdjointElectronProperties::setAdjointBremsstrahlungModeOff()
{
  d_adjoint_bremsstrahlung_mode_on = false;
}

// Set adjoint bremsstrahlung mode to on (on by default)
void SimulationAdjointElectronProperties::setAdjointBremsstrahlungModeOn()
{
  d_adjoint_bremsstrahlung_mode_on = true;
}

// Return if adjoint bremsstrahlung mode is on
bool SimulationAdjointElectronProperties::isAdjointBremsstrahlungModeOn() const
{
  return d_adjoint_bremsstrahlung_mode_on;
}

// Set adjoint atomic excitation mode to off (on by default)
void SimulationAdjointElectronProperties::setAdjointAtomicExcitationModeOff()
{
  d_adjoint_atomic_excitation_mode_on = false;
}

// Set adjoint atomic excitation mode to on (on by default)
void SimulationAdjointElectronProperties::setAdjointAtomicExcitationModeOn()
{
  d_adjoint_atomic_excitation_mode_on = true;
}

// Return if adjoint atomic excitation mode is on
bool SimulationAdjointElectronProperties::isAdjointAtomicExcitationModeOn() const
{
  return d_adjoint_atomic_excitation_mode_on;
}

// Set the adjoint electron FullyTabularTwoDDistribution evaluation tolerance (default = 1e-7)
/*! \details The evaluation tolerance is used by the
 *  InterpolatedFullyTabularTwoDDistribution as the tolerance when performing
 *  evaluations.
 */
void SimulationAdjointElectronProperties::setAdjointElectronEvaluationTolerance(
    const double tol )
{
  d_adjoint_evaluation_tol = tol;
}

// Return the adjoint electron FullyTabularTwoDDistribution evaluation tolerance (default = 1e-7)
/*! \details The evaluation tolerance is used by the
 *  InterpolatedFullyTabularTwoDDistribution as the tolerance when performing
 *  evaluations.
 */
double SimulationAdjointElectronProperties::getAdjointElectronEvaluationTolerance() const
{
  return d_adjoint_evaluation_tol;
}

// Set adjoint correlated sampling mode to off (on by default)
void SimulationAdjointElectronProperties::setAdjointCorrelatedSamplingModeOff()
{
  d_adjoint_correlated_sampling_mode_on = false;
}

// Set adjoint correlated sampling mode to on (on by default)
void SimulationAdjointElectronProperties::setAdjointCorrelatedSamplingModeOn()
{
  d_adjoint_correlated_sampling_mode_on = true;
}

// Return if adjoint correlated sampling mode is on
bool SimulationAdjointElectronProperties::isAdjointCorrelatedSamplingModeOn() const
{
  return d_adjoint_correlated_sampling_mode_on;
}

// Set adjoint unit based interpolation mode to off (on by default)
void SimulationAdjointElectronProperties::setAdjointUnitBasedInterpolationModeOff()
{
  d_adjoint_unit_based_interpolation_mode_on = false;
}

// Set adjoint unit based interpolation mode to on (on by default)
void SimulationAdjointElectronProperties::setAdjointUnitBasedInterpolationModeOn()
{
  d_adjoint_unit_based_interpolation_mode_on = true;
}

// Return if adjoint unit based interpolation mode is on
bool SimulationAdjointElectronProperties::isAdjointUnitBasedInterpolationModeOn() const
{
  return d_adjoint_unit_based_interpolation_mode_on;
}

// Set the adjoint bremsstrahlung photon angular distribution function (2BS by default)
void SimulationAdjointElectronProperties::setAdjointBremsstrahlungAngularDistributionFunction(
                          const BremsstrahlungAngularDistributionType function )
{
  d_adjoint_bremsstrahlung_angular_distribution_function = function;
}

// Return the adjoint bremsstrahlung photon angular distribution function (2BS by default)
BremsstrahlungAngularDistributionType
SimulationAdjointElectronProperties::getAdjointBremsstrahlungAngularDistributionFunction() const
{
  return d_adjoint_bremsstrahlung_angular_distribution_function;
}

// Set the adjoint elastic cutoff angle cosine (mu = 1.0 by default)
void SimulationAdjointElectronProperties::setAdjointElasticCutoffAngleCosine(
                          const double cutoff_angle_cosine )
{
  d_adjoint_elastic_cutoff_angle_cosine = cutoff_angle_cosine;
}

// Return the adjoint elastic cutoff angle cosine
double SimulationAdjointElectronProperties::getAdjointElasticCutoffAngleCosine() const
{
  return d_adjoint_elastic_cutoff_angle_cosine;
}

// Set the number of adjoint electron hash grid bins
void SimulationAdjointElectronProperties::setNumberOfAdjointElectronHashGridBins(
                                                          const unsigned bins )
{
  // Make sure the number of bins is valid
  testPrecondition( bins >= 1 );

  d_num_adjoint_electron_hash_grid_bins = bins;
}

// Get the number of adjoint electron hash grid bins
unsigned SimulationAdjointElectronProperties::getNumberOfAdjointElectronHashGridBins() const
{
  return d_num_adjoint_electron_hash_grid_bins;
}


} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationAdjointElectronProperties.cpp
//---------------------------------------------------------------------------//
