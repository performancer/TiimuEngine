#include "file.h"
#include <stdio.h>
#include <stdlib.h>

char* read_file(const char* path)
{
	int length;
	FILE* file = fopen(path, "rb");

	if (!file)
	{
		printf("ERROR::FILE::READING_FILE\n%s\n", path);
		exit(1);
	}

	fseek(file, 0, SEEK_END);
	length = ftell(file);
	rewind(file);

	char* buffer = (char*)malloc(length);

	fread(buffer, length, 1, file);
	fclose(file);
	buffer[length] = '\0';
	return buffer;
}