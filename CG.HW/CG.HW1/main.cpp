/*
CG Practical problem 3
*/

#include "Rectangle.h"
#include <windows.h>
#include <gl/glut.h>
#include <vector>

GLfloat window_width;
GLfloat window_height;
std::vector<MyRectangle*> rectangleList;


void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);		// 컬러 버퍼 초기화

	for (auto rect : rectangleList)
	{
		rect->Draw();
	}

	glutSwapBuffers(); // 내부에 glFlush가 내장되어 있음
}
void SetupRC(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	GLfloat setPos[][2] = { { -50.0f, -50.0f }, { -50.0f, 20.0f }, { 20.0f, 20.0f }, { 20.0f, -50.0f } };
	GLfloat setColor[][3] = { { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 1.0f }, { 0.0f, 0.8f, 0.5f } };
	GLfloat setSpeed[][2] = { { 2.0f, 1.0f }, { -1.0f, -2.0f }, { 1.0f, -1.0f }, { -1.0f, 1.0f }};

	for (int i = 0; i < 4; ++i)
	{
		MyRectangle* newRect = new MyRectangle();
		newRect->Init(setPos[i][0], setPos[i][1], 40.0f, window_width, window_height);
		newRect->SetColor(setColor[i][0], setColor[i][1], setColor[i][2]);
		newRect->SetChildColor(1.0f, 1.0f, 0.0f);
		newRect->SetSpeed(setSpeed[i][0], setSpeed[i][1]);

		rectangleList.push_back(newRect);
	}
}
/*
 w : 윈도우의 width
 h : 윈도우의 height
*/
void ChangeSize(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);			// viewport의 사이즈를 정의

	glMatrixMode(GL_PROJECTION);	// projection을 위한 matrix를 생성
	glLoadIdentity();				// identity matrix를 생성

	if (w <= h)
	{
		window_width = 100.0f;
		window_height = 100.0f * h / w;
		glOrtho(-100.0f, 100.0f, -100.0f*h / w, 100.0f*h / w, 1.0f, -1.0f);
	}
	else
	{
		window_width = 100.0f * w / h;
		window_height = 100.0f;
		glOrtho(-100.0f*w / h, 100.0f*w / h, -100.0f, 100.0f, 1.0f, -1.0f);
	}

	glMatrixMode(GL_MODELVIEW);		// model transform을 위한 matrix를 생성
	glLoadIdentity();

	for (auto rect : rectangleList)
	{
		rect->SetFrame(-window_width, -window_height, window_width, window_height);
	}
}

void TimerFunction(int value)
{

	for (auto rect : rectangleList)
	{
		rect->CheckCrash();
		for (auto crashRect : rectangleList)
		{
			if (crashRect != rect)
			{
				rect->CheckCrash(crashRect);
			}
		}
	}

	glutPostRedisplay();	// 화면 다시 그리셈
	glutTimerFunc(50, TimerFunction, 1);
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("BounceRectangle");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize); // 윈도우 사이즈가 변경될때 호출되는 함수
	glutTimerFunc(2000,TimerFunction,1);
	SetupRC();
	glutMainLoop();
}
