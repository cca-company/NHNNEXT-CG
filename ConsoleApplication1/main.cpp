#include <windows.h>
#include <gl/glut.h>
#include "Rectangle.h"

GLfloat x1 = 0.0f;
GLfloat y1 = 0.0f;
GLsizei rsize = 50.0f;

GLfloat xstep = 2.0f;
GLfloat ystep = 2.0f;

GLfloat window_width;
GLfloat window_height;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);		// 컬러 버퍼 초기화

	// 그리기에 사용할 색상을 정의
	glColor3f(1.0f, 0.0f, 0.0f);

	// 사각형을 그릴 좌표를 지정
	// glRectf(x1, y1, x2, y2);
	// glTranslatef
	glRectf(x1, y1, x1+rsize, y1+rsize);

	//glFlush();
	glutSwapBuffers(); // 내부에 glFlush가 내장되어 있음
}
void SetupRC(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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
		// glOrtho(left, right, top, bottom, near, far)
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
}

void TimerFunction(int value){
	if (x1 > window_width - rsize || x1 < -window_width)
		xstep = -xstep;

	if (y1 > window_height - rsize || y1 < -window_height)
		ystep = -ystep;

	if (x1 > window_width - rsize)
		x1 = window_width - rsize - 1;

	if (y1 > window_height - rsize)
		y1 = window_height - rsize - 1;

	x1 += xstep;
	y1 += ystep;
	glutPostRedisplay();	// 화면 다시 그리셈
	glutTimerFunc(1, TimerFunction, 1);
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
