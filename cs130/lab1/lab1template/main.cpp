// Name: 
// Quarter, Year: 
// Lab:
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#include <GL/glut.h>
#include <math.h>

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
	int dy = y1 - y0;
	int dx = x1 - x0;
	int steps, i;

	float xinc, yinc, x = x0, y = y0;
	if( abs(dx) > abs(dy) )
	{
		steps = abs(dx);
	}
	else
	{
		steps = abs(dy);
	}
	xinc=(float) dx / (float) steps;
	yinc = (float) dy / (float) steps;
	renderPixel( round(x), round(y) );
	for( i = 0; i < steps; i++ )
	{
		x += xinc;
		y += yinc;
		renderPixel( round(x), round(y) );
	}
}

void MPA(int x0, int y0, int r )
{
  int x = r, y = 0;
  int radiusError = 1-x;
 
  while(x >= y)
  {
	renderPixel(x + x0, y + y0);
	renderPixel(y + x0, x + y0);
	renderPixel(-x + x0, y + y0);
	renderPixel(-y + x0, x + y0);
	renderPixel(-x + x0, -y + y0);
	renderPixel(-y + x0, -x + y0);
	renderPixel(x + x0, -y + y0);
	renderPixel(y + x0, -x + y0);
 
	y++;
        if(radiusError<0)
		radiusError+=2*y+1;
        else
        {
                x--;
                radiusError+=2*(y-x+1);
        }
  }
}

//Output function to OpenGL Buffer
void GL_render()
{
	glClear(GL_COLOR_BUFFER_BIT);
//	DDA( 10, 10, 500, 500 );
//	DDA( 10, 10, 300, 20 );
//	DDA( 10, 10, 20, 300 );
	MPA( 400, 400, 100 );
	MPA( 400, 400, 110 );
	MPA( 400, 400, 120 );	
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


