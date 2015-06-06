#include "Rectangle.h"


MyRectangle::MyRectangle()
{
	mChild = nullptr;
}


MyRectangle::~MyRectangle()
{
	free(mChild);
}

void MyRectangle::Draw()
{
	glColor3f(mColorR, mColorG, mColorB);
	glRectf(mX, mY, mX+mSize, mY + mSize);

	if (mChild != nullptr) mChild->Draw();
}

void MyRectangle::SetChildColor(GLfloat colorR, GLfloat colorG, GLfloat colorB)
{
	mChild->SetColor(colorR, colorG, colorB);
}

void MyRectangle::CheckCrash()
{
	if (mX < mFrame.x1 || mX > mFrame.x2 - mSize)
		mStepX = -mStepX;

	if (mY < mFrame.y1 || mY > mFrame.y2 - mSize)
		mStepY = -mStepY;

	if (mX > mFrame.x2 - mSize)
		mX = mFrame.x2 - mSize - 1;

	if (mY > mFrame.y2 - mSize)
		mY = mFrame.y2 - mSize - 1;

	mX += mStepX;
	mY += mStepY;

	if (mChild != nullptr)
	{
		mChild->mX += mStepX;
		mChild->mY += mStepY;
		mChild->SetFrame(mX, mY, mX + mSize, mY + mSize);
		mChild->CheckCrash();
	}
}

void MyRectangle::Init(GLfloat x, GLfloat y, GLsizei size, GLfloat windowWidth, GLfloat windowHeight)
{
	SetPos(x, y);
	SetSize(size);
	SetFrame(-windowWidth, -windowHeight, windowWidth, windowHeight);

	mChild = new MyRectangle();
	mChild->SetPos(x+size/4, y+size/4);
	mChild->SetSize(size / 2);
	mChild->SetFrame(mX, mY, mX+mSize, mY+mSize);
}

void MyRectangle::SetFrame(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
	mFrame.x1 = x1;
	mFrame.y1 = y1;
	mFrame.x2 = x2;
	mFrame.y2 = y2;
}