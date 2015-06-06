#include "Planet.h"


Planet::Planet()
{
}


Planet::~Planet()
{
}


void Planet::Init(char* textureName, GLfloat size)
{
	mTexture = new MyTexture(textureName);
	mSize = size;

	mQobj = gluNewQuadric();
	gluQuadricDrawStyle(mQobj, GLU_FILL);
	gluQuadricTexture(mQobj, GL_TRUE);
	gluQuadricNormals(mQobj, GLU_SMOOTH);

}

void Planet::Draw()
{
	glTexImage2D(GL_TEXTURE_2D, 0, 4, mTexture->width, mTexture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, mTexture->image.data());

	gluSphere(mQobj, mSize, mSize * 10, mSize * 10);
}