//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomicReactionType.hpp
//! \author Luke Kersting
//! \brief  Adjoint electroatomic reaction type enumeration and helper function decls.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTROATOMIC_REACTION_TYPE_HPP
#define MONTE_CARLO_ADJOINT_ELECTROATOMIC_REACTION_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Data_SubshellType.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_TypeTraits.hpp"

namespace MonteCarlo{

/*! The electroatomic reaction type enum.
 *
 * When adding a new type the ToStringTraits methods and the serialization
 * method must be updated.
 */
enum AdjointElectroatomicReactionType{
  TOTAL_ADJOINT_ELECTROATOMIC_REACTION = 1,
  BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION = 2,
  POSITRON_ANNIHILATION_ADJOINT_ELECTROATOMIC_REACTION = 3,
  COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION = 4,
  DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION = 5,
  HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION = 6,
  CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION = 7,
  SCREENED_RUTHERFORD_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION = 8,
  MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION = 9,
  ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION = 10,
  TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 11,
  K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 12,
  L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 13,
  L2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 14,
  L3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 15,
  M1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 16,
  M2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 17,
  M3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 18,
  M4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 19,
  M5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 20,
  N1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 21,
  N2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 22,
  N3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 23,
  N4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 24,
  N5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 25,
  N6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 26,
  N7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 27,
  O1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 28,
  O2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 29,
  O3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 30,
  O4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 31,
  O5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 32,
  O6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 33,
  O7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 34,
  O8_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 35,
  O9_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 36,
  P1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 37,
  P2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 38,
  P3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 39,
  P4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 40,
  P5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 41,
  P6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 42,
  P7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 43,
  P8_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 44,
  P9_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 45,
  P10_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 46,
  P11_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 47,
  Q1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 48,
  Q2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 49,
  Q3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION = 50
};

//! Convert a Data::SubshellType enum to a AdjointElectroatomicReactionType enum
AdjointElectroatomicReactionType
convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum(
                                           const Data::SubshellType subshell );

} // end MonteCarlo namespace

namespace Utility{

/*! \brief Specialization of Utility::ToStringTraits for
 * MonteCarlo::AdjointElectroatomicReactionType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<MonteCarlo::AdjointElectroatomicReactionType>
{
  //! Convert a MonteCarlo::AdjointElectroatomicReactionType to a string
  static std::string toString( const MonteCarlo::AdjointElectroatomicReactionType type );

  //! Place the MonteCarlo::AdjointElectroatomicReactionType in a stream
  static void toStream( std::ostream& os, const MonteCarlo::AdjointElectroatomicReactionType type );
};

/*! Specialization of Utility::IsHashable for MonteCarlo::AdjointElectroatomicReactionType
 * \ingroup type_traits
 */
template<>
struct IsHashable<MonteCarlo::AdjointElectroatomicReactionType> : public std::true_type
{ /* ... */ };

} // end Utility namespace

namespace std{

//! Stream operator for printing MonteCarlo::AdjointElectroatomicReactionType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const MonteCarlo::AdjointElectroatomicReactionType reaction )
{
  os << Utility::toString( reaction );
  return os;
}

//! Specialization of std::hash for MonteCarlo::AdjointElectroatomicReactionType
template<>
struct hash<MonteCarlo::AdjointElectroatomicReactionType> : public hash<unsigned>
{ /* ... */ };

} // end std namespace

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOMIC_REACTION_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomicReactionType.hpp
//---------------------------------------------------------------------------//


