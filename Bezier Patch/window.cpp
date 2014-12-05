#include "window.h"
using namespace std;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
bpatch bPatch;
GLuint texture[5];
//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
  displayCallback();         // call display routine to show the object
}

void Window::load() {
	bPatch.setPoints(Vector4(6, 0, 6, 0), Vector4(2, 0, 6, 0), Vector4(-2, 0, 6, 0), Vector4(-6, 0, 6, 0),
		Vector4(6, 0, 2, 0), Vector4(2, 0, 2, 0), Vector4(-2, 0, 2, 0), Vector4(-6, 0, 2, 0),
		Vector4(6, 0, -2, 0), Vector4(2, 0, -2, 0), Vector4(-2, 0, -2, 0), Vector4(-6, 0, -2, 0),
		Vector4(6, 0, -6, 0), Vector4(2, 0, -6, 0), Vector4(-2, 0, -6, 0), Vector4(-6, 0, -6, 0));
	bPatch.evalBPatch();
	texture[0] = SOIL_load_OGL_texture
		(
		"front.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	texture[1] = SOIL_load_OGL_texture
		(
		"left.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	texture[2] = SOIL_load_OGL_texture
		(
		"back.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	texture[3] = SOIL_load_OGL_texture
		(
		"right.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	texture[4] = SOIL_load_OGL_texture
		(
		"top.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	std::cout << "DONE" << std::endl;
}
//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
  cerr << "Window::reshapeCallback called" << endl;
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); // set perspective projection viewing frustum
  glTranslatef(0, -1, -6);    // walk camera back 20 units so that it looks at the origin (or else it's in the origin)
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
	glColor3d(0, 0, 1);
	bPatch.draw();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Select GL_MODULATE to mix texture with polygon color for shading:
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Use bilinear interpolation:
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3d(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-6, 0,6);
	glTexCoord2d(1, 0);
	glVertex3d(6, 0, 6);
	glTexCoord2d(1, 1);
	glVertex3d(6, 12, 6);
	glTexCoord2d(0, 1);
	glVertex3d(-6, 12, 6);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1]);

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-6, 0, -6);
	glTexCoord2d(1, 0);
	glVertex3d(-6, 0, 6);
	glTexCoord2d(1, 1);
	glVertex3d(-6, 12, 6);
	glTexCoord2d(0, 1);
	glVertex3d(-6, 12, -6);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[2]);

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(6, 0, -6);
	glTexCoord2d(1, 0);
	glVertex3d(-6, 0, -6);
	glTexCoord2d(1, 1);
	glVertex3d(-6, 12, -6);
	glTexCoord2d(0, 1);
	glVertex3d(6, 12, -6);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[3]);

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(6, 0, 6);
	glTexCoord2d(1, 0);
	glVertex3d(6, 0, -6);
	glTexCoord2d(1, 1);
	glVertex3d(6, 12, -6);
	glTexCoord2d(0, 1);
	glVertex3d(6, 12, 6);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[4]);

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-6, 12, 6);
	glTexCoord2d(1, 0);
	glVertex3d(6, 12, 6);
	glTexCoord2d(1, 1);
	glVertex3d(6, 12, -6);
	glTexCoord2d(0, 1);
	glVertex3d(-6, 12, -6);
	glEnd();
	glFlush();
	glutSwapBuffers();
}
//----------------------------------------------------------------------------
// Callback method called by GLUT when users press specific keys on the keyboard
void Window::keyboardCallback(unsigned char key, int x, int y) {
	glMatrixMode(GL_PROJECTION);
	switch (key) {
	case 'w':
		glTranslatef(0, 0, 1);
		break;
	case 's':
		glTranslatef(0, 0, -1);
		break;
	case 'a':
		glRotatef(5, 0, 1, 0);
		break;
	case 'd':
		glRotatef(-5, 0, 1, 0);
		break;
	case 'r':
		glLoadIdentity();
		gluPerspective(60.0, double(width) / (double)height, 1.0, 1000.0); // set perspective projection viewing frustum
		glTranslatef(0, -1, -6);    // walk camera back 20 units so that it looks at the origin (or else it's in the origin)
		break;
	}
	glMatrixMode(GL_MODELVIEW);

}


void Window::funcMouseCallback(int button, int state, int x, int y) {
	
}

void Window::funcMouseMovement(int x, int y) {

}

void Window::funcKeyboardCallback(int key, int x, int y) {
	glMatrixMode(GL_PROJECTION);
	switch (key) {
	case GLUT_KEY_UP:
		glTranslatef(0, -1, 0);
		break;
	case GLUT_KEY_DOWN:
		glTranslatef(0, 1, 0);
		break;
	case GLUT_KEY_LEFT:
		glTranslatef(1, 0, 0);
		break;
	case GLUT_KEY_RIGHT:
		glTranslatef(-1, 0, 0);
		break;
	}
	glMatrixMode(GL_MODELVIEW);
}