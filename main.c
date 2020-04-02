#include <stdio.h>
#include "engine.h"

int texture;
short x, y;

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

void update(float delta) {

	if (isKeyDown(87)) {
		y++;
	}

	if (isKeyDown(83)) {
		y--;
	}

	if (isKeyDown(68)) {
		x++;
	}

	if (isKeyDown(65)) {
		x--;
	}
}

void draw() {
	clear(0.5f, 0.5f, 1.0f);

	begin();
	drawSprite(texture, 400, 500, 250, 250);
	drawSprite(texture, x, y, 250, 250);
	end();
}

int main() {
	init();
	load();
	run(update, draw);
	unload();
}