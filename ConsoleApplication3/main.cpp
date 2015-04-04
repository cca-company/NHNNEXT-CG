#include <windows.h>
#include <gl/glut.h>
#include <math.h>

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

GLfloat window_width;
GLfloat window_height;

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
	GLfloat x, y, z, angle;
	glClear(GL_COLOR_BUFFER_BIT);		// �÷� ���� �ʱ�ȭ

	glPushMatrix();	// Matrix�� ���ÿ� ����
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glBegin(GL_POINTS);
	z = -50.0f;

	for (angle = 0.0f; angle <= (2.0f*GL_PI)*3.0f; angle += 0.1f)
	{
		x = 60.0f*sin(angle);
		y = 60.0f*cos(angle);
		glVertex3f(x, y, z);
		x += 0.5f;
	}

	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}

void SetupRC(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 100.0f;

	glMatrixMode(GL_PROJECTION);	// projection�� ���� matrix�� ����
	glLoadIdentity();				// identity matrix�� ����
	glViewport(0, 0, w, h);			// viewport�� ����� ����

	if (w <= h)
	{
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, 1.0f, -1.0f);
	}
	else
	{
		window_width = 100.0f * w / h;
		window_height = 100.0f;
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, 1.0f, -1.0f);
	}

	glMatrixMode(GL_MODELVIEW);		// model transform�� ���� matrix�� ����
	glLoadIdentity();
}

void KeyControl(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		xRot -= 5.0f;
		break;
	case GLUT_KEY_DOWN:
		xRot += 5.0f;
		break;
	case GLUT_KEY_LEFT:
		yRot -= 5.0f;
		break;
	case GLUT_KEY_RIGHT:
		yRot += 5.0f;
		break;
	}

	glutPostRedisplay();
}