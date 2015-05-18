//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_IncoherentPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The incoherent photon scattering distribution declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_PhotonScatteringDistribution.hpp"

namespace MonteCarlo{

//! The incoherent photon scattering distribution class
class IncoherentPhotonScatteringDistribution : public PhotonScatteringDistribution
{

public:

  //! Return the min cutoff energy
  static double getMinKahnCutoffEnergy();
  
  //! Constructor
  IncoherentPhotonScatteringDistribution(
			            const double kahn_sampling_cutoff_energy );

  //! Destructor
  virtual ~IncoherentPhotonScatteringDistribution()
  { /* ... */ }

  //! Evaluate the PDF
  double evaluatePDF( const double incoming_energy,
		      const double scattering_angle_cosine ) const;

protected:

  //! Calculate the Compton line energy
  double calculateComptonLineEnergy( 
				  const double incoming_energy,
				  const double scattering_angle_cosine ) const;

  //! Evaluate the Klein-Nishina distribution
  double evaluateKleinNishinaDist(const double incoming_energy,
				  const double scattering_angle_cosine ) const;
  

  //! Klein-Nishina sampling implementation
  void sampleAndRecordTrialsKleinNishina( const double incoming_energy,
					  double& outgoing_energy,
					  double& scattering_angle_cosine,
					  SubshellType& shell_of_interaction,
					  unsigned& trials ) const;

  //! Create ejected electron
  void createEjectedElectron( const PhotonState& photon,
			      const double scattering_angle_cosine,
			      const double azimuthal_angle,
			      ParticleBank& bank ) const;
			      
private:

  // The min cutoff energy
  static const double s_min_kahn_sampling_cutoff_energy;

  // The Kahn rejection sampling cutoff energy
  double d_kahn_sampling_cutoff_energy;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
