#include "engine.h"

GLFWwindow* window;
unsigned int shader;
unsigned int vao, vbo, ubo;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void setupWindow(int width, int height, char* title) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(width, height, title, 0, 0);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyCallback);
}

void setupViewport() {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}

void initialize(int width, int height, char* title) {
	setupWindow(width, height, title);

	glewExperimental = GL_TRUE;
	glewInit();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_SCISSOR_TEST);

	setupViewport();
}

void loadShader(char* vertex, char* fragment) {
	char* vertexShader = readFile(vertex);
	char* fragmentShader = readFile(fragment);
	shader = getShader(vertexShader, fragmentShader);
}

int loadTexture(char* filename) {
	int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height;
	unsigned char* image = loadImage(filename, &width, &height);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, image);

	if (image == 0) {
		printf("Failed to load texture image.\n");
		exit(1);
	}

	free(image);
	return texture;
}

void unloadTexture(int texture) {
	glDeleteTextures(1, &texture);
}

void cleanupBuffers() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ubo);
}

void cleanup() {
	cleanupBuffers();
	glDeleteProgram(shader);
}

void initializeBuffers(struct OBJECT* object) {
	cleanupBuffers();

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ubo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(object->vertices), object->vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, 2 * sizeof(short), 0);

	glBindBuffer(GL_ARRAY_BUFFER, ubo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(object->uvs), object->uvs, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 2 * sizeof(GLfloat), 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void clear(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void begin() {
	glUseProgram(shader);
}

void drawSprite(unsigned int texture, short x, short y, unsigned short width, unsigned short height) {
	struct OBJECT object = initializeObject(x, y, width, height);
	initializeBuffers(&object);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void end() {
	glfwSwapBuffers(window);
}

void run(int* update(), int* draw()) {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		update();
		draw();
	}

	cleanup();
	glfwTerminate();
}