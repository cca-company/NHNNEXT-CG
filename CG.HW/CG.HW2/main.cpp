/*
CG Practical problem 2
*/

#include <windows.h>
#include <gl/glut.h>
#include <math.h>

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void SetupRC(void);
void RenderScene(void);
void ChangeSize(GLsizei w, GLsizei h);
void KeyControl(int key, int x, int y);

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("SpringVertex");

	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(KeyControl);	// Ű���� �̺�Ʈ�� �ޱ� ���� �Լ�
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}


void RenderScene(void)
{

	GLfloat x, y, z, r, ri, angle;

	glClear(GL_COLOR_BUFFER_BIT);		// �÷� ���� �ʱ�ȭ
	glPushMatrix();	// Matrix�� ���ÿ� ����
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glBegin(GL_POINTS);
	z = -50.0f;
	r = 0.0f;
	ri = 0.0;

	for (angle = 0.0f; angle <= (2.0f*GL_PI)*5.0f; angle += 0.1f)
	{
		x = r*sin(angle);
		y = r*cos(angle);
		glVertex3f(x, y, z);

		z += 0.3f;
		r += ri;
		ri += 0.002;
	}

	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}

void SetupRC(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 100.0f;

	glMatrixMode(GL_PROJECTION);	// projection�� ���� matrix�� ����
	glLoadIdentity();				// identity matrix�� ����
	glViewport(0, 0, w, h);			// viewport�� ����� ����

	if (w <= h)
	{
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, 100.0f, -100.0f);
	}
	else
	{
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, 100.0f, -100.0f);
	}

	glMatrixMode(GL_MODELVIEW);		// model transform�� ���� matrix�� ����
	glLoadIdentity();
}

void KeyControl(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;
	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;
	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;
	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	glutPostRedisplay();
}