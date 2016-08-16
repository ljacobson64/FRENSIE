//---------------------------------------------------------------------------//
//!
//! \file   Data_ElectronPhotonRelaxationDataContainer.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The native electron-photon-relaxation data container class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_HPP
#define DATA_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_HPP

// Std Lib Includes
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <string>

// Boost Includes
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Utility_StandardArchivableObject.hpp"
#include "Utility_StandardSerializableObject.hpp"

namespace Data{

/*! The electron-photon-relaxation data container
 * \details Linear-linear interpolation should be used for all data.
 */
class ElectronPhotonRelaxationDataContainer : public Utility::StandardArchivableObject<ElectronPhotonRelaxationDataContainer,false>, public Utility::StandardSerializableObject<ElectronPhotonRelaxationDataContainer,false>
{

public:

  //! Constructor (from saved archive)
  ElectronPhotonRelaxationDataContainer(
		  const std::string& archive_name,
                  const Utility::ArchivableObject::ArchiveType archive_type =
		  Utility::ArchivableObject::XML_ARCHIVE );

  //! Destructor
  virtual ~ElectronPhotonRelaxationDataContainer()
  { /* ... */ }

//---------------------------------------------------------------------------//
// GET TABLE DATA
//---------------------------------------------------------------------------//

  //! Return the atomic number
  unsigned getAtomicNumber() const;

  //! Return the minimum photon energy
  double getMinPhotonEnergy() const;

  //! Return the maximum photon energy
  double getMaxPhotonEnergy() const;

  //! Return the minimum electron energy
  double getMinElectronEnergy() const;

  //! Return the maximum electron energy
  double getMaxElectronEnergy() const;

  //! Return the occupation number evaluation tolerance
  double getOccupationNumberEvaluationTolerance() const;

  //! Return the subshell incoherent evaluation tolerance
  double getSubshellIncoherentEvaluationTolerance() const;

  //! Return the photon threshold energy nudge factor
  double getPhotonThresholdEnergyNudgeFactor() const;

  //! Return the upper cutoff scattering angle cosine above which moment preserving elastic scattering is used
  double getCutoffAngleCosine() const;

  //! Return the number of discrete moment preserving angles
  unsigned getNumberOfMomentPreservingAngles() const;

  //! Return the union energy grid convergence tolerance
  double getGridConvergenceTolerance() const;

  //! Return the union energy grid absolute difference tolerance
  double getGridAbsoluteDifferenceTolerance() const;

  //! Return the union energy grid distance tolerance
  double getGridDistanceTolerance() const;

//---------------------------------------------------------------------------//
// GET RELAXATION DATA
//---------------------------------------------------------------------------//

  //! Return the atomic subshells
  const std::set<unsigned>& getSubshells() const;

  //! Return the occupancy for a subshell
  double getSubshellOccupancy( const unsigned subshell ) const;

  //! Return the binding energy for a subshell
  double getSubshellBindingEnergy( const unsigned subshell ) const;

  //! Return if there is relaxation data
  bool hasRelaxationData() const;

  //! Return if the subshell has relaxation data
  bool hasSubshellRelaxationData( const unsigned subshell ) const;

  //! Return the number of transitions that can fill a subshell vacancy
  unsigned getSubshellRelaxationTransitions( const unsigned subshell ) const;

  //! Return the relaxation vacancies for a subshell
  const std::vector<std::pair<unsigned,unsigned> >&
  getSubshellRelaxationVacancies( const unsigned subshell ) const;

  //! Return the relaxation particle energies for a subshell
  const std::vector<double>& getSubshellRelaxationParticleEnergies(
					       const unsigned subshell ) const;

  //! Return the relaxation probabilities for a subshell
  const std::vector<double>& getSubshellRelaxationProbabilities(
					       const unsigned subshell ) const;

//---------------------------------------------------------------------------//
// GET PHOTON DATA
//---------------------------------------------------------------------------//

  //! Return the Compton profile momentum grid
  const std::vector<double>& getComptonProfileMomentumGrid(
					       const unsigned subshell ) const;

  //! Return the Compton profile for a subshell
  const std::vector<double>& getComptonProfile(const unsigned subshell ) const;

  //! Return the occupation number momentum grid
  const std::vector<double>& getOccupationNumberMomentumGrid(
					       const unsigned subshell ) const;

  //! Return the occupation number for a subshell
  const std::vector<double>& getOccupationNumber(
					       const unsigned subshell ) const;

  //! Return the Waller-Hartree scattering function momentum grid
  const std::vector<double>&
  getWallerHartreeScatteringFunctionMomentumGrid() const;

  //! Return the Waller-Hartree scattering function
  const std::vector<double>& getWallerHartreeScatteringFunction() const;

