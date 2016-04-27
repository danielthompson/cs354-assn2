//
// Created by Daniel Thompson on 4/26/16.
//

#include <glut.h>
#include "GLLight.h"

GLLight::GLLight(GLfloat *position, GLfloat *color, GLfloat attenuation) {
   _position[0] = position[0];
   _position[1] = position[1];
   _position[2] = position[2];
   _position[3] = position[3];

   _color[0] = color[0];
   _color[1] = color[1];
   _color[2] = color[2];
   _color[3] = color[3];

   _attenuation = attenuation;
}

void GLLight::Render() {
   glLightfv(GL_LIGHT0, GL_POSITION, _position);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, _color);
   glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, &_attenuation);
}