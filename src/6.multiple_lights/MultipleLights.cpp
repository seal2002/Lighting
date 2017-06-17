// MultipleLights.cpp Entry point for console application.
#include <iostream>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "stb_image.h"

#include "Shader.h"
#include "Camera.h"
// Window dimensions
const float WIDTH = 800, HEIGHT = 600;

// Function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

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

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

void main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Multiple Light", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initilize GLAD" << std::endl;
	}

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	// Enable Depth Test
	glEnable(GL_DEPTH_TEST);

	//Init my shader
	Shader lightingShader(".\\Resource\\MultiLights.vs", ".\\Resource\\Mutilights.fs");

	//Load image
	GLuint containerTex, specularMap;
	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(1);
	unsigned char* image = stbi_load(".\\Resource\\container2.png", &width, &height, &nrComponents, 0);
	glGenTextures(1, &containerTex);
	glBindTexture(GL_TEXTURE_2D, containerTex);

	while (!glfwWindowShouldClose(window))
	{
		//
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		glfwSwapBuffers(window);
	}
	glfwTerminate();
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}