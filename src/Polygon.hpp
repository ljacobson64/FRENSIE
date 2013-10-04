//---------------------------------------------------------------------------//
//!
//! \file   Polygon.hpp
//! \author Alex Robinson
//! \brief  Polygon class declaration
//!
//---------------------------------------------------------------------------//

#ifndef POLYGON_HPP
#define POLYGON_HPP

// Std Lib Includes
#include <list>
#include <iostream>

// FACEMC Includes
#include "Tuple.hpp"
#include "ThreeSpaceTraitsAndPolicy.hpp"
#include "LinearAlgebraPolicy.hpp"

namespace FACEMC{

template<typename OrdinalType,typename ScalarType>
class Polygon
{

public:

  //@{
  //! Typedefs
  //! Typedef for ordinal type
  typedef OrdinalType ordinaltype;
  //! Typedef for scalar type
  typedef ScalarType scalarType;
  //! Typedef for a polygon corner
  typedef Trip<ScalarType,ScalarType,ScalarType> Point;
  //! Typedef 
  //@}

private:

  //! Typedef for scalar traits
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  //! Typedef for cell ordinal traits
  typedef Teuchos::OrdinalTraits<OrdinalType> OT;
  //! Typedef for three space traits and policy struct
  typedef ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  //! Typedef for vector
  typedef typename ThreeSpace::Vector Vector;
  //! Typedef for matrix
  typedef typename ThreeSpace::Matrix Matrix;
  //! Typdef for linear algebra policy
  typedef LinearAlgebraPolicy<ScalarType> LAP;
  //! Typedef for projected point
  typedef Pair<ScalarType,ScalarType> PointProjection;

public:

  //! Constructor
  Polygon( const OrdinalType polygon_id,
	   const std::list<Point> &ordered_polygon_corners );

  //! Constructor
  Polygon( const OrdinalType polygon_id,
	   const std::list<Point> &ordered_polygon_corners,
	   const Vector &polygon_plane_unit_normal );

  //! Destructor
  ~Polygon()
  { /* ... */ }

  //! Return the polygon id
  inline OrdinalType getId() const;

  //! Return the area of the polygon
  inline ScalarType getArea() const;

  //! Return the largest x-coordinate
  inline ScalarType getLargestXCoordinate() const;

  //! Return the largest y-coordinate
  inline ScalarType getLargestYCoordinate() const;
  
  //! Return the largest z-coordinate
  inline ScalarType getLargestZCoordinate() const;
	   
  //! Return the polygon centroid
  inline Point getCentroid() const;

  //! Return the unit normal to the plane of the polygon
  inline Vector getPolygonPlaneUnitNormal() const;

  //! Print the polygon
  void print( std::ostream &output_stream ) const;

protected:

  //! Compute the unit normal to the plane of the polygon
  static Vector calculatePolygonPlaneUnitNormal( 
				     const std::list<Point> &polygon_corners );

  //! Find and set the largest coordinates of the polygon
  static void getLargestCoordinates( const std::list<Point> &polygon_corners,
				     Point &largest_coordinates );

  //! Create and set the transformation matrix and vector
  static void getTransformMatrixAndVector( 
				       const Vector &polygon_plane_unit_normal,
				       const Point &polygon_corner,
				       Matrix &rotation_matrix,
				       Vector &translation_vector );
  
  //! Simplify the polygon by transforming plane-of-polygon to x-y plane
  static void transformPolygon( 
		     const std::list<Point> &polygon_corners,
		     std::list<PointProjection> &transformed_polygon_corners,
		     const Matrix &rotation_matrix,
		     const Vector &translation_vector );

  //! Apply transform to a point on the polygon (move to x-y plane)
  static PointProjection applyTransform( const Point &point_on_polygon,
					 const Matrix &rotation_matrix,
					 const Vector &translation_vector );

  //! Apply reverse transform to point on the x-y plane
  static Point applyReverseTransform( const PointProjection &xy_plane_point,
				      const Matrix &rotation_matrix,
				      const Vector &translation_vector );

  //! Calculate the area of a simplified polygon
  static ScalarType calculateArea( 
		        const std::list<PointProjection> &simplified_polygon );

  //! Calculate the polygon centroid
  static PointProjection calculateCentroid( 
			  const std::list<PointProjection> &simplified_polygon,
			  const ScalarType polygon_area );

  //! Calculate the x-coordinate of a simplified polygon centroid
  static ScalarType calculateCentroidXCoordinate(
			  const std::list<PointProjection> &simplified_polygon,
			  const ScalarType polygon_area );

  //! Calculate the y-coordinate of a simplified polygon centroid
  static ScalarType calculateCentroidYCoordinate(
			const std::list<PoinProjection> &simplified_polygon );

private:

  // Polygon Id
  OrdinalType d_id;

  // Polygon corners
  std::list<PointProjection> d_corners;

  // Largest coordinates of the polygon
  Point d_largest_coordinates;

  // Polygon area
  ScalarType d_area;

  // Centroid of the polygon
  Point d_centroid;

  // Unit normal to plane of polygon
  Vector d_unit_normal;

  // Rotation matrix to transform plane-of-polygon to x-y plane
  Matrix d_rotation_matrix;

  // Translation vector to transform plane-of-polygon to x-y plane
  Vector d_translation_vector;
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Polygon_def.hpp"

//---------------------------------------------------------------------------//

#endif // end POLYGON_HPP

//---------------------------------------------------------------------------//
// end Polygon.hpp
//---------------------------------------------------------------------------//
