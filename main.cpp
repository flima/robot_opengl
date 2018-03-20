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

/*
***********************************************************************
-----------------------------------------------------------------------
ALUNOS => PEDRO MARQUES e FERNANDO LIMA
-----------------------------------------------------------------------
***********************************************************************/


// Robo
static int shoulder = 0, elbow = 0, upperClaw = 1, lowerClaw = -1;

// Angulo de rotacao da camera
float angle = 0.0f;

// Direcoes da camera
float lx = 0.0f, lz = -1.0f;

// Posicoes da camera
float x = 0.0f, z = 5.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

int positionX = 0, positionZ = -2;

void changeSize(int w, int h) {

	if (h == 0)
	{
		h = 1;
	}

	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void drawRobot() {

	// Desenhando o braco direito
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
	glScalef(2.0, 0.5, 0.5);
	glutSolidCube(1.0);

	glPopMatrix();

	glTranslatef(0.5, 0.0, 0.0);
	glRotatef(0.0, 0.0, 0.0, 0.0);
	glTranslatef(0.7, -0.1, 0.0);
	
	// Desenhando a garra inferior
	glPushMatrix();
	glRotatef((GLfloat)lowerClaw, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.00, 0.0);
	glScalef(1.0, 0.1, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();

	// Desenhando a garra superior
	glPushMatrix();
	glRotatef((GLfloat)upperClaw, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.2, 0.0);
	glScalef(1.0, 0.1, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();

	glPopMatrix();
	
	// Desenhando o corpo
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidCube(1.25f);

	// Desenhando a cabeca
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidCube(0.72f);

	// Preparando para os olhos e boca
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);

	// Desenhando os olhos
	glTranslatef(-0.2f, 0.2f, 0.3f);
	glutSolidSphere(0.1f, 10, 10);
	glTranslatef(0.4f, 0.0f, 0.0f);
	glutSolidSphere(0.1f, 10, 10);
	
	// Desenhando o nariz
	glTranslatef(-0.2f, -0.2f, 0.0f);
	glutSolidCone(0.13f, 0.5f, 10, 2);
	
	glPopMatrix();
}

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void renderScene(void) {

	if (deltaMove)
		computePos(deltaMove);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(x, 1.0f, z,
		x + lx, 1.0f, z + lz,
		0.0f, 1.0f, 0.0f);

	drawPlataform();

	// Draw Robot
	glPushMatrix();
	glTranslatef(positionX * 1, 0, positionZ * 1);
	drawRobot();
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
			if (upperClaw <= -10) {
				break;
				return;
			}
			upperClaw--;
			lowerClaw++;
			glutPostRedisplay();
			break;
		}
		case 'z': {
			if (upperClaw >= 30) {
				break;
				return;
			}
			upperClaw++;
			lowerClaw--;
			glutPostRedisplay();
			break;
		}

		case 'w': { 
			if (positionZ <= -100) {
				break;
				return;
			}
			positionZ--; break;
		}
		case 's': {
			if (positionZ >= 100) {
				break;
				return;
			}
			positionZ++; 
			break;
		}  
		case 'a': { 
			if (positionX <= -100) {
				break;
				return;
			}
			positionX--; 
			break;
		} 
				  
		case 'd': { 
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

	if (xOrigin >= 0) {
		// Atualiza o angulo e direcao da camera
		deltaAngle = (x - xOrigin) * 0.001f;
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}

void mouseButton(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else {
			xOrigin = x;
		}
	}
}

int main(int argc, char **argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1000, 600);
	glutCreateWindow("RobÅot 3D");

	initPlataform();

	// Inicializando os callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 1;
}