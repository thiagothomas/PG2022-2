#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
#include <../../glm/glm/glm.hpp>
#include <../../glm/glm/gtc/matrix_transform.hpp>
#include <../../glm/glm/gtc/type_ptr.hpp>
#include "PlayerSprite.h"

using namespace std;

class JanelaJogo
{

private:

	GLFWwindow* _janela;
	GLfloat _altura;
	GLfloat _largura;
	GLuint _vbo;
	GLuint _fogueteTexturaBufferID;
	GLuint _tirosTexturaBufferID;
	GLuint _asteroideTextureBufferID;
	PlayerSprite* _foguete;
	std::vector<Sprite*>* arrayTiros;
	std::vector<Sprite*>* arrayAsteroides;

	GLuint loadAndBufferTexture(string path);
	void adicionarAsteroide();
	void setupGL();
	bool verificaColisao(Sprite* sp1, Sprite* sp2 );
	void limparObjetos();
	void atualizaFoguete();

public:
	JanelaJogo(GLFWwindow* window);
	~JanelaJogo();

	void botaoMousePressionado(int button, int action);

	void renderizar();
	void atualizar();
};

