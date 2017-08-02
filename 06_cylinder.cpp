#include <iostream>
#include <math.h>
#include <GL/glut.h>

using namespace std;

//Parameters for cyl and ppd

int c_radius = 80, c_center = 100, c_height = 90;
int p_center = 300, p_width = 100, p_length = 150, p_height = 30;

void cylinder()
{
	/*
	Use parametric equation of circle repeatedly to draw cylinder
	Each new circle is drawn with an increasing y value for centre
	*/

	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
		for(int k = 0; k < c_height; k += 2)
			for(float i = 0; i < 2*3.14; i += 0.001)
				glVertex2f(c_radius*cos(i) + c_center, c_radius*sin(i) + c_center + k);
	glEnd();
}

void piped()
{
	/*
	Repeatedly draw rectangles
	Each new rectangle is drawn with increasing x,y values for centre
	*/

	glColor3f(0.0, 1.0, 1.0);
	for(int k = 0; k < p_height; ++k)
	{
		p_center += 2;

		glBegin(GL_LINE_LOOP);
			glVertex2d(p_center - p_length/2, p_center - p_width/2);
			glVertex2d(p_center - p_length/2, p_center + p_width/2);
			glVertex2d(p_center + p_length/2, p_center + p_width/2);
			glVertex2d(p_center + p_length/2, p_center - p_width/2);
		glEnd();
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	cylinder();
	piped();

	glutSwapBuffers();
}

void init()
{
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 499.0, 0.0, 499.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Cylinder and parallelopiped");

	init();

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}