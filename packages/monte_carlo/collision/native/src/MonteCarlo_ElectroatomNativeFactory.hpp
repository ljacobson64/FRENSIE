//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The electroatom native factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOM_NATIVE_FACTORY_HPP
#define MONTE_CARLO_ELECTROATOM_NATIVE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_Electroatom.hpp"
#include "MonteCarlo_ElectroatomCore.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_SimulationElectronProperties.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"

namespace MonteCarlo{

//! The Electroatomic factory class that uses Native data
class ElectroatomNativeFactory
{

public:

  using ThisType = ElectroatomNativeFactory;

  //! Create a electroatom core (using the provided atomic relaxation model)
  template <typename TwoDInterpPolicy = Utility::LogLogLog,
            typename TwoDSamplePolicy = Utility::UnitBaseCorrelated>
  static void createElectroatomCore(
       const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
       const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
       const SimulationElectronProperties& properties,
       Teuchos::RCP<ElectroatomCore>& electroatom_core );

  //! Create a electroatom (using the provided atomic relaxation model)
  static void createElectroatom(
       const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
       const std::string& electroatom_name,
       const double atomic_weight,
       const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
       const SimulationElectronProperties& properties,
       Teuchos::RCP<Electroatom>& electroatom );

private:

  //! Create the elastic reaction for a electroatom core
  template <typename TwoDInterpPolicy = Utility::LogLogLog,
            typename TwoDSamplePolicy = Utility::Correlated>
  static void createElasticElectroatomCore(
        const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
        const Teuchos::ArrayRCP<const double>& energy_grid,
        const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
        const SimulationElectronProperties& properties,
        Electroatom::ReactionMap& scattering_reactions );

  // Constructor
  ElectroatomNativeFactory();
};

} // end MonteCarlo

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ElectroatomNativeFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ELECTROATOM_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomNativeFactory.hpp
//---------------------------------------------------------------------------//
