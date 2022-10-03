#include <string>
#include "JanelaJogo.h"
#include <glad/glad.h>

//STB_IMAGE
#include "stb_image.h"

using namespace std;

typedef struct {

	GLfloat posicoes[4];
	GLfloat texturas[2];

} Vertices;

Vertices vertices[] = {
	{{ -Tamanho_Quadrado /2,  -Tamanho_Quadrado /2, 0.0f }, {0.0f, 0.0f}},
	{{ Tamanho_Quadrado / 2, -Tamanho_Quadrado /2, 0.0f }, {1.0f, 0.0f}},
	{{ Tamanho_Quadrado /2,    Tamanho_Quadrado /2, 0.0f }, {1.0f, 1.0f}},
	{{ -Tamanho_Quadrado /2,   Tamanho_Quadrado /2, 0.0f }, {0.0f, 1.0f}}
};

JanelaJogo::JanelaJogo(GLFWwindow* janela):
	_janela(janela), _altura(600), _largura(800), _vbo(0)
{
	setupGL();

	_fogueteTexturaBufferID = loadAndBufferTexture("../textures/foguete.png");
	_tirosTexturaBufferID = loadAndBufferTexture("../textures/shot.png");
	_asteroideTextureBufferID = loadAndBufferTexture("../textures/pedra.png");

	arrayTiros = new std::vector<Sprite*>;
	arrayAsteroides = new std::vector<Sprite*>;
	
	_foguete = new PlayerSprite(_fogueteTexturaBufferID, criarVetor2(_largura/2, _altura/2), _janela);
	_foguete->setLimite(demilitarLimite(_altura, 0, 0, _largura));
}

JanelaJogo::~JanelaJogo()
{
	for (std::vector<Sprite*>::iterator tiro = arrayTiros->begin();
		tiro != arrayTiros->end();
		tiro++) {

		delete (*tiro);
	}
	delete arrayTiros;
	delete _foguete;

	glDeleteBuffers(1, &_vbo);
	glDeleteTextures(1, &_fogueteTexturaBufferID);
	glDeleteTextures(1, &_tirosTexturaBufferID);
	glDeleteTextures(1, &_asteroideTextureBufferID);
}

void JanelaJogo::renderizar() {
	glfwPollEvents();

	glClear(GL_COLOR_BUFFER_BIT);

	_foguete->renderizar();

	for (std::vector<Sprite*>::iterator tiro = arrayTiros->begin();
		tiro != arrayTiros->end();
		tiro++) {

		(*tiro)->renderizar();
	}
	
	for (std::vector<Sprite*>::iterator asteroide = arrayAsteroides->begin(); 
		asteroide != arrayAsteroides->end();
		asteroide++) {

		(*asteroide)->renderizar();
	}

	glfwSwapBuffers(_janela);
}

void JanelaJogo::botaoMousePressionado(int button, int action) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		
		Sprite* tiro = new Sprite(
			_tirosTexturaBufferID, 
			criarVetor2(_foguete->getPosicao().x, _foguete->getPosicao().y+50),
			_janela
		);
		tiro->setVelocidade(criarVetor2(0, 8));
		arrayTiros->push_back(tiro);
	}
}

void JanelaJogo::atualizar()
{
	limparObjetos();

	static int updates;
	if (updates >= 30) {
		adicionarAsteroide();
		updates = 0;
	}
	++updates;

	atualizaFoguete();

	for (std::vector<Sprite*>::iterator tiro = arrayTiros->begin();
		tiro != arrayTiros->end();
		tiro++) {
			(*tiro)->atualizar(0);
	}

	for (std::vector<Sprite*>::iterator asteroide = arrayAsteroides->begin();
		asteroide != arrayAsteroides->end();
		asteroide++) {

		(*asteroide)->atualizar(0);
	}
	
}

void JanelaJogo::adicionarAsteroide()
{
	int x = rand() % (unsigned int)_largura;
	Sprite* asteroid = new Sprite(_asteroideTextureBufferID, criarVetor2(x, _altura), _janela);
	asteroid->setVelocidade(criarVetor2(0, -3));
	asteroid->setVelocidadeRotacao(1.0f);
	arrayAsteroides->push_back(asteroid);
}

void JanelaJogo::atualizaFoguete() {
	if (glfwGetKey(_janela, GLFW_KEY_UP) == GLFW_PRESS) {
		_foguete->atualizar(GLFW_KEY_UP);
	}
	if (glfwGetKey(_janela, GLFW_KEY_DOWN) == GLFW_PRESS) {
		_foguete->atualizar(GLFW_KEY_DOWN);
	}
	if (glfwGetKey(_janela, GLFW_KEY_LEFT) == GLFW_PRESS) {
		_foguete->atualizar(GLFW_KEY_LEFT);
	}
	if (glfwGetKey(_janela, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		_foguete->atualizar(GLFW_KEY_RIGHT);
	}
}

void JanelaJogo::limparObjetos() {
	std::vector<std::vector<Sprite*>::iterator> deletar;

	for (std::vector<Sprite*>::iterator asteroide = arrayAsteroides->begin();
		asteroide != arrayAsteroides->end();
		asteroide++) {
		if (verificaColisao(*asteroide, _foguete)) {
			deletar.push_back(asteroide);
		}

		for (std::vector<Sprite*>::iterator tiro = arrayTiros->begin();
			tiro != arrayTiros->end();
			tiro++
			) {
			if (verificaColisao(*asteroide, *tiro)) {
				deletar.push_back(asteroide);
				deletar.push_back(tiro);
			}
		}
	}

	for (std::vector<Sprite*>::iterator tiro = arrayTiros->begin();
		tiro != arrayTiros->end();
		tiro++) {
		if ((*tiro)->getPosicao().x > _largura + Tamanho_Quadrado) {
			deletar.push_back(tiro);
		}
	}

	for (std::vector<std::vector<Sprite*>::iterator>::iterator del = deletar.begin();
		del != deletar.end();
		del++) {
		if ((**del)->getVelocidade().y > 0) {
			arrayTiros->erase(*del);
		}
		else {
			arrayAsteroides->erase(*del);
		}

	}
}

bool JanelaJogo::verificaColisao(Sprite* sp1, Sprite* sp2) {
	return !(sp1->getPosicao().x + 30 <= sp2->getPosicao().x - 30 ||
		     sp1->getPosicao().x - 30 >= sp2->getPosicao().x + 30 ||
		     sp1->getPosicao().y + 40 <= sp2->getPosicao().y - 40 ||
		     sp1->getPosicao().y - 40 >= sp2->getPosicao().y + 40);
}

void JanelaJogo::setupGL() {
	glClearColor(0.2f, 0.2f, 0.25f, 0.0f);
	glViewport(0.0f, 0.0f, _largura, _altura);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glOrtho(0, _largura, 0, _altura, -1, 1);
	glMatrixMode(GL_MODELVIEW);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertices), (GLvoid*)offsetof(Vertices, posicoes));

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertices), (GLvoid*)offsetof(Vertices, texturas));
}

GLuint JanelaJogo::loadAndBufferTexture(string path)
{
	GLuint texID;

	// Gera o identificador da textura na memória 
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	// Parametriza o wrapping e o filtering da textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3) //jpg, bmp
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else //png
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	/*glBindTexture(GL_TEXTURE_2D, )*/;
	glActiveTexture(GL_TEXTURE0);

	return texID;
}