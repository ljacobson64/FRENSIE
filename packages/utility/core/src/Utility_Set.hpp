//---------------------------------------------------------------------------//
//!
//! \file   Utility_Set.hpp
//! \author Alex Robinson
//! \brief  Helper function and class declarations for std::set and
//!         std::unordered_set
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SET_HPP
#define UTILITY_SET_HPP

// Std Lib Includes
#include <iostream>
#include <set>
#include <unordered_set>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_FromStringTraits.hpp"

/*! \defgroup set Set
 *
 * Additional helper functions and classes for use with the std::set and
 * std::unordered_set have been defined that do not appear in the standard
 * library.
 */

namespace Utility{

/*! Partial specialization of ToStringTraits for std::set
 * \ingroup set
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<std::set<T> > : public Details::ToStringTraitsIteratorHelper<std::set<T> >
{ /* ... */ };

/*! Partial specialization of ToStringTraits for std::unordered_set
 * \ingroup set
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<std::unordered_set<T> > : public Details::ToStringTraitsIteratorHelper<std::unordered_set<T> >
{ /* ... */ };

/*! Partial specialization of FromStringTraits for std::set
 * \ingroup set
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<std::set<T> > : public Details::FromStringTraitsSTLCompliantContainerInsertHelper<std::set<T> >
{ /* ... */ };

/*! Partial specialization of FromStringTraits for std::unordered_set
 * \ingroup set
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<std::unordered_set<T> > : public Details::FromStringTraitsSTLCompliantContainerInsertHelper<std::unordered_set<T> >
{ /* ... */ };
  
} // end Utility namespace

namespace std{

/*! Place a std::set in a stream
 * \ingroup set
 */
template<typename T>
inline std::ostream& operator<<( std::ostream& os, const std::set<T>& set )
{
  Utility::toStream( os, set );

  return os;
}

/*! Extract a std::set from a stream
 * \ingroup set
 */
template<typename T>
inline std::istream& operator>>( std::istream& is, std::set<T>& set )
{
  Utility::fromStream( is, set );

  return is;
}

/*! Place a std::unordered_set in a stream
 * \ingroup set
 */
template<typename T>
inline std::ostream& operator<<( std::ostream& os,
                                 const std::unordered_set<T>& set )
{
  Utility::toStream( os, set );

  return os;
}

/*! Extract a std::unordered_set from a stream
 * \ingroup set
 */
template<typename T>
inline std::istream& operator>>( std::istream& is,
                                 std::unordered_set<T>& set )
{
  Utility::fromStream( is, set );

  return is;
}
  
} // end std namespace

#endif // end UTILITY_SET_HPP

//---------------------------------------------------------------------------//
// end Utility_Set.hpp
//---------------------------------------------------------------------------//
