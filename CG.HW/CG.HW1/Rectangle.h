#pragma once
#include <windows.h>
#include <gl/glut.h>
#include <vector>

struct Frame{
	GLfloat x1, y1, x2, y2;
};

class MyRectangle
{
public:
	MyRectangle();
	~MyRectangle();

	void Init(GLfloat x, GLfloat y, GLsizei size, GLfloat windowWidth, GLfloat windowHeight);

	void Draw();

	void SetPos(GLfloat x, GLfloat y){ mX = x; mY = y; }
	void SetSize(GLsizei size){ mSize = size; }
	void SetColor(GLfloat colorR, GLfloat colorG, GLfloat colorB){ mColorR = colorR; mColorG = colorG; mColorB = colorB; }
	void SetSpeed(GLfloat stepX, GLfloat stepY){ mStepX = stepX; mStepY = stepY; }
	void SetFrame(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
	void SetChildColor(GLfloat colorR, GLfloat colorG, GLfloat colorB);

	MyRectangle* GetChild(){ return mChild; }

	void CheckCrash(MyRectangle* rectangle);
	void CheckCrash();

protected:
	GLfloat mX;
	GLfloat mY;
	GLsizei mSize;

	GLfloat mColorR = 0.0f;
	GLfloat mColorG = 0.0f;
	GLfloat mColorB = 0.0f;

	GLfloat mStepX = 1.0f;
	GLfloat mStepY = 1.0f;

	Frame mFrame;

	MyRectangle* mChild;
};