#include <iostream>
#include <GL/glut.h>

using namespace std;

typedef float point[3];	
int m = 3;

point vert[4] = {
	{-0.81, -0.47, -0.33}, {0.81, -0.47, -0.33}, 
	{0.0, 0.94, -0.33}, {0.0, 0.0, 1.0}
};

void triangle(point a, point b, point c)
{
	glBegin(GL_TRIANGLES);
		glVertex3fv(a);
		glVertex3fv(b);
		glVertex3fv(c);
	glEnd();
}


void divide(point a, point b, point c, int m)
{
	if(m > 0)
	{
		point ab, ac, bc;
		for(int i = 0; i < 3; ++i)
		{
			ab[i] = (a[i] + b[i]) / 2.0;
			ac[i] = (a[i] + c[i]) / 2.0;
			bc[i] = (b[i] + c[i]) / 2.0;
		}

		divide(a, ab, ac, m - 1);
		divide(b, ab, bc, m - 1);
		divide(c, ac, bc, m - 1);
	}

	else
		triangle(a, b, c);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.0, 0.0, 1.0);
	divide(vert[0], vert[1], vert[2], m);

	glColor3f(0.0, 1.0, 0.0);
	divide(vert[0], vert[3], vert[2], m);

	glColor3f(0.0, 0.0, 0.0);
	divide(vert[0], vert[3], vert[1], m);

	glColor3f(1.0, 0.0, 0.0);
	divide(vert[1], vert[3], vert[2], m);

	glutSwapBuffers();
}

void init()
{
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("3D Gasket");

	init();

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}