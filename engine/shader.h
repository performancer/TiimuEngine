#pragma once

class shader
{
private:
	unsigned int _shader;
	unsigned int _link(const char* vertex, const char* fragment);
	unsigned int _compile(const char* source, unsigned int type);
public:
	void load(const char* vertex, const char* fragment);
	void unload();
	void uniform(const char* key, int value);
	void use();
};