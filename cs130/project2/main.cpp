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
#include <stdlib.h>

#define PI 3.14159265

using std::string;
using std::cout;
using std::cin;
using std::endl;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

// Retrieve random float
float randFloat()
{
	return rand() / static_cast<float>(RAND_MAX);
}
float randFloat(float min, float max)
{
	return randFloat() * (max - min) + min;
}

// A simple wrapper for store 3D vectors
struct Vector3
{
	float x;
	float y;
	float z;

	Vector3() : x(0.0), y(0.0), z(0.0)
	{}

	Vector3(float x, float y, float z)
		: x(x), y(y), z(z)
	{}

	Vector3(const Vector3 & v)
		: x(v.x), y(v.y), z(v.z)
	{}

	Vector3 operator+(const Vector3 & rhs) const
	{ return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
	Vector3 operator-(const Vector3 & rhs) const
	{ return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
	Vector3 operator*(float rhs) const
	{ return Vector3(x * rhs, y * rhs, z * rhs); }
	Vector3 operator/(float rhs) const
	{ return Vector3(x / rhs, y / rhs, z / rhs); }
	Vector3 operator+=(const Vector3 & rhs)
	{ x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
	Vector3 operator-=(const Vector3 & rhs)
	{ x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
	Vector3 operator*=(float rhs)
	{ x *= rhs; y *= rhs; z *= rhs; return *this; }
	Vector3 operator/=(float rhs)
	{ x /= rhs; y /= rhs; z /= rhs; return *this; }

	float magnitude() const
	{ return sqrt(x * x + y * y + z * z); }
	void normalize()
	{ *this /= magnitude(); }
	Vector3 normalized() const
	{ return *this / magnitude(); }
	float dot(const Vector3 & rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}
	Vector3 cross(const Vector3 & rhs) const
	{
		return Vector3(y * rhs.z - z * rhs.y,
			z * rhs.x - x * rhs.z,
			x * rhs.y - y * rhs.x);
	}
};

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
	double t;
	double color_r;
	double color_g;
	double color_b;

	S_FACE() : a(0), b(0), c(0) {}
	S_FACE(const int & na, const int & nb, const int & nc) : a(na), b(nb), c(nc) {}
};

struct RAY	// ray struct to store a ray
{
	S_POINT pos;
	S_POINT dir;

	RAY() : pos(0.0, 0.0, 0.0), dir(0.0, 0.0, 0.0) {}
	RAY(const S_POINT & ipos, const S_POINT & idir) : pos(ipos), dir(idir) {}
};

int NUM_POINTS = 0;
int NUM_FACES = 0;
std::vector<S_POINT> POINTS;
std::vector<S_FACE> FACES;

void GLMouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		cout << "x: " << x << " y: " << y << endl;
}

S_POINT Ray( double & t, S_POINT & Ro, S_POINT & Rd )
{
	if( t >= 0 )
	{
		S_POINT result;

		result.x = Ro.x + Rd.x*t;
		result.y = Ro.y + Rd.y*t;
		result.z = Ro.z + Rd.z*t;

		return result;
	}
}

double Intersection( S_POINT & Ro, S_POINT & Rd, S_POINT & Pa, S_POINT & Pb , S_POINT & Pc )
{
	double detT = 0.0;
	double detC = 0.0;
	double detB = 0.0;
	double detA = 0.0;
	double t = 0.0;
	double r = 0.0;
	double s = 0.0;
		
	S_POINT Eb;
	S_POINT Ec;
	
	Eb.x = Pb.x - Pa.x;
	Eb.y = Pb.y - Pa.y;
	Eb.z = Pb.z - Pa.z;

	Ec.x = Pc.x - Pa.x;
	Ec.y = Pc.y - Pa.y;
	Ec.z = Pc.z - Pa.z;

	detT = (-Eb.x)*((-Ec.y)*(Pa.z-Ro.z)-(Pa.y-Ro.y)*(-Ec.z)) + Ec.x*((-Eb.y)*(Pa.z-Ro.z)-(Pa.y-Ro.y)*(Eb.z)) + (Pa.x-Ro.x)*((-Eb.y)*(-Ec.z)-(-Ec.y)*(-Eb.z));

	detC = (-Eb.x)*((Pa.y-Ro.y)*(Rd.z)-(Rd.y)*(Pa.z-Ro.z)) - (Pa.x-Ro.x)*((-Eb.y)*(Rd.z)-(Rd.y)*(-Eb.z)) + (Rd.x)*((-Eb.y)*(Pa.z-Ro.z)-(Pa.y-Ro.y)*(-Eb.z));

	detB = (Pa.x-Ro.x)*((-Ec.y)*(Rd.z)-(Rd.y)*(-Ec.z)) + (Ec.x)*((Pa.y-Ro.y)*(Rd.z)-(Rd.y)*(Pa.z-Ro.z)) + (Rd.x)*((Pa.y-Ro.y)*(-Ec.z)+(Ec.y)*(Pa.z-Ro.z));

	detA = (-Eb.x)*((-Ec.y)*(Rd.z)-(Rd.y)*(-Ec.z)) + (Ec.x)*((-Eb.y)*(Rd.z)-(Rd.y)*(-Eb.z)) + (Rd.x)*((-Eb.y)*(-Ec.z)-(Ec.y)*(-Eb.z));

	t = detT/detA;
	r = detB/detA;
	s = detC/detA;

	//cout << r << endl;
	//cout << s << endl;

	if( r >= 0 && r <= 1 )
	{
		if( s >= 0 && s <= 1 )
		{
			if( r + s <= 1 )
				return t;
			else return -1;
		}
		else return -1;
	}
	else return -1;
}

// Renders a quad at cell (x, y) with dimensions CELL_LENGTH
void renderPixel(int x, int y, float r = 1.0, float g = 1.0, float b = 1.0)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

int MODE[256];

double Phong( S_FACE & face, S_POINT & Po )
{
	int alpha = 200;	// shinyness coefficient

	double La = 0.2;	// ambient light
	double Ld = 1.0;	//
	double Ks = 1;		//
	double Ls = 1;		//

	Vector3 vsource;	// viewer vector
	vsource.x = 0;
	vsource.y = 0;
	vsource.z = -1;

	Vector3 vlight;
	vlight.x = 800 - Po.x;
	vlight.y = 800 - Po.y;
	vlight.z = 0 - Po.z;

	//cout << vlight.x << " " << vlight.y << " " << vlight.z << endl;

	vlight.normalize();		// normalize vlight

	S_POINT Pa = POINTS[face.a];
	S_POINT Pb = POINTS[face.b];
	S_POINT Pc = POINTS[face.c];

	Vector3 v1, v2;

	v1.x = Pc.x - Pa.x;
	v1.y = Pc.y - Pa.y;
	v1.z = Pc.z - Pa.z;
	v2.x = Pb.x - Pa.x;
	v2.y = Pb.y - Pa.y;
	v2.z = Pb.z - Pa.z;
	v1.normalize();		// normalize v1
	v2.normalize();		// normalize v2

	Vector3 vnormal = v1.cross(v2);
	//vnormal.normalize();		// normalize vnormal
	//cout << vnormal.x << " " << vnormal.y << " " << vnormal.z << endl;

	// find centroid mesh
	double u, v, w;
	for( int i = 0; i < NUM_POINTS; i++ )
	{
		u += POINTS[i].x;
		v += POINTS[i].y;
		w += POINTS[i].z;
	}
	u = u / NUM_POINTS;
	v = v / NUM_POINTS;
	w = w / NUM_POINTS;

	Vector3 vcentroid;
	vcentroid.x = Po.x - u;
	vcentroid.y = Po.y - v;
	vcentroid.z = Po.z - w;
	vcentroid.normalize();		// normalize vcentroid

	if( vcentroid.dot(vnormal) < 0 )
		vnormal = vnormal * -1;
	
	return La+Ld*(vnormal.dot(vlight));
}

void DrawColors( S_POINT & Rd )
{
	S_POINT Ro;
	S_POINT Tri;
	S_POINT Po;
	int a;
	int b;
	int c;
	Ro.z = 0;
	double t;
	S_FACE tmin;

	double phong;

	tmin.t = 999;
	tmin.color_r = 0;
	tmin.color_g = 0;
	tmin.color_b = 0;

	for( int i = 0; i < FACES.size(); i++ )
	{
			FACES[i].color_r = 1;
			FACES[i].color_g = 1;
			FACES[i].color_b = 1;
	}

	MODE['i'] = 0;

	for(int i = 0; i < 800; i++ )
	{
		for( int j = 0; j < 800; j++ )
		{
			//cout << "i: " << i << " j: " << j << endl;
			Ro.x = i;
			Ro.y = j;
			for( int k = 0;	k < NUM_FACES; k++ )
			{
				a = FACES[k].a;
				b = FACES[k].b;
				c = FACES[k].c;
				FACES[k].t = Intersection( Ro, Rd, POINTS[a], POINTS[b], POINTS[c] );
				if( FACES[k].t > 0 && FACES[k].t < tmin.t)
				{
					Po = Ray(t, Ro, Rd);
					phong = Phong(FACES[k], Po);
					tmin.t  = FACES[k].t;
					tmin.color_r = FACES[k].color_r * phong;
					tmin.color_g = FACES[k].color_g * phong;
					tmin.color_b = FACES[k].color_b * phong;
					glColor3f(tmin.color_r,tmin.color_g,tmin.color_b);
					//if( tmin.color_r < 0 || tmin.color_g < 0 || tmin.color_b < 0 )
					//cout << tmin.color_r << " " << tmin.color_g << " " << tmin.color_b << endl;
					renderPixel( i, j );
				}
			}

			tmin.t = 999;
			tmin.color_r = 0;
			tmin.color_g = 0;
			tmin.color_b = 0;
		}
	}
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
	}
}

// draw the front of the triangle
void Draw_Front( S_FACE & face ) 
{
	DDA( POINTS[face.a].x, POINTS[face.a].y, POINTS[face.b].x, POINTS[face.b].y );
	DDA( POINTS[face.b].x, POINTS[face.b].y, POINTS[face.c].x, POINTS[face.c].y );
	DDA( POINTS[face.c].x, POINTS[face.c].y, POINTS[face.a].x, POINTS[face.a].y );
	
}

// draw the side of the triangle
void Draw_Side( S_FACE & face ) 
{
	DDA( POINTS[face.a].z, POINTS[face.a].y, POINTS[face.b].z, POINTS[face.b].y );
	DDA( POINTS[face.b].z, POINTS[face.b].y, POINTS[face.c].z, POINTS[face.c].y );
	DDA( POINTS[face.c].z, POINTS[face.c].y, POINTS[face.a].z, POINTS[face.a].y );
	//Subdivision(POINTS[face.a], POINTS[face.b], POINTS[face.c], 2, 1);
}

// draw the top of the triangle
void Draw_Top( S_FACE & face ) 
{
	DDA( POINTS[face.a].x, POINTS[face.a].z, POINTS[face.b].x, POINTS[face.b].z );
	DDA( POINTS[face.b].x, POINTS[face.b].z, POINTS[face.c].x, POINTS[face.c].z );
	DDA( POINTS[face.c].x, POINTS[face.c].z, POINTS[face.a].x, POINTS[face.a].z );
	//Subdivision(POINTS[face.a], POINTS[face.b], POINTS[face.c], 2, 2);
}

void DrawFaces(int n)
{
	for( int i = 0;	i < NUM_FACES; i++ )
	{
		Draw_Front( FACES[i] );	// replace function with what want to draw
		Subdivision(POINTS[FACES[i].a], POINTS[FACES[i].b], POINTS[FACES[i].c], n, 0);
	}
}

int SUBD;
int CALLCOLOR = 0;

//Output function to OpenGL Buffer
void GL_render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	DrawFaces(SUBD);

