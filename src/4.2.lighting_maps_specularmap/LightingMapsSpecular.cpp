// LightingMapsSpecular.cpp : Defines the entry point for the console application.

#include <iostream>

#define GLEW_STATIC

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>
#include "Shader.h"
#include "Camera.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void do_movement();

// Square
 float vertices[] = {
		// positions		  // normals		   // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,	 0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,	 0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,	0.5f, -0.5f,  0.0f,	 0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,	0.5f, -0.5f,  0.0f,	 0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,	0.5f, -0.5f,  0.0f,	 0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,	 0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,	 0.0f,	1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,	 0.0f,	1.0f,  1.0f,  0.0f,
		 0.5f,	0.5f,  0.5f,  0.0f,	 0.0f,	1.0f,  1.0f,  1.0f,
		 0.5f,	0.5f,  0.5f,  0.0f,	 0.0f,	1.0f,  1.0f,  1.0f,
		-0.5f,	0.5f,  0.5f,  0.0f,	 0.0f,	1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,	 0.0f,	1.0f,  0.0f,  0.0f,

		-0.5f,	0.5f,  0.5f, -1.0f,	 0.0f,	0.0f,  1.0f,  0.0f,
		-0.5f,	0.5f, -0.5f, -1.0f,	 0.0f,	0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,	 0.0f,	0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,	 0.0f,	0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,	 0.0f,	0.0f,  0.0f,  0.0f,
		-0.5f,	0.5f,  0.5f, -1.0f,	 0.0f,	0.0f,  1.0f,  0.0f,

		 0.5f,	0.5f,  0.5f,  1.0f,	 0.0f,	0.0f,  1.0f,  0.0f,
		 0.5f,	0.5f, -0.5f,  1.0f,	 0.0f,	0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,	 0.0f,	0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,	 0.0f,	0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,	 0.0f,	0.0f,  0.0f,  0.0f,
		 0.5f,	0.5f,  0.5f,  1.0f,	 0.0f,	0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,	0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,	0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,	0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,	0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,	0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,	0.0f,  0.0f,  1.0f,

		-0.5f,	0.5f, -0.5f,  0.0f,	 1.0f,	0.0f,  0.0f,  1.0f,
		 0.5f,	0.5f, -0.5f,  0.0f,	 1.0f,	0.0f,  1.0f,  1.0f,
		 0.5f,	0.5f,  0.5f,  0.0f,	 1.0f,	0.0f,  1.0f,  0.0f,
		 0.5f,	0.5f,  0.5f,  0.0f,	 1.0f,	0.0f,  1.0f,  0.0f,
		-0.5f,	0.5f,  0.5f,  0.0f,	 1.0f,	0.0f,  0.0f,  0.0f,
		-0.5f,	0.5f, -0.5f,  0.0f,	 1.0f,	0.0f,  0.0f,  1.0f
};

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
Camera camera = Camera(cameraPos);
bool keys[1024];

// Window dimensions
const float WIDTH = 800, HEIGHT = 600;

static float Fov = 45.0f;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Lighting Maps Specular", NULL, NULL);
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
	Shader lightingShader(".\\Resource\\LightingMapsSpecular.vs", ".\\Resource\\LightingMapsSpecular.fs");

	Shader lamp(".\\Resource\\lamp.vs", ".\\Resource\\lamp.fs");
	// Load Image
	int width, height, nrComponents;
	unsigned char* image = stbi_load(".\\Resource\\container2.png", &width, &height, &nrComponents, 0);

	GLuint diffuseMap, specularMap;
	glGenTextures(1, &diffuseMap);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(image);

	image = stbi_load(".\\Resource\\container2_specular.png", &width, &height, &nrComponents, 0);

	glGenTextures(1, &specularMap);
	glBindTexture(GL_TEXTURE_2D, specularMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	unsigned int VBO, containerVAO, lightVAO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &containerVAO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(containerVAO);
	// Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texcoords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);


	// We set the light's VAO
	glGenVertexArrays(1, &lightVAO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// shader configuration
	// --------------------
	lightingShader.Use();
	lightingShader.setInt("material.diffuse", 0);
	lightingShader.setInt("material.specular", 1);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		do_movement();
		// render
		// ------
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lightingShader.Use();
		glm::mat4 view;
		glm::mat4 model;
		model = glm::mat4();
		glm::mat4 projection;

		view = camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(Fov), (GLfloat)(WIDTH / HEIGHT), 0.1f, 100.0f);

		lightingShader.setMat4("model", model);
		lightingShader.setMat4("view", view);
		lightingShader.setMat4("projection", projection);

		lightingShader.setVec3("light.position", lightPos);
		lightingShader.setVec3("viewPos", camera.cameraPos);

		lightingShader.setFloat("material.shininess", 64.0f);

		glm::vec3 ambientColor = glm::vec3(0.2f);
		glm::vec3 diffuseColor = glm::vec3(0.5f);
		glm::vec3 sepecularColor = glm::vec3(1.0f);
		
		lightingShader.setVec3("light.ambient", ambientColor);
		lightingShader.setVec3("light.diffuse", diffuseColor);
		lightingShader.setVec3("light.specular", sepecularColor);

		// bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		glBindVertexArray(containerVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		lamp.Use();
		model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));

		lamp.setMat4("model", model);
		lamp.setMat4("view", view);
		lamp.setMat4("projection", projection);

		// Draw the lamp object
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glfwSwapBuffers(window);

	}
	glDeleteVertexArrays(1, &containerVAO);
	glfwTerminate();
	return 0;
}

void do_movement()
{
	if (keys[GLFW_KEY_W])
	{
		camera.ProcessKeyboard(Camera_Movement::FORWARD);
	}
	if (keys[GLFW_KEY_S])
	{
		camera.ProcessKeyboard(Camera_Movement::BACKWARD);
	}
	if (keys[GLFW_KEY_A])
	{
		camera.ProcessKeyboard(Camera_Movement::LEFT);
	}
	if (keys[GLFW_KEY_D])
	{
		camera.ProcessKeyboard(Camera_Movement::RIGHT);
	}
	if (keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(Camera_Movement::ROTATE_LEFT);
	}
	if (keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(Camera_Movement::ROTATE_RIGHT);
	}
	if (keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(Camera_Movement::ROTATE_UP);
	}
	if (keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(Camera_Movement::ROTATE_DOWN);
	}
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (action == GLFW_PRESS)
		keys[key] = true;
	if (action == GLFW_RELEASE)
		keys[key] = false;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
