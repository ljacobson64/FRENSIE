//---------------------------------------------------------------------------//
//!
//! \file   tstLoggingMacros.cpp
//! \author Alex Robinson
//! \brief  Logging macros unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_FancyOStream.hpp>

// FRENSIE Includes
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "FRENSIE_config.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an error can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_error )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the error log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );
  
  FRENSIE_SETUP_ERROR_LOG( os_ptr );
  FRENSIE_SETUP_ERROR_LOG( std::cout );

  // Log an error
  std::cout << std::endl;
  FRENSIE_LOG_ERROR( "testing" );
  
  // Check that the error was logged
  TEST_ASSERT( os_ptr->str().find( "Error:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a tagged error can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_tagged_error )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the error log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );
  
  FRENSIE_SETUP_ERROR_LOG( os_ptr );
  FRENSIE_SETUP_ERROR_LOG( std::cout );

  // Log an error
  std::cout << std::endl;
  FRENSIE_LOG_TAGGED_ERROR( "Tag", "testing" );
  
  // Check that the error was logged
  TEST_ASSERT( os_ptr->str().find( "Tag Error:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a scope error can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_scope_error )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the error log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  std::vector<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );
  
  FRENSIE_SETUP_ERROR_LOG( os_array );

  // Log an error
  std::cout << std::endl;
  FRENSIE_LOG_SCOPE_ERROR( "TestScope", "testing" );
  
  // Check that the error was logged
  TEST_ASSERT( os_ptr->str().find( "Error:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "TestScope" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a tagged scope error can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_tagged_scope_error )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the error log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  Teuchos::Array<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );
  
  FRENSIE_SETUP_ERROR_LOG( os_array );

  // Log an error
  std::cout << std::endl;
  FRENSIE_LOG_TAGGED_SCOPE_ERROR( "TestScope", "Tag", "testing" );

  // Check that the error was logged
  TEST_ASSERT( os_ptr->str().find( "Tag Error:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "TestScope" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that an error can be logged with the provided logger
TEUCHOS_UNIT_TEST( LoggingMacros, log_error_with_logger )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the error log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );
  
  FRENSIE_SETUP_ERROR_LOG( os_ptr );
  FRENSIE_SETUP_ERROR_LOG( std::cout );

  // Create a custom logger
  Utility::LoggingHelper::StandardLoggerType custom_logger;

  // Add a tag to the custom logger
  FRENSIE_ADD_TAG_TO_LOGGER( "Custom Logger", custom_logger );

  // Log an error
  std::cout << std::endl;
  FRENSIE_LOG_ERROR_WITH_LOGGER( custom_logger, "testing" );
  
  // Check that the error was logged
  TEST_ASSERT( os_ptr->str().find( "Custom Logger Error:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a scope error can be logged with the provided logger
TEUCHOS_UNIT_TEST( LoggingMacros, log_scope_error_with_logger )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the error log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );
  
  FRENSIE_SETUP_ERROR_LOG( os_ptr );
  FRENSIE_SETUP_ERROR_LOG( std::cout );

  // Create a custom logger
  Utility::LoggingHelper::StandardLoggerType custom_logger;

  // Add a tag to the custom logger
  FRENSIE_ADD_TAG_TO_LOGGER( "Custom Logger", custom_logger );

  // Log an error
  std::cout << std::endl;
  FRENSIE_LOG_SCOPE_ERROR_WITH_LOGGER( custom_logger, "TestScope", "testing" );
  
  // Check that the error was logged
  TEST_ASSERT( os_ptr->str().find( "Custom Logger Error:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "TestScope" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that an error with the __NESTED__ tag can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_nested_error )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the warning log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_ERROR_LOG( os_ptr );
  FRENSIE_SETUP_ERROR_LOG( std::cout );

  // Log a nested error
  std::cout << std::endl;
  FRENSIE_LOG_NESTED_ERROR( "Error: testing\n  Location: dummy.hpp:111" );

  // Check that the nested error was logged
  TEST_ASSERT( os_ptr->str().find( "Beginning nested errors..." ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "Error: testing" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "dummy.hpp:111" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a warning can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_warning )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the warning log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_WARNING_LOG( os_ptr );
  FRENSIE_SETUP_WARNING_LOG( std::cout );

  // Log a warning
  std::cout << std::endl;
  FRENSIE_LOG_WARNING( "testing" );

  // Check that the warning was logged
  TEST_ASSERT( os_ptr->str().find( "Warning:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a tagged warning can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_tagged_warning )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the warning log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  std::vector<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );

  FRENSIE_SETUP_WARNING_LOG( os_array );

  // Log a warning
  std::cout << std::endl;
  FRENSIE_LOG_TAGGED_WARNING( "Tag", "testing" );

  // Check that the warning was logged
  TEST_ASSERT( os_ptr->str().find( "Tag Warning:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a warning can be logged with the provided logger
TEUCHOS_UNIT_TEST( LoggingMacros, log_warning_with_logger )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the warning log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  Teuchos::Array<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );

  FRENSIE_SETUP_WARNING_LOG( os_array );

  // Create a custom logger
  Utility::LoggingHelper::StandardLoggerType custom_logger;

  // Add a tag to the custom logger
  FRENSIE_ADD_TAG_TO_LOGGER( "Custom Logger", custom_logger );

  // Log a warning
  std::cout << std::endl;
  FRENSIE_LOG_WARNING_WITH_LOGGER( custom_logger, "testing" );

  // Check that the warning was logged
  TEST_ASSERT( os_ptr->str().find( "Custom Logger Warning:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a notification can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_notification )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_NOTIFICATION_LOG( os_ptr );
  FRENSIE_SETUP_NOTIFICATION_LOG( std::cout );

  // Log a notification
  std::cout << std::endl;
  FRENSIE_LOG_NOTIFICATION( "testing" );

  // Check that the notification was logged
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a tagged notification can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_tagged_notification )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  std::vector<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );

  FRENSIE_SETUP_NOTIFICATION_LOG( os_array );

  // Log a notification
  std::cout << std::endl;
  FRENSIE_LOG_TAGGED_NOTIFICATION( "Tag", "testing" );

  // Check that the notification was logged
  TEST_ASSERT( os_ptr->str().find( "Tag: testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a notification can be logged with the provided logger
TEUCHOS_UNIT_TEST( LoggingMacros, log_notification_with_logger )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  Teuchos::Array<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );

  FRENSIE_SETUP_NOTIFICATION_LOG( os_array );

  // Create a custom logger
  Utility::LoggingHelper::StandardLoggerType custom_logger;

  // Add a tag to the custom logger
  FRENSIE_ADD_TAG_TO_LOGGER( "Custom Logger", custom_logger );

  // Log a notification
  std::cout << std::endl;
  FRENSIE_LOG_NOTIFICATION_WITH_LOGGER( custom_logger, "testing" );

  // Check that the notification was logged
  TEST_ASSERT( os_ptr->str().find( "Custom Logger: testing" ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Check that a detail can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_detail )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_NOTIFICATION_LOG( os_ptr );
  FRENSIE_SETUP_NOTIFICATION_LOG( std::cout );

  // Log a detail
  std::cout << std::endl;
  FRENSIE_LOG_DETAILS( "testing detail" );

  // Check that the detail was logged
#if HAVE_FRENSIE_DETAILED_LOGGING
  TEST_ASSERT( os_ptr->str().find( "testing detail" ) < os_ptr->str().size() );
#else
  TEST_ASSERT( os_ptr->str().size() == 0 );
#endif 
}

//---------------------------------------------------------------------------//
// Check that a tagged detail can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_tagged_detail )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  std::vector<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );

  FRENSIE_SETUP_NOTIFICATION_LOG( os_array );

  // Log a detail
  std::cout << std::endl;
  FRENSIE_LOG_TAGGED_DETAILS( "Tag", "testing detail" );

  // Check that the detail was logged
#if HAVE_FRENSIE_DETAILED_LOGGING
  TEST_ASSERT( os_ptr->str().find( "Tag: testing detail" ) < os_ptr->str().size() );
#else
  TEST_ASSERT( os_ptr->str().size() == 0 );
#endif 
}

//---------------------------------------------------------------------------//
// Check that a detail can be logged with the provided logger
TEUCHOS_UNIT_TEST( LoggingMacros, log_detail_with_logger )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  Teuchos::Array<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );

  FRENSIE_SETUP_NOTIFICATION_LOG( os_array );

  // Create a custom logger
  Utility::LoggingHelper::StandardLoggerType custom_logger;

  // Add a tag to the custom logger
  FRENSIE_ADD_TAG_TO_LOGGER( "Custom Logger", custom_logger );

  // Log a detail
  std::cout << std::endl;
  FRENSIE_LOG_DETAILS_WITH_LOGGER( custom_logger, "testing detail" );

  // Check that the detail was logged
#if HAVE_FRENSIE_DETAILED_LOGGING
  TEST_ASSERT( os_ptr->str().find( "Custom Logger: testing detail" ) < os_ptr->str().size() );
#else
  TEST_ASSERT( os_ptr->str().size() == 0 );
#endif 
}

//---------------------------------------------------------------------------//
// Check that a pedantic detail can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_pedantic_detail )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_NOTIFICATION_LOG( os_ptr );
  FRENSIE_SETUP_NOTIFICATION_LOG( std::cout );

  // Log a detail
  std::cout << std::endl;
  FRENSIE_LOG_PEDANTIC_DETAILS( "testing extra detail" );

  // Check that the detail was logged
#if HAVE_FRENSIE_DETAILED_LOGGING
  TEST_ASSERT( os_ptr->str().find( "testing extra detail" ) <
               os_ptr->str().size() );
#else
  TEST_ASSERT( os_ptr->str().size() == 0 );
#endif 
}

//---------------------------------------------------------------------------//
// Check that a tagged pedantic detail can be logged
TEUCHOS_UNIT_TEST( LoggingMacros, log_tagged_pedantic_detail )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the notification log
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  std::vector<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );

  FRENSIE_SETUP_NOTIFICATION_LOG( os_array );

  // Log a detail
  std::cout << std::endl;
  FRENSIE_LOG_TAGGED_PEDANTIC_DETAILS( "Tag", "testing extra detail" );

  // Check that the detail was logged
#if HAVE_FRENSIE_DETAILED_LOGGING
  TEST_ASSERT( os_ptr->str().find( "Tag: testing extra detail" ) <
               os_ptr->str().size() );
#else
  TEST_ASSERT( os_ptr->str().size() == 0 );
#endif 
}

//---------------------------------------------------------------------------//
// Check that all of the logs can be set simultaneously
TEUCHOS_UNIT_TEST( LoggingMacros, setup_all_logs )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the logs
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  FRENSIE_SETUP_STANDARD_LOGS( os_ptr );
  FRENSIE_SETUP_STANDARD_LOGS( std::cout );

  // Log an error
  std::cout << std::endl;
  FRENSIE_LOG_ERROR( "testing" );

  TEST_ASSERT( os_ptr->str().find( "Error:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_ERROR( "Tag", "testing" );

  TEST_ASSERT( os_ptr->str().find( "Tag Error:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_SCOPE_ERROR( "TestScope", "testing" );

  TEST_ASSERT( os_ptr->str().find( "Error:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "TestScope" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_SCOPE_ERROR( "TestScope", "Tag", "testing" );

  TEST_ASSERT( os_ptr->str().find( "Tag Error:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "TestScope" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_WARNING( "testing" );

  TEST_ASSERT( os_ptr->str().find( "Warning:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_WARNING( "Tag", "testing" );

  TEST_ASSERT( os_ptr->str().find( "Tag Warning:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_NOTIFICATION( "testing" );

  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_NOTIFICATION( "Tag", "testing" );

  TEST_ASSERT( os_ptr->str().find( "Tag:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_DETAILS( "testing details" );

#if HAVE_FRENSIE_DETAILED_LOGGING
  TEST_ASSERT( os_ptr->str().find( "testing details" ) < os_ptr->str().size() );
#else
  TEST_ASSERT( os_ptr.str().size() == 0 );
#endif

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_DETAILS( "Tag", "testing details" );

#if HAVE_FRENSIE_DETAILED_LOGGING
  TEST_ASSERT( os_ptr->str().find( "Tag:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing details" ) < os_ptr->str().size() );
#else
  TEST_ASSERT( os_ptr->str().size() == 0 );
#endif

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_PEDANTIC_DETAILS( "testing pedantic details" );

#if HAVE_FRENSIE_DETAILED_LOGGING 
  TEST_ASSERT( os_ptr->str().find( "testing pedantic details" ) < os_ptr->str().size() );
#else
  TEST_ASSERT( os_ptr->str().size() == 0 );
#endif

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_PEDANTIC_DETAILS( "Tag", "testing pedantic details" );

#if HAVE_FRENSIE_DETAILED_LOGGING
  TEST_ASSERT( os_ptr->str().find( "Tag:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing pedantic details" ) < os_ptr->str().size() );
#else
  TEST_ASSERT( os_ptr->str().size() == 0 );
#endif
  
  os_ptr->str( "" );
  os_ptr->clear();
}

//---------------------------------------------------------------------------//
// Check that a global filter can be set
TEUCHOS_UNIT_TEST( LoggingMacros, set_global_filter )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the logs
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  std::vector<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );

  FRENSIE_SETUP_STANDARD_LOGS( os_array );

  // Set the global log filter
  FRENSIE_SET_GLOBAL_LOG_FILTER( record_type_log_attr >= Utility::WARNING_RECORD || (boost::log::expressions::has_attr(tag_log_attr) && tag_log_attr == "Important") );

  // Log an error
  std::cout << std::endl;
  FRENSIE_LOG_ERROR( "testing" );

  TEST_ASSERT( os_ptr->str().find( "Error:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_ERROR( "Fatal", "testing" );

  TEST_ASSERT( os_ptr->str().find( "Fatal Error:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_SCOPE_ERROR( "TestScope", "testing" );

  TEST_ASSERT( os_ptr->str().find( "Error:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "TestScope" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_SCOPE_ERROR( "TestScope", "Fatal", "testing" );

  TEST_ASSERT( os_ptr->str().find( "Fatal Error:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "TestScope" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_WARNING( "testing" );

  TEST_ASSERT( os_ptr->str().find( "Warning:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_WARNING( "Critical", "testing" );

  TEST_ASSERT( os_ptr->str().find( "Critical Warning:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_NOTIFICATION( "testing" );

  TEST_ASSERT( os_ptr->str().size() == 0 );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_NOTIFICATION( "Important", "testing" );

  TEST_ASSERT( os_ptr->str().find( "Important:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing" ) < os_ptr->str().size() );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_DETAILS( "testing details" );

  TEST_ASSERT( os_ptr->str().size() == 0 );

  os_ptr->str( "" );
  os_ptr->clear();

  FRENSIE_LOG_TAGGED_DETAILS( "Useless", "testing details" );

  TEST_ASSERT( os_ptr->str().size() == 0 );

  os_ptr->str( "" );
  os_ptr->clear();

#if HAVE_FRENSIE_DETAILED_LOGGING
  FRENSIE_LOG_TAGGED_DETAILS( "Important", "testing details" );

  TEST_ASSERT( os_ptr->str().find( "Important:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing details" ) < os_ptr->str().size() );
#else
  TEST_ASSERT( os_ptr->str().size() == 0 )
#endif
    
  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_PEDANTIC_DETAILS( "testing pedantic details" );

  TEST_ASSERT( os_ptr->str().size() == 0 );

  os_ptr->str( "" );
  os_ptr->clear();

  FRENSIE_LOG_TAGGED_PEDANTIC_DETAILS( "Useless", "testing pedantic details" );

  TEST_ASSERT( os_ptr->str().size() == 0 );

  os_ptr->str( "" );
  os_ptr->clear();
  
  FRENSIE_LOG_TAGGED_PEDANTIC_DETAILS( "Important", "testing pedantic details" );

#if HAVE_FRENSIE_DETAILED_LOGGING  
  TEST_ASSERT( os_ptr->str().find( "Important:" ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "testing pedantic details" ) < os_ptr->str().size() );
#else
  TEST_ASSERT( os_ptr->str().size() == 0 );
#endif

  os_ptr->str( "" );
  os_ptr->clear();
}

//---------------------------------------------------------------------------//
// Check that the error logs can handle exception info
TEUCHOS_UNIT_TEST( LoggingMacros, exception_catch_error_logging )
{
  // Make sure that all sinks have been removed from the log
  FRENSIE_REMOVE_ALL_LOGS();

  // Setup the logs
  boost::shared_ptr<std::stringstream> os_ptr( new std::stringstream );

  Teuchos::Array<boost::shared_ptr<std::ostream> > os_array( 2 );
  os_array[0] = os_ptr;
  os_array[1].reset( &std::cout, boost::null_deleter() );

  FRENSIE_SETUP_STANDARD_LOGS( os_array );

  std::cout << std::endl;
  try{
    try{
      TEST_FOR_EXCEPTION( true, std::logic_error, "Error: testing 1" );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::logic_error,
                                std::runtime_error,
                                "Error: testing 2");
  }
  EXCEPTION_CATCH_AND_LOG( std::runtime_error, "testing 3" );

  TEST_ASSERT( os_ptr->str().find( "Caught Exception Error: testing 3" ) <
               os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "Exception Type: std::runtime_error" ) <
               os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "Beginning nested errors..." ) <
               os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "Error: testing 2" ) <
               os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "Exception Type: std::logic_error -> std::runtime_error" ) <
               os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "Error: testing 1" ) <
               os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "Throw test that evaluated to true: true" ) <
               os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "Exception Type: std::logic_error" ) <
               os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "Location: " ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "Stack: " ) < os_ptr->str().size() );
  TEST_ASSERT( os_ptr->str().find( "    **  " ) < os_ptr->str().size() );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::GlobalMPISession mpi_session( &argc, &argv );

  // Add the standard log attributes
  FRENSIE_ADD_STANDARD_LOG_ATTRIBUTES();

  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstLoggingMacros.cpp
//---------------------------------------------------------------------------//
