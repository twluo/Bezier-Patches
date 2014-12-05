#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glut.h>

#include "Window.h"
#include "Matrix4.h"
#include "main.h"
#include "object.h"
#include "Vector3.h"

using namespace std;

namespace Globals
{
  Object object;
  Shader *shader;
  Shader *sky;
};

int main(int argc, char *argv[])
{
  float specular[]  = {0.0, 0.0, 0.0, 1.0};
  float shininess[] = {100.0};
  float position[]  = {0.0, 1.0, 0.0, 0.0};	// lightsource position
  float ambient[] = { 1, 1, 1, 1 };
  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(Window::width, Window::height);      // set initial window size
  glutCreateWindow("MOHOHOHOHOHOHOHOHO");    	      // open window and set window title

  glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
  glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
  glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
  glShadeModel(GL_SMOOTH);             	      // set shading to smooth
  glMatrixMode(GL_PROJECTION); 

  glEnable(GL_NORMALIZE);

  // Generate material properties:
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  // Generate light source:
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
  glutIdleFunc(Window::idleCallback);
  glutKeyboardFunc(Window::keyboardCallback);
  glutMouseFunc(Window::funcMouseCallback);
  glutMotionFunc(Window::funcMouseMovement);
  glutSpecialFunc(Window::funcKeyboardCallback);
    
  // Initialize cube matrix:
  Globals::shader = new Shader("reflection.vert", "reflection.frag", true);
  Globals::sky = new Shader("skybox.vert", "skybox.frag", true);
  Globals::object.getMatrix().identity();
  Window::load();
  glutMainLoop();
  return 0;
}