  //! Return the Waller-Hartree atomic form factor momentum grid
  const std::vector<double>&
  getWallerHartreeAtomicFormFactorMomentumGrid() const;

  //! Return the Waller-Hartree atomic form factor
  const std::vector<double>& getWallerHartreeAtomicFormFactor() const;

  //! Return the Waller-Hartree squared atomic form factor squared mom. grid
  const std::vector<double>&
  getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid() const;

  //! Return the Waller-Hartree squared atomic form factor
  const std::vector<double>& getWallerHartreeSquaredAtomicFormFactor() const;

  //! Return the photon energy grid
  const std::vector<double>& getPhotonEnergyGrid() const;

  //! Return the average heating numbers
  const std::vector<double>& getAveragePhotonHeatingNumbers() const;

  //! Return the Waller-Hartree (WH) incoherent photon cross section
  const std::vector<double>&
  getWallerHartreeIncoherentCrossSection() const;

  //! Return the WH incoherent photon cross section threshold energy bin index
  unsigned
  getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex() const;

  //! Return the impluse approx. (IA) incoherent photon cross section
  const std::vector<double>&
  getImpulseApproxIncoherentCrossSection() const;

  //! Return the IA incoherent photon cross section threshold energy bin index
  unsigned
  getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex() const;

  //! Return the subshell Impulse approx. incoherent photon cross section
  const std::vector<double>&
  getImpulseApproxSubshellIncoherentCrossSection(
					       const unsigned subshell ) const;

  //! Return the subshell IA incoherent photon cs threshold energy bin index
  unsigned
  getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(
					       const unsigned subshell ) const;

  //! Return the Waller-Hartree coherent cross section
  const std::vector<double>&
  getWallerHartreeCoherentCrossSection() const;

  //! Return the Waller-Hartree coherent cs threshold energy bin index
  unsigned
  getWallerHartreeCoherentCrossSectionThresholdEnergyIndex() const;

  //! Return the pair production cross section
  const std::vector<double>&
  getPairProductionCrossSection() const;

  //! Return the pair production cross section threshold energy bin index
  unsigned getPairProductionCrossSectionThresholdEnergyIndex() const;

  //! Return the triplet production cross section
  const std::vector<double>&
  getTripletProductionCrossSection() const;

  //! Return the triple production cross section threshold energy bin index
  unsigned getTripletProductionCrossSectionThresholdEnergyIndex() const;

  //! Return the Photoelectric effect cross section
  const std::vector<double>& getPhotoelectricCrossSection() const;

  //! Return the Photoelectric effect cross section threshold energy bin index
  unsigned getPhotoelectricCrossSectionThresholdEnergyIndex() const;

  //! Return the Photoelectric effect cross section for a subshell
  const std::vector<double>&
  getSubshellPhotoelectricCrossSection( const unsigned subshell ) const;

  //! Return the subshell Photoelectric effect cross section threshold index
  unsigned
  getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(
					       const unsigned subshell ) const;

  //! Return the Waller-Hartree total cross section
  const std::vector<double>& getWallerHartreeTotalCrossSection() const;

  //! Return the impulse approx. total cross section
  const std::vector<double>& getImpulseApproxTotalCrossSection() const;


//---------------------------------------------------------------------------//
// GET ELECTRON DATA
//---------------------------------------------------------------------------//

  //! Return the elastic angular energy grid
  const std::vector<double>& getElasticAngularEnergyGrid() const;

  //! Return the map of the cutoff elastic scattering angles
  const std::map<double,std::vector<double> >& getCutoffElasticAngles() const;

  //! Return the map of the cutoff elastic scatering pdf
  const std::map<double,std::vector<double> >& getCutoffElasticPDF() const;

  //! Return the cutoff elastic scattering angles for an incoming energy
  const std::vector<double>& getCutoffElasticAngles(
					       const double incoming_energy ) const;

  //! Return the cutoff elastic scatering pdf for an incoming energy
  const std::vector<double>& getCutoffElasticPDF(
					       const double incoming_energy ) const;

  //! Return if there is screened Rutherford data
  bool hasScreenedRutherfordData() const;

  //! Return the screened Rutherford elastic normalization constants
  const std::vector<double>& getScreenedRutherfordNormalizationConstant() const;

  //! Return Moliere's screening constant
  const std::vector<double>& getMoliereScreeningConstant() const;

  //! Return if there is moment preserving data
  bool hasMomentPreservingData() const;

  //! Return the moment preserving elastic discrete angles
  const std::map<double,std::vector<double> >
    getMomentPreservingElasticDiscreteAngles() const;

