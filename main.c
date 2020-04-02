#include <stdio.h>
#include "engine.h"

int texture;
float x, y;

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

	int speed = 1000;

	if (isKeyDown(87)) {
		y += delta * speed;
	}

	if (isKeyDown(83)) {
		y -= delta * speed;
	}

	if (isKeyDown(68)) {
		x += delta * speed;
	}

	if (isKeyDown(65)) {
		x -= delta * speed;
	}
}

void draw() {
	clear(0.5f, 0.5f, 1.0f);

	begin();
	drawSprite(texture, 400, 500, 250, 250);
	drawSprite(texture, (int)x, (int)y, 250, 250);
	end();
}

int main() {
	init();
	load();
	run(update, draw);
	unload();
}