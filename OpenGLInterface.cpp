//
// Created by Daniel Thompson on 4/26/16.
//

#include <glut.h>
#include <cmath>
#include <cstring>
#include <string>
#include <sstream>
#include "OpenGLInterface.h"

OpenGLInterface *callBackHandler;

void DisplayHandler() {
   callBackHandler->Display();
}

void ReshapeHandler(int w, int h) {
   callBackHandler->Reshape(w, h);
}

void KeyboardHandler(unsigned char key, int x, int y) {
   callBackHandler->HandleKeyboardInput(key, x, y);
}

void MouseButtonHandler(int button, int state, int x, int y) {
   callBackHandler->HandleMouseButton(button, state, x, y);
}

void MouseMotionHandler(int x, int y) {
   callBackHandler->HandleMouseMotion(x, y);
}

void MenuSelectionHandler(int command) {
   callBackHandler->HandleMenuSelection((MenuSelectionEnum) command);
}

void OpenGLInterface::Init(int argc, char **argv) {
   callBackHandler = this;

   glutInit(&argc, argv);

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
   glutInitWindowSize(640, 480);
   glutCreateWindow("3D Gasket");
   InitGraphics();

   glutReshapeFunc(ReshapeHandler);
   glutDisplayFunc(DisplayHandler);
   glutKeyboardFunc(KeyboardHandler);
   glutMouseFunc(MouseButtonHandler);
   glutMotionFunc(MouseMotionHandler);
   BuildPopupMenu();
   glutAttachMenu(GLUT_RIGHT_BUTTON);
   glClearColor(.2, .2, .2, 1.0);

   // create lights

   GLfloat position0[4] = { 5, 5, 5, 1 };
   GLfloat color0[4] = {.7f, .7f, .7f, 1};
   _lights[0] = GLLight(position0, color0, .001f);

   GLfloat position1[4] = { -4, 5, 5, 1 };
   GLfloat color1[4] = {.706f, .49f, .063f, 1};
   _lights[1] = GLLight(position1, color1, .001f);

   GLfloat position2[4] = { 5, 5, -15, 1 };
   GLfloat color2[4] = {.047f, .541f, .133f, 1};
   _lights[2] = GLLight(position2, color2, .001f);

   GLfloat position3[4] = { -5, -5, -15, 1 };
   GLfloat color3[4] = {.706f, .11f, .063f, 1};
   _lights[3] = GLLight(position3, color3, .001f);

   glutMainLoop();
}

void OpenGLInterface::InitGraphics() {
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);
   glEnable(GL_LIGHT2);
   glEnable(GL_LIGHT3);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_BLEND);
   _polygonMode = GL_FILL;
   glPolygonMode (GL_FRONT_AND_BACK, _polygonMode);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glShadeModel(GL_FLAT);
}

void OpenGLInterface::BuildPopupMenu (void) {
   glutCreateMenu(MenuSelectionHandler);
   glutAddMenuEntry ("Increase FOV \t\t]", MENU_INCREASE_FOV);
   glutAddMenuEntry ("Decrease FOV \t\t[", MENU_DECREASE_FOV);
   glutAddMenuEntry ("Cycle Polygon Mode \t p", MENU_POLYGON_WIREFRAME);
}

void OpenGLInterface::HandleMenuSelection(MenuSelectionEnum command) {

   switch (command)
   {
      case MENU_POLYGON_WIREFRAME:
         if (_polygonMode == GL_LINE)
            _polygonMode = GL_FILL;
         else if (_polygonMode == GL_FILL)
            _polygonMode = GL_POINT;
         else if (_polygonMode == GL_POINT)
            _polygonMode = GL_LINE;
         glPolygonMode(GL_FRONT_AND_BACK, _polygonMode);
         break;
      case MENU_INCREASE_FOV:
         _perspectiveFOV += 2;
         ResetPerspective();
         break;
      case MENU_DECREASE_FOV:
         _perspectiveFOV -= 2;
         ResetPerspective();
         break;
   }
   // Almost any menu selection requires a redraw
   glutPostRedisplay();
}

void OpenGLInterface::HandleKeyboardInput(unsigned char key, int x, int y) {

   GLfloat rad = ToRadians(_rotY);
   GLfloat cosine = (GLfloat) (cos(rad) * _keyboardSensitivity);
   GLfloat sine = (GLfloat) (sin(rad) * _keyboardSensitivity);

   switch (key)
   {
      case 'w':
         _position[0] += sine;
         _position[2] -= cosine;
         break;
      case 's':
         _position[0] -= sine;
         _position[2] += cosine;
         break;
      case 'a':
         _position[0] -= cosine;
         _position[2] -= sine;
         break;
      case 'd':
         _position[0] += cosine;
         _position[2] += sine;
         break;
      case 'q':
         _position[1] -= 1;

         break;
      case 'e':
         _position[1] += 1;

         break;

      case '[':
         HandleMenuSelection(MENU_DECREASE_FOV);
         break;
      case ']':
         HandleMenuSelection(MENU_INCREASE_FOV);
         break;
      case 'p':
         HandleMenuSelection(MENU_POLYGON_WIREFRAME);
         break;


      default:
         break;
   }

   glutPostRedisplay();

}


