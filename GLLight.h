//
// Created by Daniel Thompson on 4/26/16.
//

#ifndef ASSN3_GLLIGHT_H
#define ASSN3_GLLIGHT_H

#include <OpenGL/OpenGL.h>

class GLLight {

public:
   GLLight() { };
   GLLight(GLfloat *position, GLfloat *color, GLfloat attenuation);

   GLfloat _position[4];
   GLfloat _color[4];
   GLfloat _attenuation;

   void Render();
};


#endif //ASSN3_GLLIGHT_H
