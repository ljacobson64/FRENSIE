//---------------------------------------------------------------------------//
//!
//! \file   PhaseSpaceDimension.hpp
//! \author Alex Robinson
//! \brief  Phase space dimension enumeration
//!
//---------------------------------------------------------------------------//

#ifndef PHASE_SPACE_DIMENSION_HPP
#define PHASE_SPACE_DIMENSION_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FACEMC Includes
#include "Tuple.hpp"

namespace FACEMC{

/*! The phase space dimension enumeration
 *
 * Make sure that the DIMENSION_end value equals the last dimension name if
 * more dimension names are added. The start and end enum names are used for
 * iterating through the list of dimensions.
 */
enum PhaseSpaceDimension{
  DIMENSION_start = 0,
  COSINE_DIMENSION = DIMENSION_start,
  ENERGY_DIMENSION,
  TIME_DIMENSION,
  COLLISION_NUMBER_DIMENSION,
  DIMENSION_end
};



} // end FACEMC namespace

#endif // end PHASE_SPACE_DIMENSION_HPP

//---------------------------------------------------------------------------//
// end PhaseSpaceDimension.hpp
//---------------------------------------------------------------------------//