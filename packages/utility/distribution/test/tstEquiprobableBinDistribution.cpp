//---------------------------------------------------------------------------//
//!
//! \file   tstThirtyTwoEquiprobableBinDistribution.cpp
//! \author Alex Robinson
//! \brief  Thirty-two equiprobable bin distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_EquiprobableBinDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"

using boost::units::quantity;
using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::unique_ptr<Utility::PropertyTree> test_dists_ptree;

std::shared_ptr<Utility::OneDDistribution> distribution;
std::shared_ptr<Utility::TabularOneDDistribution> tab_distribution;

std::shared_ptr<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> >
  unit_aware_distribution;
std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<MegaElectronVolt,si::amount> >
  unit_aware_tab_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution, evaluate )
{
  TEST_EQUALITY_CONST( distribution->evaluate( -17.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -16.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -15.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -14.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -13.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -12.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -11.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -10.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -9.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -8.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -7.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -6.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -5.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -4.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -3.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -2.0 ), 1.0/48 );
  TEST_EQUALITY_CONST( distribution->evaluate( -0.5 ), 1.0/16 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 1.0/16 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.5 ), 1.0/48 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 4.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 5.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 6.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 7.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 8.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 9.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 10.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 11.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 12.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 13.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 14.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 15.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 16.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 17.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution, evaluate )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV ),
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV ),
		       2.5*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.1*MeV ),
		       0.25/0.9*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV ),
		       0.0625*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 5.0*MeV ),
		       0.05*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 10.0*MeV ),
		       0.05*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 11.0*MeV ),
		       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -17.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -16.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -15.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -14.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -13.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -12.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -11.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -10.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -9.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -8.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -7.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -6.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -5.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -4.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -3.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -2.0 ), 1.0/48 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -0.5 ), 1.0/16 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 1.0/16 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.5 ), 1.0/48 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 2.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 3.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 4.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 5.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 6.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 7.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 8.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 9.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 10.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 11.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 12.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 13.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 14.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 15.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 16.0 ), 1.0/32 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( -1.0*MeV ),
		       0.0/MeV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.0*MeV ),
		       2.5/MeV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.1*MeV ),
		       0.25/0.9/MeV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 1.0*MeV ),
		       0.0625/MeV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 5.0*MeV ),
		       0.05/MeV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 10.0*MeV ),
		       0.05/MeV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 11.0*MeV ),
		       0.0/MeV );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution, evaluateCDF )
{
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -17.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -16.0 ), 0.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -15.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -14.0 ), 2.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -13.0 ), 3.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -12.0 ), 4.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -11.0 ), 5.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -10.0 ), 6.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -9.0 ), 7.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -8.0 ), 8.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -7.0 ), 9.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -6.0 ), 10.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -5.0 ), 11.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -4.0 ), 12.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -3.0 ), 13.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -2.0 ), 14.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -0.5 ), 15.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -0.25 ), 31.0/64 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 0.0 ), 16.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 0.25 ), 33.0/64 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 0.5 ), 17.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 2.0 ), 18.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 3.0 ), 19.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 4.0 ), 20.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 5.0 ), 21.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 6.0 ), 22.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 7.0 ), 23.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 8.0 ), 24.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 9.0 ), 25.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 10.0 ), 26.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 11.0 ), 27.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 12.0 ), 28.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 13.0 ), 29.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 14.0 ), 30.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 15.0 ), 31.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 16.0 ), 32.0/32 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 17.0 ), 32.0/32 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware CDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution, evaluateCDF )
{
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( -1.0*MeV ),
		       0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 0.0*MeV ),
		       0.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 0.1*MeV ),
		       0.25 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 1.0*MeV ),
		       0.5 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 5.0*MeV ),
		       0.75 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 10.0*MeV ),
		       1.0 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 11.0*MeV ),
		       1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution, sample )
{
  std::vector<double> fake_stream( 65 );
  // First bin
  fake_stream[0] = 0.0;      fake_stream[1] = 1.0/64;
  // Second bin
  fake_stream[2] = 2.0/64;   fake_stream[3] = 3.0/64;
  // Third bin
  fake_stream[4] = 4.0/64;   fake_stream[5] = 5.0/64;
  // Fourth bin
  fake_stream[6] = 6.0/64;   fake_stream[7] = 7.0/64;
  // Fifth bin
  fake_stream[8] = 8.0/64;   fake_stream[9] = 9.0/64;
  // Sixth bin
  fake_stream[10] = 10.0/64; fake_stream[11] = 11.0/64;
  // Seventh bin
  fake_stream[12] = 12.0/64; fake_stream[13] = 13.0/64;
  // Eighth bin
  fake_stream[14] = 14.0/64; fake_stream[15] = 15.0/64;
  // Nineth bin
  fake_stream[16] = 16.0/64; fake_stream[17] = 17.0/64;
  // Tenth bin
  fake_stream[18] = 18.0/64; fake_stream[19] = 19.0/64;
  // Eleventh bin
  fake_stream[20] = 20.0/64; fake_stream[21] = 21.0/64;
  // Twelfth bin
  fake_stream[22] = 22.0/64; fake_stream[23] = 23.0/64;
  // Thirteenth bin
  fake_stream[24] = 24.0/64; fake_stream[25] = 25.0/64;
  // Fourteenth bin
  fake_stream[26] = 26.0/64; fake_stream[27] = 27.0/64;
  // Fifteenth bin
  fake_stream[28] = 28.0/64; fake_stream[29] = 29.0/64;
  // Sixteenth bin
  fake_stream[30] = 30.0/64; fake_stream[31] = 31.0/64;
  // Seventeenth bin
  fake_stream[32] = 32.0/64; fake_stream[33] = 33.0/64;
  // Eighteenth bin
  fake_stream[34] = 34.0/64; fake_stream[35] = 35.0/64;
  // Nineteenth bin
  fake_stream[36] = 36.0/64; fake_stream[37] = 37.0/64;
  // Twentieth bin
  fake_stream[38] = 38.0/64; fake_stream[39] = 39.0/64;
  // Twenty-first bin
  fake_stream[40] = 40.0/64; fake_stream[41] = 41.0/64;
  // Twenty-second bin
  fake_stream[42] = 42.0/64; fake_stream[43] = 43.0/64;
  // Twenty-third bin
  fake_stream[44] = 44.0/64; fake_stream[45] = 45.0/64;
  // Twenty-fourth bin
  fake_stream[46] = 46.0/64; fake_stream[47] = 47.0/64;
  // Twenty-fifth bin
  fake_stream[48] = 48.0/64; fake_stream[49] = 49.0/64;
  // Twenty-sixth bin
  fake_stream[50] = 50.0/64; fake_stream[51] = 51.0/64;
  // Twenty-seventh bin
  fake_stream[52] = 52.0/64; fake_stream[53] = 53.0/64;
  // Twenty-eighth bin
  fake_stream[54] = 54.0/64; fake_stream[55] = 55.0/64;
  // Twenty-nineth bin
  fake_stream[56] = 56.0/64; fake_stream[57] = 57.0/64;
  // Thirtieth bin
  fake_stream[58] = 58.0/64; fake_stream[59] = 59.0/64;
  // Thirty-first bin
  fake_stream[60] = 60.0/64; fake_stream[61] = 61.0/64;
  // Thirty-second bin
  fake_stream[62] = 62.0/64; fake_stream[63] = 63.0/64;
  fake_stream[64] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // First bin
  double sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -16.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -15.5 );

  // Second bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -15.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -14.5 );

  // Third bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -14.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -13.5 );

  // Fourth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -13.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -12.5 );

  // Fifth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -12.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -11.5 );

  // Sixth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -11.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -10.5 );

  // Seventh bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -10.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -9.5 );

  // Eighth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -9.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -8.5 );

  // Nineth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -8.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -7.5 );

  // Tenth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -7.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -6.5 );

  // Eleventh bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -6.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -5.5 );

  // Twelfth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -5.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -4.5 );

  // Thirteenth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -4.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -3.5 );

  // Fourteenth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -3.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -2.5 );

  // Fifteenth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -2.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.25 );

  // Sixteenth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -0.5 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -0.25 );

  // Seventeenth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.25 );

  // Eighteenth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.5 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.25 );

  // Nineteenth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 2.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 2.5 );

  // Twentieth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 3.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 3.5 );

  // Twenty-first bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 4.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 4.5 );

  // Twenty-second bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 5.5 );

  // Twenty-third bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 6.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 6.5 );

  // Twenty-fourth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 7.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 7.5 );

  // Twenty-fifth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 8.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 8.5 );

  // Twenty-sixth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 9.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 9.5 );

  // Twenty-seventh bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 10.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 10.5 );

  // Twenty-eighth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 11.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 11.5 );

  // Twenty-nineth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 12.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 12.5 );

  // Thirtieth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 13.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 13.5 );

  // Thirty-first bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 14.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 14.5 );

  // Thirty-second bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 15.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 15.5 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 16.0, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution, sample )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.125;
  fake_stream[2] = 0.25;
  fake_stream[3] = 0.375;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.625;
  fake_stream[6] = 0.75;
  fake_stream[7] = 0.875;
  fake_stream[8] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // First bin
  quantity<MegaElectronVolt> sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0*MeV );

  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.05*MeV );

  // Second bin
  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.1*MeV );

  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.55*MeV );

  // Third bin
  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0*MeV );

  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 3.0*MeV );

  // Fourth bin
  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 5.0*MeV );

  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 7.5*MeV );

  sample = unit_aware_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*MeV, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 65 );
  // First bin
  fake_stream[0] = 0.0;      fake_stream[1] = 1.0/64;
  // Second bin
  fake_stream[2] = 2.0/64;   fake_stream[3] = 3.0/64;
  // Third bin
  fake_stream[4] = 4.0/64;   fake_stream[5] = 5.0/64;
  // Fourth bin
  fake_stream[6] = 6.0/64;   fake_stream[7] = 7.0/64;
  // Fifth bin
  fake_stream[8] = 8.0/64;   fake_stream[9] = 9.0/64;
  // Sixth bin
  fake_stream[10] = 10.0/64; fake_stream[11] = 11.0/64;
  // Seventh bin
  fake_stream[12] = 12.0/64; fake_stream[13] = 13.0/64;
  // Eighth bin
  fake_stream[14] = 14.0/64; fake_stream[15] = 15.0/64;
  // Nineth bin
  fake_stream[16] = 16.0/64; fake_stream[17] = 17.0/64;
  // Tenth bin
  fake_stream[18] = 18.0/64; fake_stream[19] = 19.0/64;
  // Eleventh bin
  fake_stream[20] = 20.0/64; fake_stream[21] = 21.0/64;
  // Twelfth bin
  fake_stream[22] = 22.0/64; fake_stream[23] = 23.0/64;
  // Thirteenth bin
  fake_stream[24] = 24.0/64; fake_stream[25] = 25.0/64;
  // Fourteenth bin
  fake_stream[26] = 26.0/64; fake_stream[27] = 27.0/64;
  // Fifteenth bin
  fake_stream[28] = 28.0/64; fake_stream[29] = 29.0/64;
  // Sixteenth bin
  fake_stream[30] = 30.0/64; fake_stream[31] = 31.0/64;
  // Seventeenth bin
  fake_stream[32] = 32.0/64; fake_stream[33] = 33.0/64;
  // Eighteenth bin
  fake_stream[34] = 34.0/64; fake_stream[35] = 35.0/64;
  // Nineteenth bin
  fake_stream[36] = 36.0/64; fake_stream[37] = 37.0/64;
  // Twentieth bin
  fake_stream[38] = 38.0/64; fake_stream[39] = 39.0/64;
  // Twenty-first bin
  fake_stream[40] = 40.0/64; fake_stream[41] = 41.0/64;
  // Twenty-second bin
  fake_stream[42] = 42.0/64; fake_stream[43] = 43.0/64;
  // Twenty-third bin
  fake_stream[44] = 44.0/64; fake_stream[45] = 45.0/64;
  // Twenty-fourth bin
  fake_stream[46] = 46.0/64; fake_stream[47] = 47.0/64;
  // Twenty-fifth bin
  fake_stream[48] = 48.0/64; fake_stream[49] = 49.0/64;
  // Twenty-sixth bin
  fake_stream[50] = 50.0/64; fake_stream[51] = 51.0/64;
  // Twenty-seventh bin
  fake_stream[52] = 52.0/64; fake_stream[53] = 53.0/64;
  // Twenty-eighth bin
  fake_stream[54] = 54.0/64; fake_stream[55] = 55.0/64;
  // Twenty-nineth bin
  fake_stream[56] = 56.0/64; fake_stream[57] = 57.0/64;
  // Thirtieth bin
  fake_stream[58] = 58.0/64; fake_stream[59] = 59.0/64;
  // Thirty-first bin
  fake_stream[60] = 60.0/64; fake_stream[61] = 61.0/64;
  // Thirty-second bin
  fake_stream[62] = 62.0/64; fake_stream[63] = 63.0/64;
  fake_stream[64] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  // First bin
  double sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -16.0 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -15.5 );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  // Second bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -15.0 );
  TEST_EQUALITY_CONST( 3.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -14.5 );
  TEST_EQUALITY_CONST( 4.0/trials, 1.0 );

  // Third bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -14.0 );
  TEST_EQUALITY_CONST( 5.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -13.5 );
  TEST_EQUALITY_CONST( 6.0/trials, 1.0 );

  // Fourth bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -13.0 );
  TEST_EQUALITY_CONST( 7.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -12.5 );
  TEST_EQUALITY_CONST( 8.0/trials, 1.0 );

  // Fifth bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -12.0 );
  TEST_EQUALITY_CONST( 9.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -11.5 );
  TEST_EQUALITY_CONST( 10.0/trials, 1.0 );

  // Sixth bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -11.0 );
  TEST_EQUALITY_CONST( 11.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -10.5 );
  TEST_EQUALITY_CONST( 12.0/trials, 1.0 );

  // Seventh bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -10.0 );
  TEST_EQUALITY_CONST( 13.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -9.5 );
  TEST_EQUALITY_CONST( 14.0/trials, 1.0 );

  // Eighth bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -9.0 );
  TEST_EQUALITY_CONST( 15.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -8.5 );
  TEST_EQUALITY_CONST( 16.0/trials, 1.0 );

  // Nineth bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -8.0 );
  TEST_EQUALITY_CONST( 17.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -7.5 );
  TEST_EQUALITY_CONST( 18.0/trials, 1.0 );

  // Tenth bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -7.0 );
  TEST_EQUALITY_CONST( 19.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -6.5 );
  TEST_EQUALITY_CONST( 20.0/trials, 1.0 );

  // Eleventh bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -6.0 );
  TEST_EQUALITY_CONST( 21.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -5.5 );
  TEST_EQUALITY_CONST( 22.0/trials, 1.0 );

  // Twelfth bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -5.0 );
  TEST_EQUALITY_CONST( 23.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -4.5 );
  TEST_EQUALITY_CONST( 24.0/trials, 1.0 );

  // Thirteenth bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -4.0 );
  TEST_EQUALITY_CONST( 25.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -3.5 );
  TEST_EQUALITY_CONST( 26.0/trials, 1.0 );

  // Fourteenth bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -3.0 );
  TEST_EQUALITY_CONST( 27.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -2.5 );
  TEST_EQUALITY_CONST( 28.0/trials, 1.0 );

  // Fifteenth bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -2.0 );
  TEST_EQUALITY_CONST( 29.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -1.25 );
  TEST_EQUALITY_CONST( 30.0/trials, 1.0 );

  // Sixteenth bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -0.5 );
  TEST_EQUALITY_CONST( 31.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, -0.25 );
  TEST_EQUALITY_CONST( 32.0/trials, 1.0 );

  // Seventeenth bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( 33.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.25 );
  TEST_EQUALITY_CONST( 34.0/trials, 1.0 );

  // Eighteenth bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.5 );
  TEST_EQUALITY_CONST( 35.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( 36.0/trials, 1.0 );

  // Nineteenth bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 2.0 );
  TEST_EQUALITY_CONST( 37.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 2.5 );
  TEST_EQUALITY_CONST( 38.0/trials, 1.0 );

  // Twentieth bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 3.0 );
  TEST_EQUALITY_CONST( 39.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 3.5 );
  TEST_EQUALITY_CONST( 40.0/trials, 1.0 );

  // Twenty-first bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 4.0 );
  TEST_EQUALITY_CONST( 41.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 4.5 );
  TEST_EQUALITY_CONST( 42.0/trials, 1.0 );

  // Twenty-second bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( 43.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 5.5 );
  TEST_EQUALITY_CONST( 44.0/trials, 1.0 );

  // Twenty-third bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 6.0 );
  TEST_EQUALITY_CONST( 45.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 6.5 );
  TEST_EQUALITY_CONST( 46.0/trials, 1.0 );

  // Twenty-fourth bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 7.0 );
  TEST_EQUALITY_CONST( 47.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 7.5 );
  TEST_EQUALITY_CONST( 48.0/trials, 1.0 );

  // Twenty-fifth bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 8.0 );
  TEST_EQUALITY_CONST( 49.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 8.5 );
  TEST_EQUALITY_CONST( 50.0/trials, 1.0 );

  // Twenty-sixth bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 9.0 );
  TEST_EQUALITY_CONST( 51.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 9.5 );
  TEST_EQUALITY_CONST( 52.0/trials, 1.0 );

  // Twenty-seventh bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 10.0 );
  TEST_EQUALITY_CONST( 53.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 10.5 );
  TEST_EQUALITY_CONST( 54.0/trials, 1.0 );

  // Twenty-eighth bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 11.0 );
  TEST_EQUALITY_CONST( 55.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 11.5 );
  TEST_EQUALITY_CONST( 56.0/trials, 1.0 );

  // Twenty-nineth bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 12.0 );
  TEST_EQUALITY_CONST( 57.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 12.5 );
  TEST_EQUALITY_CONST( 58.0/trials, 1.0 );

  // Thirtieth bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 13.0 );
  TEST_EQUALITY_CONST( 59.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 13.5 );
  TEST_EQUALITY_CONST( 60.0/trials, 1.0 );

  // Thirty-first bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 14.0 );
  TEST_EQUALITY_CONST( 61.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 14.5 );
  TEST_EQUALITY_CONST( 62.0/trials, 1.0 );

  // Thirty-second bin
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 15.0 );
  TEST_EQUALITY_CONST( 63.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 15.5 );
  TEST_EQUALITY_CONST( 64.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 16.0, 1e-14 );
  TEST_EQUALITY_CONST( 65.0/trials, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution,
		   sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.125;
  fake_stream[2] = 0.25;
  fake_stream[3] = 0.375;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.625;
  fake_stream[6] = 0.75;
  fake_stream[7] = 0.875;
  fake_stream[8] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0u;

  // First bin
  quantity<MegaElectronVolt> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0*MeV );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.05*MeV );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  // Second bin
  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.1*MeV );
  TEST_EQUALITY_CONST( 3.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.55*MeV );
  TEST_EQUALITY_CONST( 4.0/trials, 1.0 );

  // Third bin
  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1.0*MeV );
  TEST_EQUALITY_CONST( 5.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 3.0*MeV );
  TEST_EQUALITY_CONST( 6.0/trials, 1.0 );

  // Fourth bin
  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 5.0*MeV );
  TEST_EQUALITY_CONST( 7.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 7.5*MeV );
  TEST_EQUALITY_CONST( 8.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( 9.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution, sampleAndRecordBinIndex )
{
  std::vector<double> fake_stream( 65 );
  // First bin
  fake_stream[0] = 0.0;      fake_stream[1] = 1.0/64;
  // Second bin
  fake_stream[2] = 2.0/64;   fake_stream[3] = 3.0/64;
  // Third bin
  fake_stream[4] = 4.0/64;   fake_stream[5] = 5.0/64;
  // Fourth bin
  fake_stream[6] = 6.0/64;   fake_stream[7] = 7.0/64;
  // Fifth bin
  fake_stream[8] = 8.0/64;   fake_stream[9] = 9.0/64;
  // Sixth bin
  fake_stream[10] = 10.0/64; fake_stream[11] = 11.0/64;
  // Seventh bin
  fake_stream[12] = 12.0/64; fake_stream[13] = 13.0/64;
  // Eighth bin
  fake_stream[14] = 14.0/64; fake_stream[15] = 15.0/64;
  // Nineth bin
  fake_stream[16] = 16.0/64; fake_stream[17] = 17.0/64;
  // Tenth bin
  fake_stream[18] = 18.0/64; fake_stream[19] = 19.0/64;
  // Eleventh bin
  fake_stream[20] = 20.0/64; fake_stream[21] = 21.0/64;
  // Twelfth bin
  fake_stream[22] = 22.0/64; fake_stream[23] = 23.0/64;
  // Thirteenth bin
  fake_stream[24] = 24.0/64; fake_stream[25] = 25.0/64;
  // Fourteenth bin
  fake_stream[26] = 26.0/64; fake_stream[27] = 27.0/64;
  // Fifteenth bin
  fake_stream[28] = 28.0/64; fake_stream[29] = 29.0/64;
  // Sixteenth bin
  fake_stream[30] = 30.0/64; fake_stream[31] = 31.0/64;
  // Seventeenth bin
  fake_stream[32] = 32.0/64; fake_stream[33] = 33.0/64;
  // Eighteenth bin
  fake_stream[34] = 34.0/64; fake_stream[35] = 35.0/64;
  // Nineteenth bin
  fake_stream[36] = 36.0/64; fake_stream[37] = 37.0/64;
  // Twentieth bin
  fake_stream[38] = 38.0/64; fake_stream[39] = 39.0/64;
  // Twenty-first bin
  fake_stream[40] = 40.0/64; fake_stream[41] = 41.0/64;
  // Twenty-second bin
  fake_stream[42] = 42.0/64; fake_stream[43] = 43.0/64;
  // Twenty-third bin
  fake_stream[44] = 44.0/64; fake_stream[45] = 45.0/64;
  // Twenty-fourth bin
  fake_stream[46] = 46.0/64; fake_stream[47] = 47.0/64;
  // Twenty-fifth bin
  fake_stream[48] = 48.0/64; fake_stream[49] = 49.0/64;
  // Twenty-sixth bin
  fake_stream[50] = 50.0/64; fake_stream[51] = 51.0/64;
  // Twenty-seventh bin
  fake_stream[52] = 52.0/64; fake_stream[53] = 53.0/64;
  // Twenty-eighth bin
  fake_stream[54] = 54.0/64; fake_stream[55] = 55.0/64;
  // Twenty-nineth bin
  fake_stream[56] = 56.0/64; fake_stream[57] = 57.0/64;
  // Thirtieth bin
  fake_stream[58] = 58.0/64; fake_stream[59] = 59.0/64;
  // Thirty-first bin
  fake_stream[60] = 60.0/64; fake_stream[61] = 61.0/64;
  // Thirty-second bin
  fake_stream[62] = 62.0/64; fake_stream[63] = 63.0/64;
  fake_stream[64] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;

  // First bin
  double sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -16.0 );
  TEST_EQUALITY_CONST( bin_index, 0 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -15.5 );
  TEST_EQUALITY_CONST( bin_index, 0 );

  // Second bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -15.0 );
  TEST_EQUALITY_CONST( bin_index, 1 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -14.5 );
  TEST_EQUALITY_CONST( bin_index, 1 );

  // Third bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -14.0 );
  TEST_EQUALITY_CONST( bin_index, 2 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -13.5 );
  TEST_EQUALITY_CONST( bin_index, 2 );

  // Fourth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -13.0 );
  TEST_EQUALITY_CONST( bin_index, 3 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -12.5 );
  TEST_EQUALITY_CONST( bin_index, 3 );

  // Fifth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -12.0 );
  TEST_EQUALITY_CONST( bin_index, 4 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -11.5 );
  TEST_EQUALITY_CONST( bin_index, 4 );

  // Sixth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -11.0 );
  TEST_EQUALITY_CONST( bin_index, 5 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -10.5 );
  TEST_EQUALITY_CONST( bin_index, 5 );

  // Seventh bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -10.0 );
  TEST_EQUALITY_CONST( bin_index, 6 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -9.5 );
  TEST_EQUALITY_CONST( bin_index, 6 );

  // Eighth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -9.0 );
  TEST_EQUALITY_CONST( bin_index, 7 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -8.5 );
  TEST_EQUALITY_CONST( bin_index, 7 );

  // Nineth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -8.0 );
  TEST_EQUALITY_CONST( bin_index, 8 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -7.5 );
  TEST_EQUALITY_CONST( bin_index, 8 );

  // Tenth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -7.0 );
  TEST_EQUALITY_CONST( bin_index, 9 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -6.5 );
  TEST_EQUALITY_CONST( bin_index, 9 );

  // Eleventh bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -6.0 );
  TEST_EQUALITY_CONST( bin_index, 10 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -5.5 );
  TEST_EQUALITY_CONST( bin_index, 10 );

  // Twelfth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -5.0 );
  TEST_EQUALITY_CONST( bin_index, 11 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -4.5 );
  TEST_EQUALITY_CONST( bin_index, 11 );

  // Thirteenth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -4.0 );
  TEST_EQUALITY_CONST( bin_index, 12 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -3.5 );
  TEST_EQUALITY_CONST( bin_index, 12 );

  // Fourteenth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -3.0 );
  TEST_EQUALITY_CONST( bin_index, 13 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -2.5 );
  TEST_EQUALITY_CONST( bin_index, 13 );

  // Fifteenth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -2.0 );
  TEST_EQUALITY_CONST( bin_index, 14 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -1.25 );
  TEST_EQUALITY_CONST( bin_index, 14 );

  // Sixteenth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -0.5 );
  TEST_EQUALITY_CONST( bin_index, 15 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, -0.25 );
  TEST_EQUALITY_CONST( bin_index, 15 );

  // Seventeenth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 16 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.25 );
  TEST_EQUALITY_CONST( bin_index, 16 );

  // Eighteenth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.5 );
  TEST_EQUALITY_CONST( bin_index, 17 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.25 );
  TEST_EQUALITY_CONST( bin_index, 17 );

  // Nineteenth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 2.0 );
  TEST_EQUALITY_CONST( bin_index, 18 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 2.5 );
  TEST_EQUALITY_CONST( bin_index, 18 );

  // Twentieth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 3.0 );
  TEST_EQUALITY_CONST( bin_index, 19 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 3.5 );
  TEST_EQUALITY_CONST( bin_index, 19 );

  // Twenty-first bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 4.0 );
  TEST_EQUALITY_CONST( bin_index, 20 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 4.5 );
  TEST_EQUALITY_CONST( bin_index, 20 );

  // Twenty-second bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 5.0 );
  TEST_EQUALITY_CONST( bin_index, 21 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 5.5 );
  TEST_EQUALITY_CONST( bin_index, 21 );

  // Twenty-third bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 6.0 );
  TEST_EQUALITY_CONST( bin_index, 22 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 6.5 );
  TEST_EQUALITY_CONST( bin_index, 22 );

  // Twenty-fourth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 7.0 );
  TEST_EQUALITY_CONST( bin_index, 23 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 7.5 );
  TEST_EQUALITY_CONST( bin_index, 23 );

  // Twenty-fifth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 8.0 );
  TEST_EQUALITY_CONST( bin_index, 24 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 8.5 );
  TEST_EQUALITY_CONST( bin_index, 24 );

  // Twenty-sixth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 9.0 );
  TEST_EQUALITY_CONST( bin_index, 25 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 9.5 );
  TEST_EQUALITY_CONST( bin_index, 25 );

  // Twenty-seventh bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 10.0 );
  TEST_EQUALITY_CONST( bin_index, 26 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 10.5 );
  TEST_EQUALITY_CONST( bin_index, 26 );

  // Twenty-eighth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 11.0 );
  TEST_EQUALITY_CONST( bin_index, 27 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 11.5 );
  TEST_EQUALITY_CONST( bin_index, 27 );

  // Twenty-nineth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 12.0 );
  TEST_EQUALITY_CONST( bin_index, 28 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 12.5 );
  TEST_EQUALITY_CONST( bin_index, 28 );

  // Thirtieth bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 13.0 );
  TEST_EQUALITY_CONST( bin_index, 29 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 13.5 );
  TEST_EQUALITY_CONST( bin_index, 29 );

  // Thirty-first bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 14.0 );
  TEST_EQUALITY_CONST( bin_index, 30 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 14.5 );
  TEST_EQUALITY_CONST( bin_index, 30 );

  // Thirty-second bin
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 15.0 );
  TEST_EQUALITY_CONST( bin_index, 31 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 15.5 );
  TEST_EQUALITY_CONST( bin_index, 31 );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 16.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 31 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution,
		   sampleAndRecordBinIndex )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.125;
  fake_stream[2] = 0.25;
  fake_stream[3] = 0.375;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.625;
  fake_stream[6] = 0.75;
  fake_stream[7] = 0.875;
  fake_stream[8] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;

  // First bin
  quantity<MegaElectronVolt> sample =
    unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0*MeV );
  TEST_EQUALITY_CONST( bin_index, 0.0 );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.05*MeV );
  TEST_EQUALITY_CONST( bin_index, 0.0 );

  // Second bin
  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.1*MeV );
  TEST_EQUALITY_CONST( bin_index, 1.0 );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.55*MeV );
  TEST_EQUALITY_CONST( bin_index, 1.0 );

  // Third bin
  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0*MeV );
  TEST_EQUALITY_CONST( bin_index, 2.0 );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 3.0*MeV );
  TEST_EQUALITY_CONST( bin_index, 2.0 );

  // Fourth bin
  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 5.0*MeV );
  TEST_EQUALITY_CONST( bin_index, 3.0 );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 7.5*MeV );
  TEST_EQUALITY_CONST( bin_index, 3.0 );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*MeV, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 3.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution, sampleWithRandomNumber )
{
  // First bin
  double sample = tab_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, -16.0 );

  sample = tab_distribution->sampleWithRandomNumber( 1.0/64 );
  TEST_EQUALITY_CONST( sample, -15.5 );

  // Second bin
  sample = tab_distribution->sampleWithRandomNumber( 2.0/64 );
  TEST_EQUALITY_CONST( sample, -15.0 );

  sample = tab_distribution->sampleWithRandomNumber( 3.0/64 );
  TEST_EQUALITY_CONST( sample, -14.5 );

  // Third bin
  sample = tab_distribution->sampleWithRandomNumber( 4.0/64 );
  TEST_EQUALITY_CONST( sample, -14.0 );

  sample = tab_distribution->sampleWithRandomNumber( 5.0/64 );
  TEST_EQUALITY_CONST( sample, -13.5 );

  // Fourth bin
  sample = tab_distribution->sampleWithRandomNumber( 6.0/64 );
  TEST_EQUALITY_CONST( sample, -13.0 );

  sample = tab_distribution->sampleWithRandomNumber( 7.0/64 );
  TEST_EQUALITY_CONST( sample, -12.5 );

  // Fifth bin
  sample = tab_distribution->sampleWithRandomNumber( 8.0/64 );
  TEST_EQUALITY_CONST( sample, -12.0 );

  sample = tab_distribution->sampleWithRandomNumber( 9.0/64 );
  TEST_EQUALITY_CONST( sample, -11.5 );

  // Sixth bin
  sample = tab_distribution->sampleWithRandomNumber( 10.0/64 );
  TEST_EQUALITY_CONST( sample, -11.0 );

  sample = tab_distribution->sampleWithRandomNumber( 11.0/64 );
  TEST_EQUALITY_CONST( sample, -10.5 );

  // Seventh bin
  sample = tab_distribution->sampleWithRandomNumber( 12.0/64 );
  TEST_EQUALITY_CONST( sample, -10.0 );

  sample = tab_distribution->sampleWithRandomNumber( 13.0/64 );
  TEST_EQUALITY_CONST( sample, -9.5 );

  // Eighth bin
  sample = tab_distribution->sampleWithRandomNumber( 14.0/64 );
  TEST_EQUALITY_CONST( sample, -9.0 );

  sample = tab_distribution->sampleWithRandomNumber( 15.0/64 );
  TEST_EQUALITY_CONST( sample, -8.5 );

  // Nineth bin
  sample = tab_distribution->sampleWithRandomNumber( 16.0/64 );
  TEST_EQUALITY_CONST( sample, -8.0 );

  sample = tab_distribution->sampleWithRandomNumber( 17.0/64 );
  TEST_EQUALITY_CONST( sample, -7.5 );

  // Tenth bin
  sample = tab_distribution->sampleWithRandomNumber( 18.0/64 );
  TEST_EQUALITY_CONST( sample, -7.0 );

  sample = tab_distribution->sampleWithRandomNumber( 19.0/64 );
  TEST_EQUALITY_CONST( sample, -6.5 );

  // Eleventh bin
  sample = tab_distribution->sampleWithRandomNumber( 20.0/64 );
  TEST_EQUALITY_CONST( sample, -6.0 );

  sample = tab_distribution->sampleWithRandomNumber( 21.0/64 );
  TEST_EQUALITY_CONST( sample, -5.5 );

  // Twelfth bin
  sample = tab_distribution->sampleWithRandomNumber( 22.0/64 );
  TEST_EQUALITY_CONST( sample, -5.0 );

  sample = tab_distribution->sampleWithRandomNumber( 23.0/64 );
  TEST_EQUALITY_CONST( sample, -4.5 );

  // Thirteenth bin
  sample = tab_distribution->sampleWithRandomNumber( 24.0/64 );
  TEST_EQUALITY_CONST( sample, -4.0 );

  sample = tab_distribution->sampleWithRandomNumber( 25.0/64 );
  TEST_EQUALITY_CONST( sample, -3.5 );

  // Fourteenth bin
  sample = tab_distribution->sampleWithRandomNumber( 26.0/64 );
  TEST_EQUALITY_CONST( sample, -3.0 );

  sample = tab_distribution->sampleWithRandomNumber( 27.0/64 );
  TEST_EQUALITY_CONST( sample, -2.5 );

  // Fifteenth bin
  sample = tab_distribution->sampleWithRandomNumber( 28.0/64 );
  TEST_EQUALITY_CONST( sample, -2.0 );

  sample = tab_distribution->sampleWithRandomNumber( 29.0/64 );
  TEST_EQUALITY_CONST( sample, -1.25 );

  // Sixteenth bin
  sample = tab_distribution->sampleWithRandomNumber( 30.0/64 );
  TEST_EQUALITY_CONST( sample, -0.5 );

  sample = tab_distribution->sampleWithRandomNumber( 31.0/64 );
  TEST_EQUALITY_CONST( sample, -0.25 );

  // Seventeenth bin
  sample = tab_distribution->sampleWithRandomNumber( 32.0/64 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleWithRandomNumber( 33.0/64 );
  TEST_EQUALITY_CONST( sample, 0.25 );

  // Eighteenth bin
  sample = tab_distribution->sampleWithRandomNumber( 34.0/64 );
  TEST_EQUALITY_CONST( sample, 0.5 );

  sample = tab_distribution->sampleWithRandomNumber( 35.0/64 );
  TEST_EQUALITY_CONST( sample, 1.25 );

  // Nineteenth bin
  sample = tab_distribution->sampleWithRandomNumber( 36.0/64 );
  TEST_EQUALITY_CONST( sample, 2.0 );

  sample = tab_distribution->sampleWithRandomNumber( 37.0/64 );
  TEST_EQUALITY_CONST( sample, 2.5 );

  // Twentieth bin
  sample = tab_distribution->sampleWithRandomNumber( 38.0/64 );
  TEST_EQUALITY_CONST( sample, 3.0 );

  sample = tab_distribution->sampleWithRandomNumber( 39.0/64 );
  TEST_EQUALITY_CONST( sample, 3.5 );

  // Twenty-first bin
  sample = tab_distribution->sampleWithRandomNumber( 40.0/64 );
  TEST_EQUALITY_CONST( sample, 4.0 );

  sample = tab_distribution->sampleWithRandomNumber( 41.0/64 );
  TEST_EQUALITY_CONST( sample, 4.5 );

  // Twenty-second bin
  sample = tab_distribution->sampleWithRandomNumber( 42.0/64 );
  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = tab_distribution->sampleWithRandomNumber( 43.0/64 );
  TEST_EQUALITY_CONST( sample, 5.5 );

  // Twenty-third bin
  sample = tab_distribution->sampleWithRandomNumber( 44.0/64 );
  TEST_EQUALITY_CONST( sample, 6.0 );

  sample = tab_distribution->sampleWithRandomNumber( 45.0/64 );
  TEST_EQUALITY_CONST( sample, 6.5 );

  // Twenty-fourth bin
  sample = tab_distribution->sampleWithRandomNumber( 46.0/64 );
  TEST_EQUALITY_CONST( sample, 7.0 );

  sample = tab_distribution->sampleWithRandomNumber( 47.0/64 );
  TEST_EQUALITY_CONST( sample, 7.5 );

  // Twenty-fifth bin
  sample = tab_distribution->sampleWithRandomNumber( 48.0/64 );
  TEST_EQUALITY_CONST( sample, 8.0 );

  sample = tab_distribution->sampleWithRandomNumber( 49.0/64 );
  TEST_EQUALITY_CONST( sample, 8.5 );

  // Twenty-sixth bin
  sample = tab_distribution->sampleWithRandomNumber( 50.0/64 );
  TEST_EQUALITY_CONST( sample, 9.0 );

  sample = tab_distribution->sampleWithRandomNumber( 51.0/64 );
  TEST_EQUALITY_CONST( sample, 9.5 );

  // Twenty-seventh bin
  sample = tab_distribution->sampleWithRandomNumber( 52.0/64 );
  TEST_EQUALITY_CONST( sample, 10.0 );

  sample = tab_distribution->sampleWithRandomNumber( 53.0/64 );
  TEST_EQUALITY_CONST( sample, 10.5 );

  // Twenty-eighth bin
  sample = tab_distribution->sampleWithRandomNumber( 54.0/64 );
  TEST_EQUALITY_CONST( sample, 11.0 );

  sample = tab_distribution->sampleWithRandomNumber( 55.0/64 );
  TEST_EQUALITY_CONST( sample, 11.5 );

  // Twenty-nineth bin
  sample = tab_distribution->sampleWithRandomNumber( 56.0/64 );
  TEST_EQUALITY_CONST( sample, 12.0 );

  sample = tab_distribution->sampleWithRandomNumber( 57.0/64 );
  TEST_EQUALITY_CONST( sample, 12.5 );

  // Thirtieth bin
  sample = tab_distribution->sampleWithRandomNumber( 58.0/64 );
  TEST_EQUALITY_CONST( sample, 13.0 );

  sample = tab_distribution->sampleWithRandomNumber( 59.0/64 );
  TEST_EQUALITY_CONST( sample, 13.5 );

  // Thirty-first bin
  sample = tab_distribution->sampleWithRandomNumber( 60.0/64 );
  TEST_EQUALITY_CONST( sample, 14.0 );

  sample = tab_distribution->sampleWithRandomNumber( 61.0/64 );
  TEST_EQUALITY_CONST( sample, 14.5 );

  // Thirty-second bin
  sample = tab_distribution->sampleWithRandomNumber( 62.0/64 );
  TEST_EQUALITY_CONST( sample, 15.0 );

  sample = tab_distribution->sampleWithRandomNumber( 63.0/64 );
  TEST_EQUALITY_CONST( sample, 15.5 );

  sample = tab_distribution->sampleWithRandomNumber( 64.0/64 );
  TEST_FLOATING_EQUALITY( sample, 16.0, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution,
		   sampleWithRandomNumber )
{
  // First bin
  quantity<MegaElectronVolt> sample =
    unit_aware_tab_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, 0.0*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.125 );
  TEST_EQUALITY_CONST( sample, 0.05*MeV );

  // Second bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.25 );
  TEST_EQUALITY_CONST( sample, 0.1*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.375 );
  TEST_EQUALITY_CONST( sample, 0.55*MeV );

  // Third bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.5 );
  TEST_EQUALITY_CONST( sample, 1.0*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.625 );
  TEST_EQUALITY_CONST( sample, 3.0*MeV );

  // Fourth bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.75 );
  TEST_EQUALITY_CONST( sample, 5.0*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.875 );
  TEST_EQUALITY_CONST( sample, 7.5*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 1.0-1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 10.0*MeV, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution, sampleInSubrange )
{
  std::vector<double> fake_stream( 13 );
  // First bin
  fake_stream[0] = 0.0;      fake_stream[1] = 1.0/12;
  // Second bin
  fake_stream[2] = 2.0/12;   fake_stream[3] = 3.0/12;
  // Third bin
  fake_stream[4] = 4.0/12;   fake_stream[5] = 5.0/12;
  // Fourth bin
  fake_stream[6] = 6.0/12;   fake_stream[7] = 7.0/12;
  // Fifth bin
  fake_stream[8] = 8.0/12;   fake_stream[9] = 9.0/12;
  // Sixth bin
  fake_stream[10] = 10.0/12; fake_stream[11] = 11.0/12;
  fake_stream[12] = 12.0/12 - 1e-12;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // First bin
  double sample = tab_distribution->sampleInSubrange( -10.0 );
  TEST_EQUALITY_CONST( sample, -16.0 );

  sample = tab_distribution->sampleInSubrange( -10.0 );
  TEST_EQUALITY_CONST( sample, -15.5 );

  // Second bin
  sample = tab_distribution->sampleInSubrange( -10.0 );
  TEST_EQUALITY_CONST( sample, -15.0 );

  sample = tab_distribution->sampleInSubrange( -10.0 );
  TEST_EQUALITY_CONST( sample, -14.5 );

  // Third bin
  sample = tab_distribution->sampleInSubrange( -10.0 );
  TEST_EQUALITY_CONST( sample, -14.0 );

  sample = tab_distribution->sampleInSubrange( -10.0 );
  TEST_EQUALITY_CONST( sample, -13.5 );

  // Fourth bin
  sample = tab_distribution->sampleInSubrange( -10.0 );
  TEST_EQUALITY_CONST( sample, -13.0 );

  sample = tab_distribution->sampleInSubrange( -10.0 );
  TEST_EQUALITY_CONST( sample, -12.5 );

  // Fifth bin
  sample = tab_distribution->sampleInSubrange( -10.0 );
  TEST_EQUALITY_CONST( sample, -12.0 );

  sample = tab_distribution->sampleInSubrange( -10.0 );
  TEST_EQUALITY_CONST( sample, -11.5 );

  // Sixth bin
  sample = tab_distribution->sampleInSubrange( -10.0 );
  TEST_EQUALITY_CONST( sample, -11.0 );

  sample = tab_distribution->sampleInSubrange( -10.0 );
  TEST_EQUALITY_CONST( sample, -10.5 );

  sample = tab_distribution->sampleInSubrange( -10.0 );
  TEST_FLOATING_EQUALITY( sample, -10.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution, sampleInSubrange )
{
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6;
  fake_stream[2] = 2.0/6;
  fake_stream[3] = 3.0/6;
  fake_stream[4] = 4.0/6;
  fake_stream[5] = 5.0/6;
  fake_stream[6] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // First bin
  quantity<MegaElectronVolt> sample =
    unit_aware_tab_distribution->sampleInSubrange( 5.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*MeV );

  sample = unit_aware_tab_distribution->sampleInSubrange( 5.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.05*MeV );

  // Second bin
  sample = unit_aware_tab_distribution->sampleInSubrange( 5.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.1*MeV );

  sample = unit_aware_tab_distribution->sampleInSubrange( 5.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.55*MeV );

  // Third bin
  sample = unit_aware_tab_distribution->sampleInSubrange( 5.0*MeV );
  TEST_EQUALITY_CONST( sample, 1.0*MeV );

  sample = unit_aware_tab_distribution->sampleInSubrange( 5.0*MeV );
  TEST_EQUALITY_CONST( sample, 3.0*MeV );

  sample = unit_aware_tab_distribution->sampleInSubrange( 5.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*MeV, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution,
		   sampleWithRandomNumberInSubrange )
{
  // First bin
  double sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.0, -10.0 );
  TEST_EQUALITY_CONST( sample, -16.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0/12, -10.0 );
  TEST_EQUALITY_CONST( sample, -15.5 );

  // Second bin
  sample = tab_distribution->sampleWithRandomNumberInSubrange( 2.0/12, -10.0 );
  TEST_EQUALITY_CONST( sample, -15.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 3.0/12, -10.0 );
  TEST_EQUALITY_CONST( sample, -14.5 );

  // Third bin
  sample = tab_distribution->sampleWithRandomNumberInSubrange( 4.0/12, -10.0 );
  TEST_EQUALITY_CONST( sample, -14.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 5.0/12, -10.0 );
  TEST_EQUALITY_CONST( sample, -13.5 );

  // Fourth bin
  sample = tab_distribution->sampleWithRandomNumberInSubrange( 6.0/12, -10.0 );
  TEST_EQUALITY_CONST( sample, -13.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 7.0/12, -10.0 );
  TEST_EQUALITY_CONST( sample, -12.5 );

  // Fifth bin
  sample = tab_distribution->sampleWithRandomNumberInSubrange( 8.0/12, -10.0 );
  TEST_EQUALITY_CONST( sample, -12.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 9.0/12, -10.0 );
  TEST_EQUALITY_CONST( sample, -11.5 );

  // Sixth bin
  sample = tab_distribution->sampleWithRandomNumberInSubrange( 10.0/12, -10.0 );
  TEST_EQUALITY_CONST( sample, -11.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 11.0/12, -10.0 );
  TEST_EQUALITY_CONST( sample, -10.5 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0, -10.0 );
  TEST_FLOATING_EQUALITY( sample, -10.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution,
		   sampleWithRandomNumberInSubrange )
{
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6;
  fake_stream[2] = 2.0/6;
  fake_stream[3] = 3.0/6;
  fake_stream[4] = 4.0/6;
  fake_stream[5] = 5.0/6;
  fake_stream[6] = 1.0-1e-15;

  // First bin
  quantity<MegaElectronVolt> sample =
    unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 5.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.0*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 1.0/6, 5.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.05*MeV );

  // Second bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 2.0/6, 5.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.1*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 3.0/6, 5.0*MeV );
  TEST_EQUALITY_CONST( sample, 0.55*MeV );

  // Third bin
  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 4.0/6, 5.0*MeV );
  TEST_EQUALITY_CONST( sample, 1.0*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 5.0/6, 5.0*MeV );
  TEST_EQUALITY_CONST( sample, 3.0*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 1.0-1e-15, 5.0*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 5.0*MeV, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution,
		   getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 16.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution,
		   getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       10.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution,
		   getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), -16.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution,
		   getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       0.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution,
		   getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::EQUIPROBABLE_BIN_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution,
		   getDistributionType )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getDistributionType(),
		       Utility::EQUIPROBABLE_BIN_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the distribution type name can be returned
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution, getDistributionTypeName )
{
  TEST_EQUALITY_CONST( Utility::EquiprobableBinDistribution::getDistributionTypeName(),
                       "Equiprobable Bin Distribution" );
  TEST_EQUALITY_CONST( Utility::EquiprobableBinDistribution::getDistributionTypeName( false ),
                       "Equiprobable" );
  TEST_EQUALITY_CONST( Utility::EquiprobableBinDistribution::getDistributionTypeName( true, true ),
                       "equiprobable bin distribution" );
  TEST_EQUALITY_CONST( Utility::EquiprobableBinDistribution::getDistributionTypeName( false, true ),
                       "equiprobable" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type name can be returned
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution,
                   getDistributionTypeName )
{
  TEST_EQUALITY_CONST( (Utility::UnitAwareEquiprobableBinDistribution<MegaElectronVolt,si::amount>::getDistributionTypeName()),
                       "Equiprobable Bin Distribution" );
  TEST_EQUALITY_CONST( (Utility::UnitAwareEquiprobableBinDistribution<MegaElectronVolt,si::amount>::getDistributionTypeName( false )),
                       "Equiprobable" );
  TEST_EQUALITY_CONST( (Utility::UnitAwareEquiprobableBinDistribution<MegaElectronVolt,si::amount>::getDistributionTypeName( true, true )),
                       "equiprobable bin distribution" );
  TEST_EQUALITY_CONST( (Utility::UnitAwareEquiprobableBinDistribution<MegaElectronVolt,si::amount>::getDistributionTypeName( false, true )),
                       "equiprobable" );
}

//---------------------------------------------------------------------------//
// Check if the type name matches the distribution type name
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution, doesTypeNameMatch )
{
  TEST_ASSERT( Utility::EquiprobableBinDistribution::doesTypeNameMatch( "Equiprobable Bin Distribution" ) );
  TEST_ASSERT( Utility::EquiprobableBinDistribution::doesTypeNameMatch( "Equiprobable" ) );
  TEST_ASSERT( Utility::EquiprobableBinDistribution::doesTypeNameMatch( "equiprobable" ) );
  TEST_ASSERT( Utility::EquiprobableBinDistribution::doesTypeNameMatch( "EQUIPROBABLE" ) );
  TEST_ASSERT( !Utility::EquiprobableBinDistribution::doesTypeNameMatch( "EQUI" ) );
}

