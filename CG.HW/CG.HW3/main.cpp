// Project :: OpenGLColor

#include <windows.h>
#include <gl/glut.h>
#include <math.h>

#define GL_PI 3.1415f
typedef GLfloat Point3D[3];
typedef GLfloat color[4];

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void SetupRC(void);
void RenderScene(void);
void ChangeSize(GLsizei w, GLsizei h);
void KeyControl(int key, int x, int y);
void TimerFunc(int value);

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("color cube");

	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(KeyControl);	// 키보드 이벤트를 받기 위한 함수
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}


void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);

	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(45.0f, 0.0f, -1.0f, 0.0f);

	GLfloat length = 200.0f;

	int polygon[][4] = {
			{ 0, 1, 2, 3 },
			{ 4, 5, 6, 7 },
			{ 0, 4, 5, 1 },
			{ 3, 7, 6, 2 },
			{ 5, 1, 2, 6 },
			{ 4, 0, 3, 7 }
	};
	int vertex[][3] = {
			{ 1, 1, 1 },
			{ 0, 1, 1 },
			{ 0, 0, 1 },
			{ 1, 0, 1 },
			{ 1, 1, 0 },
			{ 0, 1, 0 },
			{ 0, 0, 0 },
			{ 1, 0, 0 },
	};

	for (int i = 0; i < 6; ++i)
	{
		glBegin(GL_QUADS);
		for (int j = 0; j < 4; ++j)
		{
			int numOfVertex = polygon[i][j];
			int	x = vertex[numOfVertex][0],
				y = vertex[numOfVertex][1],
				z = vertex[numOfVertex][2];

			glColor3ub((GLubyte)255 * x, (GLubyte)255 * y, (GLubyte)255 * z);
			glVertex3f(length*(x - 0.5f), length*(y - 0.5f), length*(z - 0.5f));
		}
		glEnd();
	}

	glPopMatrix();

	glutSwapBuffers();

}

void SetupRC(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glFrontFace(GL_CCW); 
	glEnable(GL_DEPTH_TEST);

}

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 250.0f;

	glMatrixMode(GL_PROJECTION);	// projection을 위한 matrix를 생성
	glLoadIdentity();				// identity matrix를 생성
	glViewport(0, 0, w, h);			// viewport의 사이즈를 정의

	if (w <= h)
	{
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange*2.0f, nRange*2.0f);
	}
	else
	{
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange*2.0f, nRange*2.0f);
	}

	glMatrixMode(GL_MODELVIEW);		// model transform을 위한 matrix를 생성
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

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}