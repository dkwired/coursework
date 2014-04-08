// Name: David Klein
// Quarter, Year: Fall 2013
// Lab: 021
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
// FRONT VIEW - Drop z axis
// SIDE VIEW - Drop x axis
// TOP VIEW - Drop y axis

#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <vector>

using std::string;
using std::cout;
using std::cin;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

struct S_POINT	// point struct to store points of each side
{
	double x;
	double y;
	double z;
	
	S_POINT() : x(0.0), y(0.0), z(0.0) {}
	S_POINT(const double & nx, const double & ny, const double & nz) : x(nx), y(ny), z(nz) {}
};

struct S_FACE	// face struct to store sides of each triangle
{
	int a;
	int b;
	int c;

	S_FACE() : a(0), b(0), c(0) {}
	S_FACE(const double & na, const double & nb, const double & nc) : a(na), b(nb), c(nc) {}
};

int NUM_POINTS = 0;
int NUM_FACES = 0;
std::vector<S_POINT> POINTS;
std::vector<S_FACE> FACES;



// Renders a quad at cell (x, y) with dimensions CELL_LENGTH
void renderPixel(int x, int y, float r = 1.0, float g = 1.0, float b = 1.0)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void DDA(int x0, int y0, int x1, int y1 )
{
	int dy = y1 - y0;
	int dx = x1 - x0;
	int m;

	float xinc;
	float yinc;
	float x = x0;
	float y = y0;
	if( abs(dx) > abs(dy) )
	{
		m = abs(dx);
	}
	else
	{
		m = abs(dy);
	}
	xinc=(float) dx / (float) m;
	yinc = (float) dy / (float) m;
	renderPixel( round(x), round(y) );
	for( int i = 0; i < m; i++ )
	{
		x += xinc;
		y += yinc;
		renderPixel( round(x), round(y) );
	}
}

// draw n subdivisions
int Subdivision( S_POINT & p1, S_POINT & p2, S_POINT & p3, int i, int n )
{
	if( i == 0 ) return 0;
	else
	{
		S_POINT mp1;			// create temporary points
		S_POINT mp2;
		S_POINT mp3;

		mp1.x = (p1.x + p2.x)/2;	// calculate midpoints for all sides
		mp1.y = (p1.y + p2.y)/2;
		mp1.z = (p1.z + p2.z)/2;

		mp2.x = (p2.x + p3.x)/2;
		mp2.y = (p2.y + p3.y)/2;
		mp2.z = (p2.z + p3.z)/2;

		mp3.x = (p3.x + p1.x)/2;
		mp3.y = (p3.y + p1.y)/2;
		mp3.z = (p3.z + p1.z)/2;

		if( n == 0 )			// if we are drawing the front
		{
			DDA( mp1.x, mp1.y, mp2.x, mp2.y );
			DDA( mp2.x, mp2.y, mp3.x, mp3.y );
			DDA( mp3.x, mp3.y, mp1.x, mp1.y );
		}
		if( n == 1 )			// if we are drawing the side
		{
			DDA( mp1.z, mp1.y, mp2.z, mp2.y );
			DDA( mp2.z, mp2.y, mp3.z, mp3.y );
			DDA( mp3.z, mp3.y, mp1.z, mp1.y );
		}
		if( n == 2 )			// if we are drawing the top
		{
			DDA( mp1.x, mp1.z, mp2.x, mp2.z );
			DDA( mp2.x, mp2.z, mp3.x, mp3.z );
			DDA( mp3.x, mp3.z, mp1.x, mp1.z );
		}

		Subdivision(mp1, mp2, mp3, i-1, n);	// recurse on left over triangles
		Subdivision(p1, mp1, mp3, i-1, n);
		Subdivision(mp1, p2, mp2, i-1, n);
		Subdivision(p3, mp3, mp2, i-1, n);
		//Subdivision(p3, mp3, mp2, i-1, n);
	}
}

// draw the front of the triangle
void Draw_Front( S_FACE & face ) 
{
	DDA( POINTS[face.a].x, POINTS[face.a].y, POINTS[face.b].x, POINTS[face.b].y );
	DDA( POINTS[face.b].x, POINTS[face.b].y, POINTS[face.c].x, POINTS[face.c].y );
	DDA( POINTS[face.c].x, POINTS[face.c].y, POINTS[face.a].x, POINTS[face.a].y );
	Subdivision(POINTS[face.a], POINTS[face.b], POINTS[face.c], 2, 0);
}

// draw the side of the triangle
void Draw_Side( S_FACE & face ) 
{
	DDA( POINTS[face.a].z, POINTS[face.a].y, POINTS[face.b].z, POINTS[face.b].y );
	DDA( POINTS[face.b].z, POINTS[face.b].y, POINTS[face.c].z, POINTS[face.c].y );
	DDA( POINTS[face.c].z, POINTS[face.c].y, POINTS[face.a].z, POINTS[face.a].y );
	Subdivision(POINTS[face.a], POINTS[face.b], POINTS[face.c], 2, 1);
}

// draw the top of the triangle
void Draw_Top( S_FACE & face ) 
{
	DDA( POINTS[face.a].x, POINTS[face.a].z, POINTS[face.b].x, POINTS[face.b].z );
	DDA( POINTS[face.b].x, POINTS[face.b].z, POINTS[face.c].x, POINTS[face.c].z );
	DDA( POINTS[face.c].x, POINTS[face.c].z, POINTS[face.a].x, POINTS[face.a].z );
	Subdivision(POINTS[face.a], POINTS[face.b], POINTS[face.c], 2, 2);
}

//Output function to OpenGL Buffer
void GL_render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for( int i = 0;	i < NUM_FACES; i++ )
	{
		Draw_Top( FACES[i] );		// replace function with what want to draw
	}
	glutSwapBuffers();
}



//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{struct Point3D
{
	double x;
	double y;
	double z;
	
	Point3D() : x(0.0), y(0.0), z(0.0) {}
	Point3D(const double & nx, const double & ny, const double & nz) : x(nx), y(ny), z(nz) {}
};
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// ...
	// Complete this function
	// ...
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
	string lineInput;	// input file

	// get the number of points
	cin >> lineInput;
	NUM_POINTS = atoi( lineInput.c_str() );
	// get the number of faces
	cin >> lineInput;
	NUM_FACES = atoi( lineInput.c_str() );
	// get the list of points

	int count = 0;				// counter for input
	S_POINT temp_point;			// temp point for each loop
	while (count < NUM_POINTS) 
	{
		cin >> lineInput;
		temp_point.x = 8 * atoi(lineInput.c_str());	// multiply by 8 to scale up
		cin >> lineInput;
		temp_point.y = 8 * atoi(lineInput.c_str());	// multiply by 8 to scale up
		cin >> lineInput;
		temp_point.z = 8 * atoi(lineInput.c_str());	// multiply by 8 to scale up
		POINTS.push_back(temp_point);
		count++;
	}

	count = 0;				// reset counter for input
	S_FACE temp_face;			// temp face for each loop
	while (count < NUM_FACES) 
	{
		cin >> lineInput;
		temp_face.a = atoi(lineInput.c_str());
		cin >> lineInput;
		temp_face.b = atoi(lineInput.c_str());
		cin >> lineInput;
		temp_face.c = atoi(lineInput.c_str());
		FACES.push_back(temp_face);
		count++;
	}

	GLInit(&argc, argv);
	glutMainLoop();

	return 0;
}


