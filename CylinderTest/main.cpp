

#include <iostream>
#include <stdlib.h> //Needed for "exit" function

//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<math.h>

using namespace std;

//Called when a key is pressed
void handleKeypress(unsigned char key, //The key that was pressed
                    int x, int y)      //The current mouse coordinates
{
    switch (key)
    {
    case 27: //Escape key
        exit(0); //Exit the program
    }
}

//Initializes 3D rendering
void initRendering()
{
    //Makes 3D drawing work when something is in front of something else
    glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h)
{
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

static float PI = 3.14;
static float resolution = 0.01;
static float radius = 2.0;
static float height = 1.0;

void drawScene()
{
    //Clear information from last draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
    glLoadIdentity(); //Reset the drawing perspective
    /* top triangle */

    glTranslatef(0.0f, 0.0f, -8.0f);
    glRotatef(_angle, 0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, -45.0);  /* center */
    for (float i = 0; i <= 2*PI; i = i+resolution)
        glVertex3f(radius * cos(i), radius * sin(i), -25.0);
    glEnd();


/*
    //bottom triangle: note: for is in reverse order
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, 0);  //center
    for (int i = 2 * PI; i >= 0; i -= resolution)
        glVertex3f(radius * cos(i),radius * sin(i),-25.0);
    // close the loop back to 0 degrees
    glVertex3f(radius, height, 0);
    glEnd();

    //middle tube
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= 2 * PI; i += resolution)
    {
        //glVertex3f(radius * cos(i),radius * sin(i), -25.0 );
        //glVertex3f(radius * cos(i),radius * sin(i),-25.0);
    }
    //close the loop back to zero degrees
    glVertex3f(radius, 0, 0);
    glVertex3f(radius, height, 0);
    glEnd();
    */
    glutSwapBuffers(); //Send the 3D scene to the screen
}
int main(int argc, char** argv)
{
    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600); //Set the window size

    //Create the window
    glutCreateWindow("Basic Shapes");
    initRendering(); //Initialize rendering

    //Set handler functions for drawing, keypresses, and window resizes
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);

    glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
    return 0; //This line is never reached
}