  //! Return the moment preserving elastic weights
  const std::map<double,std::vector<double> >
    getMomentPreservingElasticWeights() const;

  //! Return the moment preserving elastic discrete angles for an incoming energy
  const std::vector<double>& getMomentPreservingElasticDiscreteAngles(
					       const double incoming_energy ) const;

  //! Return the moment preserving elastic weights for an incoming energy
  const std::vector<double>& getMomentPreservingElasticWeights(
					       const double incoming_energy ) const;

  //! Return the electroionization energy grid for the recoil electron spectrum for a subshell
  const std::vector<double>& getElectroionizationEnergyGrid(
                           const unsigned subshell ) const;

  //! Return the electroionization recoil energy for a subshell and incoming energy
  const std::vector<double>& getElectroionizationRecoilEnergy(
                           const unsigned subshell,
					       const double incoming_energy ) const;

  //! Return the electroionization recoil energy pdf for a subshell and incoming energy
  const std::vector<double>& getElectroionizationRecoilPDF(
                           const unsigned subshell,
					       const double incoming_energy ) const;

  //! Return the bremsstrahlung energy grid for the secondary photon spectrum
  const std::vector<double>& getBremsstrahlungEnergyGrid() const;

  //! Return the bremsstrahlung photon energy for an incoming energy
  const std::vector<double>& getBremsstrahlungPhotonEnergy(
					       const double incoming_energy ) const;

  //! Return the bremsstrahlung photon energy pdf for an incoming energy
  const std::vector<double>& getBremsstrahlungPhotonPDF(
					       const double incoming_energy ) const;

  //! Return the atomic excitation average energy loss energy grid
  const std::vector<double>& getAtomicExcitationEnergyGrid() const;

  //! Return the atomic excitation average energy loss
  const std::vector<double>& getAtomicExcitationEnergyLoss() const;

  //! Return the electron energy grid
  const std::vector<double>& getElectronEnergyGrid() const;

  //! Return the elastic electron cross section below mu = 0.999999
  const std::vector<double>& getCutoffElasticCrossSection() const;

  //! Return the cutoff elastic cross section threshold energy bin index
  unsigned getCutoffElasticCrossSectionThresholdEnergyIndex() const;

  //! Return the screened Rutherford elastic electron cross section
  const std::vector<double>& getScreenedRutherfordElasticCrossSection() const;

  //! Return the screened Rutherford elastic cross section threshold energy bin index
  unsigned getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex() const;

  //! Return the total elastic electron cross section
  const std::vector<double>& getTotalElasticCrossSection() const;

  //! Return the total elastic cross section threshold energy bin index
  unsigned getTotalElasticCrossSectionThresholdEnergyIndex() const;

  //! Return the Moment Preserving (MP) elastic electron cross section
  const std::vector<double>& getMomentPreservingCrossSection() const;

  //! Return the MP elastic cross section threshold energy bin index
  unsigned getMomentPreservingCrossSectionThresholdEnergyIndex() const;

  //! Return the electroionization electron cross section for a subshell
  const std::vector<double>&
    getElectroionizationCrossSection( const unsigned subshell ) const;

  //! Return the electroionization cross section threshold energy bin index for a subshell
  unsigned getElectroionizationCrossSectionThresholdEnergyIndex(
    const unsigned subshell ) const;

  //! Return the bremsstrahlung electron cross section
  const std::vector<double>& getBremsstrahlungCrossSection() const;

  //! Return the bremsstrahlung cross section threshold energy bin index
  unsigned getBremsstrahlungCrossSectionThresholdEnergyIndex() const;

  //! Return the atomic excitation electron cross section
  const std::vector<double>& getAtomicExcitationCrossSection() const;

  //! Return the atomic excitation cross section threshold energy bin index
  unsigned getAtomicExcitationCrossSectionThresholdEnergyIndex() const;

protected:

  //! Default constructor
  ElectronPhotonRelaxationDataContainer()
  { /* ... */ }

//---------------------------------------------------------------------------//
// SET TABLE DATA
//---------------------------------------------------------------------------//

  //! Set the atomic number
  void setAtomicNumber( const unsigned atomic_number );

  //! Set the minimum photon energy
  void setMinPhotonEnergy( const double min_photon_energy );

  //! Set the maximum photon energy
  void setMaxPhotonEnergy( const double max_photon_energy );

  //! Set the minimum electron energy
  void setMinElectronEnergy( const double min_electron_energy );

  //! Set the maximum electron energy
  void setMaxElectronEnergy( const double max_electron_energy );

  //! Set the occupation number evaluation tolerance
  void setOccupationNumberEvaluationTolerance(
    const double occupation_number_evaluation_tolerance );

