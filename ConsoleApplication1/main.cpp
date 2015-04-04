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
	glClear(GL_COLOR_BUFFER_BIT);		// �÷� ���� �ʱ�ȭ

	// �׸��⿡ ����� ������ ����
	glColor3f(1.0f, 0.0f, 0.0f);

	// �簢���� �׸� ��ǥ�� ����
	// glRectf(x1, y1, x2, y2);
	// glTranslatef
	glRectf(x1, y1, x1+rsize, y1+rsize);

	//glFlush();
	glutSwapBuffers(); // ���ο� glFlush�� ����Ǿ� ����
}
void SetupRC(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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
		// glOrtho(left, right, top, bottom, near, far)
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
	glutPostRedisplay();	// ȭ�� �ٽ� �׸���
	glutTimerFunc(1, TimerFunction, 1);
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
