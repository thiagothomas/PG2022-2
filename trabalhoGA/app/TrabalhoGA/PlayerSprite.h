#include <iostream>
#include "Sprite.h"
#include "Limite.h"

class PlayerSprite: public Sprite
{

private:
	Limite _limite;

public:

	PlayerSprite(GLuint texturaBufferId, Vetor2 posicao, GLFWwindow *janela);
	void atualizar(int key);
	void setLimite(Limite limite);

};

