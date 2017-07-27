#include<iostream>
#include<GL/glut.h>

using namespace std;

int x0 = 10, y0 = 10;
int dx = 10, dy = 10;
int xmax = 200, ymax = 200;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);

	glBegin(GL_LINES);
		//Draw vertical lines between y0 and ymax for varying x values
		for(int x = x0; x <= xmax; x += dx)
		{
			glVertex2f(x, y0);
			glVertex2f(x, ymax);
		}
		//Draw horizontal lines between x0 and xmax for varying y values
		for(int y = y0; y <= ymax; y += dy)
		{
			glVertex2f(x0, y);
			glVertex2f(xmax, y);
		}
	glEnd();

	glutSwapBuffers();
}

void init()
{
	glClearColor(0.2, 0.2, 0.2, 1.0);
	gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Mesh");

	init();

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}