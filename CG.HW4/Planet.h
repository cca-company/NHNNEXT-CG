#pragma once
#include <gl/glut.h>
#include "lodepng.h"

struct MyTexture{
	std::vector<unsigned char> image;
	unsigned int width, height, error;

	MyTexture();
	MyTexture(char* textureName)
	{
		error = lodepng::decode(image, width, height, textureName);

		if (error)
			printf("error %u: %s\n", error, lodepng_error_text(error));

		printf("\nimage size is %i", image.size());
	}
};

class Planet
{
public:
	Planet();
	~Planet();

	void Init(char* textureName, GLfloat size);

	void Draw();

protected:
	GLfloat mSize;
	MyTexture* mTexture;
	GLUquadric* mQobj;
};

