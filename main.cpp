#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <cstdio>
#include ".\plataform.h"
#include ".\robot.h"

// angle of rotation for the camera direction
float angle = 0.0f;

static int shoulder = 0, elbow = 0, claw1 = 0, claw2 = 0;

// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;

// XZ position of the camera
float x = 0.0f, z = 5.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

int positionX = 0, positionZ = -2;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void drawSnowMan() {

	glPushMatrix();
	glTranslatef(-0.5 , 0.6, 0.0);
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(1.0, -0.2, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();

	glTranslatef(0.5, 0.0, 0.0);
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.4, 0.5);
	glutSolidCube(1.0);

	glPopMatrix();

	glTranslatef(0.5, 0.0, 0.0);
	glRotatef((GLfloat)claw1, 0.0, 0.0, 0.0);
	glTranslatef(0.7, -0.1, 0.0);
	glPushMatrix();
	glScalef(0.5, 0.1, 0.5);
	glutSolidCube(1.0);
	
	glPopMatrix();

	glTranslatef(0.5, 0.0, 0.0);
	glRotatef(0.0, 0.0, 0.0, 0.0);
	glTranslatef(-0.5 , 0.2, 0.0);
	glPushMatrix();
	glScalef(1, 0.1, 0.5);
	glutSolidCube(1.0);

	glPopMatrix();

	glPopMatrix();

	glColor3f(0.1f, 0.5f, 0.5f);

	// Draw Body
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidCube(1.25f);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidCube(0.72f);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.1f, 0.0f, 0.0f);
	glTranslatef(0.5f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f, 0.5f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void renderScene(void) {

	if (deltaMove)
		computePos(deltaMove);

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, 1.0f, z,
		x + lx, 1.0f, z + lz,
		0.0f, 1.0f, 0.0f);

	//glColor3f(0.9f, 0.9f, 0.9f);
	drawPlataform();

	// Draw 36 SnowMen
	glPushMatrix();
	glTranslatef(positionX * 1, 0, positionZ * 1);
	drawSnowMan();
	glPopMatrix();
	
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy) {

	switch (key) {
		case 'i': {
		shoulder = (shoulder + 5);
		if (shoulder <= 40) {
			glutPostRedisplay();
		}
		else { shoulder = 40; }
		break; }
		case 'o': {
			shoulder = (shoulder - 5);
			if (shoulder >= 0) {
				glutPostRedisplay();
			}
			else { shoulder = 0; }
			break; }
		case 'p': {
			elbow = (elbow + 5);
			if (elbow <= 85) {
				glutPostRedisplay();
			}
			else { elbow = 85; }
			break; }
		case 'u': {
			elbow = (elbow - 5) % 90;
			if (elbow >= 1) {
				glutPostRedisplay();
			}
			else { elbow = 0; }
			break; }

		case 'x':{
			claw1 = (claw1 - 1);
			claw2 = (claw2 + 1);
			if(claw1 <= 2 || claw1 >= -2){
				glutPostRedisplay();
			}
			break;
		}

		case 119: { // w
			if (positionZ <= -100) {
				break;
				return;
			}
			positionZ--; break;
		}
		case 115: { // s
			if (positionZ >= 100) {
				break;
				return;
			}
			positionZ++; 
			break;
		}  
		case 97: { // a
			if (positionX <= -100) {
				break;
				return;
			}
			positionX--; 
			break;
		} 
				  
		case 100: { // d
			if (positionX >= 100) {
				break;
				return;
			}
			positionX++; 
			break;
		}  
	}

}

void pressKey(int key, int xx, int yy) {

	switch (key) {
		case GLUT_KEY_UP: deltaMove = 0.5f; break;
		case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_UP:
		case GLUT_KEY_DOWN: deltaMove = 0; break;
	}
}


void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;
		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else {// state = GLUT_DOWN
			xOrigin = x;
		}
	}
}

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1000, 600);
	glutCreateWindow("RobÅE3D");

	initPlataform();

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	//glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	// here are the two new functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}