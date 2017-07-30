#include <iostream>
#include <GL/glut.h>

using namespace std;

int T = 8, B = 4, R = 2, L = 1;

//Actual window params
int xmin = 50, ymin = 50, xmax = 100, ymax = 100;

//Scaled window params
int xvmin = 200, yvmin = 200, xvmax = 300, yvmax = 300;

//Actual line params
int x0 = 60, y0 = 20;
int x1 = 80, y1 = 120;

int computeOC(int x, int y)
{
	int ret = 0;

	if(x > xmax)
		ret |= R;
	else if(x < xmin)
		ret |= L;

	if(y > ymax)
		ret |= T;
	else if(y < ymin)
		ret |= B;

	return ret;
}

void drawClipped(bool accept)
{
	//Draw the scaled window
	
	glBegin(GL_LINE_LOOP);
		glVertex2d(xvmin, yvmin);
		glVertex2d(xvmin, yvmax);
		glVertex2d(xvmax, yvmax);
		glVertex2d(xvmax, yvmin);
	glEnd();

	//Scale the clipped line and draw

	double sx = (xvmax-xvmin) / (xmax-xmin);
	double sy = (yvmax-yvmin) / (ymax-ymin);

	int vx0 = xvmin + (x0 - xmin)*sx;
	int vy0 = yvmin + (y0 - ymin)*sy;
	int vx1 = xvmin + (x1 - xmin)*sx;
	int vy1 = yvmin + (y1 - ymin)*sy;

	glBegin(GL_LINES);
		glVertex2d(vx0, vy0);
		glVertex2d(vx1, vy1);
	glEnd();
}

void clip()
{
	int oc0 = computeOC(x0, y0);
	int oc1 = computeOC(x1, y1);

	bool done = false, accept = false;

	while(!done)
	{
		//Both in clipping window
		if(!(oc0 | oc1))
			done = accept = true;

		//Both in same region
		else if(oc0 & oc1)
			done = true;

		else
		{
			int ocOut = oc0 ? oc0 : oc1;
			int x, y;

			//Find intersection point

			if(ocOut & T)
			{
				x = x0 + (x1 - x0)*(ymax - y0)/(y1 - y0);
				y = ymax;
			}
			
			else if(ocOut & B)
			{
				x = x0 + (x1 - x0)*(ymin - y0)/(y1 - y0);
				y = ymin;
			}

			else if(ocOut & R)
			{
				x = xmax;
				y = y0 + (y1 - y0)*(xmax - x0)/(x1 - x0);
			}

			else
			{
				x = xmin;
				y = y0 + (y1 - y0)*(xmin - x0)/(x1 - x0);
			}

			if(ocOut == oc0)
			{
				x0 = x;
				y0 = y;
				oc0 = computeOC(x, y);
			}

			else
			{
				x1 = x;
				y1 = y;
				oc1 = computeOC(x, y);
			}
		}
	}

	drawClipped(accept);
}

void drawUnclipped()
{
	//Draw the window and line, as is.

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
	glutCreateWindow("Line Clipping");

	init();

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}