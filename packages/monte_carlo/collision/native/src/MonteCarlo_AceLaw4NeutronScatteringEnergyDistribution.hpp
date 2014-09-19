//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_AceLaw4NeutronScatteringEnergyDistribution.hpp
//! \author Alex Bennett
//! \brief  The law 4 scattering energy distribution class
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_ACE_LAW_4_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION_HPP
#define FACEMC_ACE_LAW_4_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_NeutronScatteringEnergyDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

/*! The law 4 scattering eneryg distribution class (Ace Law 4)
 * \ingroup ace_laws
 */
class AceLaw4NeutronScatteringEnergyDistribution : public NeutronScatteringEnergyDistribution
{

public:

  //! Typedef for the energy distribution
  typedef Teuchos::Array<Utility::Pair<double,Teuchos::RCP<Utility::OneDDistribution> > >
                                                        EnergyDistribution;
  //! Constructor
  AceLaw4NeutronScatteringEnergyDistribution( 
				     EnergyDistribution& energy_distribution );

  //! Destructor
  ~AceLaw4NeutronScatteringEnergyDistribution()
  { /* ... */ }

  //! Sample a scattering energy
  double sampleEnergy( const double energy ) const;

  //! Sample a scattering energy
  double sampleEnergy( const double energy, 
                       unsigned& incoming_index, 
                       unsigned& outgoing_index,
                       double& energy_prime ) const;

private:

  EnergyDistribution d_energy_distribution;

};

} // end MonteCarlo namespace

#endif // end FACEMC_ACE_LAW_4_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw4NeutronScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//

