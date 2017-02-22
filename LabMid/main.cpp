#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int flag=0;

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
        else if(flag==1)
        {
            flag = 0;
        }

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

float _angle = -70.0f;

float zAxis = -6;
float x1 = -2.5f;
float x2 = -2.0f;
int lrF = 0;
float r=1.0f;
float g=1.0f;
float b=1.0f;
int red=1;
int green=0;
int blue=0;
int black=0;
//Draws the 3D scene
void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -8.0f);

    //Add ambient light
    GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);






    if(flag==0)
    {
        GLfloat lightPos0[] = {x1+0.25f, -1.75f, -2.0f, 1.0f};
        GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
        //GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

        //Add directed light
        GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
        //Coming from the direction (-1, 0.5, 0.5)
        //GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
        glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
        glLightfv(GL_LIGHT1, GL_POSITION, lightPos0);


        GLfloat lightColor2[] = {0.1f, 0.8f, 0.1f, 1.0f}; //Color (0.5, 0.2, 0.2)
        //Coming from the direction (-1, 0.5, 0.5)
        //GLfloat lightPos2[] = {-1.0f, 0.5f, zAxis, 0.0f};
        glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
        glLightfv(GL_LIGHT2, GL_POSITION, lightPos0);

    }
    else if(flag==1)
    {
        GLfloat lightPos1[] = {1.75f, 0.75f, 0.5f, 1.0f};
        GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
        //GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);

        //Add directed light
        GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
        //Coming from the direction (-1, 0.5, 0.5)
        //GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
        glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
        glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);


        GLfloat lightColor2[] = {0.1f, 0.8f, 0.1f, 1.0f}; //Color (0.5, 0.2, 0.2)
        //Coming from the direction (-1, 0.5, 0.5)
        //GLfloat lightPos2[] = {-1.0f, 0.5f, zAxis, 0.0f};
        glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
        glLightfv(GL_LIGHT2, GL_POSITION, lightPos1);

    }

    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);

    //glColor3f(r, g, b);

    glBegin(GL_QUADS);
    //Front
    glNormal3f(0.0f, 0.0f, 1.0f);
    //glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(x1, -2.0f, -2.5f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(x1, -1.5f, -2.5f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(x2, -1.5f, -2.5f);
    //glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(x2, -2.0f, -2.5f);

    //Right
    glNormal3f(1.0f, 0.0f, 0.0f);
    //glNormal3f(1.0f, 0.0f, -1.0f);
    glVertex3f(x1, -2.0f, -3.0f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(x1, -1.5f, -3.0f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(x1, -1.5f, -2.5f);
    //glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(x1, -2.0f, -2.5f);

    //Back
    glNormal3f(0.0f, 0.0f, -1.0f);
    //glNormal3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(x1, -2.0f, -3.0f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(x1, -1.5f, -3.0f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(x2, -1.5f, -3.0f);
    //glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(x2, -2.0f, -3.0f);

    //Left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    //glNormal3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(x2, -2.0f, -3.0f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(x2, -1.5f, -3.0f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(x2, -1.5f, -2.5f);
    //glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(x2, -2.0f, -2.5f);


    //Top
    glNormal3f(-1.0f, 0.0f, 0.0f);
    //glNormal3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(x1, -1.5f, -2.5f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(x2, -1.5f, -2.5);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(x2, -1.5f, -3.0f);
    //glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(x1, -1.5f, -3.0f);

    //Bottom
    glNormal3f(-1.0f, 0.0f, 0.0f);
    //glNormal3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(x1, -2.0f, -2.5f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(x2, -2.0f, -2.5);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(x2, -2.0f, -3.0f);
    //glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(x1, -2.0f, -3.0f);

    glEnd();



    glColor3f(r, g, b);
    //glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    //Bottom
    glNormal3f(0.0f, 0.0f, 1.0f);
    //glColor3f(r, g, b);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.75f, 0.5f, 0.0f);
    //glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(1.5f, 0.67f, 0.0f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(2.0f, 0.67f, 0.0f);

    //Top

    glNormal3f(0.0f, 0.0f, 1.0f);
    //glColor3f(r, g, b);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.75f, 1.0f, 0.0f);
    //glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(1.5f, 0.84f, 0.0f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(2.0f, 0.84f, 0.0f);

    glEnd();

    glBegin(GL_QUADS);
    //Front

    glNormal3f(0.0f, 0.0f, 1.0f);
    //glColor3f(r, g, b);
    //glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(1.5f, 0.67f, 0.0f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.5f, 0.84f, 0.0f);
    //glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(2.0f, 0.84f, 0.0f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(2.0f, 0.67f, 0.0f);

    glEnd();


    glutSwapBuffers();
}

void update(int value)
{
    if(lrF==0)
    {
        x1=x1+0.1;
        x2=x2+0.1;
        if(x1>=2.5&&x2>=2.0)
        {
            lrF=1;
        }
    }
    if(lrF==1)
    {
        x1=x1-0.1;
        x2=x2-0.1;
        if(x1<=-2.5&&x2<=-2.0)
        {
            lrF=0;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}


void updateC(int value)
{

    if(red==1)
    {
        r=1.0f;
        g=0.0f;
        b=0.0f;
        red=0;
        green=1;
        blue=0;
        black=0;
    }
    else if(green==1)
    {
        r=0.0f;
        g=1.0f;
        b=0.0f;
        red=0;
        green=0;
        blue=1;
        black=0;
    }
    else if(blue==1)
    {
        r=0.0f;
        g=0.0f;
        b=1.0f;
        red=0;
        green=0;
        blue=0;
        black=1;
    }
    else if(black==1)
    {
        r=0.0f;
        g=0.0f;
        b=0.0f;
        red=1;
        green=0;
        blue=0;
        black=0;
    }

    glutPostRedisplay();
    glutTimerFunc(500, updateC,0);
}



int main(int argc, char** argv)
{
    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);

    //Create the window
    glutCreateWindow("Lighting - videotutorialsrock.com");
    initRendering();

    //Set handler functions
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);

    glutTimerFunc(25, update, 0);
    glutTimerFunc(1000, updateC, 0);  //Add a timer

    glutMainLoop();
    return 0;
}