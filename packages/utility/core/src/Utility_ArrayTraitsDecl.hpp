//---------------------------------------------------------------------------//
//!
//! \file   Utility_ArrayTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Array traits class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ARRAY_TRAITS_DECL_HPP
#define UTILITY_ARRAY_TRAITS_DECL_HPP

// Std Lib Includes
#include <iostream>
#include <string>

// Boost Includes
#include <boost/mpl/bool.hpp>

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_OrdinalTraits.hpp>

// FRENSIE Includes
#include "Utility_UndefinedTraits.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

/*! \defgroup array_traits Array Traits
 * \ingroup traits
 *
 * The Utility::HDF5FileHandler has many templated member functions
 * with a template template parameter (Array). Because the Teuchos array
 * classes have slightly different interfaces, a traits class is needed to
 * homogenize the interfaces (bridge pattern). The
 * Utility::ArrayTraits struct defines the interface. Because of the
 * slightly different interfaces for each array type, the
 * Utility::HDF5ArrayTraits class must be specialized. Attempting to
 * use the class without a specialization will result in a compile time error.
 * The compile time error message is defined by the
 * Utility::UndefinedTraits struct.
 */

namespace Utility{

/*! \brief Default array traits struct.
 *
 * This struct should allow use of any Teuchos::Array when dealing with the
 * HDF5 interface and DataProcessor interface. The std::vector is also
 * supported. The functions in the templated base unspecialized struct are
 * designed not to compile (giving a nice compile-time error message) and
 * therefore specializations must be written for each array type. The design
 * pattern that is implemented with the templated class is the bridge pattern.
 * Every array type has a slightly different interface and this struct
 * homogenizes the interfaces so that they can all be used inside of the other
 * templated functions used by Utility. It should be noted that even though the
 * class name implies that this is a traits class, some behavioral functions
 * are also defined indicating that it is not a true traits class (it is also
 * a policies class). The traits name was used to conform with the standard
 * library convention (see std::char_traits which is also a hybrid traits and
 * policies class). It must be noted that one need not interact with the
 * behavioral functions directly through the traits class. Several policy
 * functions have been written that hide the traits class.
 * \tparam T An array of types.
 * \note The default defined specializations are provided for Teuchos::Array,
 * Teuchos::ArrayRCP, Teuchos::ArrayView and Teuchos::TwoDArray, and
 * std::vector
 * \ingroup array_traits
 */
template<typename Array, typename Enabled = void>
struct ArrayTraits
{
  //! The array type
  typedef Array ArrayType;
  //! The size type of the array
  typedef typename ArrayType::size_type size_type;
  //! The type contained in the array
  typedef typename ArrayType::value_type value_type;
  //! The pointer type of the array
  typedef typename ArrayType::pointer pointer;
  //! The const pointer type of the array
  typedef typename ArrayType::const_pointer const_pointer;
  //! The array view type
  typedef Teuchos::ArrayView<value_type> ArrayViewType;
  //! The array const view type
  typedef Teuchos::ArrayView<const value_type> ArrayConstViewType;
  // This typedef will only appear in specializations
  // typedef boost::mpl::true_ AvoidAmbiguousOverloads;

  //! The number of dimensions in the array
  static inline size_type numberOfDimensions( const ArrayType& array )
  { (void)UndefinedTraits<ArrayType>::notDefined(); return 0; }

  //! The size of each array dimension
  template<typename IntType,template<typename,typename...> class DimSizeArray>
  static inline void dimensionSizes( const ArrayType& array,
                                     DimSizeArray<IntType>& dim_size_array)
  { (void)UndefinedTraits<ArrayType>::notDefined(); }

  //! The size of the array
  static inline size_type size(const ArrayType& array)
  { (void)UndefinedTraits<ArrayType>::notDefined(); return 0; }

  //! Resize the array
  static inline void resize( ArrayType& array, size_type n )
  { (void)UndefinedTraits<ArrayType>::notDefined(); }

  //! Reshape the array
  template<typename IntType, template<typename,typename... > class DimSizeArray>
  static inline void reshape( ArrayType& array,
                              const DimSizeArray<IntType>& dim_size_array )
  { (void)UndefinedTraits<ArrayType>::notDefined(); }

  //! The head pointer of the array
  static inline pointer headPtr( ArrayType& array )
  { (void)UndefinedTraits<ArrayType>::notDefined(); return 0; }

  //! The head pointer of a const array
  static inline const_pointer headPtr( const ArrayType& array)
  { (void)UndefinedTraits<ArrayType>::notDefined(); return 0; }

  //! Convert the array to a string
  static inline std::string toString( const ArrayType& array )
  { (void)UndefinedTraits<ArrayType>::notDefined(); return ""; }

  //! Convert the string to an array
  static inline ArrayType fromString( const std::string& array_string )
  { (void)UndefinedTraits<ArrayType>::notDefined(); return ArrayType(); }

