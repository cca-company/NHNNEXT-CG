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
void TimerFunc(int value);

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Atom");


	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunc, 1);
	glutSpecialFunc(KeyControl);	// 키보드 이벤트를 받기 위한 함수
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}


void RenderScene(void)
{
	static GLfloat fElect1 = 0.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -100.0f);
	glColor3ub(255, 0, 0);
	glutSolidSphere(10.0f, 15, 15);

	glPushMatrix();
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(90.0f, 0.0f, 0.0f);
	glColor3ub(255, 255, 0);
	glutSolidSphere(6.0f, 15, 15);
	//glPopMatrix();

	//glPushMatrix();
	//glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	//glTranslatef(90.0f, 0.0f, 0.0f);
	//glPopMatrix();

	//glPushMatrix();
	glColor3ub(255, 0, 0);
	//glutSolidSphere(6.0f, 15, 15);
	//glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 20.0f);
	glutSolidSphere(3.0f, 10, 10);
	glPopMatrix();


	glColor3ub(0, 0, 255);
	glPushMatrix();
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(-70.0f, 0.0f, 0.0f);
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();


	fElect1 += 10.0f;
	if (fElect1 > 360.0f)
		fElect1 = 0.0f;

	glutSwapBuffers();
}

void SetupRC(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 100.0f;

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