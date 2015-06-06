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
	glClear(GL_COLOR_BUFFER_BIT);		// �÷� ���� �ʱ�ȭ

	for (auto rect : rectangleList)
	{
		rect->Draw();
	}

	glutSwapBuffers(); // ���ο� glFlush�� ����Ǿ� ����
}
void SetupRC(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	GLfloat setPos[][2] = { { -50.0f, -50.0f }, { -50.0f, 20.0f }, { 20.0f, 20.0f }, { 20.0f, -50.0f } };

	for (int i = 0; i < 1; ++i)
	{
		MyRectangle* newRect = new MyRectangle();
		newRect->Init(setPos[i][0], setPos[i][1], 40.0f, window_width, window_height);
		newRect->SetColor(0.0f, 1.0f, 1.0f);
		newRect->SetChildColor(1.0f, 1.0f, 0.0f);

		rectangleList.push_back(newRect);
	}
}
/*
 w : �������� width
 h : �������� height
*/
void ChangeSize(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);			// viewport�� ����� ����

	glMatrixMode(GL_PROJECTION);	// projection�� ���� matrix�� ����
	glLoadIdentity();				// identity matrix�� ����

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

	glMatrixMode(GL_MODELVIEW);		// model transform�� ���� matrix�� ����
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
	}

	glutPostRedisplay();	// ȭ�� �ٽ� �׸���
	glutTimerFunc(10, TimerFunction, 1);
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("BounceRectangle");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize); // ������ ����� ����ɶ� ȣ��Ǵ� �Լ�
	glutTimerFunc(2000,TimerFunction,1);
	SetupRC();
	glutMainLoop();
}
