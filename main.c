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

	if (isKeyDown(KEY_W) || isKeyDown(KEY_UP)) {
		y += delta * speed;
	}

	if (isKeyDown(KEY_A) || isKeyDown(KEY_LEFT)) {
		x -= delta * speed;
	}

	if (isKeyDown(KEY_S) || isKeyDown(KEY_DOWN)) {
		y -= delta * speed;
	}

	if (isKeyDown(KEY_D) || isKeyDown(KEY_RIGHT)) {
		x += delta * speed;
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