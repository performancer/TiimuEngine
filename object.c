#include "object.h"

struct OBJECT initializeObject(short x, short y, unsigned short width, unsigned short height) {	
	struct OBJECT object;

	// bottom right
	object.vertices[0] = x + width;
	object.vertices[1] = y;

	// top right
	object.vertices[2] = x + width;
	object.vertices[3] = y + height;

	// bottom left
	object.vertices[4] = x;
	object.vertices[5] = y;

	// top right
	object.vertices[6] = x + width;
	object.vertices[7] = y + height;

	// top left
	object.vertices[8] = x;
	object.vertices[9] = y + height;

	// bottom left
	object.vertices[10] = x;
	object.vertices[11] = y;

	// bottom right
	object.uvs[0] = 1.0f;
	object.uvs[1] = 0.0f;

	// top right
	object.uvs[2] = 1.0f;
	object.uvs[3] = 1.0f;

	// bottom left
	object.uvs[4] = 0.0f;
	object.uvs[5] = 0.0f;

	// top right
	object.uvs[6] = 1.0f;
	object.uvs[7] = 1.0f;

	// top left
	object.uvs[8] = 0.0f;
	object.uvs[9] = 1.0f;

	// bottom left
	object.uvs[10] = 0.0f;
	object.uvs[11] = 0.0f;

	return object;
}