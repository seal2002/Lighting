// MultipleLights.cpp Entry point for console application.
#include <iostream>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "stb_image.h"

#include "Shader.h"
#include "Camera.h"
// Window dimensions
const float WIDTH = 800, HEIGHT = 600;
static float Fov = 45.0f;

// Function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
unsigned int loadTexture(const char* imageName);
void do_movement();
bool keys[1024];

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

glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

glm::vec3 lightDirection(-0.2f, -1.0f, -0.3f);

//Set Camera pos
Camera camera = Camera(cameraPos);

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
	glfwSetKeyCallback(window, key_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initilize GLAD" << std::endl;
	}

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	// Enable Depth Test
	glEnable(GL_DEPTH_TEST);

	//Init my shader
	Shader lightingShader(".\\Resource\\MultipleLights.vs", ".\\Resource\\MultipleLights.fs");

	Shader lamp(".\\Resource\\lamp.vs", ".\\Resource\\lamp.fs");

	//Load image
	GLuint containerTex, specularMap;

	containerTex = loadTexture(".\\Resource\\container2.png");
	specularMap = loadTexture(".\\Resource\\container2_specular.png");

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

	glGenVertexArrays(1, &lightVAO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(lightVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// shader configuration
	// --------------------
	lightingShader.Use();
	lightingShader.setInt("material.diffuse", 0);
	lightingShader.setInt("material.specular", 1);

	while (!glfwWindowShouldClose(window))
	{
		//
		glfwPollEvents();
		do_movement();
		glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
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

		lightingShader.setVec3("dirLight.direction", lightDirection);
		lightingShader.setVec3("viewPos", camera.cameraPos);

		lightingShader.setFloat("material.shininess", 32.0f);

		glm::vec3 ambientColor = glm::vec3(0.2f);
		glm::vec3 diffuseColor = glm::vec3(0.5f);
		glm::vec3 specularColor = glm::vec3(1.0f);

		lightingShader.setVec3("dirLight.ambient", ambientColor);
		lightingShader.setVec3("dirLight.diffuse", diffuseColor);
		lightingShader.setVec3("dirLight.specular", specularColor);
		// point light 1
		lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		lightingShader.setVec3("pointLights[0].ambient", ambientColor);
		lightingShader.setVec3("pointLights[0].diffuse", diffuseColor);
		lightingShader.setVec3("pointLights[0].specular", specularColor);
		lightingShader.setFloat("pointLights[0].constant", 1.0f);
		lightingShader.setFloat("pointLights[0].linear", 0.09f);
		lightingShader.setFloat("pointLights[0].quadratic", 0.032f);
		// point light 1
		lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		lightingShader.setVec3("pointLights[1].ambient", ambientColor);
		lightingShader.setVec3("pointLights[1].diffuse", diffuseColor);
		lightingShader.setVec3("pointLights[1].specular", specularColor);
		lightingShader.setFloat("pointLights[1].constant", 1.0f);
		lightingShader.setFloat("pointLights[1].linear", 0.09f);
		lightingShader.setFloat("pointLights[1].quadratic", 0.032f);
		// point light 3
		lightingShader.setVec3("pointLights[2].position", pointLightPositions[2]);
		lightingShader.setVec3("pointLights[2].ambient", ambientColor);
		lightingShader.setVec3("pointLights[2].diffuse", diffuseColor);
		lightingShader.setVec3("pointLights[2].specular", specularColor);
		lightingShader.setFloat("pointLights[2].constant", 1.0f);
		lightingShader.setFloat("pointLights[2].linear", 0.09f);
		lightingShader.setFloat("pointLights[2].quadratic", 0.032f);
		// point light 4
		lightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);
		lightingShader.setVec3("pointLights[3].ambient", ambientColor);
		lightingShader.setVec3("pointLights[3].diffuse", diffuseColor);
		lightingShader.setVec3("pointLights[3].specular", specularColor);
		lightingShader.setFloat("pointLights[3].constant", 1.0f);
		lightingShader.setFloat("pointLights[3].linear", 0.09f);
		lightingShader.setFloat("pointLights[3].quadratic", 0.032f);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, containerTex);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		glBindVertexArray(containerVAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			angle = glfwGetTime() * 25.0f;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
			lightingShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

		lamp.Use();
		glBindVertexArray(lightVAO);
		for (unsigned int i = 0; i < 4; i++)
		{
			// calculate the matrix for each lamp and pass it to shader before drawing
			model = glm::mat4();
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f));
			lamp.setMat4("model", model);
			lamp.setMat4("view", view);
			lamp.setMat4("projection", projection);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);
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

unsigned int loadTexture(const char * imageName)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	stbi_set_flip_vertically_on_load(1);
	int width, height, nrChannels;
	unsigned char *data = stbi_load(imageName, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		texture = -1;
	}
	stbi_image_free(data);
	return texture;
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
