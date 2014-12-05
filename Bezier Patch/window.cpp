#include "window.h"
using namespace std;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
static float x = 0;
static float y = -1;
static float z = -6;
Vector4 p[16];
bool wave = false;
bool reflect = true;
bpatch bPatch;
GLuint texture[5];
GLuint cube;
double t = 0;
Camera camera;
//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
  displayCallback();         // call display routine to show the object
}

void Window::load() {

	camera.set(Vector3(0.0, 1, 6), Vector3(0, 1, 0), Vector3(0, 1, 0));

	p[0] = Vector4(6, 0, 6, 0);
	p[1] = Vector4(2, 0, 6, 0);
	p[2] = Vector4(-2, 0, 6, 0);
	p[3] = Vector4(-6, 0, 6, 0);
	p[4] = Vector4(6, 0, 2, 0);
	p[5] = Vector4(2, 0, 2, 0);
	p[6] = Vector4(-2, 0, 2, 0);
	p[7]= Vector4(-6, 0, 2, 0);
	p[8] = Vector4(6, 0, -2, 0);
	p[9] = Vector4(2, 0, -2, 0);
	p[10] = Vector4(-2, 0, -2, 0);
	p[11] = Vector4(-6, 0, -2, 0);
	p[12] = Vector4(6, 0, -6, 0);
	p[13] = Vector4(2, 0, -6, 0);
	p[14] = Vector4(-2, 0, -6, 0);
	p[15] = Vector4(-6, 0, -6, 0);
	bPatch.setPoints(p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8],p[9],p[10],p[11],p[12],p[13],p[14],p[15]);
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
	cube = SOIL_load_OGL_cubemap(
		"right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "back.jpg", "top.jpg",
		SOIL_LOAD_RGB,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
		);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,
		GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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
  //glTranslatef(x, y, z);    // walk camera back 20 units so that it looks at the origin (or else it's in the origin)
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
	Matrix4 glmatrix;
	double px = 0;
	double py = 0;
	double pz = 0;
	Vector4 pv;
	if (wave){
		for (int i = 0; i < 16; i++) {
			pv = p[i];
			px = pv.get(0);
			pz = pv.get(2);
			py = .5 * sin(sqrt((px*px) + (pz*pz) + t*M_PI/2));
			pv.setValue(1, py);
			p[i] = pv;
		}
		t = t + 1;
		bPatch.setPoints(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14], p[15]);
		bPatch.evalBPatch();
	}
	GLint texLoc;
	Matrix4 m;
	m = camera.getInverse();
	texLoc = glGetUniformLocation(Globals::shader->getPid(), "P");
	glUniformMatrix4fv(texLoc, 1, GL_TRUE, m.getMatrixFloat());
	texLoc = glGetUniformLocation(Globals::shader->getPid(), "Camera");
	glUniform3f(texLoc, camera.e.getX(),camera.e.getY(),camera.e.getZ());
	texLoc = glGetUniformLocation(Globals::shader->getPid(), "front");
	glUniform1i(texLoc, 0);
	texLoc = glGetUniformLocation(Globals::shader->getPid(), "left");
	glUniform1i(texLoc, 1);
	texLoc = glGetUniformLocation(Globals::shader->getPid(), "back");
	glUniform1i(texLoc, 2);
	texLoc = glGetUniformLocation(Globals::shader->getPid(), "right");
	glUniform1i(texLoc, 3);
	texLoc = glGetUniformLocation(Globals::shader->getPid(), "top");
	glUniform1i(texLoc, 4);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode

	glmatrix = camera.getInverse();
	glmatrix.transpose();
	glLoadMatrixd(glmatrix.getPointer());

	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Select GL_MODULATE to mix texture with polygon color for shading:
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Use bilinear interpolation:
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3d(1, 1, 1);

	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-6, -2,6);
	glTexCoord2d(1, 0);
	glVertex3d(6, -2, 6);
	glTexCoord2d(1, 1);
	glVertex3d(6, 10, 6);
	glTexCoord2d(0, 1);
	glVertex3d(-6, 10, 6);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1]);

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-6, -2, -6);
	glTexCoord2d(1, 0);
	glVertex3d(-6, -2, 6);
	glTexCoord2d(1, 1);
	glVertex3d(-6, 10, 6);
	glTexCoord2d(0, 1);
	glVertex3d(-6, 10, -6);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[2]);

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(6, -2, -6);
	glTexCoord2d(1, 0);
	glVertex3d(-6, -2, -6);
	glTexCoord2d(1, 1);
	glVertex3d(-6, 10, -6);
	glTexCoord2d(0, 1);
	glVertex3d(6, 10, -6);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[3]);

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(6, -2, 6);
	glTexCoord2d(1, 0);
	glVertex3d(6, -2, -6);
	glTexCoord2d(1, 1);
	glVertex3d(6, 10, -6);
	glTexCoord2d(0, 1);
	glVertex3d(6, 10, 6);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[4]);

	glBegin(GL_QUADS);
	glTexCoord2d( 0, 0);
	glVertex3d(-6, 10, 6);
	glTexCoord2d(1, 0);
	glVertex3d(6, 10, 6);
	glTexCoord2d(1, 1);
	glVertex3d(6, 10, -6);
	glTexCoord2d( 0, 1);
	glVertex3d(-6, 10, -6);
	glEnd();

	
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_CULL_FACE);

	/*
	glEnable(GL_TEXTURE_CUBE_MAP);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Select GL_MODULATE to mix texture with polygon color for shading:
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Use bilinear interpolation:
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Globals::sky->bind();
	glColor3d(1, 1, 1);

	glBegin(GL_QUADS);
	glVertex3d(-6, 10, 6);
	glVertex3d(6, 10, 6);
	glVertex3d(6, 10, -6);
	glVertex3d(-6, 10, -6);

	

	glEnd();
	Globals::sky->unbind();
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	glDisable(GL_TEXTURE_CUBE_MAP);
	*/
	if (reflect) {
		glColor3d(0, 0, 1);
		Globals::shader->bind();
		bPatch.draw();
		Globals::shader->unbind();
	}
	else {
		glColor3d(0, 0, 1);
		bPatch.draw();
	}
	glFlush();
	glutSwapBuffers();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when users press specific keys on the keyboard