//---------------------------------------------------------------------------//
// Check if the type name matches the unit-aware distribution type name
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution, doesTypeNameMatch )
{
  TEST_ASSERT( (Utility::UnitAwareEquiprobableBinDistribution<MegaElectronVolt,si::amount>::doesTypeNameMatch( "Equiprobable Bin Distribution" )) );
  TEST_ASSERT( (Utility::UnitAwareEquiprobableBinDistribution<MegaElectronVolt,si::amount>::doesTypeNameMatch( "Equiprobable" )) );
  TEST_ASSERT( (Utility::UnitAwareEquiprobableBinDistribution<MegaElectronVolt,si::amount>::doesTypeNameMatch( "equiprobable" )) );
  TEST_ASSERT( (Utility::UnitAwareEquiprobableBinDistribution<MegaElectronVolt,si::amount>::doesTypeNameMatch( "EQUIPROBABLE" )) );
  TEST_ASSERT( !(Utility::UnitAwareEquiprobableBinDistribution<MegaElectronVolt,si::amount>::doesTypeNameMatch( "EQUI" )) );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution, isTabular )
{
  TEST_ASSERT( distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution, isTabular )
{
  TEST_ASSERT( unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution, isContinuous )
{
  TEST_ASSERT( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution, isContinuous )
{
  TEST_ASSERT( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution, isCompatibleWithInterpType )
{
  TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Check an alternative distribution that is compatible with all interp types
  std::vector<double> bin_boundaries( 4 );

  bin_boundaries[0] = 1.0;
  bin_boundaries[1] = 2.0;
  bin_boundaries[2] = 3.0;
  bin_boundaries[3] = 4.0;

  Utility::EquiprobableBinDistribution test_dist( bin_boundaries );

  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution,
                   isCompatibleWithInterpType )
{
  TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );

  // Check an alternative distribution that is compatible with all interp types
  std::vector<double> bin_boundaries( 4 );

  bin_boundaries[0] = 1.0;
  bin_boundaries[1] = 2.0;
  bin_boundaries[2] = 3.0;
  bin_boundaries[3] = 4.0;

  Utility::UnitAwareEquiprobableBinDistribution<MegaElectronVolt,si::amount>
    test_dist( bin_boundaries );

  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( test_dist.isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can converted to a string
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution, toString )
{
  std::string dist_string = Utility::toString( *distribution );

  TEST_EQUALITY_CONST( dist_string, "{Equiprobable Bin Distribution, {-1.600000000000000000e+01, -1.500000000000000000e+01, -1.400000000000000000e+01, -1.300000000000000000e+01, -1.200000000000000000e+01, -1.100000000000000000e+01, -1.000000000000000000e+01, -9.000000000000000000e+00, -8.000000000000000000e+00, -7.000000000000000000e+00, -6.000000000000000000e+00, -5.000000000000000000e+00, -4.000000000000000000e+00, -3.000000000000000000e+00, -2.000000000000000000e+00, -5.000000000000000000e-01, 0.000000000000000000e+00, 5.000000000000000000e-01, 2.000000000000000000e+00, 3.000000000000000000e+00, 4.000000000000000000e+00, 5.000000000000000000e+00, 6.000000000000000000e+00, 7.000000000000000000e+00, 8.000000000000000000e+00, 9.000000000000000000e+00, 1.000000000000000000e+01, 1.100000000000000000e+01, 1.200000000000000000e+01, 1.300000000000000000e+01, 1.400000000000000000e+01, 1.500000000000000000e+01, 1.600000000000000000e+01}}" );

  dist_string = Utility::toString( *tab_distribution );

  TEST_EQUALITY_CONST( dist_string, "{Equiprobable Bin Distribution, {-1.600000000000000000e+01, -1.500000000000000000e+01, -1.400000000000000000e+01, -1.300000000000000000e+01, -1.200000000000000000e+01, -1.100000000000000000e+01, -1.000000000000000000e+01, -9.000000000000000000e+00, -8.000000000000000000e+00, -7.000000000000000000e+00, -6.000000000000000000e+00, -5.000000000000000000e+00, -4.000000000000000000e+00, -3.000000000000000000e+00, -2.000000000000000000e+00, -5.000000000000000000e-01, 0.000000000000000000e+00, 5.000000000000000000e-01, 2.000000000000000000e+00, 3.000000000000000000e+00, 4.000000000000000000e+00, 5.000000000000000000e+00, 6.000000000000000000e+00, 7.000000000000000000e+00, 8.000000000000000000e+00, 9.000000000000000000e+00, 1.000000000000000000e+01, 1.100000000000000000e+01, 1.200000000000000000e+01, 1.300000000000000000e+01, 1.400000000000000000e+01, 1.500000000000000000e+01, 1.600000000000000000e+01}}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be converted to a stream
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution, toString )
{
  std::string dist_string = Utility::toString( *unit_aware_distribution );

  TEST_EQUALITY_CONST( dist_string, "{Equiprobable Bin Distribution, {0.000000000000000000e+00, 1.000000000000000056e-01, 1.000000000000000000e+00, 5.000000000000000000e+00, 1.000000000000000000e+01}}" );

  dist_string = Utility::toString( *unit_aware_tab_distribution );

  TEST_EQUALITY_CONST( dist_string, "{Equiprobable Bin Distribution, {0.000000000000000000e+00, 1.000000000000000056e-01, 1.000000000000000000e+00, 5.000000000000000000e+00, 1.000000000000000000e+01}}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution, toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, *distribution );

  TEST_EQUALITY_CONST( oss.str(), "{Equiprobable Bin Distribution, {-1.600000000000000000e+01, -1.500000000000000000e+01, -1.400000000000000000e+01, -1.300000000000000000e+01, -1.200000000000000000e+01, -1.100000000000000000e+01, -1.000000000000000000e+01, -9.000000000000000000e+00, -8.000000000000000000e+00, -7.000000000000000000e+00, -6.000000000000000000e+00, -5.000000000000000000e+00, -4.000000000000000000e+00, -3.000000000000000000e+00, -2.000000000000000000e+00, -5.000000000000000000e-01, 0.000000000000000000e+00, 5.000000000000000000e-01, 2.000000000000000000e+00, 3.000000000000000000e+00, 4.000000000000000000e+00, 5.000000000000000000e+00, 6.000000000000000000e+00, 7.000000000000000000e+00, 8.000000000000000000e+00, 9.000000000000000000e+00, 1.000000000000000000e+01, 1.100000000000000000e+01, 1.200000000000000000e+01, 1.300000000000000000e+01, 1.400000000000000000e+01, 1.500000000000000000e+01, 1.600000000000000000e+01}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, *tab_distribution );

  TEST_EQUALITY_CONST( oss.str(), "{Equiprobable Bin Distribution, {-1.600000000000000000e+01, -1.500000000000000000e+01, -1.400000000000000000e+01, -1.300000000000000000e+01, -1.200000000000000000e+01, -1.100000000000000000e+01, -1.000000000000000000e+01, -9.000000000000000000e+00, -8.000000000000000000e+00, -7.000000000000000000e+00, -6.000000000000000000e+00, -5.000000000000000000e+00, -4.000000000000000000e+00, -3.000000000000000000e+00, -2.000000000000000000e+00, -5.000000000000000000e-01, 0.000000000000000000e+00, 5.000000000000000000e-01, 2.000000000000000000e+00, 3.000000000000000000e+00, 4.000000000000000000e+00, 5.000000000000000000e+00, 6.000000000000000000e+00, 7.000000000000000000e+00, 8.000000000000000000e+00, 9.000000000000000000e+00, 1.000000000000000000e+01, 1.100000000000000000e+01, 1.200000000000000000e+01, 1.300000000000000000e+01, 1.400000000000000000e+01, 1.500000000000000000e+01, 1.600000000000000000e+01}}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution, toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, *unit_aware_distribution );

  TEST_EQUALITY_CONST( oss.str(), "{Equiprobable Bin Distribution, {0.000000000000000000e+00, 1.000000000000000056e-01, 1.000000000000000000e+00, 5.000000000000000000e+00, 1.000000000000000000e+01}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, *unit_aware_tab_distribution );

  TEST_EQUALITY_CONST( oss.str(), "{Equiprobable Bin Distribution, {0.000000000000000000e+00, 1.000000000000000056e-01, 1.000000000000000000e+00, 5.000000000000000000e+00, 1.000000000000000000e+01}}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << *distribution;

  TEST_EQUALITY_CONST( oss.str(), "{Equiprobable Bin Distribution, {-1.600000000000000000e+01, -1.500000000000000000e+01, -1.400000000000000000e+01, -1.300000000000000000e+01, -1.200000000000000000e+01, -1.100000000000000000e+01, -1.000000000000000000e+01, -9.000000000000000000e+00, -8.000000000000000000e+00, -7.000000000000000000e+00, -6.000000000000000000e+00, -5.000000000000000000e+00, -4.000000000000000000e+00, -3.000000000000000000e+00, -2.000000000000000000e+00, -5.000000000000000000e-01, 0.000000000000000000e+00, 5.000000000000000000e-01, 2.000000000000000000e+00, 3.000000000000000000e+00, 4.000000000000000000e+00, 5.000000000000000000e+00, 6.000000000000000000e+00, 7.000000000000000000e+00, 8.000000000000000000e+00, 9.000000000000000000e+00, 1.000000000000000000e+01, 1.100000000000000000e+01, 1.200000000000000000e+01, 1.300000000000000000e+01, 1.400000000000000000e+01, 1.500000000000000000e+01, 1.600000000000000000e+01}}" );

  oss.str( "" );
  oss.clear();

  oss << *tab_distribution;

  TEST_EQUALITY_CONST( oss.str(), "{Equiprobable Bin Distribution, {-1.600000000000000000e+01, -1.500000000000000000e+01, -1.400000000000000000e+01, -1.300000000000000000e+01, -1.200000000000000000e+01, -1.100000000000000000e+01, -1.000000000000000000e+01, -9.000000000000000000e+00, -8.000000000000000000e+00, -7.000000000000000000e+00, -6.000000000000000000e+00, -5.000000000000000000e+00, -4.000000000000000000e+00, -3.000000000000000000e+00, -2.000000000000000000e+00, -5.000000000000000000e-01, 0.000000000000000000e+00, 5.000000000000000000e-01, 2.000000000000000000e+00, 3.000000000000000000e+00, 4.000000000000000000e+00, 5.000000000000000000e+00, 6.000000000000000000e+00, 7.000000000000000000e+00, 8.000000000000000000e+00, 9.000000000000000000e+00, 1.000000000000000000e+01, 1.100000000000000000e+01, 1.200000000000000000e+01, 1.300000000000000000e+01, 1.400000000000000000e+01, 1.500000000000000000e+01, 1.600000000000000000e+01}}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << *unit_aware_distribution;

  TEST_EQUALITY_CONST( oss.str(), "{Equiprobable Bin Distribution, {0.000000000000000000e+00, 1.000000000000000056e-01, 1.000000000000000000e+00, 5.000000000000000000e+00, 1.000000000000000000e+01}}" );

  oss.str( "" );
  oss.clear();

  oss << *unit_aware_tab_distribution;

  TEST_EQUALITY_CONST( oss.str(), "{Equiprobable Bin Distribution, {0.000000000000000000e+00, 1.000000000000000056e-01, 1.000000000000000000e+00, 5.000000000000000000e+00, 1.000000000000000000e+01}}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be initialized from a string
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution, fromString )
{
  Utility::EquiprobableBinDistribution test_dist =
    Utility::fromString<Utility::EquiprobableBinDistribution>( "{Equiprobable Bin Distribution, {-16.0, 13i, -2.0, -0.5, 0.0, 0.5, 2.0, 13i, 16.0}}" );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::EquiprobableBinDistribution*>( distribution.get() ) );

  TEST_THROW( Utility::fromString<Utility::EquiprobableBinDistribution>( "{Dummy Distribution, {-16.0, 13i, -2.0, -0.5, 0.0, 0.5, 2.0, 13i, 16.0}}" ),
              Utility::StringConversionException );

  TEST_THROW( Utility::fromString<Utility::EquiprobableBinDistribution>( "{Equiprobable Bin Distribution, {-16.0, 13i, -2.0, -0.5, 0.0r2, 0.5, 2.0, 13i, 16.0}}" ),
              Utility::StringConversionException );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be initialized from a string
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution, fromString )
{
  Utility::UnitAwareEquiprobableBinDistribution<MegaElectronVolt,si::amount> test_dist =
    Utility::fromString<decltype(test_dist)>( "{Equiprobable Bin Distribution, {0.000000000000000000e+00, 1.000000000000000056e-01, 1.000000000000000000e+00, 5.000000000000000000e+00, 1.000000000000000000e+01}}" );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_distribution.get() ) );

  TEST_THROW( Utility::fromString<decltype(test_dist)>( "{Dummy Distribution, {0.0, 3i, 10.0}}" ),
              Utility::StringConversionException );

  TEST_THROW( Utility::fromString<Utility::EquiprobableBinDistribution>( "{Equiprobable Bin Distribution, {0.0, 1.0r3, 10.0}}" ),
              Utility::StringConversionException );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be initialized from a stream
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution, fromStream )
{
  std::istringstream iss( "{Equiprobable Bin Distribution, {-16.0, 13i, -2.0, -0.5, 0.0, 0.5, 2.0, 13i, 16.0}}" );
  
  Utility::EquiprobableBinDistribution test_dist;

  Utility::fromStream( iss, test_dist );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::EquiprobableBinDistribution*>( distribution.get() ) );

  iss.str( "{Dummy Distribution, {-16.0, 13i, -2.0, -0.5, 0.0, 0.5, 2.0, 13i, 16.0}}" );
  iss.clear();

  TEST_THROW( Utility::fromStream( iss, test_dist ),
              Utility::StringConversionException );

  iss.str( "{Equiprobable Bin Distribution, {-16.0, 13i, -2.0, -0.5, 0.0r2, 0.5, 2.0, 13i, 16.0}}" );
  iss.clear();

  TEST_THROW( Utility::fromStream( iss, test_dist ),
              Utility::StringConversionException );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be initialized from a stream
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution, fromStream )
{
  std::istringstream iss( "{Equiprobable Bin Distribution, {0.000000000000000000e+00, 1.000000000000000056e-01, 1.000000000000000000e+00, 5.000000000000000000e+00, 1.000000000000000000e+01}}" );
  
  Utility::UnitAwareEquiprobableBinDistribution<MegaElectronVolt,si::amount> test_dist;

  Utility::fromStream( iss, test_dist );

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_distribution.get() ) );

  iss.str( "{Dummy Distribution, {0.0, 3i, 10.0}}" );
  iss.clear();

  TEST_THROW( Utility::fromStream( iss, test_dist ),
              Utility::StringConversionException );

  iss.str( "{Equiprobable Bin Distribution, {0.0, 1.0r3, 10.0}}" );
  iss.clear();
  
  TEST_THROW( Utility::fromStream( iss, test_dist ),
              Utility::StringConversionException );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be initialized from a stream
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution, istream_operator )
{
  std::istringstream iss( "{Equiprobable Bin Distribution, {-16.0, 13i, -2.0, -0.5, 0.0, 0.5, 2.0, 13i, 16.0}}" );
  
  Utility::EquiprobableBinDistribution test_dist;

  iss >> test_dist;

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<Utility::EquiprobableBinDistribution*>( distribution.get() ) );

  iss.str( "{Dummy Distribution, {-16.0, 13i, -2.0, -0.5, 0.0, 0.5, 2.0, 13i, 16.0}}" );
  iss.clear();

  TEST_THROW( iss >> test_dist, Utility::StringConversionException );

  iss.str( "{Equiprobable Bin Distribution, {-16.0, 13i, -2.0, -0.5, 0.0r2, 0.5, 2.0, 13i, 16.0}}" );
  iss.clear();

  TEST_THROW( iss >> test_dist, Utility::StringConversionException );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be initialized from a stream
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution, istream_operator )
{
  std::istringstream iss( "{Equiprobable Bin Distribution, {0.000000000000000000e+00, 1.000000000000000056e-01, 1.000000000000000000e+00, 5.000000000000000000e+00, 1.000000000000000000e+01}}" );
  
  Utility::UnitAwareEquiprobableBinDistribution<MegaElectronVolt,si::amount> test_dist;

  iss >> test_dist;

  TEST_EQUALITY_CONST( test_dist, *dynamic_cast<decltype(test_dist)*>( unit_aware_distribution.get() ) );

  iss.str( "{Dummy Distribution, {0.0, 3i, 10.0}}" );
  iss.clear();

  TEST_THROW( iss >> test_dist, Utility::StringConversionException );

  iss.str( "{Equiprobable Bin Distribution, {0.0, 1.0r3, 10.0}}" );
  iss.clear();
  
  TEST_THROW( iss >> test_dist, Utility::StringConversionException );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to a property tree
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", *distribution );

  Utility::EquiprobableBinDistribution copy_dist =
    ptree.get<Utility::EquiprobableBinDistribution>( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<Utility::EquiprobableBinDistribution*>( distribution.get() ) );

  ptree.put( "test distribution", *tab_distribution );

  copy_dist = ptree.get<Utility::EquiprobableBinDistribution>( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<Utility::EquiprobableBinDistribution*>( tab_distribution.get() ) );

  ptree.clear();

  // Use the PropertyTreeCompatibleObject interface
  ptree = distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::EquiprobableBinDistribution>();

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<Utility::EquiprobableBinDistribution*>( distribution.get() ) );

  ptree = distribution->toPropertyTree( false );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ),
                       "Equiprobable Bin Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           Utility::fromString<std::vector<double> >( "{-16.0, 13i, -2.0, -0.5, 0.0, 0.5, 2.0, 13i, 16.0}" ) );

  ptree = distribution->toPropertyTree();

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ),
                       "Equiprobable Bin Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           Utility::fromString<std::vector<double> >( "{-16.0, 13i, -2.0, -0.5, 0.0, 0.5, 2.0, 13i, 16.0}" ) );

  // Use the property tree helper methods
  ptree = Utility::toPropertyTree( *distribution, true );

  copy_dist = ptree.get_value<Utility::EquiprobableBinDistribution>();

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<Utility::EquiprobableBinDistribution*>( distribution.get() ) );

  ptree = Utility::toPropertyTree( *tab_distribution, true );

  copy_dist = ptree.get_value<Utility::EquiprobableBinDistribution>();

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<Utility::EquiprobableBinDistribution*>( distribution.get() ) );

  ptree = Utility::toPropertyTree( *distribution, false );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ),
                       "Equiprobable Bin Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           Utility::fromString<std::vector<double> >( "{-16.0, 13i, -2.0, -0.5, 0.0, 0.5, 2.0, 13i, 16.0}" ) );

  ptree = Utility::toPropertyTree( *tab_distribution, false );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ),
                       "Equiprobable Bin Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           Utility::fromString<std::vector<double> >( "{-16.0, 13i, -2.0, -0.5, 0.0, 0.5, 2.0, 13i, 16.0}" ) );

  ptree = Utility::toPropertyTree( *distribution );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ),
                       "Equiprobable Bin Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           Utility::fromString<std::vector<double> >( "{-16.0, 13i, -2.0, -0.5, 0.0, 0.5, 2.0, 13i, 16.0}" ) );

  ptree = Utility::toPropertyTree( *tab_distribution );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ),
                       "Equiprobable Bin Distribution" );
  TEST_COMPARE_CONTAINERS( ptree.get<std::vector<double> >( "bin boundaries" ),
                           Utility::fromString<std::vector<double> >( "{-16.0, 13i, -2.0, -0.5, 0.0, 0.5, 2.0, 13i, 16.0}" ) );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be written to a property tree
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", *unit_aware_distribution );

  Utility::UnitAwareEquiprobableBinDistribution<MegaElectronVolt,si::amount>
    copy_dist = ptree.get<decltype(copy_dist)>( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<decltype(copy_dist)*>( unit_aware_distribution.get() ) );

  ptree.put( "test distribution", *unit_aware_tab_distribution );

  copy_dist = ptree.get<decltype(copy_dist)>( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<decltype(copy_dist)*>( unit_aware_tab_distribution.get() ) );

  ptree.clear();

  // Use the PropertyTreeCompatibleObject interface
  ptree = unit_aware_distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<decltype(copy_dist)>();

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<decltype(copy_dist)*>( unit_aware_distribution.get() ) );

  ptree = unit_aware_distribution->toPropertyTree( false );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ),
                       "Equiprobable Bin Distribution" );
  TEST_COMPARE_ARRAYS( ptree.get<std::vector<double> >( "bin boundaries" ),
                       std::vector<double>({0.0, 0.1, 1.0, 5.0, 10.0}) );

  ptree = unit_aware_distribution->toPropertyTree();

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ),
                       "Equiprobable Bin Distribution" );
  TEST_COMPARE_ARRAYS( ptree.get<std::vector<double> >( "bin boundaries" ),
                       std::vector<double>({0.0, 0.1, 1.0, 5.0, 10.0}) );

  // Use the property tree helper methds
  ptree = Utility::toPropertyTree( *unit_aware_distribution, true );

  copy_dist = ptree.get_value<decltype(copy_dist)>();

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<decltype(copy_dist)*>( unit_aware_distribution.get() ) );

  ptree = Utility::toPropertyTree( *unit_aware_tab_distribution, true );

  TEST_EQUALITY_CONST( ptree.size(), 0 );
  TEST_EQUALITY_CONST( copy_dist, *dynamic_cast<decltype(copy_dist)*>( unit_aware_tab_distribution.get() ) );

  ptree = Utility::toPropertyTree( *unit_aware_distribution, false );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ),
                       "Equiprobable Bin Distribution" );
  TEST_COMPARE_ARRAYS( ptree.get<std::vector<double> >( "bin boundaries" ),
                       std::vector<double>({0.0, 0.1, 1.0, 5.0, 10.0}) );

  ptree = Utility::toPropertyTree( *unit_aware_tab_distribution, false );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ),
                       "Equiprobable Bin Distribution" );
  TEST_COMPARE_ARRAYS( ptree.get<std::vector<double> >( "bin boundaries" ),
                       std::vector<double>({0.0, 0.1, 1.0, 5.0, 10.0}) );

  ptree = Utility::toPropertyTree( *unit_aware_distribution );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ),
                       "Equiprobable Bin Distribution" );
  TEST_COMPARE_ARRAYS( ptree.get<std::vector<double> >( "bin boundaries" ),
                       std::vector<double>({0.0, 0.1, 1.0, 5.0, 10.0}) );

  ptree = Utility::toPropertyTree( *unit_aware_tab_distribution );

  TEST_EQUALITY_CONST( ptree.size(), 2 );
  TEST_EQUALITY_CONST( ptree.get<std::string>( "type" ),
                       "Equiprobable Bin Distribution" );
  TEST_COMPARE_ARRAYS( ptree.get<std::vector<double> >( "bin boundaries" ),
                       std::vector<double>({0.0, 0.1, 1.0, 5.0, 10.0}) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from a property tree
TEUCHOS_UNIT_TEST( EquiprobableBinDistribution, fromPropertyTree )
{
  Utility::EquiprobableBinDistribution dist;

  std::vector<std::string> unused_children;

  dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution A" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0 );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(),
                       2*Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution B" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), -1.0 );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 1.0 );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution C" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0 );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 10.0 );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution D" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0 );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(),
                       Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution E" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.001 );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 20.0 );
  TEST_EQUALITY_CONST( unused_children.size(), 1 );
  TEST_EQUALITY_CONST( unused_children.front(), "dummy" );

  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution F" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution G" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution H" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution I" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution J" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution K" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution L" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution M" ) ),
              Utility::PropertyTreeConversionException );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from a property tree
