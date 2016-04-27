//
// Created by Daniel Thompson on 4/26/16.
//

#include "TrimeshLoader.h"

int main(int argc, char **argv) {
   TrimeshLoader trimesh = TrimeshLoader();

   Trimesh mesh = Trimesh();

   trimesh.loadOBJ("models/mannequin.obj", &mesh);

   int c = 0;
}