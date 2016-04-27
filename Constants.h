//
// Created by Daniel Thompson on 4/26/16.
//

#ifndef ASSN3_CONSTANTS_H
#define ASSN3_CONSTANTS_H

#include <math.h>

#define TRUE 1
#define FALSE 0

enum MenuSelectionEnum {

   MENU_POLYGON_WIREFRAME,
   MENU_INCREASE_FOV,
   MENU_DECREASE_FOV

};

inline GLfloat ToRadians(const GLfloat degrees) {
   return degrees * (GLfloat)M_PI / 180.0f;
}

const GLfloat ONETHIRD = 1.0f / 3.0f;
const GLfloat TWOTHIRDS = 2.0f / 3.0f;

#endif //ASSN3_CONSTANTS_H
