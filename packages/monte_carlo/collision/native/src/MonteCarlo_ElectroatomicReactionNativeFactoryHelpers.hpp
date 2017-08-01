//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReactionNativeFactoryHelpers.hpp
//! \author Luke Kersting
//! \brief  The electroatomic reaction native factory helpers declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOMIC_REACTION_NATIVE_FACTORY_HELPERS_HPP
#define MONTE_CARLO_ELECTROATOMIC_REACTION_NATIVE_FACTORY_HELPERS_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_AnalogElasticElectroatomicReaction.hpp"

namespace MonteCarlo{

//----------------------------------------------------------------------------//
//      ****ELASTIC REACTIONS****
//----------------------------------------------------------------------------//

//! Create an analog elastic scattering electroatomic reaction
std::shared_ptr<ElectroatomicReaction>
createAnalogElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const bool linlinlog_interpolation_mode_on,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

//! Create a hybrid elastic scattering electroatomic reaction
std::shared_ptr<ElectroatomicReaction>
createHybridElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const double cutoff_angle_cosine,
    const bool linlinlog_interpolation_mode_on,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

//! Create an cutoff elastic scattering electroatomic reaction
std::shared_ptr<ElectroatomicReaction>
createCutoffElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const double cutoff_angle_cosine,
    const bool linlinlog_interpolation_mode_on,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

//! Create a screened Rutherford elastic scattering electroatomic reaction
std::shared_ptr<ElectroatomicReaction>
createScreenedRutherfordElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const double cutoff_angle_cosine,
    const bool linlinlog_interpolation_mode_on,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

//! Create the moment preserving elastic scattering electroatomic reaction
std::shared_ptr<ElectroatomicReaction>
createMomentPreservingElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const double cutoff_angle_cosine,
    const bool linlinlog_interpolation_mode_on,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

//----------------------------------------------------------------------------//
//      ****ATOMIC EXCITATION DISTRIBUTION****
//----------------------------------------------------------------------------//

//! Create an atomic excitation scattering electroatomic reaction
std::shared_ptr<ElectroatomicReaction>
createAtomicExcitationReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data );

//----------------------------------------------------------------------------//
//      ****ELECTROIONIZATION SUBSHELL REACTIONS****
//----------------------------------------------------------------------------//

//! Create the subshell electroionization electroatomic reaction
std::shared_ptr<ElectroatomicReaction>
createSubshellElectroionizationReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const unsigned subshell,
    const bool linlinlog_interpolation_mode_on,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol );

//! Create the subshell electroionization electroatomic reactions
std::vector<std::shared_ptr<ElectroatomicReaction> >
createSubshellElectroionizationReactions(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const bool linlinlog_interpolation_mode_on,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol );

//----------------------------------------------------------------------------//
//      ****BREMSSTRAHLUNG REACTIONS****
//----------------------------------------------------------------------------//

//! Create the bremsstrahlung electroatomic reaction
std::shared_ptr<ElectroatomicReaction>
createBremsstrahlungReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const bool dipole_distribution_mode_on,
    const bool linlinlog_interpolation_mode_on,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROATOMIC_REACTION_NATIVE_FACTORY_HELPERS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomicReactionNativeFactoryHelpers.hpp
//---------------------------------------------------------------------------//