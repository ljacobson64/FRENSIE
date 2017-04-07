//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationAdjointElectronPropertiesFactory.cpp
//! \author Alex Robinson
//! \brief  Simulation adjoint electron properties factory class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_SimulationAdjointElectronPropertiesFactory.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize the simulation adjoint electron properties
void SimulationAdjointElectronPropertiesFactory::initializeProperties(
                  const Teuchos::ParameterList& properties,
                  SimulationAdjointElectronProperties& adjoint_electron_properties,
                  std::ostream* os_warn )
{
  // Get the min adjoint electron energy - optional
  if( properties.isParameter( "Min Adjoint Electron Energy" ) )
  {
    double min_energy = properties.get<double>( "Min Adjoint Electron Energy" );

    if( min_energy >= adjoint_electron_properties.getAbsoluteMinAdjointElectronEnergy() )
      adjoint_electron_properties.setMinAdjointElectronEnergy( min_energy );
    else
    {
      adjoint_electron_properties.setMinAdjointElectronEnergy(
               adjoint_electron_properties.getAbsoluteMinAdjointElectronEnergy() );

      *os_warn << "Warning: the lowest supported adjoint electron energy is "
               << adjoint_electron_properties.getAbsoluteMinAdjointElectronEnergy()
               << ". This value will be used instead of "
               << min_energy << "." << std::endl;
    }
  }

  // Get the max adjoint electron energy - optional
  if( properties.isParameter( "Max Adjoint Electron Energy" ) )
  {
    double max_energy = properties.get<double>( "Max Adjoint Electron Energy" );

    if( max_energy <= adjoint_electron_properties.getAbsoluteMaxAdjointElectronEnergy() )
      adjoint_electron_properties.setMaxAdjointElectronEnergy( max_energy );
    else
    {
      adjoint_electron_properties.setMaxAdjointElectronEnergy(
               adjoint_electron_properties.getAbsoluteMaxAdjointElectronEnergy() );

      *os_warn << "Warning: the highest supported adjoint electron energy is "
               << adjoint_electron_properties.getAbsoluteMaxAdjointElectronEnergy()
               << ". This value will be used instead of "
               << max_energy << "." << std::endl;
    }
  }

  // Get the adjoint elastic scattering reaction mode - optional
  if( properties.isParameter( "Adjoint Electron Elastic" ) )
  {
    if( !properties.get<bool>( "Adjoint Electron Elastic" ) )
      adjoint_electron_properties.setAdjointElasticModeOff();
  }

  // Get the adjoint electroionization scattering reaction mode - optional
  if( properties.isParameter( "Adjoint Electron Electroionization" ) )
  {
    if( !properties.get<bool>( "Adjoint Electron Electroionization" ) )
      adjoint_electron_properties.setAdjointElectroionizationModeOff();
  }

  // Get the adjoint bremsstrahlung reaction mode - optional
  if( properties.isParameter( "Adjoint Electron Bremsstrahlung" ) )
  {
    if( !properties.get<bool>( "Adjoint Electron Bremsstrahlung" ) )
      adjoint_electron_properties.setAdjointBremsstrahlungModeOff();
  }

  // Get the adjoint atomic excitation scattering reaction mode - optional
  if( properties.isParameter( "Adjoint Electron Atomic Excitation" ) )
  {
    if( !properties.get<bool>( "Adjoint Electron Atomic Excitation" ) )
      adjoint_electron_properties.setAdjointAtomicExcitationModeOff();
  }

  // Get the secondary adjoint electron evaluation tolerance - optional
  if( properties.isParameter( "Adjoint Electron Evaluation Tolerance" ) )
  {
    double evaluation_tol =
        properties.get<double>( "Adjoint Electron Evaluation Tolerance" );

    if( evaluation_tol > 0.0 && evaluation_tol < 1.0 )
    {
      adjoint_electron_properties.setAdjointElectronEvaluationTolerance(
                                                            evaluation_tol );
    }
    else
    {
      std::cerr << "Warning: the adjoint electron evaluation tolerance must "
                << "have a value between 0 and 1. The default value of "
                << adjoint_electron_properties.getAdjointElectronEvaluationTolerance()
                << " will be used instead of " << evaluation_tol << "."
                << std::endl;
    }
  }

  // Get the adjoint correlated sampling mode - optional
  if( properties.isParameter( "Adjoint Electron Correlated Sampling" ) )
  {
    if( !properties.get<bool>( "Adjoint Electron Correlated Sampling" ) )
      adjoint_electron_properties.setAdjointCorrelatedSamplingModeOff();
  }

  // Get the adjoint unit based interpolation mode - optional
  if( properties.isParameter( "Adjoint Electron Unit Based Interpolation" ) )
  {
    if( !properties.get<bool>( "Adjoint Electron Unit Based Interpolation" ) )
      adjoint_electron_properties.setAdjointUnitBasedInterpolationModeOff();
  }

  // Get the adjoint bremsstrahlung photon angular distribution function - optional
  if( properties.isParameter( "Adjoint Bremsstrahlung Angular Distribution" ) )
  {
    std::string raw_function =
      properties.get<std::string>( "Adjoint Bremsstrahlung Angular Distribution" );

     MonteCarlo::BremsstrahlungAngularDistributionType function;

    if( raw_function == "Dipole" || raw_function == "dipole" || raw_function == "DIPOLE" )
      function = MonteCarlo::DIPOLE_DISTRIBUTION;
    else if( raw_function == "2BS" || raw_function == "2bs" || raw_function == "twobs" )
      function = MonteCarlo::TWOBS_DISTRIBUTION;
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Error: adjoint bremsstrahlung angular distribution "
                       << raw_function <<
                       " is not currently supported!" );
    }

     adjoint_electron_properties.setAdjointBremsstrahlungAngularDistributionFunction(
                                                                    function );
  }

  // Get the adjoint elastic cutoff angle cosine - optional
  if( properties.isParameter( "Adjoint Elastic Cutoff Angle Cosine" ) )
  {
    double cutoff_angle_cosine =
      properties.get<double>( "Adjoint Elastic Cutoff Angle Cosine" );

    if( cutoff_angle_cosine >= -1.0 && cutoff_angle_cosine <= 1.0 )
    {
      adjoint_electron_properties.setAdjointElasticCutoffAngleCosine(
                                                        cutoff_angle_cosine );
    }
    else
    {
      std::cerr << "Warning: the adjoint elastic cutoff angle cosine must have "
                << "a value between -1 and 1. The default value of "
                << adjoint_electron_properties.getAdjointElasticCutoffAngleCosine()
                << " will be used instead of " << cutoff_angle_cosine << "."
                << std::endl;
    }
  }

  // Get the number of adjoint electron hash grid bins - optional
  if( properties.isParameter( "Adjoint Electron Hash Grid Bins" ) )
  {
    unsigned bins = properties.get<unsigned>( "Adjoint Electron Hash Grid Bins" );

    adjoint_electron_properties.setNumberOfAdjointElectronHashGridBins( bins );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationAdjointElectronPropertiesFactory.cpp
//---------------------------------------------------------------------------//
