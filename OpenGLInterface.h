//
// Created by Daniel Thompson on 4/26/16.
//

#ifndef ASSN3_OPENGLINTERFACE_H
#define ASSN3_OPENGLINTERFACE_H

#include "Constants.h"
#include "GLLight.h"

class OpenGLInterface {

private:
   void InitGraphics();
   void BuildPopupMenu();

   void ResetPerspective();

   void DrawOverlay();
   void DrawString(void * font, char* string);
   void DrawString(void *font, std::string string);

   GLenum _polygonMode = GL_FILL;
   GLint _perspectiveFOV = 45;
   GLfloat _keyboardSensitivity = .5f;
   GLfloat _mouseSensitivity = .2f;
   int _mousePrevX = 0;
   int _mousePrevY = 0;
   GLfloat _nearPlane = 1;
   GLfloat _farPlane = 1000;

   GLfloat _position[3] = {0, 0, 10};
   GLfloat _rotX = 0;
   GLfloat _rotY = 0;

   GLLight _lights[4];

public:
   OpenGLInterface() {};

   void Init(int i, char **pString);
   void Display();

   void Reshape(int w, int h);

   void HandleKeyboardInput(unsigned char key, int x, int y);

   void HandleMouseButton(int button, int state, int x, int y);

   void HandleMouseMotion(int x, int y);

   void HandleMenuSelection(MenuSelectionEnum command);


};




#endif //ASSN3_OPENGLINTERFACE_H
