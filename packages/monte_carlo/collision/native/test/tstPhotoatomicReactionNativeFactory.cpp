//---------------------------------------------------------------------------//
//!
//! \file   tstPhotoatomicReactionNativeFactory.cpp
//! \author Alex Robinson
//! \brief  Photoatomic reaction factory using native data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReactionNativeFactory.hpp"
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::ElectronPhotonRelaxationDataContainer> data_container;
Teuchos::ArrayRCP<double> energy_grid;
Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher;
Teuchos::RCP<MonteCarlo::PhotoatomicReaction> reaction;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a total incoherent reaction without Doppler data can be created
TEUCHOS_UNIT_TEST( PhotoatomicReactionNativeFactory,
		   createTotalIncoherentReaction_no_doppler )
{
  MonteCarlo::PhotoatomicReactionNativeFactory::createTotalIncoherentReaction(
							       *data_container,
							       energy_grid,
							       grid_searcher,
							       reaction,
							       false );

  // Test the reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
		       MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(),
		       1e-3 );

  // Test that the stored cross section is correct
  double cross_section = reaction->getCrossSection( 0.001 );

  TEST_FLOATING_EQUALITY( cross_section, 1.23509999999967790e+00, 1e-15 );
  
  cross_section = reaction->getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 2.47834228852720528e+00, 1e-15 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that a total incoherent reaction with Doppler data can be created
TEUCHOS_UNIT_TEST( PhotoatomicReactionNativeFactory,
		   createTotalIncoherentReaction_doppler )
{
  MonteCarlo::PhotoatomicReactionNativeFactory::createTotalIncoherentReaction(
							       *data_container,
							       energy_grid,
							       grid_searcher,
							       reaction,
							       true );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
		       MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(),
		       0.001 );

  // Test that the stored cross section is correct
  double cross_section = reaction->getCrossSection( 0.001 );

  TEST_FLOATING_EQUALITY( cross_section, 1.23509999999967790e+00, 1e-15 );
  
  cross_section = reaction->getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 2.47834228852720528e+00, 1e-15 );

  // Test that Doppler broadening is done
  MonteCarlo::SubshellType shell_of_interaction;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  
  MonteCarlo::ParticleBank bank;

  // Set up the random number stream
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 0.5; // accept x in scattering function rejection loop
  fake_stream[3] = 0.08; // select L3 shell for collision
  fake_stream[4] = 0.5; // select pz = 0.0
  fake_stream[5] = 0.0; // azimuthal_angle = 0.0
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  reaction->react( photon, bank, shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top()->getParticleType(), MonteCarlo::ELECTRON );
  TEST_FLOATING_EQUALITY( bank.top()->getEnergy(), 
  			  19.50173181484825,
  			  1e-15 );
  TEST_FLOATING_EQUALITY( bank.top()->getZDirection(), 
  			  0.9996898054103247, 
  			  1e-15 );
  TEST_FLOATING_EQUALITY( bank.top()->getYDirection(), 
  			  0.024905681252821114, 
  			  1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top()->getXDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getYDirection(), -1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getXDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::L3_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the subshell incoherent reactions w/o Doppler data can be created
TEUCHOS_UNIT_TEST( PhotoatomicReactionNativeFactory,
		   createSubshellIncoherentReactions_no_doppler )
{
  Teuchos::Array<Teuchos::RCP<MonteCarlo::PhotoatomicReaction> > reactions;

  MonteCarlo::PhotoatomicReactionNativeFactory::createSubshellIncoherentReactions(
							       *data_container,
							       energy_grid,
							       grid_searcher,
							       reactions,
							       false );

  TEST_EQUALITY_CONST( reactions.size(), 24 );

  // Test the first shell's reaction properties
  TEST_EQUALITY_CONST(reactions.front()->getReactionType(),
		      MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.front()->getThresholdEnergy(),
		       8.82900086220703151e-02 );

  double cross_section = reactions.front()->getCrossSection( 
						     8.82900086220703151e-02 );
  
  TEST_FLOATING_EQUALITY( cross_section, 5.25553220583787745e-09, 1e-15 );
  
  cross_section = reactions.front()->getCrossSection( 20.0 );
  
  TEST_FLOATING_EQUALITY( cross_section, 6.03100615156834802e-02, 1e-15 );
						     
  // Check the last shell's reaction properties
  TEST_EQUALITY_CONST(reactions.back()->getReactionType(),
		      MonteCarlo::P3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION);
  TEST_EQUALITY_CONST( reactions.back()->getThresholdEnergy(),
		       1e-3 );

  cross_section = reactions.back()->getCrossSection( 1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 1.98041761897415292e-01, 1e-15 );

  cross_section = reactions.back()->getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 4.02322890775264064e-02, 1e-15 );  
}

