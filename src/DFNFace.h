/*! 
 *	DFNFace.hpp
 *  @authors   Pedro Lima
 *  @authors   Jorge Ordoñez
 *  @date      2018-2019
 */

#ifndef DFNFace_hpp
#define DFNFace_hpp

#include <stdio.h>
#include "pzmanvector.h"
#include "pzmatrix.h"
#include "pzcompel.h"
#include "pzgeoelbc.h"
#include "DFNRibs.h"

class DFNFractureMesh;

/// DFNFace class describes a plane and whether it's cut by a plane. It also carries a method to split itself into smaller sub faces.
class DFNFace
{
    
private:
    /// Face element index within it's gmesh
    int64_t fFaceIndex;

    /// Indicates whether it intersects a plane
    bool fIsCut;

    /// Indicates which ribs and nodes are cut
    TPZManVector<bool,8> fStatus;
    
    /// Vector with global indexes of its ribs
    TPZManVector<int64_t,4> fRibs;

    /// Vector of sub faces
    TPZVec<int64_t> fSubFaces;
    
    /// Index of in-plane intersection EPoint (only for FractureMesh::EndFaces)
    int64_t fIntersection = -1;
    
    /// Pointer to a fracture mesh
    DFNFractureMesh *fFracMesh = nullptr;

    /// Index of enclosing volume (-1 if no enclosing volume has been set)
    int64_t fEnclosingVolume = -1;
 
public:
    
    /// Empty constructor
    DFNFace();
    
    /// Constructor
    DFNFace(int64_t index, bool iscut);
    
    /// Copy constructor
    DFNFace(const DFNFace &copy);
    
    /// Assignment operator
    DFNFace &operator=(const DFNFace &copy);
    
    /// Define the element index and whether it cuts the plane
    void SetElementIndex(int64_t elindex, bool iscut);
    
    /// Element index
    int64_t ElementIndex() const;
    
    /// Intersects the plane or not
    bool IsCut() const;
    
    /// Return the subelement indices
    TPZVec<int64_t> SubElements() const;
    
    /// Set the subelement indices
    void SetChildren(TPZVec<int64_t> subels);
    
    /** 
     * @brief Divide the given this surface, generate subelements and return vector with indices
     * @param Material id for subelements
     * @return A vector with indices for all new subelements
     */
    void DivideSurface(int matid);
    
    /// Set status vector (boolean) that indicates which ribs and/or nodes are cut
    void SetStatus(TPZVec<bool> StatusVector){fStatus = StatusVector;}
    
    /**
     * @brief Returns the split pattern that should be used to split this face
     * @param Status vector (boolean) that indicates which ribs and/or nodes are cut
     * @return Integer that indicates which split pattern to use. (check documentation)
     */
    int GetSplitPattern(TPZVec<bool> &status);
    
    /// Set ribs of face
    void SetRibs(TPZVec<int64_t> &RibsIndexes) {fRibs = RibsIndexes;}

    /// Get ribs of face
    TPZVec<int64_t> GetRibs() {return fRibs;}

    /// Access intersection index data (only for FractureMesh::EndFaces)
    void SetIntersectionIndex(int64_t index) {fIntersection = index;}

    /// Returns index for intersection point in face (only for FractureMesh::EndFaces)
    int64_t IntersectionIndex() {return fIntersection;}

    /// Give face a pointer to which fracture is cutting it
    void SetFractureMesh(DFNFractureMesh *FractureMesh){fFracMesh = FractureMesh;}

    // /// Sets Father element
    // void SetFather(TPZGeoEl *father){ fFather = father;}
    // /// Get pointer to father element
    // TPZGeoEl *Father(){return fFather;}

    /// Set the volume in which this face is contained
    void SetEnclosingVolume(int64_t volumeIndex){fEnclosingVolume = volumeIndex;}
    /// Get the volume in which this face is contained
    int64_t EnclosingVolume(){return fEnclosingVolume;}
};
#endif /* DFNFace_h */