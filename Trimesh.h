//
// Created by Daniel Thompson on 4/25/16.
//

#ifndef __TRIMESH_H__
#define __TRIMESH_H__

#include <vector>
#include <array>
#include <OpenGL/OpenGL.h>

class Trimesh {

public:
   Trimesh();

   ~Trimesh();

public:
   void addVertex(float pDouble[3]);

   void addFace(int pInt[3]);

   std::vector<std::array<float, 3>> *Vertices;
   std::vector<std::array<int, 3>> *Faces;
};




#endif //__TRIMESH_H__
