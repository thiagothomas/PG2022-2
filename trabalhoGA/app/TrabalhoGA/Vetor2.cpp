#include "Vetor2.h"

Vetor2 criarVetor2(GLfloat x, GLfloat y) 
{
	Vetor2 vector;
	vector.x = x;
	vector.y = y;

	return vector;
}

Vetor2 adicionarVetor2(Vetor2 v1, Vetor2 v2)
{
	Vetor2 vector;
	vector.x = v1.x + v2.x;
	vector.y = v1.y + v2.y;
	return vector;
}