  //! Place the array in a stream
  static inline void toStream( std::ostream& os, const ArrayType& array )
  { (void)UndefinedTraits<ArrayType>::notDefined(); }

  //! A view of the array
  static inline ArrayViewType view(
	  ArrayType& array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  { (void)UndefinedTraits<ArrayType>::notDefined(); return 0; }

  //! A view of the const array
  static inline ArrayConstViewType view(
	  const ArrayType& array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  { (void)UndefinedTraits<ArrayType>::notDefined(); return 0; }

  //! Copy the ArrayView object
  static inline void copyView( ArrayType& array, const ArrayViewType &view )
  { (void)UndefinedTraits<ArrayType>::notDefined(); }

  //! Copy the ArrayView of const object
  static inline void copyView( ArrayType& array,
                               const ArrayConstViewType &view )
  { (void)UndefinedTraits<ArrayType>::notDefined(); }
};

/*! This function allows access to the headPtr ArrayTraits function.
 *
 * This function is simply a more concise way to access the getRawPtr static
 * member function associated with the ArrayTraits class. It simply forwards
 * calls to get a raw pointer to the associated Utility::ArrayTraits
 * class. It is important to note that the array type will be deduced by
 * the function.
 * \ingroup array_traits
 */
template<typename Array>
inline typename ArrayTraits<Array>::pointer
getHeadPtr( Array &array )
{ return ArrayTraits<Array>::headPtr( array ); }

/*! This function allows access to the headPtr ArrayTraits function.
 * \ingroup array_traits
 */
template<typename Array>
inline typename ArrayTraits<Array>::const_pointer
getHeadPtr( const Array &array )
{
  return ArrayTraits<Array>::headPtr( array );
}

/*! This function allows access to the numberOfDimensions ArrayTraits function.
 *
 * This function is simply a more concise way to access the numberOfDimensions
 * static member function associated with the ArrayTraits class. It simply 
 * forwards calls to get the number of dimensions of an array to the
 * associated Utility::ArrayTraits class. The array type will be deduced
 * by the function.
 * \ingroup array_traits
 */
template<typename Array>
inline typename ArrayTraits<Array>::size_type getNumberOfArrayDimensions(
                                                           const Array& array )
{
  return ArrayTraits<Array>::numberOfDimensions( array );
}

/*! This function allows access to the dimensionSizes ArrayTraits function.
 * 
 * This function is simply a more concise way to access the dimensionSizes
 * static member function associated with the ArrayTraits class. It simply
 * forwards calls to get the dimension sizes of an array to the associated 
 * Utility::ArrayTraits class. 
 * \ingroup array_traits
 */
template<typename Array,
         typename IntType,
         template<typename,typename...> class DimSizeArray>
inline void getArrayDimensionSizes( const Array& array,
                                    DimSizeArray<IntType>& dim_size_array )
{
  ArrayTraits<Array>::dimensionSizes( array, dim_size_array );
}

/*! This function allows access to the size ArrayTraits function.
 *
 * This function is simply a more concise way to access the size static
 * member function associated with the ArrayTraits class. It simply forwards
 * calls to get the size of an array to the associated
 * Utility::ArrayTraits class. It is important to note that the array
 * type will be deduced by the function.
 * \ingroup array_traits
 */
template<typename Array>
inline typename ArrayTraits<Array>::size_type
getArraySize( const Array &array )
{
  return ArrayTraits<Array>::size( array );
}

/*! This function allows access to the resize ArrayTraits function.
 *
 * This function is simply a more concise way to access the resize static
 * member function associated with the ArrayTraits class. It simply forwards
 * calls to resize an array to the assocaited Utility::ArrayTraits
 * class. It is important to note that the array type will be deduced by the
 * function.
 * \ingroup array_traits
 */
template<typename Array>
inline void
resizeArray( Array &array, typename ArrayTraits<Array>::size_type n )
{
  return ArrayTraits<Array>::resize( array, n );
}

/*! This function allows access to the reshape ArrayTraits function.
 *
 * This function is simply a more concise way to access the reshape static
 * member function associated with the ArrayTraits class. It simply forwards
 * calls to reshape the array to the associated Utility::ArrayTraits class.
 * It is important to note that the array type will be deduced by the
 * function.
 * \ingroup array_traits
 */
template<typename Array,
         typename IntType,
         template<typename,typename... > class DimSizeArray>
inline void reshapeArray( Array& array,
                          const DimSizeArray<IntType> dim_size_array )
{
  ArrayTraits<Array>::reshape( array, dim_size_array );
}

/*! This function allows access to the toString ArrayTraits function
 *
 * This function is simply a more concise way to access the toString static
 * member function associated with the ArrayTraits class. It simply forwards
 * calls to convert the array to a string to the associated 
 * Utility::ArrayTraits class. The array type will be deduced by the function
 * and need not be explicitly stated.
 * \ingroup array_traits
 */
template<typename Array>
inline std::string arrayToString( Array& array )
{
  return ArrayTraits<Array>::toString( array );
}

/*! This function allows access to the fromString ArrayTraits function
 *
 * This function is simply a more concise way to access the fromString static
 * member function associated with the ArrayTraits class. It simply forwards
 * calls to convert the string to an array to the associated
 * Utility::ArrayTraits class. The array type will not be deduced by the
 * function and needs to be stated explicitly.
 * \ingroup array_traits
 */
template<typename Array>
inline Array stringToArray( const std::string& string )
{
  try{
    return ArrayTraits<Array>::fromString( string );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Could not convert the string to an array!" );
}

/*! This function allows arrays to be placed in a stream object
 *
 * To avoid ambiguous overloads with the << operator we use the same
 * trick that is commonly employed when using boost::enable_if. Only
 * the specializations of the ArrayTraits class have the 
 * AvoidAmbiguousOverloads typedef defined. Therefore the compiler will
 * only resolve the AvoidAmbiguousOverloads template parameter when the
 * Array type has an ArrayTraits specialization. When it cannot resolve the
 * template parameter it will move on to the next overload for the operator.
 * \ingroup array_traits
 */
template<typename T,
         template<typename,typename...> class Array,
         typename AvoidAmbiguousOverloads = typename ArrayTraits<Array<T> >::AvoidAmbiguousOverloads>
std::ostream& operator<<( std::ostream& os, const Array<T>& array )
{
  ArrayTraits<Array<T> >::toStream( os, array );

  return os;
}

/*! This function allows access to the view ArrayTriats function.
 *
 * This function is simply a more concise way to access the view static
 * member function associated with the ArrayTraits class. It simply forwards
 * calls to get a view of the array to the associated
 * Utility::ArrayTraits class. It is important to note that the array
 * type will be deduced by the function.
 * \ingroup array_traits
 */
template<typename Array>
inline typename ArrayTraits<Array>::ArrayViewType
getArrayView( Array& array,
	      const typename ArrayTraits<Array>::size_type offset = Teuchos::OrdinalTraits<typename ArrayTraits<Array>::size_type>::zero(),
	      typename ArrayTraits<Array>::size_type size = Teuchos::OrdinalTraits<typename ArrayTraits<Array>::size_type>::invalid() )
{
  // make sure the offset and size supplied are acceptable
  remember( typename ArrayTraits<Array>::size_type array_size =
	    getArraySize( array ) );
  testPrecondition( offset < array_size );
  testPrecondition( size == Teuchos::OrdinalTraits<typename ArrayTraits<Array>::size_type>::invalid() || ( size > Teuchos::OrdinalTraits<typename ArrayTraits<Array>::size_type>::zero() && size <= array_size-offset ) );

  return ArrayTraits<Array>::view( array, offset, size );
}

/*! This function allows access to the view ArrayTraits function.
 * \ingroup array_traits
 */
template<typename Array>
inline typename ArrayTraits<Array>::ArrayConstViewType
getArrayView( const Array& array,
	      const typename ArrayTraits<Array>::size_type offset = Teuchos::OrdinalTraits<typename ArrayTraits<Array>::size_type>::zero(),
	      const typename ArrayTraits<Array>::size_type size = Teuchos::OrdinalTraits<typename ArrayTraits<Array>::size_type>::invalid() )
{
  // make sure the offset and size supplied are acceptable
  remember( typename ArrayTraits<Array>::size_type array_size =
	    getArraySize( array ) );
  testPrecondition( offset < array_size );
  testPrecondition( size == Teuchos::OrdinalTraits<typename ArrayTraits<Array>::size_type>::invalid() || ( size > Teuchos::OrdinalTraits<typename ArrayTraits<Array>::size_type>::zero() && size <= array_size-offset ) );

  return ArrayTraits<Array>::view( array, offset, size );
}

/*! This function allows access to the copyView ArrayTraits function
 *
 * This function is simply a more concise way to access the copyView
 * static member function associated with the ArrayTraits class. It simply
 * forwards calls to copy the ArrayView object to the associated
 * Utility::ArrayTraits class. It is important to note that the array
 * type will be deduced by the function.
 * \ingroup array_traits
 */
template<typename Array>
inline void copyArrayView(
                 Array& array,
		 const typename ArrayTraits<Array>::ArrayViewType& array_view )
{
  ArrayTraits<Array>::copyView( array, array_view );
}

/*! This function allows access to the copyView ArrayTraits function
 * \ingroup array_traits
 */
template<typename Array>
inline void copyArrayView(
            Array& array,
	    const typename ArrayTraits<Array>::ArrayConstViewType& array_view )
{
  ArrayTraits<Array>::copyView( array, array_view );
}

} // end Utility namespace

#endif // end UTILITY_ARRAY_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_ArrayTraitsDecl.hpp
//---------------------------------------------------------------------------//