  //! Set the subshell incoherent evaluation tolerance
  void setSubshellIncoherentEvaluationTolerance(
    const double subshell_incoherent_evaluation_tolerance );

  //! Set the photon threshold energy nudge factor
  void setPhotonThresholdEnergyNudgeFactor( const double nudge_factor );

  //! Set the upper cutoff scattering angle below which moment preserving elastic scattering is used
  void setCutoffAngleCosine( const double cutoff_angle_cosine );

  //! Set the number of discrete moment preserving angles
  void setNumberOfMomentPreservingAngles(
    const unsigned number_of_moment_preserving_angles);

  //! Set the union energy grid convergence tolerance
  void setGridConvergenceTolerance( const double grid_convergence_tol );

  //! Set the union energy grid absolute difference tolerance
  void setGridAbsoluteDifferenceTolerance( const double grid_absolute_diff_tol );

  //! Set the union energy grid distance tolerance
  void setGridDistanceTolerance( const double grid_distance_tol );

//---------------------------------------------------------------------------//
// SET RELAXATION DATA
//---------------------------------------------------------------------------//

  //! Set the atomic subshells
  void setSubshells( const std::set<unsigned>& subshells );

  //! Set the occupancy for a subshell
  void setSubshellOccupancy( const unsigned subshell,
			     const double occupancy );

  //! Set the binding energy for a subshell
  void setSubshellBindingEnergy( const unsigned subshell,
				 const double binding_energy );

  //! Set the number of transitions that can fill a subshell vacancy
  void setSubshellRelaxationTransitions( const unsigned subshell,
					 const unsigned transitions );

  //! Set the relaxation vacancies for a subshell
  void setSubshellRelaxationVacancies(
      const unsigned subshell,
      const std::vector<std::pair<unsigned,unsigned> >& relaxation_vacancies );

  //! Set the relaxation particle energies for a subshell
  void setSubshellRelaxationParticleEnergies(
		     const unsigned subshell,
		     const std::vector<double>& relaxation_particle_energies );

  //! Set the relaxation probabilities for a subshell
  void setSubshellRelaxationProbabilities(
			 const unsigned subshell,
			 const std::vector<double>& relaxation_probabilities );

//---------------------------------------------------------------------------//
// SET PHOTON DATA
//---------------------------------------------------------------------------//

  //! Set the Compton profile momentum grid
  void setComptonProfileMomentumGrid(
		    const unsigned subshell,
		    const std::vector<double>& compton_profile_momentum_grid );

  //! Set the Compton profile for a subshell
  void setComptonProfile( const unsigned subshell,
			  const std::vector<double>& compton_profile );

  //! Set the occupation number momentum grid
  void setOccupationNumberMomentumGrid(
		   const unsigned subshell,
		   const std::vector<double>& occupation_number_momentum_grid );

  //! Set the occupation number for a subshell
  void setOccupationNumber( const unsigned subshell,
			   const std::vector<double>& occupation_number );

  //! Set the Waller-Hartree scattering function momentum grid
  void setWallerHartreeScatteringFunctionMomentumGrid(
				    const std::vector<double>& momentum_grid );

  //! Set the Waller-Hartree scattering function
  void setWallerHartreeScatteringFunction(
			      const std::vector<double>& scattering_function );

  //! Set the Waller-Hartree atomic form factor momentum grid
  void setWallerHartreeAtomicFormFactorMomentumGrid(
				    const std::vector<double>& momentum_grid );

  //! Set the Waller-Hartree atomic form factor
  void setWallerHartreeAtomicFormFactor(
			       const std::vector<double>& atomic_form_factor );

  //! Return the Waller-Hartree squared atomic form factor squared mom. grid
  void setWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid(
                            const std::vector<double>& squared_momentum_grid );

  //! Return the Waller-Hartree squared atomic form factor
  void setWallerHartreeSquaredAtomicFormFactor(
                       const std::vector<double>& squared_atomic_form_factor );

  //! Set the photon energy grid
  void setPhotonEnergyGrid( const std::vector<double>& energy_grid );

  //! Set the average photon heating numbers
  void setAveragePhotonHeatingNumbers(
				  const std::vector<double>& heating_numbers );

  //! Set the incoherent photon cross section using Waller-Hartree (WH) theory
  void setWallerHartreeIncoherentCrossSection(
			 const std::vector<double>& incoherent_cross_section );

  //! Set the WH incoherent cross section threshold energy bin index
  void setWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(
						        const unsigned index );

  //! Set the incoherent photon cross section using the impulse approx. (IA)
  void setImpulseApproxIncoherentCrossSection(
			 const std::vector<double>& incoherent_cross_section );

