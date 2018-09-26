//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectroatomicReactionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  Adjoint electroatomic reaction factory using Native data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

MonteCarlo::BremsstrahlungAngularDistributionType photon_distribution_function;
std::unique_ptr<Data::AdjointElectronPhotonRelaxationDataContainer> data_container;
std::shared_ptr<std::vector<double> > energy_grid( new std::vector<double> );
std::shared_ptr<Utility::HashBasedGridSearcher<double> > grid_searcher;
std::shared_ptr<const MonteCarlo::AdjointElectroatomicReaction> reaction;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an coupled elastic reaction can be created
FRENSIE_UNIT_TEST( AdjointElectroatomicReactionNativeFactory,
                   createCoupledElasticReaction )
{
  MonteCarlo::CoupledElasticSamplingMethod sampling_method =
    MonteCarlo::TWO_D_UNION;
  double evaluation_tol = 1e-7;

  MonteCarlo::AdjointElectroatomicReactionNativeFactory::createCoupledElasticReaction<Utility::LinLinLog,Utility::Correlated>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                sampling_method,
                evaluation_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.74896E+08, 1e-12 );

  energy = 1e-3;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.874725328661224805e+06, 1e-12 );

  energy = 20.0;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.3022122514987E+04, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an coupled elastic reaction can be created
FRENSIE_UNIT_TEST( AdjointElectroatomicReactionNativeFactory,
                   createDecoupledElasticReaction )
{
  double evaluation_tol = 1e-7;

  MonteCarlo::AdjointElectroatomicReactionNativeFactory::createDecoupledElasticReaction<Utility::LinLinLog,Utility::UnitBaseCorrelated>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                evaluation_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.74896E+08, 1e-12 );

  energy = 1e-3;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.874725328661224805e+06, 1e-12 );

  energy = 20.0;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.3022122514987E+04, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an cutoff elastic reaction can be created
FRENSIE_UNIT_TEST( AdjointElectroatomicReactionNativeFactory,
                   createCutoffElasticReaction )
{
  double cutoff_angle_cosine = 1.0;
  double evaluation_tol = 1e-7;

  MonteCarlo::AdjointElectroatomicReactionNativeFactory::createCutoffElasticReaction<Utility::LinLinLog,Utility::Correlated>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                cutoff_angle_cosine,
                evaluation_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section =
    reaction->getCrossSection( energy );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.74896E+08, 1e-12 );

  energy = 1e-3;
  cross_section = reaction->getCrossSection( energy );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.874725328661224805e+06, 1e-12 );

  energy = 20.0;
  cross_section = reaction->getCrossSection( energy );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.04727623729037E+02, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that a screened Rutherford elastic reaction can be created
FRENSIE_UNIT_TEST( AdjointElectroatomicReactionNativeFactory,
                   createScreenedRutherfordElasticReaction )
{
  MonteCarlo::AdjointElectroatomicReactionNativeFactory::createScreenedRutherfordElasticReaction(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
       MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 2.59024e-01 );

  // Test that the stored cross section is correct
  double energy = 1.0;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.492318970451783571e+03, 1e-12 );

  energy = 10.0;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.206070802327034289e+04, 1e-12 );

  energy = 20.0;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.2717394891258004e+04, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an moment preserving elastic reaction can be created
FRENSIE_UNIT_TEST( AdjointElectroatomicReactionNativeFactory,
                   createMomentPreservingElasticReaction )
{
  double cutoff_angle_cosine = 0.9;
  double evaluation_tol = 1e-15;

  MonteCarlo::AdjointElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction<Utility::LogLogCosLog,Utility::Correlated>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                cutoff_angle_cosine,
                evaluation_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
         MonteCarlo::MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section =
    reaction->getCrossSection( energy );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.2217606103336416e+07, 1e-12 );

  energy = 1e-3;
  cross_section = reaction->getCrossSection( energy );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.696297499655022053e+06, 1e-12 );

  energy = 20.0;
  cross_section = reaction->getCrossSection( energy );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.051440287719986433, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an atomic excitation reaction can be created
FRENSIE_UNIT_TEST( AdjointElectroatomicReactionNativeFactory,
                   createAtomicExcitationReaction )
{
  MonteCarlo::AdjointElectroatomicReactionNativeFactory::createAtomicExcitationReaction(
                               *data_container,
                               energy_grid,
                               grid_searcher,
                               reaction);

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                 MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( 1e-5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.1243057898416743e+07, 1e-12 );

  cross_section = reaction->getCrossSection( 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.071196592417021282e+07, 1e-12 );

  cross_section = reaction->getCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.1829299836129925e+04, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that the electroionization subshell reactions can be created
FRENSIE_UNIT_TEST( AdjointElectroatomicReactionNativeFactory,
                   createSubshellElectroelectricReactions )
{
  double evaluation_tol = 1e-7;

  std::vector<std::shared_ptr<const MonteCarlo::AdjointElectroatomicReaction> > reactions;

  MonteCarlo::AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<Utility::LogLogLog,Utility::UnitBaseCorrelated>(
        *data_container,
        energy_grid,
        grid_searcher,
        reactions,
        evaluation_tol );

  FRENSIE_CHECK_EQUAL( reactions.size(), 1 );

  // Test the first shell's reaction properties
  FRENSIE_CHECK_EQUAL( reactions.front()->getReactionType(),
      MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reactions.front()->getThresholdEnergy(),
                       1e-5 );

  // Test the first shell's stored cross section is correct
  double cross_section = reactions.front()->getCrossSection( 1e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.599858431241171265e+10, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.627599463243934512e+07, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.203546061164286948e+04, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a basic (dipole distribution) bremsstrahlung reaction can be created
FRENSIE_UNIT_TEST( AdjointElectroatomicReactionNativeFactory,
                   createBremsstrahlungReaction_dipole )
{
  double evaluation_tol = 1e-7;

  MonteCarlo::AdjointElectroatomicReactionNativeFactory::createBremsstrahlungReaction<Utility::LogLogLog,Utility::UnitBaseCorrelated>(
        *data_container,
        energy_grid,
        grid_searcher,
        reaction,
        evaluation_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                    MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double cross_section = reaction->getCrossSection( reaction->getThresholdEnergy() );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.980092756766359940e+01, 1e-12 );

  cross_section = reaction->getCrossSection( 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.441998445400516893e+01, 1e-12 );

  cross_section = reaction->getCrossSection( 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.497134894717789044e-01, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_file",
                                        test_native_file_name, "",
                                        "Test Native file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the native data file container
  data_container.reset( new Data::AdjointElectronPhotonRelaxationDataContainer(
                             test_native_file_name ) );

  // Extract the common energy grid
  energy_grid->assign( data_container->getAdjointElectronEnergyGrid().begin(),
                       data_container->getAdjointElectronEnergyGrid().end() );

  // Create the hash-based grid searcher
  grid_searcher.reset(
       new Utility::StandardHashBasedGridSearcher<std::vector<double>,false>(
                 energy_grid,
                 100 ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointElectroatomicReactionNativeFactory.cpp
//---------------------------------------------------------------------------//

