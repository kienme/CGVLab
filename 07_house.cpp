#include <iostream>
#include <math.h>
#include <GL/glut.h>

using namespace std;

//Vertex to rotate about
int pivot_index = 0;

//Angle in degrees
int angle = 30;

int house[9][2] = {
	{100, 100}, {100, 300}, {175, 400}, {250, 300}, {250, 100},
	{200, 100}, {200, 150}, {150, 150}, {150, 100}
};

void drawHouse()
{
	glBegin(GL_LINE_LOOP);
		for(int i = 0; i < 9; ++i)
			glVertex2i(house[i][0], house[i][1]);
	glEnd();

	glBegin(GL_LINES);
		glVertex2i(house[1][0], house[1][1]);
		glVertex2i(house[3][0], house[3][1]);
		glVertex2i(house[5][0], house[5][1]);
		glVertex2i(house[8][0], house[8][1]);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawHouse();
	
	glTranslated(house[pivot_index][0], house[pivot_index][1], 0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	glTranslated(-house[pivot_index][0], -house[pivot_index][1], 0);

	drawHouse();

	glutSwapBuffers();
}

void init()
{
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 499.0, 0.0, 499.0);
	glMatrixMode(GL_MODELVIEW);
	glColor3f(1.0, 1.0, 0.0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("house");

	init();

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}