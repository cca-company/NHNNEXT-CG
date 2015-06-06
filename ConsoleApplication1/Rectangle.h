#pragma once
#include <windows.h>
#include <gl/glut.h>

class Rectangle
{
public:
	Rectangle();
	~Rectangle();

	void Init(GLfloat x, GLfloat y, GLsizei size);

	void SetPos(GLfloat x, GLfloat y){ mX = x; mY = y; }
	void SetSize(GLsizei size);
	void SetColor(GLfloat colorR, GLfloat colorG, GLfloat colorB);
	void SetSpeed(GLfloat stepX, GLfloat stepY);

	void CheckCrash(GLsizei windowWidth, GLsizei windowHeight);

protected:
	GLfloat mX;
	GLfloat mY;
	GLsizei mRsize;

	GLfloat mColorR = 0.0f;
	GLfloat mColorG = 0.0f;
	GLfloat mColorB = 0.0f;

	GLfloat mXstep = 1.0f;
	GLfloat mYstep = 1.0f;
};