TEUCHOS_UNIT_TEST( UnitAwareEquiprobableBinDistribution, fromPropertyTree )
{
  Utility::UnitAwareEquiprobableBinDistribution<MegaElectronVolt,si::amount> dist;

  std::vector<std::string> unused_children;

  dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution A" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0*MeV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(),
                       2*Utility::PhysicalConstants::pi*MeV );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution B" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), -1.0*MeV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 1.0*MeV );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution C" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0*MeV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 10.0*MeV );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution D" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.0*MeV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(),
                       Utility::PhysicalConstants::pi*MeV );
  TEST_EQUALITY_CONST( unused_children.size(), 0 );

  dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution E" ),
                         unused_children );

  TEST_EQUALITY_CONST( dist.getLowerBoundOfIndepVar(), 0.001*MeV );
  TEST_EQUALITY_CONST( dist.getUpperBoundOfIndepVar(), 20.0*MeV );
  TEST_EQUALITY_CONST( unused_children.size(), 1 );
  TEST_EQUALITY_CONST( unused_children.front(), "dummy" );

  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution F" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution G" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution H" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution I" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution J" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution K" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution L" ) ),
              Utility::PropertyTreeConversionException );
  TEST_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( "Equiprobable Bin Distribution M" ) ),
              Utility::PropertyTreeConversionException );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( UnitAwareEquiprobableBinDistribution,
				   explicit_conversion,
				   IndepUnitA,
				   DepUnitA,
				   IndepUnitB,
				   DepUnitB )
{
  typedef typename Utility::UnitTraits<IndepUnitA>::template GetQuantityType<double>::type IndepQuantityA;
  typedef typename Utility::UnitTraits<typename Utility::UnitTraits<IndepUnitA>::InverseUnit>::template GetQuantityType<double>::type InverseIndepQuantityA;

  typedef typename Utility::UnitTraits<IndepUnitB>::template GetQuantityType<double>::type IndepQuantityB;
  typedef typename Utility::UnitTraits<typename Utility::UnitTraits<IndepUnitB>::InverseUnit>::template GetQuantityType<double>::type InverseIndepQuantityB;

  typedef typename Utility::UnitTraits<DepUnitA>::template GetQuantityType<double>::type DepQuantityA;
  typedef typename Utility::UnitTraits<DepUnitB>::template GetQuantityType<double>::type DepQuantityB;

  // Copy from unitless distribution to distribution type A
  Utility::UnitAwareEquiprobableBinDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareEquiprobableBinDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<Utility::EquiprobableBinDistribution*>( distribution.get() ) );

  // Copy from distribution type A to distribution type B
  Utility::UnitAwareEquiprobableBinDistribution<IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  InverseIndepQuantityA inv_indep_quantity_a =
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 1./16);
  DepQuantityA dep_quantity_a =
    Utility::QuantityTraits<DepQuantityA>::initializeQuantity( 1./16 );

  IndepQuantityB indep_quantity_b( indep_quantity_a );
  InverseIndepQuantityB inv_indep_quantity_b( inv_indep_quantity_a );
  DepQuantityB dep_quantity_b =
    Utility::QuantityTraits<DepQuantityB>::initializeQuantity(
			     Utility::getRawQuantity( inv_indep_quantity_b ) );

  UTILITY_TEST_FLOATING_EQUALITY(
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-15 );

  Utility::setQuantity( indep_quantity_a, 17.0 );
  Utility::setQuantity( inv_indep_quantity_a, 0.0 );
  Utility::setQuantity( dep_quantity_a, 0.0 );

  indep_quantity_b = IndepQuantityB( indep_quantity_a );
  inv_indep_quantity_b = InverseIndepQuantityB( inv_indep_quantity_a );
  dep_quantity_b = DepQuantityB( dep_quantity_a );

  UTILITY_TEST_FLOATING_EQUALITY(
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-15 );
}

