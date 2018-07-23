//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardCellEstimator.hpp
//! \author Alex Robinson
//! \brief  Standard cell estimator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_CELL_ESTIMATOR_HPP
#define MONTE_CARLO_STANDARD_CELL_ESTIMATOR_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardEntityEstimator.hpp"
#include "Geometry_Model.hpp"

namespace MonteCarlo{

//! The standard cell estimator base class
class StandardCellEstimator : public StandardEntityEstimator
{

public:

  //! Typedef for the cell id type
  typedef Geometry::Model::EntityId CellIdType;

  //! Constructor
  StandardCellEstimator( const uint32_t id,
			 const double multiplier,
			 const std::vector<CellIdType>& cell_ids,
			 const std::vector<double>& cell_volumes );

  //! Constructor (extract cell volumes from model)
  StandardCellEstimator( const uint32_t id,
			 const double multiplier,
			 const std::vector<CellIdType>& cell_ids,
			 const Geometry::Model& cell_volumes );

  //! Destructor
  virtual ~StandardCellEstimator()
  { /* ... */ }

protected:

  //! Default constructor
  StandardCellEstimator();

  //! Assign discretization to an estimator dimension
  void assignDiscretization( const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins,
                             const bool range_dimension ) override;
  

  //! Assign the particle type to the estimator
  void assignParticleType( const ParticleType particle_type ) override;

  

private:

  // Serialize the estimator data
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( StandardEntityEstimator ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::StandardCellEstimator, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT( MonteCarlo::StandardCellEstimator );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, StandardCellEstimator );

#endif // end MONTE_CARLO_STANDARD_CELL_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardCellEstimator.hpp
//---------------------------------------------------------------------------//
