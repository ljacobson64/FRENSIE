//---------------------------------------------------------------------------//
//!
//! \file   tstElectroatom.cpp
//! \author Luke Kersting
//! \brief  Electroatom unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_Electroatom.hpp"
#include "MonteCarlo_ElectroatomACEFactory.hpp"
#include "MonteCarlo_AtomicExcitationElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_VoidAbsorptionElectroatomicReaction.hpp"
#include "MonteCarlo_VoidAtomicRelaxationModel.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::Electroatom> ace_electroatom,
  native_electroatom,
  epr14_electroatom;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
bool notEqualZero( double value )
{
  return value != 0.0;
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the scattering reaction types can be returned
FRENSIE_UNIT_TEST( Electroatom, getScatteringReactionTypes )
{
  const boost::unordered_set<MonteCarlo::ElectroatomicReactionType>&
    scattering_types = MonteCarlo::Electroatom::getScatteringReactionTypes();

  FRENSIE_CHECK( scattering_types.count(
               MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::L2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::L3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::M1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::M2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::M3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::M4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::M5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::N1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::N2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::N3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::N4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::N5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::N6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::N7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::O1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::O2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::O3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::O4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::O5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::O6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::O7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::O8_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::O9_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::P1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::P2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::P4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::P5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::P6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::P7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::P8_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::P9_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::P10_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::P11_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::Q1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::Q2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
        MonteCarlo::Q3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION ) );

  FRENSIE_CHECK( scattering_types.count(
               MonteCarlo::COUPLED_ELASTIC_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
               MonteCarlo::HYBRID_ELASTIC_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
               MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
               MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
               MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
               MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_types.count(
               MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the electroatom atom name can be returned
FRENSIE_UNIT_TEST( Electroatom, getAtomName_ace )
{
  FRENSIE_CHECK_EQUAL( ace_electroatom->getAtomName(), "82000.12p" );
}

//---------------------------------------------------------------------------//
// Check that the electroatom atom name can be returned
FRENSIE_UNIT_TEST( Electroatom, getAtomName_native )
{
  FRENSIE_CHECK_EQUAL( native_electroatom->getAtomName(), "Pb" );
}

//---------------------------------------------------------------------------//
// Check that the electroatom nuclide name can be returned
FRENSIE_UNIT_TEST( Electroatom, getNuclideName_ace )
{
  FRENSIE_CHECK_EQUAL( ace_electroatom->getNuclideName(), "82000.12p" );
}

//---------------------------------------------------------------------------//
// Check that the electroatom nuclide name can be returned
FRENSIE_UNIT_TEST( Electroatom, getNuclideName_native )
{
  FRENSIE_CHECK_EQUAL( native_electroatom->getNuclideName(), "Pb" );
}

//---------------------------------------------------------------------------//
// Check that the electroatom atomic number can be returned
FRENSIE_UNIT_TEST( Electroatom, getAtomicNumber_ace )
{
  FRENSIE_CHECK_EQUAL( ace_electroatom->getAtomicNumber(), 82 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom atomic number can be returned
FRENSIE_UNIT_TEST( Electroatom, getAtomicNumber_native )
{
  FRENSIE_CHECK_EQUAL( native_electroatom->getAtomicNumber(), 82 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom atomic mass number can be returned
FRENSIE_UNIT_TEST( Electroatom, getAtomicMassNumber_ace )
{
  FRENSIE_CHECK_EQUAL( ace_electroatom->getAtomicMassNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom atomic mass number can be returned
FRENSIE_UNIT_TEST( Electroatom, getAtomicMassNumber_native )
{
  FRENSIE_CHECK_EQUAL( native_electroatom->getAtomicMassNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom isomer number can be returned
FRENSIE_UNIT_TEST( Electroatom, getIsomerNumber_ace )
{
  FRENSIE_CHECK_EQUAL( ace_electroatom->getIsomerNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom isomer number can be returned
FRENSIE_UNIT_TEST( Electroatom, getIsomerNumber_native )
{
  FRENSIE_CHECK_EQUAL( native_electroatom->getIsomerNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom atomic weight can be returned
FRENSIE_UNIT_TEST( Electroatom, getAtomicWeight_ace )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( ace_electroatom->getAtomicWeight(),
                          207.1999470456033,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom atomic weight can be returned
FRENSIE_UNIT_TEST( Electroatom, getAtomicWeight_native )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( native_electroatom->getAtomicWeight(),
                          207.1999470456033,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom temperature can be returned
FRENSIE_UNIT_TEST( Electroatom, getTemperature_ace )
{
  FRENSIE_CHECK_EQUAL( ace_electroatom->getTemperature(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the electroatom temperature can be returned
FRENSIE_UNIT_TEST( Electroatom, getTemperature_native )
{
  FRENSIE_CHECK_EQUAL( native_electroatom->getTemperature(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the total cross section can be returned
FRENSIE_UNIT_TEST( Electroatom, getTotalCrossSection_ace )
{
  double cross_section =
    ace_electroatom->getTotalCrossSection( 2e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          9.258661418255E+03 + 1.96517E+08,
                          1e-12 );
  cross_section =
    ace_electroatom->getTotalCrossSection( 4e-4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          8.914234996439E+03 + 6.22682E+08,
                          1e-12 );
  cross_section =
    ace_electroatom->getTotalCrossSection( 9E-05 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          7.249970966838E+03 + 1.16042E+09,
                          1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the total cross section can be returned
FRENSIE_UNIT_TEST( Electroatom, getTotalCrossSection_native )
{
  double cross_section =
    native_electroatom->getTotalCrossSection( 2e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          9.2586614182549074e+03 + 1.96517E+08,
                          1e-12 );
  cross_section =
    native_electroatom->getTotalCrossSection( 4e-4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          8.9142349964387486e+03 + 6.22682E+08,
                          1e-12 );
  cross_section =
    native_electroatom->getTotalCrossSection( 9e-5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          7.2499709668376108e+03 + 1.16042E+09,
                          1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the total cross section can be returned
FRENSIE_UNIT_TEST( Electroatom, getTotalCrossSection_epr14 )
{
  double cross_section =
    epr14_electroatom->getTotalCrossSection( 5.2371421547030929e-02 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.4981484456753917e+07, 1e-12 );

  cross_section = epr14_electroatom->getTotalCrossSection( 2e-03 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.9416460301500607e+08, 1e-12 );

  cross_section = epr14_electroatom->getTotalCrossSection( 4e-04 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.1706481556832719e+08, 1e-12 );

  cross_section = epr14_electroatom->getTotalCrossSection( 9e-05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.5083218251907730e+09, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption cross section can be returned
FRENSIE_UNIT_TEST( Electroatom, getAbsorptionCrossSection_ace )
{
  double cross_section =
    ace_electroatom->getAbsorptionCrossSection( 1.000000000E-02 );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =
    ace_electroatom->getAbsorptionCrossSection( 2e-3 );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =
    ace_electroatom->getAbsorptionCrossSection( 4e-4 );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =
    ace_electroatom->getAbsorptionCrossSection( 9e-5 );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the absorption cross section can be returned
FRENSIE_UNIT_TEST( Electroatom, getAbsorptionCrossSection_native )
{
  double cross_section =
    native_electroatom->getAbsorptionCrossSection( 1.000000000E-02 );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =
    native_electroatom->getAbsorptionCrossSection( 2e-3 );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =
    native_electroatom->getAbsorptionCrossSection( 4e-4 );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =
    native_electroatom->getAbsorptionCrossSection( 9e-5 );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
FRENSIE_UNIT_TEST( Electroatom, getSurvivalProbability_ace )
{
  double survival_prob =
    ace_electroatom->getSurvivalProbability( 2e-3 );

   FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );

  survival_prob =
    ace_electroatom->getSurvivalProbability( 4e-4 );

   FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );

  survival_prob =
    ace_electroatom->getSurvivalProbability( 9e-5 );

   FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
FRENSIE_UNIT_TEST( Electroatom, getSurvivalProbability_native )
{
  double survival_prob =
    native_electroatom->getSurvivalProbability( 2e-3 );

   FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );

  survival_prob =
    native_electroatom->getSurvivalProbability( 4e-4 );

   FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );

  survival_prob =
    native_electroatom->getSurvivalProbability( 9e-5 );

   FRENSIE_CHECK_EQUAL( survival_prob, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction cross section can be returned
FRENSIE_UNIT_TEST( Electroatom, getReactionCrossSection_ace )
{
  // Total Electroionization
  double cross_section = ace_electroatom->getReactionCrossSection(
                   1.000000000000E-02,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = ace_electroatom->getReactionCrossSection(
                   2e-3,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = ace_electroatom->getReactionCrossSection(
                   4e-4,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = ace_electroatom->getReactionCrossSection(
                   9e-5,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Atomic Excitation
  cross_section = ace_electroatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96517E+08, 1e-12 );

  cross_section = ace_electroatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.22682E+08, 1e-12 );

  cross_section = ace_electroatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.16042E+09, 1e-12 );

  // Bremsstrahlung
  cross_section = ace_electroatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.258661418255E+03, 1e-12 );

  cross_section = ace_electroatom->getReactionCrossSection(
                    4e-4,
                 MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.914234996439E+03, 1e-12 );

  cross_section = ace_electroatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.249970966838E+03, 1e-12 );

  // Coupled Elastic
  cross_section = ace_electroatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::COUPLED_ELASTIC_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = ace_electroatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::COUPLED_ELASTIC_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = ace_electroatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::COUPLED_ELASTIC_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Cutoff Elastic
  cross_section = ace_electroatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = ace_electroatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = ace_electroatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Total
  cross_section = ace_electroatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::TOTAL_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          9.258661418255E+03 + 1.96517E+08,
                          1e-12 );

  cross_section = ace_electroatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::TOTAL_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          8.914234996439E+03 + 6.22682E+08,
                          1e-12 );

  cross_section = ace_electroatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::TOTAL_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          7.249970966838E+03 + 1.16042E+09,
                          1e-12 );

  // Absorption
  cross_section = ace_electroatom->getReactionCrossSection(
                    1.000000000000E-02,
                    MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =ace_electroatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = ace_electroatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = ace_electroatom->getReactionCrossSection(
                    9e-5,
               MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction cross section can be returned
FRENSIE_UNIT_TEST( Electroatom, getReactionCrossSection_native )
{
  // Total Electroionization
  double cross_section = native_electroatom->getReactionCrossSection(
                   1.000000000000E-02,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = native_electroatom->getReactionCrossSection(
                   2e-3,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = native_electroatom->getReactionCrossSection(
                   4e-4,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = native_electroatom->getReactionCrossSection(
                   9e-5,
                   MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

   FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Atomic Excitation
  cross_section = native_electroatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96517E+08, 1e-12 );

  cross_section = native_electroatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.22682E+08, 1e-12 );

  cross_section = native_electroatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.16042E+09, 1e-12 );

  // Bremsstrahlung
  cross_section = native_electroatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.2586614182549074e+03, 1e-12 );

  cross_section = native_electroatom->getReactionCrossSection(
                    4e-4,
                 MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.9142349964387486e+03, 1e-12 );

  cross_section = native_electroatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.2499709668376108e+03, 1e-12 );

  // Cutoff Elastic
  cross_section = native_electroatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = native_electroatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = native_electroatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Total
  cross_section = native_electroatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::TOTAL_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          9.2586614182549074e+03 + 1.96517E+08,
                          1e-12 );

  cross_section = native_electroatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::TOTAL_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          8.9142349964387486e+03 + 6.22682E+08,
                          1e-12 );

  cross_section = native_electroatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::TOTAL_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          7.2499709668376108e+03 + 1.16042E+09,
                          1e-12 );

  // Absorption
  cross_section = native_electroatom->getReactionCrossSection(
                    1.000000000000E-02,
                    MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =native_electroatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = native_electroatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = native_electroatom->getReactionCrossSection(
                    9e-5,
               MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that an analogue collision with the atom can be modeled
FRENSIE_UNIT_TEST( Electroatom, collideAnalogue )
{
  std::shared_ptr<MonteCarlo::ElectronState> electron(
                        new MonteCarlo::ElectronState( 0 ) );
  electron->setEnergy( 20 );
  electron->setDirection( 0.0, 0.0, 1.0 );
  electron->setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // choose scattering rxn

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ace_electroatom->collideAnalogue( *electron, bank );

  FRENSIE_CHECK( !electron->isGone() );
  FRENSIE_CHECK_EQUAL( electron->getWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a survival biased collision with the atom can be modeled
FRENSIE_UNIT_TEST( Electroatom, collideSurvivalBias )
{
  std::shared_ptr<MonteCarlo::ElectronState> electron(
                        new MonteCarlo::ElectronState( 0 ) );
  electron->setEnergy( 1 );
  electron->setDirection( 0.0, 0.0, 1.0 );
  electron->setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  ace_electroatom->collideSurvivalBias( *electron, bank );

  FRENSIE_CHECK( !electron->isGone() );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );

  // reset the particle
  electron.reset( new MonteCarlo::ElectronState( 0 ) );
  electron->setEnergy( 1 );
  electron->setDirection( 0.0, 0.0, 1.0 );
  electron->setWeight( 1.0 );

  ace_electroatom->collideSurvivalBias( *electron, bank );

  FRENSIE_CHECK( !electron->isGone() );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron->getWeight(), 1.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the atom can be relaxed
FRENSIE_UNIT_TEST( Electroatom, relaxAtom )
{
  std::shared_ptr<MonteCarlo::ElectronState> electron(
                                          new MonteCarlo::ElectronState( 0 ) );
  electron->setEnergy( exp( -1.214969212306E+01 ) );
  electron->setDirection( 0.0, 0.0, 1.0 );
  electron->setWeight( 1.0 );

  Data::SubshellType vacancy = Data::K_SUBSHELL;
  MonteCarlo::ParticleBank bank;

  ace_electroatom->relaxAtom( vacancy, *electron, bank );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that a electroatom can be constructed from a core
FRENSIE_UNIT_TEST( Electroatom, core_constructor )
{
  MonteCarlo::Electroatom electroatom_copy( ace_electroatom->getAtomName(),
                                            ace_electroatom->getAtomicNumber(),
                                            ace_electroatom->getAtomicWeight(),
                                            ace_electroatom->getCore() );

  FRENSIE_CHECK_EQUAL( electroatom_copy.getAtomName(),
         ace_electroatom->getAtomName() );
  FRENSIE_CHECK_EQUAL( electroatom_copy.getNuclideName(),
         ace_electroatom->getNuclideName() );
  FRENSIE_CHECK_EQUAL( electroatom_copy.getAtomicNumber(),
         ace_electroatom->getAtomicNumber() );
  FRENSIE_CHECK_EQUAL( electroatom_copy.getAtomicMassNumber(),
         ace_electroatom->getAtomicMassNumber() );
  FRENSIE_CHECK_EQUAL( electroatom_copy.getIsomerNumber(),
         ace_electroatom->getIsomerNumber() );
  FRENSIE_CHECK_EQUAL( electroatom_copy.getAtomicWeight(),
         ace_electroatom->getAtomicWeight() );
  FRENSIE_CHECK_EQUAL( electroatom_copy.getTemperature(),
         ace_electroatom->getTemperature() );

  FRENSIE_CHECK_EQUAL( electroatom_copy.getTotalCrossSection( 1e-3 ),
         ace_electroatom->getTotalCrossSection( 1e-3 ) );
  FRENSIE_CHECK_EQUAL( electroatom_copy.getTotalCrossSection( 20.0 ),
         ace_electroatom->getTotalCrossSection( 20.0 ) );
  FRENSIE_CHECK_EQUAL( electroatom_copy.getAbsorptionCrossSection( 1e-3 ),
         ace_electroatom->getAbsorptionCrossSection( 1e-3 ) );
  FRENSIE_CHECK_EQUAL( electroatom_copy.getAbsorptionCrossSection( 20.0 ),
         ace_electroatom->getAbsorptionCrossSection( 20.0 ) );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name, test_ace_table_name, test_native_file_name,
            test_epr14_file_name, test_epr14_table_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file",
                                        test_ace_file_name, "",
                                        "Test ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_table",
                                        test_ace_table_name, "",
                                        "Test ACE table name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_file",
                                        test_native_file_name, "",
                                        "Test Native file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_epr14_file",
                                        test_epr14_file_name, "",
                                        "Test EPR14 file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_epr14_table",
                                        test_epr14_table_name, "",
                                        "Test EPR14 table name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  {
    // Create a file handler and data extractor
    std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
                 new Data::ACEFileHandler( test_ace_file_name,
                                           test_ace_table_name,
                                           1u ) );
    std::shared_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor(
                      ace_file_handler->getTableNXSArray(),
                      ace_file_handler->getTableJXSArray(),
                      ace_file_handler->getTableXSSArray() ) );

    // Create the atomic excitation, bremsstrahlung cross sections
    std::shared_ptr<const std::vector<double> > energy_grid(
       new std::vector<double>( xss_data_extractor->extractElectronEnergyGrid() ) );

    // Create the hash-based grid searcher
    std::shared_ptr<Utility::HashBasedGridSearcher<double> > grid_searcher(
       new Utility::StandardHashBasedGridSearcher<std::vector<double>,false>(
                         energy_grid,
                         energy_grid->front(),
                         energy_grid->back(),
                         100 ) );

    Utility::ArrayView<const double> raw_ae_cross_section =
      xss_data_extractor->extractExcitationCrossSection();

    Utility::ArrayView<const double>::iterator start =
      std::find_if( raw_ae_cross_section.begin(),
            raw_ae_cross_section.end(),
            notEqualZero );

    std::shared_ptr<const std::vector<double> > ae_cross_section(
                new std::vector<double>( start, raw_ae_cross_section.end() ) );

    size_t ae_threshold_index =
      energy_grid->size() - ae_cross_section->size();

    // Extract the atomic excitation information data block (EXCIT)
    Utility::ArrayView<const double> excit_block(
                      xss_data_extractor->extractEXCITBlock() );

    // Extract the number of tabulated energies
    int size = excit_block.size()/2;

    // Extract the energy grid for atomic excitation energy loss
    std::vector<double> ae_energy_grid(excit_block(0,size));

    // Extract the energy loss for atomic excitation
    std::vector<double> energy_loss(excit_block(size,size));

    // Create the energy loss distributions
    MonteCarlo::AtomicExcitationElectronScatteringDistribution::AtomicDistribution
     ae_energy_loss_function;

    ae_energy_loss_function.reset(
      new Utility::TabularDistribution<Utility::LinLin>( ae_energy_grid,
                                                         energy_loss ) );

    std::shared_ptr<const MonteCarlo::AtomicExcitationElectronScatteringDistribution>
                      ae_energy_loss_distribution;

    ae_energy_loss_distribution.reset(
    new MonteCarlo::AtomicExcitationElectronScatteringDistribution(
                      ae_energy_loss_function ) );

    std::shared_ptr<MonteCarlo::ElectroatomicReaction> ae_reaction(
        new MonteCarlo::AtomicExcitationElectroatomicReaction<Utility::LinLin>(
                energy_grid,
                ae_cross_section,
                ae_threshold_index,
                ae_energy_loss_distribution ) );

    Utility::ArrayView<const double> raw_b_cross_section =
      xss_data_extractor->extractBremsstrahlungCrossSection();

    start = std::find_if( raw_b_cross_section.begin(),
                          raw_b_cross_section.end(),
                          notEqualZero );

    std::shared_ptr<const std::vector<double> > b_cross_section(
                 new std::vector<double>( start, raw_b_cross_section.end() ) );

    size_t b_threshold_index =
      energy_grid->size() - b_cross_section->size();

    std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
        b_scattering_distribution;

    MonteCarlo::BremsstrahlungElectronScatteringDistributionACEFactory::createBremsstrahlungDistribution(
        xss_data_extractor->extractAtomicNumber(),
        *xss_data_extractor,
        b_scattering_distribution );

    // Create the scattering distributions
    std::shared_ptr<MonteCarlo::ElectroatomicReaction> b_reaction(
        new MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin>(
                energy_grid,
                b_cross_section,
                b_threshold_index,
                b_scattering_distribution ) );

    // Create the reaction maps
    MonteCarlo::ElectroatomCore::ConstReactionMap scattering_reactions,
      absorption_reactions;

    scattering_reactions[ae_reaction->getReactionType()] = ae_reaction;

    scattering_reactions[b_reaction->getReactionType()] = b_reaction;

    // Create a void atomic relaxation model
    std::shared_ptr<MonteCarlo::AtomicRelaxationModel> relaxation_model(
                   new MonteCarlo::VoidAtomicRelaxationModel );

    // Extract the atomic weight
    double atomic_weight = ace_file_handler->getTableAtomicWeightRatio()*
      Utility::PhysicalConstants::neutron_rest_mass_amu;

    // Create a test electroatom
    ace_electroatom.reset(
           new MonteCarlo::Electroatom(
                    ace_file_handler->getTableName(),
                    xss_data_extractor->extractAtomicNumber(),
                    atomic_weight,
                    energy_grid,
                    grid_searcher,
                    scattering_reactions,
                    absorption_reactions,
                    relaxation_model,
                    false,
                    Utility::LinLin() ) );
  }

  // Create the Native electroatom core
  {
    // Create the native data file container
    Data::ElectronPhotonRelaxationDataContainer data_container(
        test_native_file_name );

    // Create the atomic excitation, bremsstrahlung cross sections
    std::shared_ptr<const std::vector<double> > energy_grid(
       new std::vector<double>( data_container.getElectronEnergyGrid() ) );

    // Create the hash-based grid searcher
    std::shared_ptr<Utility::HashBasedGridSearcher<double> > grid_searcher(
       new Utility::StandardHashBasedGridSearcher<std::vector<double>,false>(
                         energy_grid,
                         energy_grid->front(),
                         energy_grid->back(),
                         100 ) );

    // Atomic Excitation cross section
    std::shared_ptr<const std::vector<double> > ae_cross_section(
       new std::vector<double>( data_container.getAtomicExcitationCrossSection() ) );

    size_t ae_threshold_index =
        data_container.getAtomicExcitationCrossSectionThresholdEnergyIndex();

    // Create the energy loss distributions
    MonteCarlo::AtomicExcitationElectronScatteringDistribution::AtomicDistribution
        ae_energy_loss_function(
            new Utility::TabularDistribution<Utility::LogLog>(
                data_container.getAtomicExcitationEnergyGrid(),
                data_container.getAtomicExcitationEnergyLoss() ) );

    std::shared_ptr<const MonteCarlo::AtomicExcitationElectronScatteringDistribution>
        ae_energy_loss_distribution(
            new MonteCarlo::AtomicExcitationElectronScatteringDistribution(
                      ae_energy_loss_function ) );

    std::shared_ptr<MonteCarlo::ElectroatomicReaction> ae_reaction(
        new MonteCarlo::AtomicExcitationElectroatomicReaction<Utility::LogLog>(
            energy_grid,
            ae_cross_section,
            ae_threshold_index,
            grid_searcher,
            ae_energy_loss_distribution ) );


    // Bremsstrahlung cross section
    std::shared_ptr<const std::vector<double> > b_cross_section(
       new std::vector<double>( data_container.getBremsstrahlungCrossSection() ) );

    size_t b_threshold_index =
        data_container.getBremsstrahlungCrossSectionThresholdEnergyIndex();


    // Get the energy grid for bremsstrahlung energy distributions
    const std::vector<double>& b_energy_grid =
        data_container.getBremsstrahlungEnergyGrid();

    std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
      secondary_dists( b_energy_grid.size() );

    for( unsigned n = 0; n < b_energy_grid.size(); ++n )
    {
      // Get the energy of the bremsstrahlung photon at the incoming energy
      std::vector<double> photon_energy(
        data_container.getBremsstrahlungPhotonEnergy( b_energy_grid[n] ) );

      // Get the bremsstrahlung photon pdf at the incoming energy
      std::vector<double> pdf(
        data_container.getBremsstrahlungPhotonPDF( b_energy_grid[n] ) );

      secondary_dists[n].reset(
        new const Utility::TabularDistribution<Utility::LinLin>( photon_energy,
                                                                 pdf ) );
    }

    // Create the scattering function
    std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> b_energy_loss_function(
       new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBaseCorrelated<Utility::LogLogLog> >(
                                                           b_energy_grid,
                                                           secondary_dists ) );

    std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
        b_scattering_distribution(
            new MonteCarlo::BremsstrahlungElectronScatteringDistribution(
                data_container.getAtomicNumber(),
                b_energy_loss_function ) );


    // Create the bremsstrahlung scattering reaction
    std::shared_ptr<MonteCarlo::ElectroatomicReaction> b_reaction(
        new MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LogLog>(
            energy_grid,
            b_cross_section,
            b_threshold_index,
            b_scattering_distribution ) );

    // Create the reaction maps
    MonteCarlo::ElectroatomCore::ConstReactionMap scattering_reactions,
      absorption_reactions;

    scattering_reactions[ae_reaction->getReactionType()] = ae_reaction;

    scattering_reactions[b_reaction->getReactionType()] = b_reaction;

    // Create a void atomic relaxation model
    std::shared_ptr<MonteCarlo::AtomicRelaxationModel> relaxation_model(
                   new MonteCarlo::VoidAtomicRelaxationModel );

    // Create a test electroatom
    native_electroatom.reset(
           new MonteCarlo::Electroatom(
                    "Pb",
                    data_container.getAtomicNumber(),
                    207.1999470456033,
                    energy_grid,
                    grid_searcher,
                    scattering_reactions,
                    absorption_reactions,
                    relaxation_model,
                    false,
                    Utility::LogLog() ) );
  }

  {
    // Create a file handler and data extractor
    std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
                 new Data::ACEFileHandler( test_epr14_file_name,
                                           test_epr14_table_name,
                                           1u ) );
    std::shared_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor(
                      ace_file_handler->getTableNXSArray(),
                      ace_file_handler->getTableJXSArray(),
                      ace_file_handler->getTableXSSArray() ) );

    // Create a void atomic relaxation model
    std::shared_ptr<MonteCarlo::AtomicRelaxationModel> relaxation_model(
                   new MonteCarlo::VoidAtomicRelaxationModel );

    // Extract the atomic weight
    double atomic_weight = ace_file_handler->getTableAtomicWeightRatio()*
      Utility::PhysicalConstants::neutron_rest_mass_amu;

    // Create the simulation properties
    MonteCarlo::SimulationElectronProperties properties;

    std::shared_ptr<const MonteCarlo::ElectroatomCore> core;

    MonteCarlo::ElectroatomACEFactory::createElectroatomCore(
                                                  *xss_data_extractor,
                                                  relaxation_model,
                                                  properties,
                                                  core );

  // Create the electroatom
  epr14_electroatom.reset(
    new MonteCarlo::Electroatom( ace_file_handler->getTableName(),
                                 xss_data_extractor->extractAtomicNumber(),
                                 atomic_weight,
                                 *core ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroatom.cpp
//---------------------------------------------------------------------------//

