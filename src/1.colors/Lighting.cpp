// Lighting.cpp : Defines the entry point for the console application.

#include <iostream>

#define GLEW_STATIC

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>
#include "Shader.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Square
GLfloat vertices[] = {
	// Pos
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	0.5f,  0.5f,  0.5f,
	0.5f,  0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f,  0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	0.5f,  0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
};

// Window dimensions
const float WIDTH = 800, HEIGHT = 800;

float mixValue = 0;
static float Fov = 45.0f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Lighting", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetKeyCallback(window, key_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initilize GLAD" << std::endl;
		return -1;
	}

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	// Enable Depth test
	glEnable(GL_DEPTH_TEST);

	// Init my shader
	Shader object(".\\Resource\\Colors.vs", ".\\Resource\\Colors.fs");

	Shader lamp(".\\Resource\\lamp.vs", ".\\Resource\\lamp.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	unsigned int VBO, VAO, lightVAO;
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);
	// Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);	

	glGenVertexArrays(1, &lightVAO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(lightVAO);
	// Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		object.Use();
		glm::mat4 view;
		glm::mat4 model;
		glm::mat4 projection;

		model = glm::translate(model, glm::vec3(-0.5f, -0.5f, -0.2f));

		view = glm::translate(view, glm::vec3(0.0f, 0.2f, -3.0f));

		projection = glm::perspective(Fov, (GLfloat)(WIDTH / HEIGHT), 0.1f, 100.0f);

		GLint modelLoc = glGetUniformLocation(object.Program, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		GLint viewLoc = glGetUniformLocation(object.Program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		GLint projectionLoc = glGetUniformLocation(object.Program, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		GLint objectColorLoc = glGetUniformLocation(object.Program, "objectColor");
		GLint lightColorLoc = glGetUniformLocation(object.Program, "lightColor");

		glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
		glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f); // Also set light's color (white)

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		lamp.Use();
		glm::vec3 lightPos(1.2f, 1.0f, 0.2f);

		model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));

		modelLoc = glGetUniformLocation(lamp.Program, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		viewLoc = glGetUniformLocation(lamp.Program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		projectionLoc = glGetUniformLocation(lamp.Program, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Draw the lamp object
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glfwSwapBuffers(window);

	}
	glDeleteVertexArrays(1, &VAO);
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	
	// Change value of uniform with arrow keys (sets amount of textre mix)

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		Fov += 1.0f;
		cout << Fov << endl;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		Fov -= 1.0f;
		cout << Fov << endl;
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
