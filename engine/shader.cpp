#include "shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include "io/file.h"

void shader::load(const char* vertex, const char* fragment)
{
	_shader = _link(read_file(vertex), read_file(fragment));
}

void shader::unload()
{
	glDeleteProgram(_shader);
}

void shader::uniform(const char* key, int value)
{
	glUniform1f(glGetUniformLocation(_shader, key), value);
}

void shader::use()
{
	glUseProgram(_shader);
}

unsigned int shader::_link(const char* vertex, const char* fragment)
{
	unsigned int compiled_vertex, compiled_fragment;
	compiled_vertex = _compile(vertex, GL_VERTEX_SHADER);
	compiled_fragment = _compile(fragment, GL_FRAGMENT_SHADER);

	unsigned int id = glCreateProgram();
	glAttachShader(id, compiled_vertex);
	glAttachShader(id, compiled_fragment);
	glLinkProgram(id);

	int success;
	char log[512];
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, 512, 0, log);
		printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", log);
		exit(1);
	}

	glDeleteShader(compiled_vertex);
	glDeleteShader(compiled_fragment);
	return id;
}

unsigned int shader::_compile(const char* source, unsigned int type)
{
	unsigned int shader;

	shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, 0);
	glCompileShader(shader);

	int success;
	char log[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, 0, log);
		printf("ERROR::SHADER::%d::COMPILATION_FAILED\n%s\n", type, log);
		exit(1);
	}

	return shader;
}