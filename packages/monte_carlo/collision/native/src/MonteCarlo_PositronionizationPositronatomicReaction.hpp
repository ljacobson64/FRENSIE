//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronionizationPositronatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The electroionization electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRONIONIZATION_POSITRONATOMIC_REACTION_HPP
#define MONTE_CARLO_POSITRONIONIZATION_POSITRONATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PositronatomicReaction.hpp"
#include "MonteCarlo_StandardGenericAtomicReaction.hpp"

namespace MonteCarlo{

/*! The electroionization electroatomic reaction class
* \details This class should be used to represent the total electroionization
* reaction and not the reaction with individual subshells.
*/

template<typename InterpPolicy, bool processed_cross_section = false>
class PositronionizationPositronatomicReaction : public StandardGenericAtomicReaction<PositronatomicReaction,InterpPolicy,processed_cross_section>
{

private:

  // Typedef for the base class type
typedef StandardGenericAtomicReaction<PositronatomicReaction,InterpPolicy,processed_cross_section>
    BaseType;

public:

  //! Basic Constructor
  PositronionizationPositronatomicReaction(
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index );

  //! Constructor
  PositronionizationPositronatomicReaction(
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher );


  //! Destructor
  ~PositronionizationPositronatomicReaction()
  { /* ... */ }

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const;

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return the differential cross section
  double getDifferentialCrossSection( const double incoming_energy,
                                      const double outgoing_energy ) const;

  //! Return the reaction type
  PositronatomicReactionType getReactionType() const;

  //! Simulate the reaction
  void react( PositronState& electron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_PositronionizationPositronatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_POSITRONIONIZATION_POSITRONATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronionizationPositronatomicReaction.hpp
//---------------------------------------------------------------------------//