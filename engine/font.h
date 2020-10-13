#pragma once
#include <string>
#include "physics/point.h"
#include "graphics.h"
#include "texture.h"

struct Character
{
	Point size;
	Point bearing;
};

class Font
{
private:
	texture _texture;
	Character _characters[256];
	int _spacing;

	void LoadFontData(unsigned int width, unsigned int height, unsigned char* data);
	Character CalculateCharacterData(int location, unsigned int width, unsigned int height, unsigned char* data);
public:
	Font(int spacing = 0);
	~Font();

	void Load(const char* path);

	int Length(std::string string) const;
	void Draw(graphics* graphics, int x, int y, std::string string);
};