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

using namespace std;

// callback para redimensionar janela glut
void resizeWindow(int x, int y)
{
	if (y == 0 || x == 0) return;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.5, 1.5, -1.5, 1.5, 3.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	if (x>y) glViewport(0, 0, y, y);
	else glViewport(0, 0, x, x);
}

// desenha cubo
void drawScene(void)
{
	drawPlataform();
}

// callback de teclado
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Robô");
	initPlataform();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resizeWindow);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}