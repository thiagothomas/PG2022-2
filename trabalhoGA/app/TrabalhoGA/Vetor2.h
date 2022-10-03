#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

typedef struct {

	GLfloat x;
	GLfloat y;

} Vetor2;

Vetor2 criarVetor2(GLfloat x, GLfloat y);
Vetor2 adicionarVetor2(Vetor2 v1, Vetor2 v2);


