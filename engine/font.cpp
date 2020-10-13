#include "font.h"
#include <algorithm>
#include "io/image.h"
#include "physics/rectangle.h"

Font::Font(int spacing)
{
	_spacing = spacing;
}

Font::~Font()
{
}

void Font::Load(const char* path)
{
	unsigned int width, height;
	unsigned char* data = loadImage(path, &width, &height);

	LoadFontData(width, height, data);
	_texture = texture_load(width, height, data);

	if (data == 0)
	{
		printf("ERROR::FONT_TEXTURE::LOADING_FAILED\n%s\n", path);
		exit(1);
	}

	free(data);
}

Character Font::CalculateCharacterData(int location, unsigned int width, unsigned int height, unsigned char* data)
{
	int cellWidth = width / 16;
	int cellHeight = height / 16;

	Point first = { cellWidth, cellHeight };
	Point last = { 0, 0 };

	for (int cy = 0; cy < cellHeight; cy++)
	{
		for (int cx = 0; cx < cellWidth; cx++)
		{
			int i = location + (cy * width + cx) * 4;
			Color color = { data[i++], data[i++], data[i++], data[i++] };

			if (color.A != 0)
			{
				last.x = std::max(cx + 1, last.x);
				last.y = std::max(cy + 1, last.y);
				first.x = std::min(cx, first.x);
				first.y = std::min(cy, first.y);
			}
		}
	}

	last.x = last.x == 0 ? cellWidth / 2 : last.x;
	first.x = first.x == cellWidth ? 0 : first.x;
	first.y = first.y == cellHeight ? 0 : first.y;

	return { last.x - first.x, last.y - first.y, first.x, first.y };
}

void Font::LoadFontData(unsigned int width, unsigned int height, unsigned char* data)
{
	int cellWidth = width / 16;
	int cellHeight = height / 16;

	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			int pixel = ((y * cellHeight) * width + x * cellWidth) * 4;

			_characters[(16 - (y + 1)) * 16 + x] = CalculateCharacterData(pixel, width, height, data);
		}
	}
}

int Font::Length(std::string string) const
{
	int x = 0;

	for (int i = 0; i < string.length(); i++)
		x += _characters[string[i]].size.x + _spacing;

	return x;
}

void Font::Draw(graphics* graphics, int x, int y, std::string string)
{
	Point advance = { _texture.width / 16, _texture.height / 16 };

	for (int i = 0; i < string.length(); i++)
	{
		char code = string[i];
		Character data = _characters[code];

		Vector destination = { x, y + data.bearing.y };

		rectangle source = {
			(code % 16) * advance.x + data.bearing.x,
			_texture.height - (1 + code / 16) * advance.y + data.bearing.y,
			data.size.x,
			data.size.y
		};

		graphics->draw(_texture, destination, source);

		x += data.size.x + _spacing;
	}
}