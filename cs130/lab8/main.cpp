// Name: 
// Quarter, Year: 
// Lab:
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#include <GL/glut.h>
#include <math.h>
#include <complex>
#include "color.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
int MAX_ITERS = 5;

void renderJuliaSet(double xmin, double xmax, double ymin, double ymax)
{
	std::complex<double> x(0.5);

	int iters = 0;
	while( abs(x) < 2.0 && iters < MAX_ITERS )
	{
		x = x + 2;
		++iters;
	}

	float R = (xmax-xmin)/800;
}

// Renders a quad at cell (x, y) with dimensions CELL_LENGTH
void renderPixel(int x, int y, float r = 1.0, float g = 1.0, float b = 1.0)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

//Output function to OpenGL Buffer
void GL_render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	renderJuliaSet( -2.0, 2.0, -2.0, 2.0 );
	glutSwapBuffers();
}

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	
	glutCreateWindow("CS 130 - David Klein");
	glutDisplayFunc(GL_render);
	// The default view coordinates is (-1.0, -1.0) bottom left & (1.0, 1.0) top right.
	// For the purposes of this lab, this is set to the number of pixels
	// in each dimension.
	glMatrixMode(GL_PROJECTION_MATRIX);
	glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
}

int main(int argc, char** argv)
{	
	GLInit(&argc, argv);
	glutMainLoop();
	


	return 0;
}


