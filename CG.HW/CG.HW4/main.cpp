#include <windows.h>
#include <gl/glut.h>
#include <math.h>
#include "lodepng.h"
#include "Planet.h"

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;


GLfloat amb[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPos[] = { 0.0f, 0.0f, 50.0f, 1.0f };

GLuint texID[100];
Planet sun, earth, moon, mars;

void SetupRC(void);
void RenderScene(void);
void ChangeSize(GLsizei w, GLsizei h);
void KeyControl(int key, int x, int y);
void TimerFunc(int value);
void LoatTexture();

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


	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();
	
	glTranslatef(0.0f, 0.0f, -100.0f);

	sun.Draw();

	glPushMatrix();
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(90.0f, 0.0f, 0.0f);

	earth.Draw();

	glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 20.0f);

	// moon
	moon.Draw();

	glPopMatrix();


	glPushMatrix();
	glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(-70.0f, 0.0f, 0.0f);

	// mars
	mars.Draw();

	glPopMatrix();


	fElect1 += 10.0f;
	if (fElect1 > 360.0f)
		fElect1 = 0.0f;

	glutSwapBuffers();
}

void LoatTexture()
{
	sun.Init("sun.png", 18.0f);
	earth.Init("earth.png", 10.0f);
	moon.Init("moon.png", 5.0f);
	mars.Init("mars.png", 15.0f);
}

void SetupRC(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glFrontFace(GL_CCW);

	glGenTextures(4, texID);
	LoatTexture();

	glBindTexture(GL_TEXTURE_2D, texID[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
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
	glutTimerFunc(50, TimerFunc, 1);
}