  //! Set the IA incoherent photon cross section threshold energy bin index
  void setImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(
							const unsigned index );

  //! Set the IA subshell incoherent photon cross section
  void setImpulseApproxSubshellIncoherentCrossSection(
			 const unsigned subshell,
			 const std::vector<double>& incoherent_cross_section );

  //! Set the IA subshell incoherent photon cs threshold energy bin index
  void setImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(
						       const unsigned subshell,
						       const unsigned index );

  //! Set the WH coherent cross section
  void setWallerHartreeCoherentCrossSection(
			   const std::vector<double>& coherent_cross_section );

  //! Set the WH coherent cross section threshold energy bin index
  void setWallerHartreeCoherentCrossSectionThresholdEnergyIndex(
							const unsigned index );

  //! Set the pair production cross section
  void setPairProductionCrossSection(
		    const std::vector<double>& pair_production_cross_section );

  //! Set the pair production cross section threshold energy bin index
  void setPairProductionCrossSectionThresholdEnergyIndex(
							const unsigned index );

  //! Set the triplet production cross section
  void setTripletProductionCrossSection(
                 const std::vector<double>& triplet_production_cross_section );

  //! Set the triplet production cross section threshold energy bin index
  void setTripletProductionCrossSectionThresholdEnergyIndex(
                                                        const unsigned index );

  //! Set the Photoelectric effect cross section
  void setPhotoelectricCrossSection(
		      const std::vector<double>& photoelectric_cross_section );

  //! Set the Photoelectric effect cross section threshold energy bin index
  void setPhotoelectricCrossSectionThresholdEnergyIndex(const unsigned index );

  //! Set the Photoelectric effect cross section for a subshell
  void setSubshellPhotoelectricCrossSection(
		      const unsigned subshell,
		      const std::vector<double>& photoelectric_cross_section );

  //! Set the subshell Photoelectric effect cross section threshold index
  void setSubshellPhotoelectricCrossSectionThresholdEnergyIndex(
						       const unsigned subshell,
						       const unsigned index );

  //! Set the Waller-Hartree total cross section
  void setWallerHartreeTotalCrossSection(
			      const std::vector<double>& total_cross_section );

  //! Set the impulse approx. total cross section
  void setImpulseApproxTotalCrossSection(
			      const std::vector<double>& total_cross_section );

//---------------------------------------------------------------------------//
// SET ELECTRON DATA
//---------------------------------------------------------------------------//

  //! Set the elastic angular energy grid
  void setElasticAngularEnergyGrid(
    const std::vector<double>& angular_energy_grid );

  //! Set the elastic scattering angles for an incoming energy
  void setCutoffElasticAnglesAtEnergy(
    const double incoming_energy,
    const std::vector<double>& elastic_angles );

  //! Set the elastic scattering pdf for an incoming energy
  void setCutoffElasticPDFAtEnergy(
    const double incoming_energy,
    const std::vector<double>& elastic_pdf );

  //! Set the elastic scattering angles
  void setCutoffElasticAngles(
    const std::map<double,std::vector<double> >& elastic_angles );

  //! Set the elastic scattering pdf
  void setCutoffElasticPDF(
    const std::map<double,std::vector<double> >& elastic_pdf );

  //! Set the screened Rutherford elastic normalization constant
  void setScreenedRutherfordNormalizationConstant(
    const std::vector<double>& screened_rutherford_normalization_constant );

  //! Set Moliere's screening constant
  void setMoliereScreeningConstant(
    const std::vector<double>& moliere_screening_constant );

  //! Set the moment preserving elastic discrete angles for an incoming energy
  void setMomentPreservingElasticDiscreteAngles(
	const double incoming_energy,
	const std::vector<double>& moment_preserving_elastic_discrete_angles );

  //! Set the moment preserving elastic weights for an incoming energy
  void setMomentPreservingElasticWeights(
	const double incoming_energy,
	const std::vector<double>& moment_preserving_elastic_weights );

  //! Set the electroionization energy grid for the recoil electron spectrum
  void setElectroionizationEnergyGrid(
    const unsigned subshell,
    const std::vector<double>& electroionization_energy_grid );

  //! Set the electroionization recoil energy for an incoming energy and subshell
  void setElectroionizationRecoilEnergyAtIncomingEnergy(
    const unsigned subshell,
    const double incoming_energy,
    const std::vector<double>& electroionization_recoil_energy );

  //! Set the electroionization recoil energy pdf for an incoming energy and subshell
  void setElectroionizationRecoilPDFAtIncomingEnergy(
    const unsigned subshell,
    const double incoming_energy,
    const std::vector<double>& electroionization_recoil_pdf );

