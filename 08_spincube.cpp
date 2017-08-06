#include <iostream>
#include <GL/glut.h>

using namespace std;

int cube[8][3] = {
	{-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1},
	{-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1}
};

float colors[8][3] = {
	{0, 0, 1}, {1, 0, 1}, {1, 1, 1}, {0, 1, 1},
	{0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0}
};

float theta[3];
int axis = 2;

void mouse(int btn, int state, int x, int y)
{
	if(state == GLUT_DOWN)
	{
		switch(btn)
		{
			case GLUT_LEFT_BUTTON:
				axis = 0;
				break;
			
			case GLUT_MIDDLE_BUTTON:
				axis = 1;
				break;

			case GLUT_RIGHT_BUTTON:
				axis = 2;
				break;
		}
	}
}

void face(int a, int b, int c, int d)
{
	glBegin(GL_QUADS);
		glColor3fv(colors[a]);
		glVertex3iv(cube[a]);
		glColor3fv(colors[b]);
		glVertex3iv(cube[b]);
		glColor3fv(colors[c]);
		glVertex3iv(cube[c]);
		glColor3fv(colors[d]);
		glVertex3iv(cube[d]);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	face(0, 1, 2, 3);
	face(3, 7, 6, 2);
	face(7, 4, 5, 6);
	face(4, 0, 1, 5);
	face(2, 1, 5, 6);
	face(0, 4, 7, 3);

	glutSwapBuffers();
}

void idle()
{
	theta[axis] += 0.5;
	if(theta[axis] > 360.0)
		theta[axis] -= 360.0;

	glLoadIdentity();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	glutPostRedisplay();
}

void init()
{
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -2, 2);
	glMatrixMode(GL_MODELVIEW);
	
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Cube");

	init();

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutMainLoop();

	return 0;
}