#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<math.h>
#include <math.h>
#define PI 3.1415927
int flag=1;
int angleRF=0;
int angleLF=0;
float _angle = -70.0f;
float zAxis = -6;

using namespace std;

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'p': //Escape key

        if(flag==0)
        {
            flag=1;
        }
        else flag = 0;
    case 'a': //LeftArrow
        angleLF=1;
    //angleRF=0;
    case 'd': //RightArrow
        //angleLF=0;
        angleRF=1;
    }
}
//Initializes 3D rendering
void initRendering()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    //glEnable(GL_LIGHTING); //Enable lighting
    //glEnable(GL_LIGHT0); //Enable light #0
    //glEnable(GL_LIGHT1); //Enable light #1
    //glEnable(GL_LIGHT2); //Enable light #1
    glEnable(GL_NORMALIZE); //Automatically normalize normals
    //glShadeModel(GL_SMOOTH); //Enable smooth shading
}

//Called when the window is resized
void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void drawHalfSphere(int scaley, int scalex, GLfloat r) {
   int i, j;
   GLfloat v[scalex*scaley][3];

   for (i=0; i<scalex; ++i) {
     for (j=0; j<scaley; ++j) {
       v[i*scaley+j][0]=r*cos(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
       v[i*scaley+j][1]=r*sin(i*M_PI/(2*scalex));
       v[i*scaley+j][2]=r*sin(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
     }
   }

   glBegin(GL_QUADS);
     for (i=0; i<scalex-1; ++i) {
       for (j=0; j<scaley; ++j) {
         glVertex3fv(v[i*scaley+j]);
         glVertex3fv(v[i*scaley+(j+1)%scaley]);
         glVertex3fv(v[(i+1)*scaley+(j+1)%scaley]);
         glVertex3fv(v[(i+1)*scaley+j]);
       }
     }
   glEnd();
 }

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0,-0.5,-3.0);

    glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
    drawHalfSphere(50, 50, 0.3);

    glutSwapBuffers();
}

void update(int value)
{
    if (_angle > 360)
    {
        _angle -= 360;
    }
    else if (_angle < -360)
    {
        _angle += 360;
    }
    if(angleLF==1)
    {
        _angle =_angle-1.5f;
        angleRF=0;
        angleLF=0;
    }
    else if(angleRF==1)
    {
        _angle =_angle+1.5f;
        angleRF=0;
        angleLF=0;
    }

    zAxis +=0.35;
    if(zAxis>=6)
    {
        zAxis=-6;
    }

    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv)
{
    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 650);

    //Create the window
    glutCreateWindow("Shat Gambuj Masque");
    initRendering();

    //Set handler functions
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);

    glutTimerFunc(25, update, 0); //Add a timer

    glutMainLoop();
    return 0;
}
