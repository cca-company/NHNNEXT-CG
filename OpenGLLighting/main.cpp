// Project :: OpenGLColor

#include <windows.h>
#include <gl/glut.h>
#include <math.h>
#include "gltools.h"
#include "GLEXT.H"

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat xPos = 0.0f;
static GLfloat yPos = 0.0f;

void SetupRC(void);
void RenderScene(void);
void ChangeSize(GLsizei w, GLsizei h);
void KeyControl(int key, int x, int y);
void MouseControl(GLint x, GLint y);
void TimerFunc(int value);
void DrawJet();

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("ambientJet");

	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(KeyControl);	// 키보드 이벤트를 받기 위한 함수
	glutPassiveMotionFunc(MouseControl);	// 마우스 이벤트를 받기 위한 함수
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

	DrawJet();
	
	glPopMatrix();

	glutSwapBuffers();

}

void SetupRC(void)
{
	GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	GLfloat lightPos[] = { 50.0f, 50.0f, 100.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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

void MouseControl(GLint x, GLint y)
{
	xPos = x;
	yPos = y;

	glutPostRedisplay();
}

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}

void DrawJet()
{
	GLTVector3 vNormal;	// Storeage for calculated surface normal (glTools.h)


	glBegin(GL_TRIANGLES);

	glColor3f(0.0f, 0.75f, 0.0f);

	//front bottom
	glNormal3f(0.0f, -1.0f, 0.0f);

		glVertex3f(0.0f, 0.0f, 60.0f);
			glVertex3f(-15.0f, 0.0f, 30.0f);
			glVertex3f(15.0f,0.0f,30.0f);
	//		//주석처리 제거   

	//Right Winng
	GLTVector3 vPoints[3] = { { 15.0f, 0.0f, 30.0f },
	{ 0.0f, 15.0f, 30.0f },
	{ 0.0f, 0.0f, 60.0f } };

	// Calculate the normal for the plane
	gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal); //(glTools.h)

	glNormal3fv(vNormal);
	glVertex3fv(vPoints[0]);
	glVertex3fv(vPoints[1]);
	glVertex3fv(vPoints[2]);

	{
		GLTVector3 vPoints[3] = { { 0.0f, 0.0f, 60.0f },
		{ 0.0f, 15.0f, 30.0f },
		{ -15.0f, 0.0f, 30.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}

	glColor3f(0.6f, 0.6f, 0.6f);

	// Body of the Plane ////////////////////////
	{
		GLTVector3 vPoints[3] = { { -15.0f, 0.0f, 30.0f },
		{ 0.0f, 15.0f, 30.0f },
		{ 0.0f, 0.0f, -56.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}

	{
		GLTVector3 vPoints[3] = { { 0.0f, 0.0f, -56.0f },
		{ 0.0f, 15.0f, 30.0f },
		{ 15.0f, 0.0f, 30.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}


	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(15.0f, 0.0f, 30.0f);
	glVertex3f(-15.0f, 0.0f, 30.0f);
	glVertex3f(0.0f, 0.0f, -56.0f);


	glColor3f(0.3f, 0.3f, 0.3f);
	///////////////////////////////////////////////
	// Left wing
	// Large triangle for bottom of wing
	{
		GLTVector3 vPoints[3] = { { 0.0f, 2.0f, 27.0f },
		{ -60.0f, 2.0f, -8.0f },
		{ 60.0f, 2.0f, -8.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}


	{
		GLTVector3 vPoints[3] = { { 60.0f, 2.0f, -8.0f },
		{ 0.0f, 7.0f, -8.0f },
		{ 0.0f, 2.0f, 27.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}

	{
		GLTVector3 vPoints[3] = { { 60.0f, 2.0f, -8.0f },
		{ -60.0f, 2.0f, -8.0f },
		{ 0.0f, 7.0f, -8.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}

	{
		GLTVector3 vPoints[3] = { { 0.0f, 2.0f, 27.0f },
		{ 0.0f, 7.0f, -8.0f },
		{ -60.0f, 2.0f, -8.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}


	// Tail section///////////////////////////////
	// Bottom of back fin
	glColor3f(0.75f, 0.75f, 0.0f);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-30.0f, -0.50f, -57.0f);
	glVertex3f(30.0f, -0.50f, -57.0f);
	glVertex3f(0.0f, -0.50f, -40.0f);


	{
		GLTVector3 vPoints[3] = { { 0.0f, -0.5f, -40.0f },
		{ 30.0f, -0.5f, -57.0f },
		{ 0.0f, 4.0f, -57.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}


	{
		GLTVector3 vPoints[3] = { { 0.0f, 4.0f, -57.0f },
		{ -30.0f, -0.5f, -57.0f },
		{ 0.0f, -0.5f, -40.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}


	{
		GLTVector3 vPoints[3] = { { 30.0f, -0.5f, -57.0f },
		{ -30.0f, -0.5f, -57.0f },
		{ 0.0f, 4.0f, -57.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}

	glColor3f(0.75f, 0.0f, 0.0f);
	{
		GLTVector3 vPoints[3] = { { 0.0f, 0.5f, -40.0f },
		{ 3.0f, 0.5f, -57.0f },
		{ 0.0f, 25.0f, -65.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}

	{
		GLTVector3 vPoints[3] = { { 0.0f, 25.0f, -65.0f },
		{ -3.0f, 0.5f, -57.0f },
		{ 0.0f, 0.5f, -40.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}

	{
		GLTVector3 vPoints[3] = { { 3.0f, 0.5f, -57.0f },
		{ -3.0f, 0.5f, -57.0f },
		{ 0.0f, 25.0f, -65.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}


	glEnd();
}
