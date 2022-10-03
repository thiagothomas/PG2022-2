#include <iostream>
#include <string>
#include <assert.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "JanelaJogo.h";

#define Updates_Per_Second 60

JanelaJogo* janelaJogo;

using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouseButtonPressed(GLFWwindow* window, int button, int action, int mods);

const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Trabalho GA", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouseButtonPressed);
	glfwSwapInterval(0);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	janelaJogo = new JanelaJogo(window);

	double lastTime = glfwGetTime();
	double deltaTime = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		janelaJogo->renderizar();

		deltaTime += (glfwGetTime() - lastTime) * Updates_Per_Second;
		lastTime = glfwGetTime();
		while (deltaTime >= 1.0f) {
			janelaJogo->atualizar();
			--deltaTime;
		}
	}

	delete janelaJogo;

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void mouseButtonPressed(GLFWwindow* window, int button, int action, int mods) {
	janelaJogo->botaoMousePressionado(button, action);
}