//---------------------------------------------------------------------------//
// Check that the subshell incoherent reactions w/Doppler data can be created
TEUCHOS_UNIT_TEST( PhotoatomicReactionNativeFactory,
		   createSubshellIncoherentReactions_doppler )
{
  Teuchos::Array<Teuchos::RCP<MonteCarlo::PhotoatomicReaction> > reactions;

  MonteCarlo::PhotoatomicReactionNativeFactory::createSubshellIncoherentReactions(
							       *data_container,
							       energy_grid,
							       grid_searcher,
							       reactions,
							       true );

  TEST_EQUALITY_CONST( reactions.size(), 24 );

  // Test the first shell's reaction properties
  TEST_EQUALITY_CONST(reactions.front()->getReactionType(),
		      MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.front()->getThresholdEnergy(),
		       8.82900086220703151e-02 );

  double cross_section = reactions.front()->getCrossSection( 
						     8.82900086220703151e-02 );
  
  TEST_FLOATING_EQUALITY( cross_section, 5.25553220583787745e-09, 1e-15 );
  
  cross_section = reactions.front()->getCrossSection( 20.0 );
  
  TEST_FLOATING_EQUALITY( cross_section, 6.03100615156834802e-02, 1e-15 );

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  
  MonteCarlo::ParticleBank bank;

  MonteCarlo::SubshellType shell_of_interaction;
  
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 1.0-1e-15; // accept x in occupation number rejection loop
  fake_stream[3] = 0.5; // select pz = 0.0
  fake_stream[4] = 0.0; // azimuthal_angle = 0.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  reactions.front()->react( photon, bank, shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top()->getParticleType(), MonteCarlo::ELECTRON );
  TEST_FLOATING_EQUALITY( bank.top()->getEnergy(), 
			  19.50173181484825,
			  1e-15 );
  TEST_FLOATING_EQUALITY( bank.top()->getZDirection(), 
			  0.9996898054103247, 
			  1e-15 );
  TEST_FLOATING_EQUALITY( bank.top()->getYDirection(), 
			  0.024905681252821114, 
			  1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top()->getXDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getYDirection(), -1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getXDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::K_SUBSHELL );
						     
  // Check the last shell's reaction properties
  TEST_EQUALITY_CONST(reactions.back()->getReactionType(),
		      MonteCarlo::P3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION);
  TEST_EQUALITY_CONST( reactions.back()->getThresholdEnergy(),
		       1e-3 );

  cross_section = reactions.back()->getCrossSection( 1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 1.98041761897415292e-01, 1e-15 );

  cross_section = reactions.back()->getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 4.02322890775264064e-02, 1e-15 );

  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  bank.pop();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  reactions.back()->react( photon, bank, shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top()->getParticleType(), MonteCarlo::ELECTRON );
  TEST_FLOATING_EQUALITY( bank.top()->getEnergy(), 
			  19.50173181484825,
			  1e-15 );
  TEST_FLOATING_EQUALITY( bank.top()->getZDirection(), 
			  0.9996898054103247, 
			  1e-15 );
  TEST_FLOATING_EQUALITY( bank.top()->getYDirection(), 
			  0.024905681252821114, 
			  1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top()->getXDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getYDirection(), -1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getXDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::P3_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that a coherent reaction can be created
TEUCHOS_UNIT_TEST( PhotoatomicReactionNativeFactory,
		   createCoherentReaction )
{
  MonteCarlo::PhotoatomicReactionNativeFactory::createCoherentReaction(
							       *data_container,
							       energy_grid,
							       grid_searcher,
							       reaction );

  // Test the reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
		       MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(),
		       1e-3 );

  // Test that the stored cross section is valid
  double cross_section = reaction->getCrossSection( 0.001 );

  TEST_FLOATING_EQUALITY( cross_section, 2.26802744627581296e+03, 1e-3 );

  cross_section = reaction->getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 2.33286215895818971e-03, 1e-3 );
}

