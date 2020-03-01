

#include "litscene.h"
#include "simplecamera.h"

using namespace std;

LitScene         TheScene;
SimpleCamera     TheCamera(250, 250);
int              Nx, Ny; // resolution

static const int DEPTH = 4; // maximum recursion depth

void set_pixel(int x, int y, Colour col)
{
    glBegin(GL_POINTS);
        glColor3f(col.red(), col.green(), col.blue());
        glVertex2i(x, y);
    glEnd();
}

void display(void)
{
    int i, j;
    Colour col;

    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    for(i = 0; i < Nx; i++)
    for(j = 0; j < Ny; j++) {
            Ray ray = TheCamera.ray(i,j);
            if (TheScene.intersect(NULL, ray, DEPTH, col))
            {
                set_pixel(i,j,col); 
            }
    }

    glFlush();
}

void reshape_window(int width, int height)
{
    Nx = width;
    Ny = height;
    TheCamera.setResolution(Nx, Ny);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluOrtho2D(0.0,(double)Nx-1,0.0,(double)Ny-1);
	glViewport(0,0,Nx,Ny);
}

void create_window(void)
{
	Nx = TheCamera.xResolution();
	Ny = TheCamera.yResolution();
	  
	glutInitWindowSize(Nx, Ny);
	glutCreateWindow("simple graphics");

	glutDisplayFunc(display);

    glutReshapeFunc(reshape_window);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluOrtho2D(0.0,(double)Nx-1,0.0,(double)Ny-1);
	glViewport(0,0,Nx,Ny);
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	TheCamera.setResolution(250,250);
	TheCamera.setVPWindow(-2.0,2.0,-2.0,2.0);
	TheCamera.zcop() = 2.0;
		
	const char* fileName;

	if (argc < 2) {
		fileName = "../scenes/complexscene.dat";
		//fileName = "simplescene.dat";
	} else {
		fileName = argv[1];
	}		

	ifstream sceneFile;
	sceneFile.open(fileName);
	if (!sceneFile.is_open()) {
		cout << "Couldn't open file " << fileName << "!" << endl;
	}
	
	sceneFile >> TheScene;

	sceneFile.close();
	
	cout << TheScene << "\n";

	create_window();

	glutMainLoop();
}
