# Ongoing
- [ ] Tetrahedralization on volumetric mesh (gmesh should do it) 
  - [x] Search which volume encloses each face
  - [x] Inform to volumes what faces lie inside it 
  - [ ] **Write geometry to GMSH** 
    - [x] Write points 
    - [x] Write Lines 
    - [x] Define physical groups of lines 
    - [x] Write faces 
    - [x] Define physical groups of faces 
    - [x] Test rules for proper definition of surface loops 
    - [x] Write surface loops 
    - [x] Write volumes 
    - [x] Define physical groups of volumes 
    - [ ] Rewrite using gmsh API
# ToDo

- [ ] Mesh fracplane 
  - [x] Ear-clipping-like algorithm 
    - [ ] Legalize triangles 
- [ ] Face splitting 
  - [x] Store status of each rib and node
  - [x] Identify case 
  - [x] Store all intersections for each face 
  - [x] Father elements 
  - [ ] Quadrilateral splitting 
    - [x] Case 1 
    - [x] Case 2 
    - [ ] Case 3 
    - [ ] Case 4
    - [x] Case 5 
    - [ ] Case 6 
    - [ ] Case 7 
    - [ ] Case 8 (No ribs 1) 
    - [ ] Case 9 (No ribs 2) 
  - [ ] Triangle splitting 
    - [ ] Case 10 
    - [ ] Case 11 
    - [ ] Case 12 
    - [ ] Case 13 
    - [ ] Case 14 
    - [ ] Case 15 (No ribs 1) 
    - [ ] Case 16 (No ribs 2) 
- [ ] Tetrahedralization on volumetric mesh (gmesh should do it) 
  - [x] Search which volume encloses each face
  - [x] Inform to volumes what faces lie inside it 
  - [ ] Write geometry to GMSH 
    - [x] Write points 
    - [x] Write Lines 
    - [x] Define physical groups of lines 
    - [x] Write faces 
    - [x] Define physical groups of faces 
    - [x] Test rules for proper definition of surface loops 
    - [x] Write surface loops 
    - [x] Write volumes 
    - [x] Define physical groups of volumes 
    - [ ] Rewrite using gmsh API
- [ ] Check if rib cut happens too close to vertex 
- [ ] Check if face intersection happens too close to rib 
- [ ] Search for critical cases 
  - [ ] Fractures that are almost parallel to mesh plane 
  - [ ] Fracture that overlaps mesh plane should not divide anything 
- [ ] Id volumes that contain fracture corners 
- [ ] Check if point is too close to vertex -> rib -> face 
- [ ] Change comparisons from a == b to $|a-b|<\varepsilon$


# Done and Documented
- [x] Rib class
- [x] Face class
- [x] Fracture Plane class
  - [x] Check data consistency
  - [x] Compute axis
  - [x] Compute area
- [x] Fracture Mesh class
  - [x] Map of ribs
  - [x] Map of Mid-Faces
  - [x] Map of End-Faces
- [x] Create skeleton mesh
  - [x] Check if element already has skeleton 
- [x] Check if point is above or bellow plane
- [x] Check if rib is cut by infinite plane
- [x] Calculate intersection with inifinite plane
- [x] Check if intersection is within plane boundaries
  - [x] Compute area of triangles from every corner of plane to point
  - [x] Compare area of triangles to area of plane (to a tolerance)
- [x] Find faces that are cut
  - [x] Iterate over faces
  - [x] Iterate over its 1D neighbours through 1D sides
  - [x] Store in mid-faces if has 2 ribs cut
  - [x] Store in end-faces if has 1 rib cut
- [x] Find intersection points in end-faces
  - [x] figure out 'prettiest' conversion from TPZGeoEl to TRSFracPlane
  - [x] create EPoint for intersection points 
- [x] Connect intersection points to define fracture surface outline
  - [x] Connect them at the time an intersected face is found and pair of points are created
- [x] Split fracture front (fracture surface edges)
  - [x] iterate over end-faces
  - [x] find which edge cuts them
  - [x] sort them
  - [x] connect points accordingly