  //! Set electroionization recoil energy for all incoming energies in a subshell
  void setElectroionizationRecoilEnergy(
    const unsigned subshell,
    const std::map<double,std::vector<double> >& electroionization_recoil_energy );

  //! Set electroionization recoil energy pdf for all incoming energies in a subshell
  void setElectroionizationRecoilPDF(
    const unsigned subshell,
    const std::map<double,std::vector<double> >& electroionization_recoil_pdf );

  //! Set the bremsstrahlung energy grid for the secondary photon spectrum
  void setBremsstrahlungEnergyGrid(
    const std::vector<double>& bremsstrahlung_energy_grid );

  //! Set the bremsstrahlung photon energy for an incoming energy
  void setBremsstrahlungPhotonEnergyAtIncomingEnergy(
    const double incoming_energy,
    const std::vector<double>& bremsstrahlung_photon_energy );

  //! Set the bremsstrahlung photon energy pdf for an incoming energy
  void setBremsstrahlungPhotonPDFAtIncomingEnergy(
    const double incoming_energy,
    const std::vector<double>&  bremsstrahlung_photon_pdf );

  //! Set all the bremsstrahlung photon energy data
  void setBremsstrahlungPhotonEnergy(
    const std::map<double,std::vector<double> >& bremsstrahlung_photon_energy );

  //! Set all the bremsstrahlung photon energy pdf data
  void setBremsstrahlungPhotonPDF(
    const std::map<double,std::vector<double> >&  bremsstrahlung_photon_pdf );

  //! Set the atomic excitation average energy loss energy grid
  void setAtomicExcitationEnergyGrid(
    const std::vector<double>& atomic_excitation_energy_grid );

  //! Set the atomic excitation average energy loss
  void setAtomicExcitationEnergyLoss(
            const std::vector<double>& atomic_excitation_energy_loss );

  //! Set the electron energy grid
  void setElectronEnergyGrid( const std::vector<double>& energy_grid );

  //! Set the elastic electron cross section below mu = 0.999999
  void setCutoffElasticCrossSection(
    const std::vector<double>& cutoff_elastic_cross_section );

  //! Set the elastic cutoff cross section threshold energy bin index
  void setCutoffElasticCrossSectionThresholdEnergyIndex( const unsigned index );

  //! Set the screened Rutherford elastic electron cross section
  void setScreenedRutherfordElasticCrossSection(
    const std::vector<double>& total_elastic_cross_section );

  //! Set the screened Rutherford elastic cross section threshold energy bin index
  void setScreenedRutherfordElasticCrossSectionThresholdEnergyIndex( const unsigned index );

  //! Set the total elastic electron cross section
  void setTotalElasticCrossSection(
    const std::vector<double>& total_elastic_cross_section );

  //! Set the total elastic cross section threshold energy bin index
  void setTotalElasticCrossSectionThresholdEnergyIndex( const unsigned index );

  //! Set the moment preserving elastic electron cross section using Moment Preserving (MP) theory
  void setMomentPreservingCrossSection(
			 const std::vector<double>& moment_preserving_elastic_cross_section );

  //! Set the MP moment preserving elastic cross section threshold energy bin index
  void setMomentPreservingCrossSectionThresholdEnergyIndex(
						        const unsigned index );

  //! Set the electroionization electron cross section for a subshell
  void setElectroionizationCrossSection( const unsigned subshell,
			 const std::vector<double>& electroionization_cross_section );

  //! Set the electroionization cross section threshold energy bin index
  void setElectroionizationCrossSectionThresholdEnergyIndex(
             const unsigned subshell,
             const unsigned index );

  //! Set the bremsstrahlung electron cross section
  void setBremsstrahlungCrossSection(
			 const std::vector<double>& bremsstrahlung_cross_section );

  //! Set the bremsstrahlung cross section threshold energy bin index
  void setBremsstrahlungCrossSectionThresholdEnergyIndex(
                                const unsigned index );

  //! Set the atomic excitation electron cross section
  void setAtomicExcitationCrossSection(
			 const std::vector<double>& atomic_excitation_cross_section );

  //! Set the bremsstrahlung cross section threshold energy bin index
  void setAtomicExcitationCrossSectionThresholdEnergyIndex(
                                const unsigned index );

private:

  // Save the data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

//---------------------------------------------------------------------------//
// SET TABLE DATA
//---------------------------------------------------------------------------//

  // The atomic number
  unsigned d_atomic_number;

  // The minimum photon energy
  double d_min_photon_energy;

  // The maximum photon energy
  double d_max_photon_energy;

  // The minimum electron energy
  double d_min_electron_energy;

  // The maximum electron energy
  double d_max_electron_energy;

  // The occupation number evaluation tolerance
  double d_occupation_number_evaluation_tolerance;

