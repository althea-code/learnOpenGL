#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main() {

	glfwInit();

	// tell glfw what version of openGL I am using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);		
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// vertices for a triangle
	GLfloat vertices[]{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,	// lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		// lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f	// upper corner
	};

	GLFWwindow* window = glfwCreateWindow(800, 800, "learnOpenGL", NULL, NULL);

	if (window == NULL) {
		// error check to make sure window was created
		std::cout << "Failed to create GLFW window" << std::endl;	 
		glfwTerminate();
		return -1;
	}
	// add window we just created as part of OpenGL context
	glfwMakeContextCurrent(window);		
	// load glad so it configures OpenGL
	gladLoadGL();

	// Define the area of the window I wanted OpenGL to render in
	glViewport(0, 0, 800, 800);

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader souce to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile vertex shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment shader source to the fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// compile vertex shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program object and get its reference
	GLuint shaderProgram = glCreateProgram();
	// Attach the vertex and fragment Shaders to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// wrap-up/link all shaders together into the shader program
	glLinkProgram(shaderProgram);

	// delete now useless vertex and grament shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// create reference containers for the vertex array object and the vertex buffer object
	GLuint VAO, VBO;

	// generate the vao and vbo with only 1 object each (!! VAO must come first !!)
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// make the VAO the current Vertex Array Obejct by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 so that we don't accdientally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	// swapping back buffer with front buffer
	glfwSwapBuffers(window);

	// Main While loop
	while (!glfwWindowShouldClose(window)) {

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// clean back buffer and assign new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// tell openGL which Shader Program we want to use
		glUseProgram(shaderProgram);
		// Bind VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		// Draw the triangle using the GL_TRIABGLES primitive
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// Swap the back buffere with the front buffer
		glfwSwapBuffers(window);

		// process GLFW window events
		glfwPollEvents();		 

	}
	// Delete objects I've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}