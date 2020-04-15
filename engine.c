#include "engine.h"

GLFWwindow* window;
unsigned int shader;
unsigned int vao, vbo, ubo;

void setupWindow(int width, int height, const char* title) {
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

void initialize(int width, int height, const char* title) {
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

void loadShader(const char* vertex, const char* fragment) {
	char* vertexShader = readFile(vertex);
	char* fragmentShader = readFile(fragment);
	shader = getShader(vertexShader, fragmentShader);

	glUseProgram(shader);
}

struct TEXTURE loadTexture(const char* filename) {
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unsigned int width, height;
	unsigned char* image = loadImage(filename, &width, &height);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, image);

	if (image == 0) {
		printf("ERROR::TEXTURE::LOADING_FAILED\n%s\n", filename);
		exit(1);
	}

	free(image);

	struct TEXTURE t = { texture, width, height };
	return t;
}

void unloadTexture(struct TEXTURE texture) {
	glDeleteTextures(1, &texture.texture);
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

void getVertices(short* arr, struct RECTANGLE bounds) {
	// bottom right
	arr[0] = bounds.x + bounds.width;
	arr[1] = bounds.y;

	// top right
	arr[2] = bounds.x + bounds.width;
	arr[3] = bounds.y + bounds.height;

	// bottom left
	arr[4] = bounds.x;
	arr[5] = bounds.y;

	// top right
	arr[6] = bounds.x + bounds.width;
	arr[7] = bounds.y + bounds.height;

	// top left
	arr[8] = bounds.x;
	arr[9] = bounds.y + bounds.height;

	// bottom left
	arr[10] = bounds.x;
	arr[11] = bounds.y;
}

void getUVs(float* arr, float x, float y, float width, float height) {
	// bottom right
	arr[0] = x + width;
	arr[1] = y;

	// top right
	arr[2] = x + width;
	arr[3] = y + height;

	// bottom left
	arr[4] = x;
	arr[5] = y;

	// top right
	arr[6] = x + width;
	arr[7] = y + height;

	// top left
	arr[8] = x;
	arr[9] = y + height;

	// bottom left
	arr[10] = x;
	arr[11] = y;
}

void initializeBuffers(short* vertices, float* uvs) {
	cleanupBuffers();

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ubo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(short) * 12, vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, 2 * sizeof(short), 0);

	glBindBuffer(GL_ARRAY_BUFFER, ubo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, uvs, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 2 * sizeof(float), 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void clear(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void drawSprite(struct TEXTURE texture, struct RECTANGLE destination, struct RECTANGLE source, bool flipped) {	
	short vertices[12];
	float uvs[12];
	getVertices(vertices, destination);

	if(flipped)
		getUVs(uvs, (source.x + source.width) / (float)texture.width, source.y / (float)texture.height, -source.width / (float)texture.width, source.height / (float)texture.height );
	else
		getUVs(uvs, source.x / (float)texture.width, source.y / (float)texture.height, source.width / (float)texture.width, source.height / (float)texture.height );
	
	initializeBuffers(vertices, uvs);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.texture);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void render() {
	glfwSwapBuffers(window);
}

float getDeltaTime(float* time) {
	float tmp = (float)glfwGetTime();
	float delta = tmp - *time;
	*time = tmp;

	return delta;
}

void run(void(*update)(float), void(*draw)(float)) {

	float time = (float)glfwGetTime();

	while (!glfwWindowShouldClose(window)) {
		float delta = getDeltaTime(&time);
		glfwPollEvents();
		update(delta);
		draw(delta);
	}

	cleanup();
	glfwTerminate();
}

void setRenderTarget(unsigned int framebuffer, unsigned int width, unsigned int height) {
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glViewport(0, 0, width, height);
	glUseProgram(shader);
}

void passShaderValue(const char* key, int value) {
	int location = glGetUniformLocation(shader, key);
	glUniform1f(location, value);
}