  // The subshell incoherent evaluation tolerance
  double d_subshell_incoherent_evaluation_tolerance;

  // The photon threshold energy nudge factor
  double d_photon_threshold_energy_nudge_factor;

  // The elastic cutoff angle
  double d_cutoff_angle_cosine;

  // The number of discrete moment preserving angles
  double d_number_of_moment_preserving_angles;

  // The union energy grid convergence tolerance
  double d_grid_convergence_tol;

  // The union energy grid absolute difference tolerance
  double d_grid_absolute_diff_tol;

  // The union energy grid distance tolerance
  double d_grid_distance_tol;

//---------------------------------------------------------------------------//
// RELAXATION DATA
//---------------------------------------------------------------------------//

  // The atomic subshells (ENDF designators)
  std::set<unsigned> d_subshells;

  // The subshell occupancies
  std::map<unsigned,double> d_subshell_occupancies;

  // The subshell binding energies
  std::map<unsigned,double> d_subshell_binding_energies;

  // The subshell relaxation transitions
  std::map<unsigned,unsigned> d_relaxation_transitions;

  // The subshell relaxation vacancies
  std::map<unsigned,std::vector<std::pair<unsigned,unsigned> > >
  d_relaxation_vacancies;

  // The subshell relaxation particle energies
  std::map<unsigned,std::vector<double> > d_relaxation_particle_energies;

  // The subshell relaxation probabilities
  std::map<unsigned,std::vector<double> > d_relaxation_probabilities;

//---------------------------------------------------------------------------//
// PHOTON DATA
//---------------------------------------------------------------------------//

  // The Compton profile momentum grids (me*c units)
  std::map<unsigned,std::vector<double> > d_compton_profile_momentum_grids;

  // The subshell Compton profiles ((me*c)^-1 units)
  std::map<unsigned,std::vector<double> > d_compton_profiles;

  // The occupation number momentum grids
  std::map<unsigned,std::vector<double> > d_occupation_number_momentum_grids;

  // The subshell occupation numbers
  std::map<unsigned,std::vector<double> > d_occupation_numbers;

  // The Waller-Hartree scattering function momentum grid (1/cm)
  std::vector<double> d_waller_hartree_scattering_function_momentum_grid;

  // The Waller-Hartree scattering function
  std::vector<double> d_waller_hartree_scattering_function;

  // The Waller-Hartree atomic form factor momentum grid (1/cm)
  std::vector<double> d_waller_hartree_atomic_form_factor_momentum_grid;

  // The Waller-Hartree atomic form factor
  std::vector<double> d_waller_hartree_atomic_form_factor;

  // The Waller-Hartree squared atomic form factor squared mom. grid (1/cm^2)
  std::vector<double>
  d_waller_hartree_squared_atomic_form_factor_squared_momentum_grid;

  // The Waller-Hartree squared atomic form factor
  std::vector<double> d_waller_hartree_squared_atomic_form_factor;

  // The photon energy grid (MeV)
  std::vector<double> d_photon_energy_grid;

  // The average heating numbers
  std::vector<double> d_average_photon_heating_numbers;

  // The Waller-Hartree incoherent photon cross section (b)
  std::vector<double> d_waller_hartree_incoherent_cross_section;

  // The Waller-Hartree incoherent photon cross section threshold energy index
  unsigned d_waller_hartree_incoherent_cross_section_threshold_index;

  // The impulse approx. incoherent photon cross section (b)
  std::vector<double> d_impulse_approx_incoherent_cross_section;

  // The impulse approx. incoherent photon cross section threshold energy index
  unsigned d_impulse_approx_incoherent_cross_section_threshold_index;

  // The impulse approx. subshell incoherent photon cross sections (b)
  std::map<unsigned,std::vector<double> >
  d_impulse_approx_subshell_incoherent_cross_sections;

  // The impulse approx. subshell incoherent photon cross section thes. indices
  std::map<unsigned,unsigned>
  d_impulse_approx_subshell_incoherent_cross_section_threshold_indices;

  // The Waller-Hartree coherent cross section (b)
  std::vector<double> d_waller_hartree_coherent_cross_section;

  // The Waller-Hartree coherent cross section threshold energy index
  unsigned d_waller_hartree_coherent_cross_section_threshold_index;

  // The pair production cross section (b)
  std::vector<double> d_pair_production_cross_section;

  // The pair production cross section threshold energy index
  unsigned d_pair_production_cross_section_threshold_index;

  // The triplet production cross section (b)
  std::vector<double> d_triplet_production_cross_section;

  // The triplet production cross section threshold energy index
  unsigned d_triplet_production_cross_section_threshold_index;

