//  Geo file generated by Discrete Fracture Network methods 
// Fracture #1 

// POINTS DEFINITION 

h = 0;

Point(1) = {0,0,0, h};
Point(2) = {2,0,0, h};
Point(3) = {0,2,0, h};
Point(4) = {2,2,0, h};
Point(5) = {0,0,2, h};
Point(6) = {2,0,2, h};
Point(7) = {0,2,2, h};
Point(8) = {2,2,2, h};
Point(9) = {0.95,2,2, h};
Point(10) = {0.95,0,2, h};
Point(11) = {0.95,2,0, h};
Point(12) = {0.95,0,0, h};


// LINES DEFINITION 

Line(2) = {7,5};
Line(4) = {6,8};
Line(6) = {3,7};
Line(7) = {4,8};
Line(8) = {2,6};
Line(9) = {1,5};
Line(10) = {3,1};
Line(12) = {2,4};
Line(20) = {8,9};
Line(21) = {9,7};
Line(22) = {5,10};
Line(23) = {10,6};
Line(24) = {4,11};
Line(25) = {11,3};
Line(26) = {1,12};
Line(27) = {12,2};
Line(36) = {9,10};
Line(37) = {11,9};
Line(38) = {12,10};
Line(39) = {12,11};


// FACES DEFINITION 

Curve Loop(15) = {-10,6,2,-9};
Surface(15) = {15};
Curve Loop(17) = {12,7,-4,-8};
Surface(17) = {17};
Curve Loop(28) = {36,23,4,20};
Surface(28) = {28};
Curve Loop(29) = {-36,21,2,22};
Surface(29) = {29};
Curve Loop(30) = {-37,-24,7,20};
Surface(30) = {30};
Curve Loop(31) = {37,21,-6,-25};
Surface(31) = {31};
Curve Loop(32) = {-38,27,8,-23};
Surface(32) = {32};
Curve Loop(33) = {38,-22,-9,26};
Surface(33) = {33};
Curve Loop(34) = {-39,27,12,24};
Surface(34) = {34};
Curve Loop(35) = {39,25,10,26};
Surface(35) = {35};
Curve Loop(40) = {-36,-37,-39,38};
Surface(40) = {40};



// VOLUMES DEFINITION 

Surface Loop(3) = {15,29,31,33,35,40};
Volume(3) = {3};
Surface Loop(4) = {17,28,30,32,34,40};
Volume(4) = {4};


// COARSE ELEMENTS GROUPING

Physical Volume("c1",1) = {3};
Physical Volume("c2",2) = {4};



 // FRACTURES

// frac1[] = {40};

// Physical Surface("Fracture2",2) = {frac1[]};



// BOUNDARY CONDITIONS

// Physical Surface("bc1",1) = {15,17,28,29,30,31,32,33,34,35};
// Physical Surface("inlet") = {31, 30};
// Physical Surface("outlet") = {32, 33};
// Physical Surface("noflux") = {28, 29, 15, 35, 34, 17};
Physical Surface("inlet") = {28};
Physical Surface("outlet") = {15};
Physical Surface("noflux") = {29, 17, 31, 30, 35, 34, 33, 32};


BCfrac0[] = {36,37,39,38};
Physical Curve("BCfrac0", 10) = {BCfrac0[]};

// OPTIONS

Coherence Mesh;
Transfinite Curve{:} = 2;
// Transfinite Curve{2, 36, 4, 12, 39, 10} = 3;
Transfinite Surface{:};
Transfinite Volume{:};
Recombine Surface{:};
Recombine Volume{:};//+


