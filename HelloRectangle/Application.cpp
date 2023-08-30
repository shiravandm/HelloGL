#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../shared/shader.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

enum PolygonMode {Fill = 1, Wireframe=2};

enum PolygonMode currentPolygonMode = Fill;

int main()
{

	// GLFW Initializations
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Loading OpenGl methods
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Set size of rendering window
	glViewport(0, 0, 800, 600);
	// Set framebuffer size change callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	Shader shaderProgram("vertex.gls", "fragment.gls");

	float vertices[] = {
	  0.5f,  0.5f, 0.0f, // top right
	  0.5f, -0.5f, 0.0f, // bottom right
	 -0.5f, -0.5f, 0.0f, // bottom left
	 -0.5f,  0.5f, 0.0f  // top right
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	// Vertex buffer boject
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind vertex array
	glBindVertexArray(VAO);

	// Bind buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Copy data to currently bound buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// telling OpenGL how it should interpret the vertex data (per vertex attribute)
	// the first attribute specifies which arribute we want to configure, we use the same location we used in vertex shader source
	// the second arg specifies the size of the vertex attribute which is vec3
	// third is the type of data
	// fourth is normalization enable/disable
	// the fifth is `stride` and specifies the space between consecutive vertex attributes
	// the sixth is the offset where the the position data begins in the buffer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	// Keep drawing
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.use();
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		if (currentPolygonMode == Fill)
		{
			currentPolygonMode = Wireframe;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			currentPolygonMode = Fill;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
		
}