	S_POINT Rd;
	Rd.x = 0;
	Rd.y = 0;
	Rd.z = 1;

	if( CALLCOLOR == 1 )
	{
		DrawColors(Rd);
	}

	glutSwapBuffers();
}

void Translate ()
{

}

void Rotate( )
{

}

void GLKeyboardInput(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'r':
			MODE[key] = 1;
			MODE['t'] = 0;
			MODE['l'] = 0;
			MODE['i'] = 0;
		case 't':
			MODE['r'] = 0;
			MODE[key] = 1;
			MODE['l'] = 0;
			MODE['i'] = 0;
		case 'l':
			MODE['r'] = 0;
			MODE['t'] = 0;
			MODE[key] = 1;
			MODE['i'] = 0;
		case 'i':
			MODE['r'] = 0;
			MODE['t'] = 0;
			MODE['l'] = 0;
			MODE[key] = 1;
			if( key == 'i' )
			{
				CALLCOLOR = 1;
				GL_render();
			}
		case 'a':
			if( MODE['r'] == 1 && key == 'a' ) // rotate left
			{
				//cout << "Rotation MODE - Rotate Left" << endl;
				double u = 0;
				double v = 0;

				for( int i = 0; i < NUM_POINTS; i++ )
				{
					u += POINTS[i].x;
					v += POINTS[i].y;
				}

				u = u / NUM_POINTS;
				v = v / NUM_POINTS;

				for( int i = 0; i < NUM_POINTS; i++ )
				{
					POINTS[i].x = u + (POINTS[i].x-u)*cos(-1*PI/180) + (POINTS[i].y-v)*sin(-1*PI/180);
					POINTS[i].y = v + (POINTS[i].y-v)*cos(-1*PI/180) - (POINTS[i].x-u)*sin(-1*PI/180);
				}

				GL_render();
			}
			if( MODE['t'] == 1 && key == 'a'  ) // translate left
			{
				//cout << "Translation MODE - Translate Left" << endl;
				for( int i = 0; i <  POINTS.size(); i++ )
				{
					POINTS[i].x += -1;
				}
				GL_render();
			}
		case 's':
			if( MODE['r'] == 1 && key == 's'  ) // rotate down
			{
				//cout << "Rotation MODE - Rotate Down" << endl;
				double u = 0;
				double v = 0;

				for( int i = 0; i < NUM_POINTS; i++ )
				{
					u += POINTS[i].z;
					v += POINTS[i].y;
				}

				u = u / NUM_POINTS;
				v = v / NUM_POINTS;

				for( int i = 0; i < NUM_POINTS; i++ )
				{
					POINTS[i].z = u + (POINTS[i].z-u)*cos(1*PI/180) + (POINTS[i].y-v)*sin(1*PI/180);
					POINTS[i].y = v + (POINTS[i].y-v)*cos(1*PI/180) - (POINTS[i].z-u)*sin(1*PI/180);
				}

				GL_render();
			}
			if( MODE['t'] == 1 && key == 's'  ) // translate down
			{
				//cout << "Trasnlation MODE - Translate Down" << endl;
				for( int i = 0; i <  POINTS.size(); i++ )
				{
					POINTS[i].y += -1;
				}
				GL_render();
			}
		case 'd':
			if( MODE['r'] == 1 && key == 'd'  ) // rotate right
			{
				//cout << "Rotation MODE - Rotate Right" << endl;
				double u = 0;
				double v = 0;

				for( int i = 0; i < NUM_POINTS; i++ )
				{
					u += POINTS[i].x;
					v += POINTS[i].y;
				}

				u = u / NUM_POINTS;
				v = v / NUM_POINTS;

				for( int i = 0; i < NUM_POINTS; i++ )
				{
					POINTS[i].x = u + (POINTS[i].x-u)*cos(1*PI/180) + (POINTS[i].y-v)*sin(1*PI/180);
					POINTS[i].y = v + (POINTS[i].y-v)*cos(1*PI/180) - (POINTS[i].x-u)*sin(1*PI/180);
				}

				GL_render();
			}
			if( MODE['t'] == 1 && key == 'd'  ) // translate right
			{
				//cout << "Translation MODE - Translate Right" << endl;	
				for( int i = 0; i <  POINTS.size(); i++ )
				{
					POINTS[i].x += 1;
				}
				GL_render();
			}
		case 'w':
			if( MODE['r'] == 1 && key == 'w'  ) // rotate up
			{
				//cout << "Rotation MODE - Rotate Up" << endl;
				double u = 0;
				double v = 0;

				for( int i = 0; i < NUM_POINTS; i++ )
				{
					u += POINTS[i].z;
					v += POINTS[i].y;
				}

				u = u / NUM_POINTS;
				v = v / NUM_POINTS;

				for( int i = 0; i < NUM_POINTS; i++ )
				{
					POINTS[i].z = u + (POINTS[i].z-u)*cos(-1*PI/180) + (POINTS[i].y-v)*sin(-1*PI/180);
					POINTS[i].y = v + (POINTS[i].y-v)*cos(-1*PI/180) - (POINTS[i].z-u)*sin(-1*PI/180);
				}

				GL_render();
			}
			if( MODE['t'] == 1 && key == 'w'  ) // translate up
			{
				//cout << "Translation MODE - Translate Up" << endl;
				for( int i = 0; i <  POINTS.size(); i++ )
				{
					POINTS[i].y += 1;
				}
				GL_render();
			}
		case '1':
			if( MODE['l'] == 1 and key == '1')
			{
				cout << "Subdivide by: " << int(key)-48 << endl;
				SUBD = 1;
				GL_render();
			}
		case '2':
			if( MODE['l'] == 1 and key == '2')
			{
				cout << "Subdivide by: " << int(key)-48 << endl;
				SUBD = 2;
				GL_render();
			}
		case '3':
			if( MODE['l'] == 1 and key == '3')
			{
				cout << "Subdivide by: " << int(key)-48 << endl;
				SUBD = 3;
				GL_render();
			}
		case '4':
			if( MODE['l'] == 1 and key == '4')
			{
				cout << "Subdivide by: " << int(key)-48 << endl;
				SUBD = 4;
				GL_render();
			}
	};
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
	glutKeyboardFunc(GLKeyboardInput);
	glutMouseFunc(GLMouseInput);
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