void Window::keyboardCallback(unsigned char key, int xn, int yn) {
	glMatrixMode(GL_PROJECTION);
	switch (key) {
	case 'z':
		camera.moveForward(1);
		break;
	case 'Z':
		camera.moveBackward(1);
		break;
	case 'w':
		camera.rotateX(5);
		break;
	case's':
		camera.rotateX(-5);
		break;
	case 'a':
		camera.rotateY(5);
		break;
	case 'd':
		camera.rotateY(-5);
		break;
	case 'r':
		camera.set(Vector3(0.0, 1, 6), Vector3(0, 1, 0), Vector3(0, 1, 0));
		break;
	case 'p':
		wave = !wave;
		if (wave) 
			std::cout << "WAVE" << std::endl;
		else
			std::cout << "NO WAVE" << std::endl;
		break;
	case'e':
		reflect = !reflect;
		if (reflect)
			std::cout << "REFLECT" << std::endl;
		else
			std::cout << "NO REFLECT" << std::endl;
	}
	glMatrixMode(GL_MODELVIEW);

}


void Window::funcMouseCallback(int button, int state, int x, int y) {
	
}

void Window::funcMouseMovement(int x, int y) {

}

void Window::funcKeyboardCallback(int key, int xn, int yn) {
	glMatrixMode(GL_PROJECTION);
	switch (key) {
	case GLUT_KEY_UP:
		camera.moveUp(1);
		break;
	case GLUT_KEY_DOWN:
		camera.moveDown(1);
		break;
	case GLUT_KEY_LEFT:
		camera.moveLeft(1);
		break;
	case GLUT_KEY_RIGHT:
		camera.moveRight(1);
		break;
	}
	glMatrixMode(GL_MODELVIEW);
}