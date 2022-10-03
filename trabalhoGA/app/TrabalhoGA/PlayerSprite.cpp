#include "PlayerSprite.h"

PlayerSprite::PlayerSprite(GLuint texturaBufferId, Vetor2 posicao, GLFWwindow *janela) :
	Sprite(texturaBufferId, posicao, janela)
{

}

void PlayerSprite::atualizar(int key)
{

	if (key == GLFW_KEY_UP && _posicao.y <= _limite.topo) {
		_posicao = adicionarVetor2(_posicao, criarVetor2(0.0f, 4.f));
	}
		
	if (key == GLFW_KEY_DOWN && _posicao.y >= _limite.baixo) {
		_posicao = adicionarVetor2(_posicao, criarVetor2(0.0f, -4.f));
	}

	if (key == GLFW_KEY_LEFT && _posicao.x >= _limite.esquerda) {
		_posicao = adicionarVetor2(_posicao, criarVetor2(-4.f, 0.0f));
	}

	if (key == GLFW_KEY_RIGHT && _posicao.x <= _limite.direita) {
		_posicao = adicionarVetor2(_posicao, criarVetor2(4.f, 0.0f));
	}
	
}

void PlayerSprite::setLimite(Limite limite) {
	_limite = limite;
}
