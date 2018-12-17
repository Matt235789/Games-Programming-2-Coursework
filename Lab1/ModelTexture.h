#pragma once
#include <string>
#include <GL\glew.h>

class ModelTexture
{
public:
	ModelTexture();

	void Bind(unsigned int unit); // bind upto 32 textures
	void init(const std::string& fileName);

	~ModelTexture();

protected:
private:

	GLuint textureHandler;
};

