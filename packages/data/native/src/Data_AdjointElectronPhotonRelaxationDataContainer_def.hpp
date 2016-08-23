//---------------------------------------------------------------------------//
//!
//! \file   Data_AdjointElectronPhotonRelaxationDataContainer_def.hpp
//! \author Luke Kersting
//! \brief  The native adjoint electron-photon-relaxation data container template defs.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_DEF_HPP
#define DATA_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_DEF_HPP

// Boost Includes
#include <boost/serialization/vector.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>

// FRENSIE Includes
#include "Data_DataContainerHelpers.hpp"

namespace Data{

// Save the data to an archive
template<typename Archive>
void AdjointElectronPhotonRelaxationDataContainer::save( Archive& ar,
						  const unsigned version) const
{
  // Notes
  DATA_MAKE_NVP_DEFAULT( ar, notes );

  // Table Data
  DATA_MAKE_NVP_DEFAULT( ar, atomic_number );
  DATA_MAKE_NVP_DEFAULT( ar, min_photon_energy );
  DATA_MAKE_NVP_DEFAULT( ar, max_photon_energy );
  DATA_MAKE_NVP_DEFAULT( ar, min_electron_energy );
  DATA_MAKE_NVP_DEFAULT( ar, max_electron_energy );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_pair_production_energy_dist_norm_constant_evaluation_tol );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_triplet_production_energy_dist_norm_constant_evaluation_tol );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_incoherent_max_energy_nudge_value );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_incoherent_energy_to_max_energy_nudge_value );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_incoherent_evaluation_tol );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_incoherent_grid_convergence_tol );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_incoherent_grid_absolute_diff_tol );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_incoherent_grid_distance_tol );
  DATA_MAKE_NVP_DEFAULT( ar, cutoff_angle_cosine );
  DATA_MAKE_NVP_DEFAULT( ar, number_of_adjoint_moment_preserving_angles );
  DATA_MAKE_NVP_DEFAULT( ar, grid_convergence_tol );
  DATA_MAKE_NVP_DEFAULT( ar, grid_absolute_diff_tol );
  DATA_MAKE_NVP_DEFAULT( ar, grid_distance_tol );

  // Relaxation Data
  DATA_MAKE_NVP_DEFAULT( ar, subshells );
  DATA_MAKE_NVP_DEFAULT( ar, subshell_occupancies );
  DATA_MAKE_NVP_DEFAULT( ar, subshell_binding_energies );

  // Photon Data
  DATA_MAKE_NVP_DEFAULT( ar, compton_profile_momentum_grids );
  DATA_MAKE_NVP_DEFAULT( ar, compton_profiles );
  DATA_MAKE_NVP_DEFAULT( ar, occupation_number_momentum_grids );
  DATA_MAKE_NVP_DEFAULT( ar, occupation_numbers );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_scattering_function_momentum_grid );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_scattering_function );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_atomic_form_factor_momentum_grid );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_atomic_form_factor );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_photon_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_waller_hartree_incoherent_max_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_waller_hartree_incoherent_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_impulse_approx_incoherent_max_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_impulse_approx_incoherent_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_impulse_approx_subshell_incoherent_max_energy_grids );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_impulse_approx_subshell_incoherent_cross_sections );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_coherent_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_waller_hatree_total_max_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_waller_hatree_total_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_impulse_approx_total_max_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_impulse_approx_total_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_total_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, impulse_approx_total_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_pair_production_energy_distribution_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_pair_production_energy_distribution );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_pair_production_norm_constant_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_pair_production_norm_constant );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_triplet_production_energy_distribution_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_triplet_production_energy_distribution );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_triplet_production_norm_constant_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_triplet_production_norm_constant );
  
  // Electron Data
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_angular_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_cutoff_elastic_angles );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_cutoff_elastic_pdf );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_moment_preserving_elastic_discrete_angles );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_moment_preserving_elastic_weights );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_electroionization_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_electroionization_recoil_energy );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_electroionization_recoil_pdf );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_bremsstrahlung_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_bremsstrahlung_photon_energy );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_bremsstrahlung_photon_pdf );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_atomic_excitation_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_atomic_excitation_energy_gain );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_electron_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_cutoff_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_cutoff_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_screened_rutherford_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_screened_rutherford_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_total_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_total_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_moment_preserving_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_moment_preserving_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_electroionization_subshell_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_electroionization_subshell_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_bremsstrahlung_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_bremsstrahlung_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_atomic_excitation_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_atomic_excitation_cross_section_threshold_index );
}

