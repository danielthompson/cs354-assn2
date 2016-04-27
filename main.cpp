#include <stdlib.h>
#include <glut.h>
#include <stdio.h>
#include "TrimeshLoader.h"
#include "OpenGLInterface.h"


/* #include <GL/glut.h> for linux */

GLfloat v[4][3] = {
      {0.0,       0.0,       1.0},
      {0.0,       0.942809,  -0.33333},
      {-0.816497, -0.471405, -0.333333},
      {0.816497,  -0.471405, -0.333333}};

GLfloat colors[4][3] = {{1.0, 0.0, 0.0},
                        {0.0, 1.0, 0.0},
                        {0.0, 0.0, 1.0},
                        {0.0, 0.0, 0.0}};



void checkError() {

   int error = glGetError();
   if (error != GL_NO_ERROR) {
      switch (error) {
         case GL_INVALID_ENUM:
            printf("GL_INVALID_ENUM");
            break;
         case GL_INVALID_VALUE:
            printf("GL_INVALID_VALUE");
            break;
         case GL_INVALID_OPERATION:
            printf("GL_INVALID_OPERATION");
            break;
         case GL_INVALID_FRAMEBUFFER_OPERATION:
            printf("GL_INVALID_FRAMEBUFFER_OPERATION");
            break;
         case GL_OUT_OF_MEMORY:
            printf("GL_OUT_OF_MEMORY");
            break;
         default:
            printf("UNKNOWN");
            break;
      }
   }
}

int main(int argc, char **argv) {
   /* enter number of subdivision steps here */
   /*

   if (argc > 1) {
      n = atoi(argv[1]);
   }
   else n = 2;

   */


   TrimeshLoader trimesh = TrimeshLoader();

   Trimesh mesh = Trimesh();

   trimesh.loadOBJ("models/mannequin.obj", &mesh);

   OpenGLInterface interface = OpenGLInterface(&mesh);

   interface.Init(argc, argv);

   interface.MainLoop();

   return 0;
}
