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
float _angle = 90.0f;
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
    glEnable(GL_LIGHTING); //Enable lighting
    glEnable(GL_LIGHT0); //Enable light #0
    glEnable(GL_LIGHT1); //Enable light #1
    glEnable(GL_LIGHT2); //Enable light #1
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

void drawHalfSphere(int scaley, int scalex, GLfloat r)
{
    int i, j;
    GLfloat v[scalex*scaley][3];

    for (i=0; i<scalex; ++i)
    {
        for (j=0; j<scaley; ++j)
        {
            v[i*scaley+j][0]=r*cos(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
            v[i*scaley+j][1]=r*sin(i*M_PI/(2*scalex));
            v[i*scaley+j][2]=r*sin(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
        }
    }

    glBegin(GL_QUADS);
    for (i=0; i<scalex-1; ++i)
    {
        for (j=0; j<scaley; ++j)
        {
            glVertex3fv(v[i*scaley+j]);
            glVertex3fv(v[i*scaley+(j+1)%scaley]);
            glVertex3fv(v[(i+1)*scaley+(j+1)%scaley]);
            glVertex3fv(v[(i+1)*scaley+j]);
        }
    }
    glEnd();
}


static float resolution = 0.01;
static float radius = 2.0;
static float height = 5.0;
//Draws the 3D scene
void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -8.0f);

    //Add ambient light
    GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    //Add positioned light
    GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    //Add directed light
    GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
    //Coming from the direction (-1, 0.5, 0.5)
    GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);


    GLfloat lightColor2[] = {0.1f, 0.8f, 0.1f, 1.0f}; //Color (0.5, 0.2, 0.2)
    //Coming from the direction (-1, 0.5, 0.5)
    GLfloat lightPos2[] = {-1.0f, 0.5f, zAxis, 0.0f};
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);


    glRotatef(_angle, 1.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);

    //middle dom
    glTranslatef(0.0f, 1.2f, 0.0f);
    drawHalfSphere(50, 50, 0.5);
    glTranslatef(0.0f, -1.2f, 0.0f);

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
