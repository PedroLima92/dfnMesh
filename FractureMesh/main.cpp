
#ifdef HAVE_CONFIG_H
#include <pz_config.h>
#endif

#include "pzgmesh.h"
#include "pzgengrid.h"
#include "TPZExtendGridDimension.h"
#include "TPZVTKGeoMesh.h"

// #include "pzlog.h"

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>

#include <set>
#include <map>
#include <vector>

#include "TRSFractureMesh.h"
#include "TRSRibs.h"
#include "TRSFace.h"

//MATERIAL ID MAP
// 1 gmesh
// 4 skeleton
// 12 ribs that will be divided
// 19 children ribs
// 20 mid-fracture cut faces
// 35 end-fracture cut faces
// 40 Fracture plane
// 45 Intersection points in end-faces

using namespace std;

int main(){


  // Creating the Geo mesh

	int dimel = 4;
	TPZManVector<REAL, 3> x0(3, 0.), x1(3, 4);
	x1[2] = 0.;
	TPZManVector<int, 2> nelx(2, dimel);
	TPZGenGrid gengrid(nelx, x0, x1);
	gengrid.SetElementType(EQuadrilateral);
	TPZGeoMesh *gmesh = new TPZGeoMesh;
	gmesh->SetDimension(2);
	gengrid.Read(gmesh);

	// Mesh 3D

  TPZExtendGridDimension extend(gmesh, 1);
  extend.SetElType(1);
  TPZGeoMesh *gmesh3d = extend.ExtendedMesh(3);
  gmesh = gmesh3d;
  //std::ofstream out3("3DMESH.vtk");
  //TPZVTKGeoMesh::PrintGMeshVTK(gmesh, out3, true);


	//    Reading coordinates of a plane from txt file
	string value;
  int npoints = 0;
	string line;
  // count number of corners
  while (npoints == 0){
    ifstream plane_file("fracture.txt");
    if (!plane_file)
    {
      std::cout << "Error reading file" << std::endl;
      DebugStop();
    }
    getline(plane_file, line);
		std::stringstream ss(line);
		while (getline(ss, value, ' '))
		{
			while (value.length() == 0){getline(ss, value, ' ');}
      npoints++;
		}
  }
  // then read points
	Matrix plane(3, npoints);
	int i = 0;
	int j = 0;
	std::cout << "Fracture plane defined as: \n";
  ifstream plane_file("fracture.txt");
	while (getline(plane_file, line))
	{
		std::stringstream ss(line);
		while (getline(ss, value, ' '))
		{
			while (value.length() == 0){getline(ss, value, ' ');}
			plane(i, j) = std::stod(value);
			std::cout << plane(i, j) << " , ";
			j++;
		}
		j = 0;
		i++;
		std::cout << std::endl;
	}
	std::cout << std::endl;


// well behaved fracture
// 2.9084405 1.6236484 0.091559516 1.3763516
// 2.5516489 2.2694336 2.4483511 2.7305664
// 1.3832619 2.8898022 1.6167381 0.11019779













    //  Construction of fracplane and FractureMesh
    TRSFracPlane fracplane(plane);
    TRSFractureMesh fracmesh(fracplane, gmesh);
    
    // Find and split intersected ribs
    fracmesh.SplitRibs(19);

    // Find and split intersected faces
    fracmesh.SplitFaces(20);  

    // Split edge of fracture
    fracmesh.SplitFractureEdge();

    // triangulation of fracture plane
    fracmesh.SplitFracturePlane();


    std::ofstream meshprint("meshprint.txt");
    gmesh->Print(meshprint);
    //Print result
    std::ofstream out("./TestSurfaces.vtk");
    TPZVTKGeoMesh::PrintGMeshVTK(fracmesh.GetgeoMesh(), out, true);
    return 0;

}