//---------------------------------------------------------------------------//
// Check that a pair production reaction can be created
TEUCHOS_UNIT_TEST( PhotoatomicReactionNativeFactory,
		   createPairProductionReaction )
{
  MonteCarlo::PhotoatomicReactionNativeFactory::createPairProductionReaction(
							       *data_container,
							       energy_grid,
							       grid_searcher,
							       reaction,
							       false );

  // Test the reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
		       MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(),
		       1.02673329640432032e+00 );

  // Test that the stored cross section is correct
  double cross_section = reaction->getCrossSection( 0.001 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = reaction->getCrossSection( 1.02673329640432032e+00 );

  TEST_FLOATING_EQUALITY( cross_section, 2.09098184021483652e-06, 1e-15 );

  cross_section = reaction->getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 1.87762999999973985e+01, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a total photoelectric reaction can be created
TEUCHOS_UNIT_TEST( PhotoatomicReactionNativeFactory,
		   createTotalPhotoelectricReaction )
{
  MonteCarlo::PhotoatomicReactionNativeFactory::createTotalPhotoelectricReaction(
							       *data_container,
							       energy_grid,
							       grid_searcher,
							       reaction );

  // Test the reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
		       MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(),
		       1e-3 );

  // Test that the stored cross section is correct
  double cross_section = reaction->getCrossSection( 0.001 );

  TEST_FLOATING_EQUALITY( cross_section, 1.78857306272290740e+06, 1e-15 );

  cross_section = reaction->getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 8.03368055321776603e-02, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the subshell photoelectric reactions can be created
TEUCHOS_UNIT_TEST( PhotoatomicReactionNativeFactory,
		   createSubshellPhotoelectricReactions )
{
  Teuchos::Array<Teuchos::RCP<MonteCarlo::PhotoatomicReaction> > reactions;

  MonteCarlo::PhotoatomicReactionNativeFactory::createSubshellPhotoelectricReactions(
							       *data_container,
							       energy_grid,
							       grid_searcher,
							       reactions );

  TEST_EQUALITY_CONST( reactions.size(), 24 );

  // Test the first shell's reaction properties
  TEST_EQUALITY_CONST( 
		   reactions.front()->getReactionType(),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.front()->getThresholdEnergy(),
		       8.82900099999595622e-02 );

  double cross_section = reactions.front()->getCrossSection(
						     8.82900099999595622e-02 );

  TEST_FLOATING_EQUALITY( cross_section, 1.95582145812230942e+03, 1e-15 );
		      
  cross_section = reactions.front()->getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 6.61425467896072372e-02, 1e-15 );

  // Test the last shell's reaction properties
  TEST_EQUALITY_CONST( 
		  reactions.back()->getReactionType(),
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.back()->getThresholdEnergy(),
		       1e-3 );

  cross_section = reactions.back()->getCrossSection( 1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 7.38175550850533909e+02, 1e-24 );
  
  cross_section = reactions.back()->getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 3.03007633456089762e-07, 1e-15 );  
}

//---------------------------------------------------------------------------//
// Check that the heating photoatomic reaction can be created
TEUCHOS_UNIT_TEST( PhotoatomicReactionNativeFactory,
		   createHeatingReaction )
{
  MonteCarlo::PhotoatomicReactionNativeFactory::createHeatingReaction(
							       *data_container,
							       energy_grid,
							       grid_searcher,
							       reaction );
  
  // Test the reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
		       MonteCarlo::HEATING_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(),
		       1e-3 );

  // Test that the stored cross section is correct
  double cross_section = reaction->getCrossSection( 0.001 );

  TEST_FLOATING_EQUALITY( cross_section, 9.98732853633727512e-04, 1e-15 );

  cross_section = reaction->getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 1.84633231171998133e+01, 1e-15 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_native_file_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_native_file",
		 &test_native_file_name,
		 "Test Native file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) 
  {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  {
    // Create the native data file container
    data_container.reset( new Data::ElectronPhotonRelaxationDataContainer( 
						     test_native_file_name ) );

    // Extract the common energy grid
    energy_grid.assign( data_container->getPhotonEnergyGrid().begin(),
			data_container->getPhotonEnergyGrid().end() );

    // Create the hash-based grid searcher
    grid_searcher.reset( new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,true>( 
					     energy_grid,
					     energy_grid[0],
					     energy_grid[energy_grid.size()-1],
					     100 ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstPhotoatomicReactionNativeFactory.cpp
//---------------------------------------------------------------------------//
