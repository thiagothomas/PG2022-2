#include <iostream>
#include <string>
#include <assert.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <../../glm/glm/glm.hpp>
#include <../../glm/glm/gtc/matrix_transform.hpp>
#include <../../glm/glm/gtc/type_ptr.hpp>

#include <../../shaders/Shader.h>

using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int setupGeometry();

const GLuint WIDTH = 800, HEIGHT = 600;

const int numColunas = 10;
const int numLinhas = 10;
const int numQuadrados = numLinhas * numColunas;
const float verde[] = { 0.0f, 1.0f, 0.0f };
const float azul[] = { 0.0f, 0.0f, 1.0f };
const float laranja[] = { 1.0f, 0.5f, 0.0f };
const float amarelo[] = { 1.0f, 1.0f, 0.0f };
const float ciano[] = { 0.0f, 1.0f, 1.0f };
const float vermelho[] = { 1.0f, 0.0f, 0.0f };
const float roxo[] = { 1.0f, 0.0f, 1.0f };

int main()
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Lista 3", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	Shader shader("../../dependencies/shaders/vertex.vs", "../../dependencies/shaders/fragment.fs");

	GLuint VAO = setupGeometry();

	GLint colorLoc = glGetUniformLocation(shader.ID, "inputColor");
	assert(colorLoc > -1);

	glUseProgram(shader.ID);

	glm::mat4 projection = glm::mat4(1);
	projection = glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, -1.0f, 1.0f);

	GLint projLoc = glGetUniformLocation(shader.ID, "projection");
	glUniformMatrix4fv(projLoc, 1, false, glm::value_ptr(projection));

	srand((unsigned)time(NULL));

	int cores[numQuadrados] = { };
	for (int i = 0; i < numQuadrados; i++) {
		cores[i] = (int)(rand() % (7)) + 1;
	}

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glLineWidth(10);
		glPointSize(20);

		glBindVertexArray(VAO);

		glfwGetFramebufferSize(window, &width, &height);

		int corCount = 0;
		for (int i = 0; i < numLinhas; i++) {
			for (int j = 0; j < numColunas; j++) {
				glm::mat4 model = glm::mat4(1);
				model = glm::translate(model, glm::vec3(i * (WIDTH / numLinhas), j * (HEIGHT / numColunas), 0.0f));
				model = glm::scale(model, glm::vec3(WIDTH / numLinhas, HEIGHT / numColunas, 0.0));
				shader.setMat4("model", glm::value_ptr(model));
				
				switch (cores[corCount++]) {
					case 1:
						glUniform4f(colorLoc, verde[0], verde[1], verde[2], 1.0f);
						break;
					case 2:
						glUniform4f(colorLoc, azul[0], azul[1], azul[2], 1.0f);
						break;
					case 3:
						glUniform4f(colorLoc, laranja[0], laranja[1], laranja[2], 1.0f);
						break;
					case 4:
						glUniform4f(colorLoc, amarelo[0], amarelo[1], amarelo[2], 1.0f);
						break;
					case 5:
						glUniform4f(colorLoc, ciano[0], ciano[1], ciano[2], 1.0f);
						break;
					case 6:
						glUniform4f(colorLoc, vermelho[0], vermelho[1], vermelho[2], 1.0f);
						break;
					default:
						glUniform4f(colorLoc, roxo[0], roxo[1], roxo[2], 1.0f);
						break;
				}

				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}
		}

		glViewport(0, 0, width, height);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int setupGeometry()
{
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	GLfloat vertices[] = {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	GLuint VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	
	glEnableVertexAttribArray(0);

	return EBO;
}