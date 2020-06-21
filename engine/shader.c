#include "shader.h"
#include <GL/glew.h>
#include "io/file.h"

unsigned int _shader;

unsigned int _compile(const char* source, unsigned int shaderType)
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

unsigned int _link(const char* vertexFile, const char* fragmentFile)
{
	unsigned int vertex, fragment;
	vertex = _compile(vertexFile, GL_VERTEX_SHADER);
	fragment = _compile(fragmentFile, GL_FRAGMENT_SHADER);

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

void shader_use()
{
	glUseProgram(_shader);
}

void shader_delete()
{
	glDeleteProgram(_shader);
}

void shader_set(const char* vertex, const char* fragment)
{
	_shader = _link(vertex, fragment);
	shader_use();
}

void shader_uniform(const char* key, int value)
{
	glUniform1f(glGetUniformLocation(_shader, key), value);
}

void shader_load(const char* vertex, const char* fragment)
{
	char* vertex_data = read_file(vertex);
	char* fragment_data = read_file(fragment);
	shader_set(vertex_data, fragment_data);
}