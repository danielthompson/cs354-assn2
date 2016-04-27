//
// Created by Daniel Thompson on 4/25/16.
//

#include "Trimesh.h"

void Trimesh::addFace(int *pInt) {
   int v0 = pInt[0];
   int v1 = pInt[1];
   int v2 = pInt[2];
   std::array<int, 3> val = {v0, v1, v2};

   Faces->push_back(val);

}

void Trimesh::addVertex(float *pDouble) {
   float v0 = pDouble[0];
   float v1 = pDouble[1];
   float v2 = pDouble[2];
   std::array<float, 3> val = {v0, v1, v2};

   Vertices->push_back(val);
}

Trimesh::Trimesh() {
   Vertices = new std::vector<std::array<float, 3>>();
   Faces = new std::vector<std::array<int, 3>>();
}

Trimesh::~Trimesh() {
   delete Vertices;
   delete Faces;
}
