#include <stdio.h>
#include "engine.h"

int texture;

void init() {
	initialize(900, 450, "TiimuEngine");
}

void load() {
	texture = loadTexture("doge129.bmp");
	loadShader("shader.vert", "shader.frag");
}

void unload() {
	unloadTexture(texture);
}

void update() {

}

void draw() {
	clear(0.5f, 0.5f, 1.0f);

	begin();
	drawSprite(texture, 400, 500, 250, 250);
	drawSprite(texture, 200, 500, 250, 250);
	end();
}

int main() {
	init();
	load();
	run(draw, update);
	unload();
}