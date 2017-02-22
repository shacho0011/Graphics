#include <iostream>
#include <stdlib.h> //Needed for "exit" function

//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <math.h>
#endif

using namespace std;
float  angle1 = 360.0f;

//Called when a key is pressed
void handleKeypress(unsigned char key, //The key that was pressed
					int x, int y) {    //The current mouse coordinates
	switch (key) {
		case 27: //Escape key
			exit(0); //Exit the program
	}
}

//Initializes 3D rendering
void initRendering() {
	//Makes 3D drawing work when something is in front of something else
	glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h) {
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective

	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(45.0,                  //The camera angle
				   (double)w / (double)h, //The width-to-height ratio
				   1.0,                   //The near z clipping coordinate
				   200.0);                //The far z clipping coordinate
}

//Draws the 3D scene
float _angle = 0.0f;
void drawScene() {
	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

	 //Begin quadrilateral GL_TRIANGLES


glTranslatef(0.0f, 0.0f, -9.0f);
glRotatef(65.0f, 0.0f, 1.0f, 0.0f);

 glBegin(GL_QUADS); //Begin quadrilateral coordinates

    glColor3f (0.647, 0.165, 0.165);


	glVertex3f(-0.8f, -1.8f, -5.0f);
	glVertex3f(-0.5f, -1.8f, -5.0f);
	glVertex3f(-0.5f,  0.0f, -5.0f);
	glVertex3f(-0.8f,  0.0f, -5.0f);

    glVertex3f( 0.8f, -1.8f, -5.0f);
	glVertex3f( 0.5f, -1.8f, -5.0f);
	glVertex3f( 0.5f,  0.0f, -5.0f);
	glVertex3f( 0.8f,  0.0f, -5.0f);

    glVertex3f(-0.5f, -1.8f, -5.0f);
	glVertex3f( 0.5f, -1.8f, -5.0f);
	glVertex3f( 0.5f, -1.8f, -6.0f);
    glVertex3f(-0.5f, -1.8f, -6.0f);




    glColor3f(1.0,1.0,1.0);

    glVertex3f(-0.5f, -1.8f, -5.0f);
    glVertex3f(-0.3f, -1.8f, -6.0f);
	glVertex3f(-0.3f,  0.0f, -6.0f);
	glVertex3f(-0.5f,  0.0f, -5.0f);

    glVertex3f( 0.5f, -1.8f, -5.0f);
    glVertex3f( 0.3f, -1.8f, -6.0f);
	glVertex3f( 0.3f,  0.0f, -6.0f);
	glVertex3f( 0.5f,  0.0f, -5.0f);

	glColor3f(0.804, 0.361, 0.361);

	glVertex3f( -0.8f, -1.8f, -4.5f);
	glVertex3f( -1.2f, -1.8f, -4.5f);
	glVertex3f( -1.2f,  1.4f, -4.5f);
	glVertex3f( -0.8f,  1.4f, -4.5f);

    glVertex3f( 0.8f, -1.8f, -4.5f);
	glVertex3f( 1.2f, -1.8f, -4.5f);
	glVertex3f( 1.2f,  1.4f, -4.5f);
	glVertex3f( 0.8f,  1.4f, -4.5f);

    glVertex3f( -1.2f,    1.4f, -4.5f);
	glVertex3f(  1.2f,    1.4f, -4.5f);
	glVertex3f(  1.2f,    1.8f, -4.5f);
	glVertex3f( -1.2f,    1.8f, -4.5f);

	glColor3f(0.502,0.0,0.0);
	glNormal3f(1.0f,0.0f,0.0f);

	glVertex3f( -0.8f, -1.8f, -5.0f);
	glVertex3f( -0.8f,  1.4f, -5.0f);
	glVertex3f( -0.8f,  1.4f, -4.5f);
	glVertex3f( -0.8f, -1.8f, -4.5f);

    glVertex3f( 0.8f, -1.8f, -5.0f);
	glVertex3f( 0.8f,  1.4f, -5.0f);
	glVertex3f( 0.8f,  1.4f, -4.5f);
	glVertex3f( 0.8f, -1.8f, -4.5f);

    glVertex3f( -0.8f,  1.4f, -5.0f);
    glVertex3f(  0.8f,  1.4f, -5.0f);
	glVertex3f(  0.8f,  1.4f, -4.5f);
	glVertex3f( -0.8f,  1.4f, -4.5f);






	glEnd();

	glBegin(GL_LINE_LOOP);

    for(int i=0; i<1000;i++){

    if(i<500){

    glColor3f (0.647, 0.165, 0.165); //upper red circle of the door
    glVertex3f(0.5*cos((2*3.14159*i)/1000.0), 0.5*sin((2*3.14159*i)/1000.0),-5.0f);
    glVertex3f(0.8*cos((2*3.14159*i)/1000.0), 0.8*sin((2*3.14159*i)/1000.0),-5.0f);


    glColor3f (1.0, 1.0, 1.0); //inner white circle of the door
    glVertex3f(0.3*cos((2*3.14159*i)/1000.0), 0.3*sin((2*3.14159*i)/1000.0),-6.0f);
    glVertex3f(0.5*cos((2*3.14159*i)/1000.0), 0.5*sin((2*3.14159*i)/1000.0),-5.0f);

    glColor3f (0.545, 0.5, 0.0);

    /*glVertex3f(0.8-(0.0032*i),  1.4f, -5.0f);
    glVertex3f(0.8*cos((2*3.14159*i)/1000), 0.8*sin((2*3.14159*i)/1000),-5.0f);*/


    }
    else continue;
    }

    glEnd();


  glutSwapBuffers();
}
void update(int value) {
	_angle += 1.5f;
	if (_angle > 360) {
		_angle -= 360;
	}

	glutPostRedisplay();
	glutTimerFunc(100, update, 0);
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500); //Set the window size

	//Create the window
	glutCreateWindow("SGM");
	initRendering(); //Initialize rendering

	//Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	//glutTimerFunc(100,update,0);

	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
	return 0; //This line is never reached
}