void OpenGLInterface::ResetPerspective() {
   GLint params[4] = {0, 0, 0, 0};

   glGetIntegerv(GL_VIEWPORT, params);

   Reshape(params[2], params[3]);
}


void OpenGLInterface::Display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glLoadIdentity();

   glRotatef(_rotX, 1, 0, 0);
   glRotatef(_rotY, 0, 1, 0);

   glTranslatef(-_position[0], -_position[1], -_position[2]);

   //glPushMatrix();

   // key light

   for (int i = 0; i < 4; i++) {
      _lights[i].Render();
   }

   // display objects


   DrawOverlay();

   glFlush();
   //checkError();
}



void OpenGLInterface::HandleMouseButton(int button, int state, int x, int y) {
   if (button == GLUT_LEFT_BUTTON)
   {
      _mousePrevX = x;
      _mousePrevY = y;
   }
}

void OpenGLInterface::HandleMouseMotion(int x, int y) {
   int xDiff = _mousePrevX - x;
   int yDiff = _mousePrevY - y;

   _rotX -= (GLfloat)yDiff * _mouseSensitivity;
   _rotY -= (GLfloat)xDiff * _mouseSensitivity;

   _mousePrevX = x;
   _mousePrevY = y;
   glutPostRedisplay();
}


void OpenGLInterface::Reshape(int w, int h) {
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   gluPerspective(_perspectiveFOV, (GLfloat)w / h, _nearPlane, _farPlane);
   glMatrixMode(GL_MODELVIEW);
   glutPostRedisplay();
}


void OpenGLInterface::DrawOverlay() {

   void* font = GLUT_BITMAP_8_BY_13;

   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();
   gluOrtho2D(0, 1024, 0, 720);
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
   glDisable(GL_LIGHTING);
   glDisable(GL_DEPTH_TEST);

   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

   glBegin(GL_QUADS); {
      glColor4f(0.0f, 0.0f, 0.0f, .5f);
      glVertex3f(0.0, 720.0, 0.0);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(225.0, 0.0, 0.0);
      glVertex3f(225.0, 720.0, 0.0);
   }
   glEnd();

   glPolygonMode(GL_FRONT_AND_BACK, _polygonMode);

   glColor3f(1, 1, 1);

   glRasterPos2i(10, 690);
   DrawString(font, "Position");

   char *str;
   int length;

   /*std::ostringstream stringStream;
   stringStream << "Hello";

   std::string copyOfStr = stringStream.str();

   std::string x = "lsdf";
   */

   length = snprintf(NULL, 0, "[%.1f, %.1f, %.1f]", _position[0], _position[1], _position[2]);
   if (!(str = (char *) malloc((length + 1) * sizeof(char))))
      exit(1);
   length = snprintf(str, length + 1, "[%.1f, %.1f, %.1f]", _position[0], _position[1], _position[2]);
   printf("\nPosition: [%.1f, %.1f, %.1f]", _position[0], _position[1], _position[2]);
   printf("%i", length);

   glRasterPos2i(30, 650);
   DrawString(font, str);

   free(str);

   glRasterPos2i(10, 610);
   DrawString(font, "Rotation");

   length = snprintf(NULL, 0, "[%.1f, %.1f]", _rotX, _rotY);
   if (!(str = (char *) malloc((length + 1) * sizeof(char))))
      exit(1);
   length = snprintf(str, length + 1, "[%.1f, %.1f]", _rotX, _rotY);
   printf("\nRotation: [%.1f, %.1f]", _rotX, _rotY);
   printf("%i", length);

   glRasterPos2i(30, 570);
   DrawString(font, str);

   free(str);

   glRasterPos2i(10, 450);
   DrawString(font, "Perspective FOV");
   length = snprintf(NULL, 0, "[%i]", _perspectiveFOV);
   if (!(str = (char *) malloc((length + 1) * sizeof(char))))
      exit(1);
   length = snprintf(str, length + 1, "[%i]", _perspectiveFOV);
   printf("\n[%i]", _perspectiveFOV);

   //printf("%i", length);
   glRasterPos2i(30, 410);
   DrawString(font, str);

   glRasterPos2i(10, 370);

   DrawString(font, "Polygon Mode");

   glRasterPos2i(30, 330);

   switch (_polygonMode) {
      case GL_LINE:
         DrawString(font, "Line");
         break;
      case GL_POINT:
         DrawString(font, "Point");
         break;
      case GL_FILL:
         DrawString(font, "Fill");
         break;
      default:
         DrawString(font, "Unknown");
         break;
   }

   length = snprintf(NULL, 0, "[%i]", _perspectiveFOV);
   if (!(str = (char *) malloc((length + 1) * sizeof(char))))
      exit(1);
   snprintf(str, length + 1, "[%i]", _perspectiveFOV);
   printf("\n[%i]", _perspectiveFOV);
   //printf("%i", length);

   glRasterPos2i(30, 410);
   DrawString(font, str);

   glEnable(GL_LIGHTING);
   glEnable(GL_DEPTH_TEST);

   glPopMatrix();
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);

}

void OpenGLInterface::DrawString(void * font, char* string) {
   for (int i = 0; i < strlen(string); i++) {

      glutBitmapCharacter(font, string[i]);
   }
}

void OpenGLInterface::DrawString(void * font, std::string string) {
   for (int i = 0; i < string.length(); i++) {
      glutBitmapCharacter(font, string[i]);
   }
}

