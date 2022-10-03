#include <iostream>
#include <GLFW/glfw3.h>

#include "Vetor2.h"

#define Tamanho_Quadrado 100

class Sprite
{
private:

	GLuint _texturaBufferId;
	Vetor2 _velocidade;
	GLfloat _rotacao;
	GLfloat _velocidadeRotacao;

protected:

	Vetor2 _posicao;
	GLFWwindow* _janela;

public:

	Sprite(GLuint texturaBufferID, Vetor2 posicao, GLFWwindow *janela);

	virtual void atualizar(int key);
	void renderizar();

	Vetor2 getPosicao();
	void setPosicao(Vetor2 posicao);

	Vetor2 getVelocidade();
	void setVelocidade(Vetor2 velocidade);

	GLfloat getRotacao();
	void setRotacao(GLfloat rotacao);

	GLfloat getVelocidadeRotacao();
	void setVelocidadeRotacao(GLfloat velocidade);
};

