#include "engine.h"

GLFWwindow* window;
unsigned int shaderId, textureId;
unsigned int vao, vbo, ubo;

static short vertices[12];
static float uvs[12];

const char *vertexShader =
"#version 330\n"
"layout (location = 0) in vec2 vert;\n"
"layout (location = 1) in vec2 _uv;\n"
"out vec2 uv;\n"
"void main()\n"
"{\n"
"    uv = _uv;\n"
"    gl_Position = vec4(vert.x / 720.0 - 1.0, vert.y / 405.0 - 1.0, 0.0, 1.0);\n"
"}\n";

const char *fragmentShader =
"#version 330\n"
"out vec4 color;\n"
"in vec2 uv;\n"
"uniform sampler2D tex;\n"
"void main()\n"
"{\n"
"    color = texture(tex, uv);\n"
"}\n";

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void initialize(int width, int height, char* title) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(width, height, title, 0, 0);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyCallback);

	glewExperimental = GL_TRUE;
	glewInit();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_SCISSOR_TEST);

	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
	}

	shaderId = getShader(vertexShader, fragmentShader);

	
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	{
		int width, height;
		unsigned char* image = loadImage("doge128.bmp", &width, &height);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

		if (image == 0)
		{
			printf("Failed to load texture image.\n");
		}
		else
		{
			free(image);
		}
	}

	{
		// top right
		vertices[0] = width;
		vertices[1] = 0;

		// bottom right
		vertices[2] = width;
		vertices[3] = height;

		// top left
		vertices[4] = 0;
		vertices[5] = 0;

		// bottom right
		vertices[6] = width;
		vertices[7] = height;

		// bottom left
		vertices[8] = 0;
		vertices[9] = height;

		// top left
		vertices[10] = 0;
		vertices[11] = 0;
	}

	{
		// top right
		uvs[0] = 0.0f;
		uvs[1] = 1.0f;

		// bottom right
		uvs[2] = 1.0f;
		uvs[3] = 1.0f;

		// top left
		uvs[4] = 0.0f;
		uvs[5] = 0.0f;

		// bottom right
		uvs[6] = 1.0f;
		uvs[7] = 1.0f;

		// bottom left
		uvs[8] = 1.0f;
		uvs[9] = 0.0f;

		// top left
		uvs[10] = 0.0f;
		uvs[11] = 0.0f;
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ubo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, 2 * sizeof(short), 0);

	glBindBuffer(GL_ARRAY_BUFFER, ubo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 2 * sizeof(GLfloat), 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glUseProgram(shaderId);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glBindVertexArray(vao);
}

void update(){

}

void render(){
	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glfwSwapBuffers(window);
}


void cleanup() {
	glDeleteTextures(1, &textureId);
	glDeleteProgram(shaderId);
}

void run() {
	while (!glfwWindowShouldClose(window)){
		glfwPollEvents();
		update();
		render();
	}

	cleanup();
	glfwTerminate();
}