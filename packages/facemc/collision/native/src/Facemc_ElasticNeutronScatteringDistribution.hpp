//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ElasticNeutronScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The elastic scattering distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_ELASTIC_NEUTRON_SCATTERING_DISTRIBUTION_HPP
#define FACEMC_ELASTIC_NEUTRON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_NeutronScatteringDistribution.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_Tuple.hpp"

namespace Facemc{

//! The elastic scattering distribution class
class ElasticNeutronScatteringDistribution : public NeutronScatteringDistribution
{

public:
  
  //! Constructor
  ElasticNeutronScatteringDistribution( const double atomic_weight_ratio,
					const Teuchos::Array<Utility::Pair<double,Teuchos::RCP<Utility::OneDDistribution> > >& angular_scattering_distribution );

  //! Destructor
  ~ElasticNeutronScatteringDistribution()
  { /* ... */ }
  
  //! Randomly scatter the neutron
  void scatterNeutron( NeutronState& neutron,
		       const double temperature ) const;

private:

  // Sample center-of-mass scattering angle cosine
  double sampleCMScatteringAngleCosine( const double energy ) const;

  // The incoming energy dependent angular scattering distribution
  Teuchos::Array<Utility::Pair<double,
			       Teuchos::RCP<Utility::OneDDistribution> > > 
  d_angular_scattering_distribution;
};

} // end Facemc namespace

#endif // end FACEMC_ELASTIC_NEUTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Facemc_ElasticNeutronScatteringDistribution.hpp
//---------------------------------------------------------------------------//