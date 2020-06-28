/*! 
 *  @brief     Describes a planar polygon from it's corner points.
 *  @details   
 *  @author    Pedro Lima
 *  @date      2019.05
 */

#ifndef DFNPolygon_h
#define DFNPolygon_h

#include "pzfmatrix.h"
#include "pzvec.h"
#include "pzmanvector.h"
#include "pzstack.h"

#include <stdio.h>
#include <tuple>
#include "pzmatrix.h"
#include "pzcompel.h"
#include "pzgeoelbc.h"


typedef TPZFMatrix<REAL> Matrix;

/*! 
 *  @brief     Describes a planar convex polygon from it's corner points.
 *  @details Enumeration of corner points should follow standard PZ topology, where 
 *  corner nodes are numbered counter-clockwise (clockwise should work as well) from
 *  zero to N. (This condition will automatically be met for triangles, but not 
 *  always for quadrilaterals and higher order polygons)
 */
class DFNPolygon
{
  private:
	/// Contains polygon corner coordinates. Matrix 3xn (n is the number of corners)
	Matrix fCornerPoints;
	
	/// Axis that define polygon orientation (Ax0 from node1 to node0, Ax1 from node1 to node2 and Ax2 the normal vector). Matrix 3x3
	Matrix fAxis ;

	/// Area of polygon
	double fArea;

	/// If nodes of this polygon have been added to a geometric mesh, this vector holds GeoNodes indices
	TPZManVector<int64_t> fPointsIndex;

  public:
	/// Empty constructor
	DFNPolygon(){};

	/// Define polygon from 3 to 4 corner points. Matrix should be 3xN (3 coordinates for each of the N corner points)
	DFNPolygon(const Matrix &CornerPoints);

	/// Copy constructor
	DFNPolygon(const DFNPolygon &copy);

	/// Assignment operator
	DFNPolygon &operator=(const DFNPolygon &copy);

	/// Define corner coordinates
	void SetCornersX(Matrix &CornerPoints);

	/// axis(i, j) returns component i of axis j
	REAL axis(int row, int col){return fAxis(row,col);}

	/// Get matrix with axis 0, 1 and 2 on each column
	Matrix axis() const {return fAxis;}

	/// Return corner coordinates
	Matrix GetCornersX() const;

	/// Return corner coordinates matching indices of corner nodes that have been added to GeoMesh
	Matrix GetRealCornersX(TPZGeoMesh* gmesh) const;

	/// Return area of polygon
	double area() const { return fArea; }

	/// Compute area of polygon
	REAL ComputeArea();

	/// Return true if the rib intersects the polygon
	bool Check_rib(const TPZManVector<REAL,3> &p1, const TPZManVector<REAL,3> &p2, TPZManVector<REAL,3> *intersection = nullptr);

	/// Return true if the rib intersects the polygon
	bool Check_rib(TPZGeoEl *rib, TPZManVector<REAL,3> *intersection = nullptr);

	/// Return true if a point is above the polygon plane
   	bool Check_point_above(const TPZVec<REAL> &point) const;

   	/// Check whether the point coordinates are within the polygon region
   	bool IsPointInPolygon(TPZVec<REAL> &point);
	
	/// Computes the intersection point with the polygon
	TPZManVector<REAL,3> CalculateIntersection(const TPZVec<REAL> &p1, const TPZVec<REAL> &p2);
   

	/**
	 * @brief Inserts corner nodes in geometric mesh
	 * @param Pointer to geometric mesh
	 * @return Vector with nodes indices in gmesh
	 */
	TPZManVector<int64_t,4> SetPointsInGeomesh(TPZGeoMesh *gmesh);

	/**
	 * @brief Returns index of GeoNode that was created for corner i using DFNPolygon::SetPointsInGeomesh(gmesh, matID)
	 * @param Local index of corner
	 */
	int64_t CornerIndex(int i) const{
		return fPointsIndex[i];
	}

	/**
	 * @brief Takes a set of coordinates in 3D and returns its projection onto the polygon
	*/
	TPZManVector<REAL, 3> GetProjectedX(TPZManVector<REAL, 3> &point);

  private:
	/// Checks consistency and initializes the datastructure of the object
	bool Check_Data_Consistency(Matrix CornerPoints);

};

#endif /* DFNPolygon */
