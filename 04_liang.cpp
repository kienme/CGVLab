#include <iostream>
#include <GL/glut.h>

using namespace std;

bool accept = false;

float xmin = 50, ymin = 50, xmax = 100, ymax = 100;
float xvmin = 200, yvmin = 200, xvmax = 300, yvmax = 300;

float x0 = 60, y0 = 20;
float x1 =  80, y1 = 120;

void drawClipped()
{
	glBegin(GL_LINE_LOOP);
		glVertex2d(xvmin, yvmin);
		glVertex2d(xvmin, yvmax);
		glVertex2d(xvmax, yvmax);
		glVertex2d(xvmax, yvmin);
	glEnd();

	if(accept)
	{
		float sx = (xvmax - xvmin) / (xmax - xmin);
		float sy = (yvmax - yvmin) / (ymax - ymin);

		float xv0 = xvmin + (x0 - xmin)*sx;
		float yv0 = yvmin + (y0 - ymin)*sy;
		float xv1 = xvmin + (x1 - xmin)*sx;
		float yv1 = yvmin + (y1 - ymin)*sy;

		glBegin(GL_LINES);
			glVertex2d(xv0, yv0);
			glVertex2d(xv1, yv1);
		glEnd();
	}
}

bool test(float p, float q, float *t1, float *t2)
{
	float r = (float)q / p;
	
	if(p == 0.0)
		if(q < 0.0)
			return false;

	if(p < 0.0)
		if(r > *t1)
			*t1 = r;

	if(p > 0.0)
		if(r < *t2)
			*t2 = r;

	if(*t1 > *t2)
		return false;

	return true;
}

void clip()
{
	float t1 = 0.0, t2 = 1.0;
	float dx = x1 - x0, dy = y1 - y0;
	
	float p1 = -dx, p2 = dx, p3 = -dy, p4 = dy;
	float q1 = x0 - xmin, q2 = xmax - x0, q3 = y0 - ymin, q4 = ymax - y0;

	if(test(p1, q1, &t1, &t2))
		if(test(p2, q2, &t1, &t2))
			if(test(p3, q3, &t1, &t2))
				if(test(p4, q4, &t1, &t2))
				{
					accept = true;

					if(t2 < 1.0)
					{						
						x1 = x0 + t2 * dx; 
						y1 = y0 + t2 * dy;
					}

					if(t1 > 0.0)
					{
						x0 = x0 + t1 * dx; 
						y0 = y0 + t1 * dy;
					}
				}

	drawClipped();
}

void drawUnclipped()
{
	glBegin(GL_LINE_LOOP);
		glVertex2d(xmin, ymin);
		glVertex2d(xmin, ymax);
		glVertex2d(xmax, ymax);
		glVertex2d(xmax, ymin);
	glEnd();

	glBegin(GL_LINES);
		glVertex2d(x0, y0);
		glVertex2d(x1, y1);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);

	drawUnclipped();
	clip();

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
	glutCreateWindow("Line clipping");

	init();

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}