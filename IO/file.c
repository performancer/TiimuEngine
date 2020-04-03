#include "file.h"

char* readFile(const char* filePath) {
	int len;
	FILE* file = fopen(filePath, "rb"); 	// Open the file in binary mode
	fseek(file, 0, SEEK_END);          		// Jump to the end of the file
	len = ftell(file);             			// Get the current byte offset in the file
	rewind(file);                      		// Jump back to the beginning of the file

	char* buffer = (char*)malloc(len);

	fread(buffer, len, 1, file); 			// Read in the entire file
	fclose(file); 							// Close the file
	buffer[len] = '\0';
	return buffer;
}