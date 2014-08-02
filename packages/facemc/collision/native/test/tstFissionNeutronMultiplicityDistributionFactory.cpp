//---------------------------------------------------------------------------//
//!
//! \file   tstFissionNeutronMultiplicityDistributionFactory.cpp
//! \author Alex Robinson
//! \brief  Fission neutron multiplicity distribution factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Facemc_FissionNeutronMultiplicityDistributionFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestFissionNeutronMultiplicityDistributionFactory : public Facemc::FissionNeutronMultiplicityDistributionFactory
{
public:
  TestFissionNeutronMultiplicityDistributionFactory(
			    const std::string& table_name,
			    const Teuchos::ArrayView<const double>& nu_block,
			    const Teuchos::ArrayView<const double>& dnu_block )
    : FissionNeutronMultiplicityDistributionFactory( table_name,
						     nu_block,
						     dnu_block )
  { /* ... */ }

  ~TestFissionNeutronMultiplicityDistributionFactory()
  { /* ... */ }

  using Facemc::FissionNeutronMultiplicityDistributionFactory::doesPromptDistExist;
  using Facemc::FissionNeutronMultiplicityDistributionFactory::doesDelayedDistExist;
  using Facemc::FissionNeutronMultiplicityDistributionFactory::doesTotalDistExist;
  using Facemc::FissionNeutronMultiplicityDistributionFactory::getPromptMultDist;
  using Facemc::FissionNeutronMultiplicityDistributionFactory::getDelayedMultDist;
  using Facemc::FissionNeutronMultiplicityDistributionFactory::getTotalMultDist;
};

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::string test_u238_ace_file_name;
std::string test_u238_ace_table_name;

Teuchos::RCP<Data::ACEFileHandler> ace_file_handler;
Teuchos::RCP<Data::XSSNeutronDataExtractor> xss_data_extractor;
Teuchos::RCP<TestFissionNeutronMultiplicityDistributionFactory> 
multiplicity_dist_factory;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the prompt distribution can be found
TEUCHOS_UNIT_TEST( FissionNeutronMultiplicityDistributionFactory,
		   doesPromptDistExist )
{
  TEST_ASSERT( multiplicity_dist_factory->doesPromptDistExist() );
}

//---------------------------------------------------------------------------//
// Check that the delayed distribution can be found
TEUCHOS_UNIT_TEST( FissionNeutronMultiplicityDistributionFactory,
		   doesDelayedDistExist )
{
  TEST_ASSERT( multiplicity_dist_factory->doesDelayedDistExist() );
}

//---------------------------------------------------------------------------//
// Check that the total distribution can be found
TEUCHOS_UNIT_TEST( FissionNeutronMultiplicityDistributionFactory,
		   doesTotalDistExist )
{
  TEST_ASSERT( multiplicity_dist_factory->doesTotalDistExist() );
}

//---------------------------------------------------------------------------//
// Check that the prompt distribution is valid
TEUCHOS_UNIT_TEST( FissionNeutronMultiplicityDistributionFactory,
		   getPromptMultDist )
{
  const Teuchos::RCP<Utility::OneDDistribution>& prompt_dist = 
    multiplicity_dist_factory->getPromptMultDist();

  TEST_ASSERT( !prompt_dist.is_null() );
  TEST_EQUALITY_CONST( prompt_dist->getDistributionType(),
		       Utility::TABULAR_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the delayed distribution is valid
TEUCHOS_UNIT_TEST( FissionNeutronMultiplicityDistributionFactory,
		   getDelayedMultDist )
{
  const Teuchos::RCP<Utility::OneDDistribution>& delayed_dist = 
    multiplicity_dist_factory->getPromptMultDist();

  TEST_ASSERT( !delayed_dist.is_null() );
  TEST_EQUALITY_CONST( delayed_dist->getDistributionType(),
		       Utility::TABULAR_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the total distribution is valid
TEUCHOS_UNIT_TEST( FissionNeutronMultiplicityDistributionFactory,
		   getTotalMultDist )
{
  const Teuchos::RCP<Utility::OneDDistribution>& total_dist = 
    multiplicity_dist_factory->getTotalMultDist();

  TEST_ASSERT( !total_dist.is_null() );
  TEST_EQUALITY_CONST( total_dist->getDistributionType(),
		       Utility::TABULAR_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the FissionNeutronMultiplicityDistribution can be created
TEUCHOS_UNIT_TEST( FissionNeutronMultiplicityDistributionFactory,
		   createDistribution )
{
  Teuchos::RCP<Facemc::FissionNeutronMultiplicityDistribution> distribution;

  multiplicity_dist_factory->createDistribution( distribution );

  TEST_ASSERT( !distribution.is_null() );
  TEST_ASSERT( distribution->getAverageNumberOfEmittedNeutrons( 1.0 ) > 0.0 );
  TEST_ASSERT( distribution->getAverageNumberOfEmittedNeutrons( 1.0 ) < 4.0 );
  TEST_ASSERT( distribution->getAverageNumberOfPromptNeutrons( 1.0 ) > 0.0 );
  TEST_ASSERT( distribution->getAverageNumberOfPromptNeutrons( 1.0 ) < 4.0 );
  TEST_ASSERT( distribution->getAverageNumberOfDelayedNeutrons( 1.0 ) > 0.0 );
  TEST_ASSERT( distribution->getAverageNumberOfDelayedNeutrons( 1.0 ) < 1.0 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_u238_ace_file",
		 &test_u238_ace_file_name,
		 "Test U238 ACE file name" );
  clp.setOption( "test_u238_ace_table",
		 &test_u238_ace_table_name,
		 "Test U238 ACE table name in basic ACE file" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize ace file handler, data extractor and multiplicity factory
  ace_file_handler.reset( new Data::ACEFileHandler( test_u238_ace_file_name,
						    test_u238_ace_table_name,
						    1u ) );

  xss_data_extractor.reset( 
   new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  multiplicity_dist_factory.reset(
		    new TestFissionNeutronMultiplicityDistributionFactory( 
				     ace_file_handler->getTableName(),
				     xss_data_extractor->extractNUBlock(),
				     xss_data_extractor->extractDNUBlock() ) );

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
// end tstFissionNeutronMultiplicityDistributionFactory.cpp
//---------------------------------------------------------------------------//