// Load the data from an archive
template<typename Archive>
void AdjointElectronPhotonRelaxationDataContainer::load( Archive& ar,
						  const unsigned version )
{
  // Notes
  DATA_MAKE_NVP_DEFAULT( ar, notes );
  
  // Table Data
  DATA_MAKE_NVP_DEFAULT( ar, atomic_number );
  DATA_MAKE_NVP_DEFAULT( ar, min_photon_energy );
  DATA_MAKE_NVP_DEFAULT( ar, max_photon_energy );
  DATA_MAKE_NVP_DEFAULT( ar, min_electron_energy );
  DATA_MAKE_NVP_DEFAULT( ar, max_electron_energy );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_pair_production_energy_dist_norm_constant_evaluation_tol );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_triplet_production_energy_dist_norm_constant_evaluation_tol );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_incoherent_max_energy_nudge_value );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_incoherent_energy_to_max_energy_nudge_value );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_incoherent_evaluation_tol );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_incoherent_grid_convergence_tol );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_incoherent_grid_absolute_diff_tol );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_incoherent_grid_distance_tol );
  DATA_MAKE_NVP_DEFAULT( ar, cutoff_angle_cosine );
  DATA_MAKE_NVP_DEFAULT( ar, number_of_adjoint_moment_preserving_angles );
  DATA_MAKE_NVP_DEFAULT( ar, grid_convergence_tol );
  DATA_MAKE_NVP_DEFAULT( ar, grid_absolute_diff_tol );
  DATA_MAKE_NVP_DEFAULT( ar, grid_distance_tol );

  // Relaxation Data
  DATA_MAKE_NVP_DEFAULT( ar, subshells );
  DATA_MAKE_NVP_DEFAULT( ar, subshell_occupancies );
  DATA_MAKE_NVP_DEFAULT( ar, subshell_binding_energies );

  // Photon Data
  DATA_MAKE_NVP_DEFAULT( ar, compton_profile_momentum_grids );
  DATA_MAKE_NVP_DEFAULT( ar, compton_profiles );
  DATA_MAKE_NVP_DEFAULT( ar, occupation_number_momentum_grids );
  DATA_MAKE_NVP_DEFAULT( ar, occupation_numbers );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_scattering_function_momentum_grid );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_scattering_function );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_atomic_form_factor_momentum_grid );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_atomic_form_factor );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_photon_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_waller_hartree_incoherent_max_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_waller_hartree_incoherent_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_impulse_approx_incoherent_max_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_impulse_approx_incoherent_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_impulse_approx_subshell_incoherent_max_energy_grids );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_impulse_approx_subshell_incoherent_cross_sections );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_coherent_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_waller_hatree_total_max_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_waller_hatree_total_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_impulse_approx_total_max_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_impulse_approx_total_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, waller_hartree_total_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, impulse_approx_total_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_pair_production_energy_distribution_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_pair_production_energy_distribution );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_pair_production_norm_constant_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_pair_production_norm_constant );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_triplet_production_energy_distribution_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_triplet_production_energy_distribution );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_triplet_production_norm_constant_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_triplet_production_norm_constant );

  // Electron Data
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_angular_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_cutoff_elastic_angles );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_cutoff_elastic_pdf );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_moment_preserving_elastic_discrete_angles );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_moment_preserving_elastic_weights );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_electroionization_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_electroionization_recoil_energy );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_electroionization_recoil_pdf );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_bremsstrahlung_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_bremsstrahlung_photon_energy );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_bremsstrahlung_photon_pdf );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_atomic_excitation_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_atomic_excitation_energy_gain );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_electron_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_cutoff_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_cutoff_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_screened_rutherford_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_screened_rutherford_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_total_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_total_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_moment_preserving_elastic_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_moment_preserving_elastic_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_electroionization_subshell_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_electroionization_subshell_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_bremsstrahlung_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_bremsstrahlung_cross_section_threshold_index );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_atomic_excitation_cross_section );
  DATA_MAKE_NVP_DEFAULT( ar, adjoint_atomic_excitation_cross_section_threshold_index );
}

} // end Data namespace

#endif // end DATA_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_DEF_HPP

//---------------------------------------------------------------------------//
// end Data_AdjointElectronPhotonRelaxationDataContainer_def.hpp
//---------------------------------------------------------------------------//
