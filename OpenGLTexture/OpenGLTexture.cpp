// OpenGLTexture.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>
#include <gl/glut.h>
#include <math.h>
#include "lodepng.h"

#define GL_PI 3.1415f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zDistance = 0.0f;

GLfloat amb[] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat dif[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat lightPos[] = { -50.0f, 50.0f, 100.0f, 1.0f };

GLuint texID[100];
std::vector<unsigned char> image;
std::vector<unsigned char> image2;
unsigned int width = 0, height = 0, width2 = 0, height2 = 0, error;

void SetupRC();
void LoadTexture();
void RenderScene();
void KeyControl(int key, int x, int y);
void ChangeSize(int w, int h);
void NormalkeyInput(unsigned char key, int x, int y);

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 800);
	glutCreateWindow("2D texture");

	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(KeyControl);	// 키보드 이벤트를 받기 위한 함수
	glutKeyboardFunc(NormalkeyInput);
	glutDisplayFunc(RenderScene);
	SetupRC();
	LoadTexture();
	glutMainLoop();
}


void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
		glTranslatef(-10.0f, 0.0f, zDistance);

		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		glEnable(GL_LIGHT0);

		glColor3f(1.0f, 1.0f, 1.0f);

		glBindTexture(GL_TEXTURE_2D, texID[0]);

		glEnable(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
		glutSolidTeapot(10.0f);

		glTranslatef(20.0f, 0.0f, 0.0f);
		glRotatef(0.0f, 1.0f, 0.0f, 0.0f);


		glBindTexture(GL_TEXTURE_2D, texID[1]);

		glEnable(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2.data());
		glutSolidTeapot(5.0f);
	glPopMatrix();

	glutSwapBuffers();
}

void SetupRC(void)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glGenTextures(2, texID);
}

void LoadTexture()
{
	error = lodepng::decode(image, width, height, "texture.png");

	if (error)
		printf("error %u: %s\n", error, lodepng_error_text(error));

	printf("\nimage size is %i", image.size());

	error = lodepng::decode(image2, width2, height2, "texture2.png");

	if (error)
		printf("error %u: %s\n", error, lodepng_error_text(error));

	printf("\nimage size is %i", image2.size());
}

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat fAspect;
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, fAspect, 1.0f, 500.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -50.0f);
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
	if (key == GLUT_KEY_F1) 
		zDistance += 5.0f;
	if (key == GLUT_KEY_F2)
		zDistance -= 5.0f;

	glutPostRedisplay();
}

void NormalkeyInput(unsigned char key, int x, int y)
{
	if (key == 'q') exit(-1);
}