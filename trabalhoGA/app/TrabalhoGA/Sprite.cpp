#include "Sprite.h"

Sprite::Sprite(GLuint texturaBufferId, Vetor2 posicao, GLFWwindow *janela)
{
	_texturaBufferId = texturaBufferId;
	_posicao = posicao;
	_janela = janela;
}

void Sprite::renderizar()
{
	glBindTexture(GL_TEXTURE_2D, _texturaBufferId);

	glLoadIdentity();

	glTranslatef(_posicao.x, _posicao.y, 0);
	glRotatef(_rotacao, 0, 0, 1.0f);

	glDrawArrays(GL_QUADS, 0, 4);
}

void Sprite::atualizar(int key)
{
	_posicao = adicionarVetor2(_posicao, _velocidade);
	_rotacao += _velocidadeRotacao;
}

Vetor2 Sprite::getPosicao()
{
	return _posicao;
}

void Sprite::setPosicao(Vetor2 posicao)
{
	_posicao = posicao;
}

Vetor2 Sprite::getVelocidade()
{
	return _velocidade;
}

void Sprite::setVelocidade(Vetor2 velocidade)
{
	_velocidade = velocidade;
}

GLfloat Sprite::getRotacao()
{
	return _rotacao;
}

void Sprite::setRotacao(GLfloat rotacao)
{
	_rotacao = rotacao;
}

GLfloat Sprite::getVelocidadeRotacao()
{
	return _velocidadeRotacao;
}

void Sprite::setVelocidadeRotacao(GLfloat velocidade)
{
	_velocidadeRotacao = velocidade;
}
