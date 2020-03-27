#include <stdio.h>

#include <GL/glew.h>

unsigned int compileShader(const char* source, unsigned int shaderType)
{
	unsigned int shader;

	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &source, 0);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, 0, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
	};

	return shader;
}

unsigned int getShader(const char* vertexFile, const char* fragmentFile){
	unsigned int vertex, fragment;
	vertex = compileShader(vertexFile, GL_VERTEX_SHADER);
	fragment = compileShader(fragmentFile, GL_FRAGMENT_SHADER);

	unsigned int id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	int success;
	char infoLog[512];
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, 512, 0, infoLog);
		printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return id;
}