typedef si::energy si_energy;
typedef cgs::energy cgs_energy;
typedef si::amount si_amount;
typedef si::length si_length;
typedef cgs::length cgs_length;
typedef si::mass si_mass;
typedef cgs::mass cgs_mass;
typedef si::dimensionless si_dimensionless;
typedef cgs::dimensionless cgs_dimensionless;

TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      si_energy,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      cgs_energy,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      si_energy,
				      si_length,
				      cgs_energy,
				      cgs_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_length,
				      si_energy,
				      si_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      si_energy,
				      si_mass,
				      cgs_energy,
				      cgs_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_mass,
				      si_energy,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      si_energy,
				      si_dimensionless,
				      cgs_energy,
				      cgs_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_dimensionless,
				      si_energy,
				      si_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      si_energy,
				      void,
				      cgs_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      cgs_energy,
				      void,
				      si_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEquiprobableBinDistribution,
				      explicit_conversion,
				      void,
				      MegaElectronVolt,
				      void,
				      KiloElectronVolt );

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_dists_json_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_dists_json_file",
                   &test_dists_json_file_name,
                   "Test distributions json file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Load the property tree from the json file
  test_dists_ptree.reset( new Utility::PropertyTree );

  std::ifstream test_dists_json_file( test_dists_json_file_name );

  test_dists_json_file >> *test_dists_ptree;

  // Initialize the distribution
  std::vector<double> bin_boundaries( 33 );

  bin_boundaries[0] = -16.0;
  bin_boundaries[1] = -15.0;
  bin_boundaries[2] = -14.0;
  bin_boundaries[3] = -13.0;
  bin_boundaries[4] = -12.0;
  bin_boundaries[5] = -11.0;
  bin_boundaries[6] = -10.0;
  bin_boundaries[7] = -9.0;
  bin_boundaries[8] = -8.0;
  bin_boundaries[9] = -7.0;
  bin_boundaries[10] = -6.0;
  bin_boundaries[11] = -5.0;
  bin_boundaries[12] = -4.0;
  bin_boundaries[13] = -3.0;
  bin_boundaries[14] = -2.0;
  bin_boundaries[15] = -0.5;
  bin_boundaries[16] = 0.0;
  bin_boundaries[17] = 0.5;
  bin_boundaries[18] = 2.0;
  bin_boundaries[19] = 3.0;
  bin_boundaries[20] = 4.0;
  bin_boundaries[21] = 5.0;
  bin_boundaries[22] = 6.0;
  bin_boundaries[23] = 7.0;
  bin_boundaries[24] = 8.0;
  bin_boundaries[25] = 9.0;
  bin_boundaries[26] = 10.0;
  bin_boundaries[27] = 11.0;
  bin_boundaries[28] = 12.0;
  bin_boundaries[29] = 13.0;
  bin_boundaries[30] = 14.0;
  bin_boundaries[31] = 15.0;
  bin_boundaries[32] = 16.0;

  tab_distribution.reset(
	  new Utility::EquiprobableBinDistribution( bin_boundaries ) );

  distribution = tab_distribution;

  // Initialize the unit-aware distribution
  std::vector<quantity<KiloElectronVolt> > bin_boundary_quantities( 5 );
  bin_boundary_quantities[0] = 0.0*keV;
  bin_boundary_quantities[1] = 1e2*keV;
  bin_boundary_quantities[2] = 1e3*keV;
  bin_boundary_quantities[3] = 5e3*keV;
  bin_boundary_quantities[4] = 1e4*keV;

  unit_aware_tab_distribution.reset(
   new Utility::UnitAwareEquiprobableBinDistribution<MegaElectronVolt,si::amount>( bin_boundary_quantities ) );

  unit_aware_distribution = unit_aware_tab_distribution;

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstEquiprobableBinDistribution.cpp
//---------------------------------------------------------------------------//
