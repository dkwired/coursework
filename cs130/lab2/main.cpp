// Name: 
// Quarter, Year: 
// Lab:
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#include <GL/glut.h>
#include <math.h>
#include "point2d.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

// Renders a quad at cell (x, y) with dimensions CELL_LENGTH
void renderPixel(int x, int y, float r = 1.0, float g = 1.0, float b = 1.0)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void DDA(int x1, int y1, int x2, int y2 )
{
	float x = x1;
	float y = y1;
	float m = 0;

	if( x1 != x2 )
	{
		m = (float)(y2 - y1)/(x2 - x1);
	}

	float start;
	float end;

	if( x1 == x2 )
	{
		if( y1 > y2 )	start = y2;
		else	start = y1;

		if( y2 > y1 )	end = y2;
		else	end = y1;

		while( start <= end )
		{
			renderPixel(x1, start);
			start++;
		}
	}
	else if( abs(m) <= 1 )
	{
		if( x1 > x2 )	start = x2;
		else	start = x1;

		if( x2 > x1 )	end = x2;
		else	end = x1;

		while( start <= end )
		{
			renderPixel(start, round(y));
			start = start++;
			y = y + m;
		}
	}
	else
	{
		if( y1 > y2 )	start = y2;
		else	start = y1;

		if( y2 > y1 )	end = y2;
		else	end = y1;
		double i = x2<x2?x1:x2;
		if( m > 0 )
		{
			i = x2<x2?x2:x1;
		}
		while( start <= end )
		{
			renderPixel(round(i), start);
			i = i + 1/m;
			start = start++;
		}
	}
}

Point2D POINTS[3];
int COUNT = 0;

void GLMouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && COUNT < 3) 
	{ 
		POINTS[COUNT].x = x;
		POINTS[COUNT].y = y;
		COUNT++;
		glutPostRedisplay();
	}
}

Point2D ComputeBezierCurve( Point2D POINTS[], float t )
{
	Point2D point = POINTS[0]*((1-t)*(1-t)) + POINTS[1]*t*(2*(1-t)) + POINTS[2]*(t*t);
	return point;
}

void RenderBezierCurve( )
{
	float t = 0;
	Point2D point1;
	Point2D point2;

	for( int i = 0; i <= 99; i = i++ )
	{
		point1 = ComputeBezierCurve( POINTS, t );
		t += 0.01;
		point2 = ComputeBezierCurve( POINTS, t );

		DDA( point1.x, point1.y, point2.x, point2.y );
	}
}

//Output function to OpenGL Buffer
void GL_render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	RenderBezierCurve();

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
	glutMouseFunc(GLMouseInput);
	// The default view coordinates is (-1.0, -1.0) bottom left & (1.0, 1.0) top right.
	// For the purposes of this lab, this is set to the number of pixels
	// in each dimension.
	glMatrixMode(GL_PROJECTION_MATRIX);
	glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1);
}

int main(int argc, char** argv)
{	
	GLInit(&argc, argv);
	glutMainLoop();

	return 0;
}


