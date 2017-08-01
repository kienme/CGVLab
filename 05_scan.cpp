#include <iostream>
#include <GL/glut.h>

using namespace std;

int le[500], re[500];

float x1 = 200, y1 = 200;
float x2 = 100, y2 = 300;
float x3 = 200, y3 = 400;
float x4 = 300, y4 = 300;

void detectEdge(float x1, float y1, float x2, float y2)
{
	if(y1 > y2)
	{ 
		float temp=x1; x1=x2; x2=temp; 
		temp=y1; y1=y2; y2=temp; 
	}

	float mx = (x2 - x1);
	if(y1 != y2)
		mx /= (y2 - y1);

	float x = x1;
	for(int i = y1; i <= y2; ++i)
	{
		if(x < le[i])
			le[i] = x;

		if(x > re[i])
			re[i] = x;

		x += mx;
	} 
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	for(int i = 0; i < 500; ++i)
	{
		le[i] = 500;
		re[i] = 0;
	}

	detectEdge(x1, y1, x2, y2);
	detectEdge(x2, y2, x3, y3);
	detectEdge(x3, y3, x4, y4);
	detectEdge(x4, y4, x1, y1);

	glColor3f(1.0, 1.0, 0.0);
	for(int i = 0; i < 500; ++i)
	{
		if(le[i] < re[i])
		{
			glBegin(GL_LINES);
				glVertex2d(le[i], i);
				glVertex2d(re[i], i);
			glEnd();
		}
	}

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
	glutCreateWindow("Polygon filling");

	init();

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}