  // The photoelectric effect cross section (b)
  std::vector<double> d_photoelectric_cross_section;

  // The photoelectric effect cross section energy index
  unsigned d_photoelectric_cross_section_threshold_index;

  // The subshell photoelectric effect cross sections (b)
  std::map<unsigned,std::vector<double> >
  d_subshell_photoelectric_cross_sections;

  // The subshell photoelectric effect cross section threshold indices
  std::map<unsigned,unsigned>
  d_subshell_photoelectric_cross_section_threshold_indices;

  // The Waller-Hartree total cross section (b)
  std::vector<double> d_waller_hartree_total_cross_section;

  // The impulse approx. total cross section (b)
  std::vector<double> d_impulse_approx_total_cross_section;


//---------------------------------------------------------------------------//
// ELECTRON DATA
//---------------------------------------------------------------------------//

  // The elastic angular energy grid (MeV)
  std::vector<double> d_angular_energy_grid;

  // The cutoff elastic scattering angles
  std::map<double,std::vector<double> > d_cutoff_elastic_angles;

  // The cutoff elastic scattering pdf
  std::map<double,std::vector<double> > d_cutoff_elastic_pdf;

  // The screened rutherford normalization constant for elastic scattering
  std::vector<double> d_screened_rutherford_normalization_constant;

  // Moliere's screening constant
  std::vector<double> d_moliere_screening_constant;

  // The moment preserving elastic discrete angles
  std::map<double,std::vector<double> > d_moment_preserving_elastic_discrete_angles;

  // The moment preserving elastic weights
  std::map<double,std::vector<double> > d_moment_preserving_elastic_weights;

  // The electroionization energy grid (MeV) for a subshell
  std::map<unsigned,std::vector<double> > d_electroionization_energy_grid;

  // The electroionization recoil energy for subshell and incoming energy
  std::map<unsigned,std::map<double,std::vector<double> > >
    d_electroionization_recoil_energy;

  // The electroionization recoil pdf for subshell and incoming energy
  std::map<unsigned,std::map<double,std::vector<double> > >
    d_electroionization_recoil_pdf;

  // The bremsstrahlung energy grid (MeV)
  std::vector<double> d_bremsstrahlung_energy_grid;

  // The bremsstrahlung photon energy
  std::map<double,std::vector<double> > d_bremsstrahlung_photon_energy;

  // The bremsstrahlung photon pdf
  std::map<double,std::vector<double> > d_bremsstrahlung_photon_pdf;

  // The atomic excitation energy grid (MeV)
  std::vector<double> d_atomic_excitation_energy_grid;

  // The atomic excitation energy loss
  std::vector<double> d_atomic_excitation_energy_loss;

  // The electron energy grid (MeV)
  std::vector<double> d_electron_energy_grid;

  // The cutoff elastic electron cross section (b)
  std::vector<double> d_cutoff_elastic_cross_section;

  // The cutoff elastic electron cross section threshold energy index
  unsigned d_cutoff_elastic_cross_section_threshold_index;

  // The screened rutherford elastic electron cross section (b)
  std::vector<double> d_screened_rutherford_elastic_cross_section;

  // The screened rutherford elastic electron cross section threshold energy index
  unsigned d_screened_rutherford_elastic_cross_section_threshold_index;

  // The total elastic electron cross section (b)
  std::vector<double> d_total_elastic_cross_section;

  // The total elastic electron cross section threshold energy index
  unsigned d_total_elastic_cross_section_threshold_index;

  // The Moment Preserving elastic electron cross section (b)
  std::vector<double> d_moment_preserving_elastic_cross_section;

  // The Moment Preserving elastic electron cross section threshold energy index
  unsigned d_moment_preserving_elastic_cross_section_threshold_index;

  // The electroionization subshell electron cross section (b)
  std::map<unsigned,std::vector<double> >
    d_electroionization_subshell_cross_section;

  // The hard elastic electron cross section threshold energy index
  std::map<unsigned,unsigned>
    d_electroionization_subshell_cross_section_threshold_index;

  // The bremsstrahlung electron cross section (b)
  std::vector<double> d_bremsstrahlung_cross_section;

  // The bremsstrahlung electron cross section threshold energy index
  unsigned d_bremsstrahlung_cross_section_threshold_index;

  // The atomic excitation electron cross section (b)
  std::vector<double> d_atomic_excitation_cross_section;

  // The atomic excitation electron cross section threshold energy index
  unsigned d_atomic_excitation_cross_section_threshold_index;
};

} // end Data namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_ElectronPhotonRelaxationDataContainer_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_ElectronPhotonRelaxationDataContainer.hpp
//---------------------------------------------------------------------------//

