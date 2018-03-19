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
#include ".\RgbImage.h"

// variaveis globais
GLfloat xRotated, yRotated, zRotated; //angulos de rotacao
GLuint texture[1]; // id da textura
char filename[] = "textura3.bmp";  //arquivo com a textura

void drawPlataform(void) {
	glColor3f(0.9f, 0.9f, 0.9f);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 100.0f);    glVertex3f(-100.0f, 0.0f, -100.0f);
	glTexCoord2f(0.0f, 0.0f);      glVertex3f(-100.0f, 0.0f, 100.0f);
	glTexCoord2f(100.0f, 0.0f);    glVertex3f(100.0f, 0.0f, 100.0f);
	glTexCoord2f(100.0f, 100.0f);  glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();
}

// carrega textura de arquivo
void loadTextureFromFile(char *filename)
{
	//glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	RgbImage theTexMap(filename);
	glGenTextures(1, &texture[0]); // Cria a textura
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, //Sempre GL_TEXTURE_2D
		0, //Nível de detalhe da textura (0)
		3, //Numero de componentes de cor
		theTexMap.GetNumCols(), //Largura
		theTexMap.GetNumRows(), //Altura
		0, //Bordas (deve ser 0)
		GL_RGB, //Formato interno: RGB
		GL_UNSIGNED_BYTE, //Pixels armazenados como unsigned
		theTexMap.ImageData()); //A imagem/pixels da textura
}

void initPlataform(void)
{
	glEnable(GL_TEXTURE_2D);
	loadTextureFromFile(filename);
}