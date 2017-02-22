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
#include "GL/imageloader.h"
int flag=0;
int angleRF=0;
int angleLF=0;
int up=0;
int down=0;
float _angle = -70.0f;
float zAxis = -6;
float nF  = 0;
using namespace std;

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'p': //toggle
        if(flag==0)
        {
            flag=1;
        }
        else if(flag==1)
        {
            flag = 2;
        }
        else if(flag==2)
        {
            flag = 3;
        }
        else if(flag==3)
        {
            flag = 0;
        }
        break;
    case 'a': //LeftArrow
        angleLF=1;
        break;
    //angleRF=0;
    case 'd': //RightArrow
        //angleLF=0;
        angleRF=1;
        break;
    case 'w': //up
        up=1;
        break;
    //angleRF=0;
    case 'x': //down
        //angleLF=0;
        down=1;
        break;
    case 'n':
        if(nF==0)
        {
            nF = 1;
        }
        else if(nF==1)
        {
            nF = 2;
        }
        else if(nF==2)
        {
            nF = 0;
        }
        break;
    }
}

GLuint loadTexture(Image* image)
{
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data
    return textureId; //Returns the id of the texture
}


GLuint sky;
GLuint brickW;
GLuint brickW1;
GLuint brickH;
GLuint brickH1;
GLuint grass;
//Initializes 3D rendering
void initRendering()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING); //Enable lighting
    glEnable(GL_LIGHT0); //Enable light #0
    glEnable(GL_LIGHT1); //Enable light #1
    glEnable(GL_LIGHT2); //Enable light #1

    glEnable(GL_LIGHT3); //Enable light #0
    glEnable(GL_LIGHT4); //Enable light #1
    glEnable(GL_LIGHT5); //Enable light #1
    glEnable(GL_LIGHT6); //Enable light #0
    glEnable(GL_LIGHT7); //Enable light #1
//    glEnable(GL_LIGHT8); //Enable light #1
//    glEnable(GL_LIGHT9); //Enable light #1
//    glEnable(GL_LIGHT10); //Enable light #1
    glEnable(GL_NORMALIZE); //Automatically normalize normals
    //glShadeModel(GL_SMOOTH); //Enable smooth shading
    Image* image = loadBMP("E:\\Education\\4.2\\Graphics\\PracticeCode\\ShatGambujMasque\\sky.bmp");
    sky = loadTexture(image);
    delete image;
    image = loadBMP("E:\\Education\\4.2\\Graphics\\PracticeCode\\ShatGambujMasque\\brickW.bmp");
    brickW = loadTexture(image);
    delete image;
    image = loadBMP("E:\\Education\\4.2\\Graphics\\PracticeCode\\ShatGambujMasque\\brickW1.bmp");
    brickW1 = loadTexture(image);
    delete image;
    image = loadBMP("E:\\Education\\4.2\\Graphics\\PracticeCode\\ShatGambujMasque\\brickH.bmp");
    brickH = loadTexture(image);
    delete image;
    image = loadBMP("E:\\Education\\4.2\\Graphics\\PracticeCode\\ShatGambujMasque\\brickH1.bmp");
    brickH1 = loadTexture(image);
    delete image;
    image = loadBMP("E:\\Education\\4.2\\Graphics\\PracticeCode\\ShatGambujMasque\\grass.bmp");
    grass = loadTexture(image);
    delete image;
}

//Called when the window is resized
void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void draw_cylinder(GLfloat radius,
                   GLfloat height,
                   GLubyte R,
                   GLubyte G,
                   GLubyte B)
{
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;



    glRotatef(-90, 1.0, 0.0, 0.0);
    /** Draw the tube */
    glColor3ub(R-40,G-40,B-40);
    glBegin(GL_QUAD_STRIP);
    angle = 0.1;

    while( angle < 2*PI )
    {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x, y, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(radius, 0.0, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glEnd();

    /** Draw the circle on top of cylinder */
    glColor3ub(R,G,B);
    glBegin(GL_POLYGON);
    angle = 0.0;
    while( angle < 2*PI )
    {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();
}

void draw_ring_design(GLfloat radius,
                      GLfloat height,
                      GLubyte R,
                      GLubyte G,
                      GLubyte B)
{
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the circle on top of cylinder */
    glColor3ub(R,G,B);
    glBegin(GL_POLYGON);
    angle = 0.0;
    while( angle < 2*PI )
    {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();
}

void drawHalfSphere(int scaley, int scalex, GLfloat r)
{
    glColor3f(1.0f, 1.0f, 0.0f);
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

void singleDom()
{
    glRotatef(0.0, 1.0, 0.0, 0.0);
    drawHalfSphere(50, 50, 0.5);
    glRotatef(0.0, 1.0, 0.0, 0.0);
}

void topView()
{
    //glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.5f, 0.0f, 0.0f);

    //middle dom
    glTranslatef(0.0f, 1.2f, -1.35f);
    drawHalfSphere(50, 50, 0.5);
    glTranslatef(0.0f, -1.2f, 1.35f);

    glTranslatef(0.0f, 1.2f, 0.0f);
    drawHalfSphere(50, 50, 0.5);
    glTranslatef(0.0f, -1.2f, 0.0f);

    glTranslatef(0.0f, 1.2f, 1.35f);
    drawHalfSphere(50, 50, 0.5);
    glTranslatef(0.0f, -1.2f, -1.35f);

    float i=0,j=0,k=1.05,h=0;
    int count =0;
    for(j=-1.715; j<=2; j=j+0.57)//z axis
    {
        h=k;
        count++;
        float inc=(1.2-h)/5.0;
        for(i=-3.65; i<-0.56; i=i+0.7)//x axis
        {
            glTranslatef(i, h, j);
            drawHalfSphere(50, 50, 0.28);
            glTranslatef(-i, -h, -j);
            if(count==4) h=h;
            else h=h+inc;
        }
        if(count<=3) k=k+0.05;
        else k=k-0.05;
    }

    k=1.05;
    h=0;
    count =0;
    for(j=-1.715; j<=2; j=j+0.57)//z axis
    {
        h=k;
        count++;
        float inc=(1.2-h)/5.0;
        for(i=3.65; i>0.56; i=i-0.7)//x axis
        {
            glTranslatef(i, h, j);
            drawHalfSphere(50, 50, 0.28);
            glTranslatef(-i, -h, -j);
            if(count==4) h=h;
            else h=h+inc;
        }
        if(count<=3) k=k+0.05;
        else k=k-0.05;
    }


    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    //Front
    glNormal3f(0.0f, 0.0f, 1.0f);
    //glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(-4.0f, 1.0f, -2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-4.0f, 1.2f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0f, 1.20f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f, 1.20f, -2.0f);
    glTexCoord2f(0.0f, 0.0f);


    //glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 1.20f, -2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.0f, 1.20f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(4.0f, 1.2f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(4.0f, 1.0f, -2.0f);
    glTexCoord2f(0.0f, 0.0f);


    glNormal3f(0.0f, 0.0f, 1.0f);
    //glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(-4.0f, 1.0f, 2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-4.0f, 1.20f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0f, 1.20f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f, 1.20f, 2.0f);
    glTexCoord2f(0.0f, 0.0f);


    //glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(4.0f, 1.20f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(4.0f, 1.0f, 2.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0f, 1.2f, 2.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f, 1.2f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);

    glEnd();
}


void drawMinarRing(float height)
{
    //glTranslatef(0.0,-0.4,-3.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    draw_ring_design(0.51, height, 10, 10, 40);
    height=height+0.01;
    draw_ring_design(0.52, height, 20, 20, 50);
    height=height+0.01;
    draw_ring_design(0.53, height, 30, 30, 60);
    height=height+0.01;
    draw_ring_design(0.54, height, 40, 40, 70);
    height=height+0.01;
    draw_ring_design(0.55, height, 50, 50, 80);
    height=height+0.01;
    draw_ring_design(0.55, height, 50, 50, 80);
    height=height+0.01;
    draw_ring_design(0.54, height, 40, 40, 70);
    height=height+0.01;
    draw_ring_design(0.53, height, 30, 30, 60);
    height=height+0.01;
    draw_ring_design(0.52, height, 20, 20, 50);
    height=height+0.01;
    draw_ring_design(0.51, height, 10, 10, 40);
    glRotatef(90, 1.0, 0.0, 0.0);
    //glTranslatef(0.0,0.4,3.0);
}


void door()
{
    glBegin(GL_QUADS); //Begin quadrilateral coordinates
    //top

    glVertex3f(0.25f,-0.4f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.25f, 0.1f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0f,  0.1f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f,  -0.15f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);

    glVertex3f(-0.25f,-0.4f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-0.25f, 0.1f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0f,  0.1f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f,  -0.15f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS); //Begin quadrilateral coordinates
    //low
    glColor3f (0.9, 0.9, 0.9);
    glVertex3f(0.25f, -1.0f, 0.06f);
    glVertex3f(0.25f, -1.0f, -0.05f);
    glVertex3f(0.25f, 0.1f, -0.05f);
    glVertex3f(0.25f, 0.1f, 0.06f);

    glVertex3f(-0.25f, -1.0f, 0.06f);
    glVertex3f(-0.25f, -1.0f, -0.05f);
    glVertex3f(-0.25f, 0.1f, -0.05f);
    glVertex3f(-0.25f, 0.1f, 0.06f);


    glVertex3f(-0.25f, -1.0f, 0.06f);
    glVertex3f(-0.25f, -1.0f, -0.05f);
    glVertex3f(0.25f, -1.0f, -0.05f);
    glVertex3f(0.25f, -1.0f, 0.06f);

    glEnd();


    glBegin(GL_QUADS); //Begin quadrilateral coordinate
    //top first
    glColor3f (1.0, 1.0, 1.0);
    glVertex3f(0.25f, -0.05f, 0.02f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.25f, 0.1f, 0.02f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.25f, 0.1f, 0.02f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.25f, -0.05f, 0.02f);
    glTexCoord2f(0.0f, 0.0f);

    glVertex3f(0.25f, -0.05f, 0.02f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.25f, -0.05f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.25f, -0.05f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.25f, -0.05f, 0.02f);
    glTexCoord2f(0.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS); //Begin quadrilateral coordinate
    //top second
    glVertex3f(0.25f, 0.0f, 0.04f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.25f, 0.1f, 0.04f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.25f, 0.1f, 0.04f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.25f, 0.0f, 0.04f);
    glTexCoord2f(0.0f, 0.0f);

    glVertex3f(0.25f, 0.0f, 0.04f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.25f, 0.0f, 0.02f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.25f, 0.0f, 0.02f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.25f, 0.0f, 0.04f);
    glTexCoord2f(0.0f, 0.0f);
    glEnd();


    glBegin(GL_QUADS); //Begin quadrilateral coordinate
    //top third

    glVertex3f(0.25f, 0.05f, 0.06f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.25f, 0.1f, 0.06f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.25f, 0.1f, 0.06f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.25f, 0.05f, 0.06f);
    glTexCoord2f(0.0f, 0.0f);

    glVertex3f(0.25f, 0.05f, 0.06f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.25f, 0.05f, 0.04f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.25f, 0.05f, 0.04f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.25f, 0.05f, 0.06f);
    glTexCoord2f(0.0f, 0.0f);
    glEnd();
}

void middelDoor()
{
    glBegin(GL_QUADS); //Begin quadrilateral coordinates
    //top

    glVertex3f(0.325f,-0.3f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.325f, 0.3f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0f,  0.3f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f,  0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);

    glVertex3f(-0.325f,-0.3f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-0.325f, 0.3f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0f,  0.3f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f,  0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS); //Begin quadrilateral coordinates
    //low
    glColor3f (0.9, 0.9, 0.9);
    glVertex3f(0.325f, -1.0f, 0.06f);
    glVertex3f(0.325f, -1.0f, -0.05f);
    glVertex3f(0.325f, 0.3f, -0.05f);
    glVertex3f(0.325f, 0.3f, 0.06f);

    glVertex3f(-0.325f, -1.0f, 0.06f);
    glVertex3f(-0.325f, -1.0f, -0.05f);
    glVertex3f(-0.325f, 0.3f, -0.05f);
    glVertex3f(-0.325f, 0.3f, 0.06f);


    glVertex3f(-0.325f, -1.0f, 0.06f);
    glVertex3f(-0.325f, -1.0f, -0.05f);
    glVertex3f(0.325f, -1.0f, -0.05f);
    glVertex3f(0.325f, -1.0f, 0.06f);

    glEnd();


    glBegin(GL_QUADS); //Begin quadrilateral coordinate
    //top first
    glColor3f (1.0, 1.0, 1.0);
    glVertex3f(0.325f, 0.15f, 0.02f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.325f, 0.3f, 0.02f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.325f, 0.3f, 0.02f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.325f, 0.15f, 0.02f);
    glTexCoord2f(0.0f, 0.0f);

    glVertex3f(0.325f, 0.15f, 0.02f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.325f, 0.15f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.325f, 0.15f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.325f, 0.15f, 0.02f);
    glTexCoord2f(0.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS); //Begin quadrilateral coordinate
    //top second

    glVertex3f(0.325f, 0.20f, 0.04f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.325f, 0.3f, 0.04f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.325f, 0.3f, 0.04f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.325f, 0.20f, 0.04f);
    glTexCoord2f(0.0f, 0.0f);

    glVertex3f(0.325f, 0.20f, 0.04f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.325f, 0.20f, 0.02f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.325f, 0.20f, 0.02f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.325f, 0.20f, 0.04f);
    glTexCoord2f(0.0f, 0.0f);
    glEnd();


    glBegin(GL_QUADS); //Begin quadrilateral coordinate
    //top third

    glVertex3f(0.325f, 0.25f, 0.06f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.325f, 0.3f, 0.06f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.325f, 0.3f, 0.06f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.325f, 0.25f, 0.06f);
    glTexCoord2f(0.0f, 0.0f);

    glVertex3f(0.325f, 0.25f, 0.06f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.325f, 0.25f, 0.04f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.325f, 0.25f, 0.04f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.325f, 0.25f, 0.06f);
    glTexCoord2f(0.0f, 0.0f);
    glEnd();

}

void mimbor()
{
    glBegin(GL_QUADS); //Begin quadrilateral coordinates
    //top


    glVertex3f(0.1f,0.6f, 0.3f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.1f,0.6f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.1f,0.6f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.1f,0.6f, 0.3f);
    glTexCoord2f(0.0f, 0.0f);

    glVertex3f(0.1f,0.6f, 0.3f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.2f,0.3f, 0.3f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.2f,0.3f, 0.3f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.1f,0.6f, 0.3f);
    glTexCoord2f(0.0f, 0.0f);


    glVertex3f(0.2f,-0.5f, 0.3f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.2f, 0.3f, 0.3f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.2f,0.3f, 0.3f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.2f, -0.5f, 0.3f);
    glTexCoord2f(0.0f, 0.0f);

    //right

    glVertex3f(0.2f,-0.5f, 0.3f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.2f, 0.3f, 0.3f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.365f,0.3f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.365f, -0.5f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);

    glVertex3f(0.1f,0.6f, 0.3f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.2f,0.3f, 0.3f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.365f,0.3f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.1f,0.6f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);

    //left

    glVertex3f(-0.2f,-0.5f, 0.3f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-0.2f, 0.3f, 0.3f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.365f,0.3f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.365f, -0.5f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);

    glVertex3f(-0.1f,0.6f, 0.3f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-0.2f,0.3f, 0.3f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.365f,0.3f, 0.0f);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-0.1f,0.6f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);

    glEnd();
}
const float RADIUS = 0.15f;
void lamp()
{
    GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    GLfloat lightColor[] = {1.0f, 1.0f,1.0f, 1.0f};

    GLfloat lightPos3[] = {-1.5f * RADIUS, 2 * RADIUS, 1.5f * RADIUS, 1.0f};
    //Diffuse (non-shiny) light component
    glLightfv(GL_LIGHT3, GL_DIFFUSE, lightColor);
    //Specular (shiny) light component
    glLightfv(GL_LIGHT3, GL_SPECULAR, lightColor);
    glLightfv(GL_LIGHT3, GL_POSITION, lightPos3);

    GLfloat lightPos4[] = {1.5f * RADIUS, -2 * RADIUS, -1.5f * RADIUS, 1.0f};
    //Diffuse (non-shiny) light component
    glLightfv(GL_LIGHT4, GL_DIFFUSE, lightColor);
    //Specular (shiny) light component
    glLightfv(GL_LIGHT4, GL_SPECULAR, lightColor);
    glLightfv(GL_LIGHT4, GL_POSITION, lightPos4);

    GLfloat lightPos5[] = {-1.5f * RADIUS, 2 * RADIUS, -1.5f * RADIUS, 1.0f};
    //Diffuse (non-shiny) light component
    glLightfv(GL_LIGHT5, GL_DIFFUSE, lightColor);
    //Specular (shiny) light component
    glLightfv(GL_LIGHT5, GL_SPECULAR, lightColor);
    glLightfv(GL_LIGHT5, GL_POSITION, lightPos5);

    GLfloat lightPos6[] = {1.5f * RADIUS, 2 * RADIUS, -1.5f * RADIUS, 1.0f};
    //Diffuse (non-shiny) light component
    glLightfv(GL_LIGHT6, GL_DIFFUSE, lightColor);
    //Specular (shiny) light component
    glLightfv(GL_LIGHT6, GL_SPECULAR, lightColor);
    glLightfv(GL_LIGHT6, GL_POSITION, lightPos6);

    GLfloat lightPos7[] = {-1.5f * RADIUS, -2 * RADIUS, -1.5f * RADIUS, 1.0f};
    //Diffuse (non-shiny) light component
    glLightfv(GL_LIGHT7, GL_DIFFUSE, lightColor);
    //Specular (shiny) light component
    glLightfv(GL_LIGHT7, GL_SPECULAR, lightColor);
    glLightfv(GL_LIGHT7, GL_POSITION, lightPos7);
    /*
        GLfloat lightPos8[] = {1.5f * RADIUS, -2 * RADIUS, 1.5f * RADIUS, 1.0f};
        //Diffuse (non-shiny) light component
        glLightfv(GL_LIGHT8, GL_DIFFUSE, lightColor);
        //Specular (shiny) light component
        glLightfv(GL_LIGHT8, GL_SPECULAR, lightColor);
        glLightfv(GL_LIGHT8, GL_POSITION, lightPos8);


        GLfloat lightPos9[] = {1.5f * RADIUS, 2 * RADIUS, 1.5f * RADIUS, 1.0f};
        //Diffuse (non-shiny) light component
        glLightfv(GL_LIGHT9, GL_DIFFUSE, lightColor);
        //Specular (shiny) light component
        glLightfv(GL_LIGHT9, GL_SPECULAR, lightColor);
        glLightfv(GL_LIGHT9, GL_POSITION, lightPos9);

        GLfloat lightPos10[] = {-1.5f * RADIUS, -2 * RADIUS, 1.5f * RADIUS, 1.0f};
        //Diffuse (non-shiny) light component
        glLightfv(GL_LIGHT10, GL_DIFFUSE, lightColor);
        //Specular (shiny) light component
        glLightfv(GL_LIGHT10, GL_SPECULAR, lightColor);
        glLightfv(GL_LIGHT10, GL_POSITION, lightPos10);
    */

    //Determine the specularity, emissivity, and shininess parameters, based on
    //variables that can be toggled with keystrokes
    float specularity;
    specularity = 0.3f;

    float emissivity;

    emissivity = 0.05f;


    float shininess;

    shininess = 25;

    //The color of the sphere
    GLfloat materialColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    //The specular (shiny) component of the material
    GLfloat materialSpecular[] = {specularity, specularity, specularity, 1.0f};
    //The color emitted by the material
    GLfloat materialEmission[] = {emissivity, emissivity, emissivity, 1.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess); //The shininess parameter

    //Draw the sphere
    glutSolidSphere(RADIUS, 150, 80);
}


static float resolution = 0.01;
static float radius = 2.0;
static float height = 5.0;
//Draws the 3D scene
float rF = 1.0f;
float gF = 1.0f;
float bF = 1.0f;

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, -2.0f, -13.0f);

    //Add ambient light
    GLfloat ambientColor[] = {rF, gF, bF, 1.0f}; //Color (0.2, 0.2, 0.2)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    if(nF==0){

    }
    //Add positioned light
    GLfloat lightColor0[] = {rF, gF, bF, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    //Add directed light
    GLfloat lightColor1[] = {rF, gF, bF, 1.0f}; //Color (0.5, 0.2, 0.2)
    //Coming from the direction (-1, 0.5, 0.5)
    GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);


    GLfloat lightColor2[] = {rF, gF, bF, 1.0f}; //Color (0.5, 0.2, 0.2)
    //Coming from the direction (-1, 0.5, 0.5)
    GLfloat lightPos2[] = {-1.0f, 0.5f, 0.5, 0.0f};
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, sky);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0f,1.0f,1.0f);

    glVertex3f(-18.0f, -10.0f, -6.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(18.0f, -10.0f, -6.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18.0f, 10.0f, -6.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-18.0f, 10.0f, -6.5f);
    glTexCoord2f(0.0f, 0.0f);

    glEnd();
    /*
    	glColor3f(1.0f, 1.0f, 1.0f);
    	glBegin(GL_QUADS);
    	glNormal3f(0.0f, 0.0f, 1.0f);
        //Front
        glTexCoord2f(-10.0f, -10.0f);
        glVertex3f(-10.0f, -10.0f, -5.0f);
        glTexCoord2f(10.0f, -10.0f);
        glVertex3f(10.0f, -10.0f, -5.0f);
        glTexCoord2f(10.0f, 10.0f);
        glVertex3f(10.0f, 10.0f, -5.0f);
        glTexCoord2f(-10.0f, 10.0f);
        glVertex3f(-10.0f, 10.0f, -5.0f);
        glEnd();
        */

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, grass);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0f,1.0f,1.0f);

    glVertex3f(-16.0f, -1.0f, -10.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(16.0f, -1.0f, -10.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(16.0f, -1.0f, 10.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-16.0f, -1.0f, 10.0f);
    glTexCoord2f(0.0f, 0.0f);

    glEnd();

    glDisable(GL_TEXTURE_2D);



    if(flag==0)
    {
        glRotatef(_angle, 0.0f, 1.0f, 0.0f);
    }
    else if(flag==1)
    {
        glRotatef(_angle, 1.0f, 0.0f, 0.0f);
    }
    else if(flag==2)
    {
        glRotatef(_angle, 1.0f, 1.0f, 0.0f);
    }
    else if(flag==3)
    {
        glRotatef(_angle, 1.0f, 1.0f, 1.0f);
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, brickW1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //glBindTexture(GL_TEXTURE_2D, brickW1);
    //front top triangle
    glNormal3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex3f(-4.0f, 1.0f, 2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.0f, 1.2f, 2.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(4.0f, 1.0f, 2.0f);
    glTexCoord2f(1.0f, 1.0f);
    //glTexCoord2f(0.0f, 1.0f);
    glEnd();

    glBegin(GL_QUADS);
    //Front
    glVertex3f(-4.0f, 0.6f, 2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(4.0f, 0.6f, 2.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(4.0f, 1.0f, 2.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-4.0f, 1.0f, 2.0f);
    glTexCoord2f(0.0f, 0.0f);
    glEnd();

    //right top triangle
    glNormal3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);

    glVertex3f(4.0f, 1.0f, 2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(4.0f, 1.2f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(4.0f, 1.0f, -2.0f);
    glTexCoord2f(1.0f, 1.0f);
    glEnd();

    glBegin(GL_QUADS);
    //right
    glVertex3f(4.0f, 0.6f, -2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(4.0f, 0.6f, 2.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(4.0f, 1.0f, 2.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(4.0f, 1.0f, -2.0f);
    glTexCoord2f(0.0f, 0.0f);
    glEnd();

    //left top triangle
    glNormal3f(0.0f, 0.0f, -1.0f);
    glBegin(GL_TRIANGLES);

    glVertex3f(-4.0f, 1.0f, 2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-4.0f, 1.2f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-4.0f, 1.0f, -2.0f);
    glTexCoord2f(1.0f, 1.0f);
    glEnd();

    glBegin(GL_QUADS);
    //left
    glVertex3f(-4.0f, 0.6f, -2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-4.0f, 0.6f, 2.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-4.0f, 1.0f, 2.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-4.0f, 1.0f, -2.0f);
    glTexCoord2f(0.0f, 0.0f);
    glEnd();

    //back top triangle
    glNormal3f(0.0f, 0.0f, -1.0f);
    glBegin(GL_TRIANGLES);
    glVertex3f(-4.0f, 1.0f, -2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.0f, 1.2f, -2.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(4.0f, 1.0f, -2.0f);
    glTexCoord2f(1.0f, 1.0f);
    glEnd();

    glBegin(GL_QUADS);
    //right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-4.0f, 0.6f, -2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(4.0f, 0.6f, -2.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(4.0f, 1.0f, -2.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-4.0f, 1.0f, -2.0f);
    glTexCoord2f(0.0f, 0.0f);
    glEnd();
//    glDisable(GL_TEXTURE_2D);
//
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, brickH);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

//front side slice
    glNormal3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS); //Begin quadrilateral coordinates
    glVertex3f(-4.0f,-0.5f, 2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-3.9f,-0.5f, 2.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-3.9f,0.6f, 2.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-4.0f,0.6f, 2.0f);
    glTexCoord2f(0.0f, 0.0f);


    glVertex3f(4.0f,-0.5f, 2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(3.9f,-0.5f, 2.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(3.9f,0.6f, 2.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(4.0f,0.6f, 2.0f);
    glTexCoord2f(0.0f, 0.0f);
    glEnd();

    //left side slice
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS); //Begin quadrilateral coordinates
    glVertex3f(-4.0f,-0.5f, 2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-4.0f,-0.5f, 1.75f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-4.0f,0.6f, 1.75f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-4.0f,0.6f, 2.0f);
    glTexCoord2f(0.0f, 0.0f);


    glVertex3f(-4.0f,-0.5f, -2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-4.0f,-0.5f, -1.75f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-4.0f,0.6f, -1.75f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-4.0f,0.6f, -2.0f);
    glTexCoord2f(0.0f, 0.0f);
    glEnd();

    //right side slice
    glNormal3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS); //Begin quadrilateral coordinates

    glVertex3f(4.0f,-0.5f, 2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(4.0f,-0.5f, 1.75f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(4.0f,0.6f, 1.75f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(4.0f,0.6f, 2.0f);
    glTexCoord2f(0.0f, 0.0f);


    glVertex3f(4.0f,-0.5f, -2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(4.0f,-0.5f, -1.75f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(4.0f,0.6f, -1.75f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(4.0f,0.6f, -2.0f);
    glTexCoord2f(0.0f, 0.0f);
    glEnd();


    //back side slice
    glColor3f (1.0, 1.0, 1.0);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glBegin(GL_QUADS); //Begin quadrilateral coordinates

    glVertex3f(4.0f,-0.5f, -2.0f);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(0.365f,-0.5f, -2.0f);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(0.365f,0.6f, -2.0f);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(4.0f,0.6f, -2.0f);
    glTexCoord2f(0.0f,0.0f);



    glVertex3f(-4.0f,-0.5f, -2.0f);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-0.365f,-0.5f, -2.0f);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(-0.365f,0.6f, -2.0f);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-4.0f,0.6f, -2.0f);
    glTexCoord2f(0.0f,0.0f);
    glEnd();

    glBegin(GL_TRIANGLES);

    glVertex3f(-0.1f, 0.6f, -2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-0.365f, 0.31f, -2.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.365f, 0.6f, -2.0f);
    glTexCoord2f(1.0f, 1.0f);

    glVertex3f(0.1f, 0.6f, -2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.365f, 0.31f, -2.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.365f, 0.6f, -2.0f);
    glTexCoord2f(1.0f, 1.0f);
    glEnd();

    //door front
    for(float i=-3.65; i<=-0.323; i=i+0.714)
    {
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTranslatef(i, 0.5f, 2.0f);
        door();
        glTranslatef(-i, -0.5f, -2.0f);


        float sl1 = i+0.25f;
        float sl2 = sl1+0.214f;
        glBegin(GL_QUADS); //Begin quadrilateral coordinates
        //glColor3f (0.0, 1.0, 0.0);
        glVertex3f(sl1,-0.5f, 2.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(sl2,-0.5f, 2.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(sl2,0.6f, 2.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(sl1,0.6f, 2.0f);
        glTexCoord2f(0.0f, 0.0f);
        glEnd();

    }

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, 0.5f, 2.0f);
    middelDoor();
    glTranslatef(0.0f, -0.5f, -2.0f);

    glNormal3f(0.0f, 0.0f, 1.0f);
    for(float i=3.65; i>= 0.323; i=i-0.714)
    {
        glTranslatef(i, 0.5f, 2.0f);
        door();
        glTranslatef(-i, -0.5f, -2.0f);


        float sl1 = i-0.25f;
        float sl2 = sl1-0.214f;
        glBegin(GL_QUADS); //Begin quadrilateral coordinates
        glVertex3f(sl1,-0.5f, 2.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(sl2,-0.5f, 2.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(sl2,0.6f, 2.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(sl1,0.6f, 2.0f);
        glTexCoord2f(0.0f, 0.0f);
        glEnd();


    }

    //door right
    for(float i=1.5; i>= 0.786; i=i-0.714)
    {
        glNormal3f(1.0f, 0.0f, 0.0f);
        glTranslatef(4.0f, 0.5f, i);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        door();
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(-4.0f, -0.5f, -i);


        float sl1 = i-0.25f;
        float sl2 = sl1-0.214f;
        glBegin(GL_QUADS); //Begin quadrilateral coordinates
        glVertex3f(4.0f,-0.5f, sl1);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(4.0f,-0.5f, sl2);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(4.0f,0.6f, sl2);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(4.0f,0.6f, sl1);
        glTexCoord2f(0.0f, 0.0f);
        glEnd();


    }

    glNormal3f(1.0f, 0.0f, 0.0f);
    glTranslatef(4.0f, 0.5f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    middelDoor();
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(-4.0f, -0.5f, 0.0f);

    for(float i=-1.50; i<=-0.786; i=i+0.714)
    {
        glNormal3f(1.0f, 0.0f, 0.0f);
        glTranslatef(4.0f, 0.5f, i);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        door();
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(-4.0f, -0.5f, -i);


        float sl1 = i+0.25f;
        float sl2 = sl1+0.214f;
        glBegin(GL_QUADS); //Begin quadrilateral coordinates

        glVertex3f(4.0f,-0.5f, sl1);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(4.0f,-0.5f, sl2);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(4.0f,0.6f, sl2);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(4.0f,0.6f, sl1);
        glTexCoord2f(0.0f, 0.0f);
        glEnd();
    }


    //door left
    for(float i=1.5; i>=0.786; i=i-0.714)
    {
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTranslatef(-4.0f, 0.5f, i);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        door();
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(4.0f, -0.5f, -i);

        float sl1 = i-0.25f;
        float sl2 = sl1-0.214f;
        glBegin(GL_QUADS); //Begin quadrilateral coordinates

        glVertex3f(-4.0f,-0.5f, sl1);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-4.0f,-0.5f, sl2);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-4.0f,0.6f, sl2);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-4.0f,0.6f, sl1);
        glTexCoord2f(0.0f, 0.0f);
        glEnd();

    }

    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTranslatef(-4.0f, 0.5f, 0.0f);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    middelDoor();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(4.0f, -0.5f, 0.0f);

    for(float i=-1.50; i<=-0.786; i=i+0.714)
    {
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTranslatef(-4.0f, 0.5f, i);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        door();
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(4.0f, -0.5f, -i);


        float sl1 = i+0.25f;
        float sl2 = sl1+0.214f;
        glBegin(GL_QUADS); //Begin quadrilateral coordinates
        glVertex3f(-4.0f,-0.5f, sl1);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-4.0f,-0.5f, sl2);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-4.0f,0.6f, sl2);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-4.0f,0.6f, sl1);
        glTexCoord2f(0.0f, 0.0f);
        glEnd();
    }

    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, -2.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    mimbor();
    glRotatef(-180.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 2.0f);

    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);

    /*
        //Front
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-4.0f, -1.0f, 2.0f);
        //glNormal3f(1.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, -1.0f, 2.0f);
        //glNormal3f(1.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 1.20f, 2.0f);
        //glNormal3f(-1.0f, 0.0f, 1.0f);
        glVertex3f(-4.0f, 1.0f, 2.0f);


        glVertex3f(0.0f, -1.0f, 2.0f);
        //glNormal3f(1.0f, 0.0f, 1.0f);
        glVertex3f(4.0f, -1.0f, 2.0f);
        //glNormal3f(1.0f, 0.0f, 1.0f);
        glVertex3f(4.0f, 1.0f, 2.0f);
        //glNormal3f(-1.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 1.20f, 2.0f);
    */

    /*
        //Right
        glNormal3f(1.0f, 0.0f, 0.0f);
        //glNormal3f(1.0f, 0.0f, -1.0f);
        glVertex3f(4.0f, -1.0f, -2.0f);
        //glNormal3f(1.0f, 0.0f, -1.0f);
        glVertex3f(4.0f, 1.0f, -2.0f);
        //glNormal3f(1.0f, 0.0f, 1.0f);
        glVertex3f(4.0f, 1.2f, 0.0f);
        //glNormal3f(1.0f, 0.0f, 1.0f);
        glVertex3f(4.0f, -1.0f, 0.0f);

        //glNormal3f(1.0f, 0.0f, -1.0f);
        glVertex3f(4.0f, -1.0f, 0.0f);
        //glNormal3f(1.0f, 0.0f, -1.0f);
        glVertex3f(4.0f, 1.2f, 0.0f);
        //glNormal3f(1.0f, 0.0f, 1.0f);
        glVertex3f(4.0f, 1.0f, 2.0f);
        //glNormal3f(1.0f, 0.0f, 1.0f);
        glVertex3f(4.0f, -1.0f, 2.0f);

    */

    /*
        //Back
        glNormal3f(0.0f, 0.0f, -1.0f);
        //glNormal3f(-1.0f, 0.0f, -1.0f);
        glVertex3f(-4.0f, -1.0f, -2.0f);
        //glNormal3f(1.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, -1.0f, -2.0f);
        //glNormal3f(1.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 1.20f, -2.0f);
        //glNormal3f(-1.0f, 0.0f, 1.0f);
        glVertex3f(-4.0f, 1.0f, -2.0f);

        glVertex3f(0.0f, -1.0f, -2.0f);
        //glNormal3f(1.0f, 0.0f, 1.0f);
        glVertex3f(4.0f, -1.0f, -2.0f);
        //glNormal3f(1.0f, 0.0f, 1.0f);
        glVertex3f(4.0f, 1.0f, -2.0f);
        //glNormal3f(-1.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 1.20f, -2.0f);

        */
    /*
    //Left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    //glNormal3f(1.0f, 0.0f, -1.0f);
    glVertex3f(-4.0f, -1.0f, -2.0f);
    //glNormal3f(1.0f, 0.0f, -1.0f);
    glVertex3f(-4.0f, 1.0f, -2.0f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-4.0f, 1.2f, 0.0f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-4.0f, -1.0f, 0.0f);

    //glNormal3f(1.0f, 0.0f, -1.0f);
    glVertex3f(-4.0f, -1.0f, 0.0f);
    //glNormal3f(1.0f, 0.0f, -1.0f);
    glVertex3f(-4.0f, 1.2f, 0.0f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-4.0f, 1.0f, 2.0f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-4.0f, -1.0f, 2.0f);
    */

    glEnd();

    float domCil = 4.45f;
    //
    glNormal3f(-1.0f, 0.0f, -1.0f);
    glTranslatef(-domCil,-0.5f,-2.2f);
    draw_cylinder(0.5, 2.0, 255, 160, 100);
    glRotatef(90, 1.0, 0.0, 0.0);
    glTranslatef(domCil,0.5f,2.2f);

    glTranslatef(-domCil, 1.5f, -2.2f);
    singleDom();
    glTranslatef(domCil,-1.5f,2.2f);

    glTranslatef(-domCil, 0.0f, -2.2f);
    drawMinarRing(1.45f);
    glTranslatef(domCil,0.0f,2.2f);

    glTranslatef(-domCil, 0.0f, -2.2f);
    drawMinarRing(1.05f);
    glTranslatef(domCil,0.0f,2.2f);

    glTranslatef(-domCil, 0.0f, -2.2f);
    drawMinarRing(0.90f);
    glTranslatef(domCil,0.0f,2.2f);



    //
    glNormal3f(-1.0f, 0.0f, 1.0f);
    glTranslatef(-domCil,-0.5f,2.2);
    draw_cylinder(0.5, 2.0, 255, 160, 100);
    glRotatef(90, 1.0, 0.0, 0.0);
    glTranslatef(domCil,0.5f,-2.2);

    glTranslatef(-domCil,1.5,2.2);
    singleDom();
    glTranslatef(domCil,-1.5,-2.2);

    glTranslatef(-domCil, 0.0f, 2.2f);
    drawMinarRing(1.45f);
    glTranslatef(domCil,0.0f,-2.2f);

    glTranslatef(-domCil, 0.0f, 2.2f);
    drawMinarRing(1.05f);
    glTranslatef(domCil,0.0f,-2.2f);

    glTranslatef(-domCil, 0.0f, 2.2f);
    drawMinarRing(0.90f);
    glTranslatef(domCil,0.0f,-2.2f);

    //
    glNormal3f(1.0f, 0.0f, 1.0f);
    glTranslatef(domCil,-0.5f,2.2);
    draw_cylinder(0.5, 2.0, 255, 160, 100);
    glRotatef(90, 1.0, 0.0, 0.0);
    glTranslatef(-domCil,0.5f,-2.2);

    glTranslatef(domCil,1.5,2.2);
    singleDom();
    glTranslatef(-domCil,-1.5,-2.2);

    glTranslatef(domCil, 0.0f, 2.2f);
    drawMinarRing(1.45f);
    glTranslatef(-domCil,0.0f,-2.2f);

    glTranslatef(domCil, 0.0f, 2.2f);
    drawMinarRing(1.05f);
    glTranslatef(-domCil,0.0f,-2.2f);

    glTranslatef(domCil, 0.0f, 2.2f);
    drawMinarRing(0.90f);
    glTranslatef(-domCil,0.0f,-2.2f);


    //
    glNormal3f(1.0f, 0.0f, -1.0f);
    glTranslatef(domCil,-0.5f,-2.2);
    draw_cylinder(0.5, 2.0, 255, 160, 100);
    glRotatef(90, 1.0, 0.0, 0.0);
    glTranslatef(-domCil,0.5f,2.2);

    glTranslatef(domCil,1.5,-2.2);
    singleDom();
    glTranslatef(-domCil,-1.5,2.2);

    glTranslatef(domCil, 0.0f, -2.2f);
    drawMinarRing(1.45f);
    glTranslatef(-domCil,0.0f,2.2f);

    glTranslatef(domCil, 0.0f, -2.2f);
    drawMinarRing(1.05f);
    glTranslatef(-domCil,0.0f,2.2f);

    glTranslatef(domCil, 0.0f, -2.2f);
    drawMinarRing(0.90f);
    glTranslatef(-domCil,0.0f,2.2f);

    glNormal3f(0.0f, 1.0f, 0.0f);
    topView();



    glBegin(GL_QUADS); //Begin quadrilateral coordinates
    glVertex3f(-4.0f,-0.5f, 2.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-4.0f,-0.5f, -2.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(4.0f,-0.5f, -2.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(4.0f,-0.5f, 2.0);
    glTexCoord2f(0.0f, 0.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);



    glColor3f(0.5f,0.5f,0.5f);
    glBegin(GL_QUADS); //Begin quadrilateral coordinates
    glVertex3f(-1.0f,-0.5f, 2.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f,-0.5f, 10.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f,-0.5f, 10.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f,-0.5f, 2.0);
    glTexCoord2f(0.0f, 0.0f);
    glEnd();

    glTranslatef(0.0f, 0.0f, 1.0f);
    //
    glTranslatef(-1.0f, 1.0f, 3.0f);
    lamp();
    glTranslatef(1.0f, -1.0f, -3.0f);

    glTranslatef(1.0f, 1.0f, 3.0f);
    lamp();
    glTranslatef(-1.0f, -1.0f, -3.0f);

    //
    glTranslatef(-1.0f, 1.0f, 3.5f);
    lamp();
    glTranslatef(1.0f, -1.0f, -3.5f);

    glTranslatef(1.0f, 1.0f, 3.5f);
    lamp();
    glTranslatef(-1.0f, -1.0f, -3.5f);

    //
    glTranslatef(-1.0f, 1.0f, 4.0f);
    lamp();
    glTranslatef(1.0f, -1.0f, -4.0f);

    glTranslatef(1.0f, 1.0f, 4.0f);
    lamp();
    glTranslatef(-1.0f, -1.0f, -4.0f);

    //
    glTranslatef(-1.0f, 1.0f, 4.5f);
    lamp();
    glTranslatef(1.0f, -1.0f, -4.5f);

    glTranslatef(1.0f, 1.0f, 4.5f);
    lamp();
    glTranslatef(-1.0f, -1.0f, -4.5f);

    glTranslatef(0.0f, 0.0f, -1.0f);

    glutSwapBuffers();
}

void update(int value)
{
    if(nF == 1)
    {
        if(rF>=0.0f&&gF>=0.0f&&bF>=0.0f)
        {
            rF = rF - 0.05;
            gF = gF - 0.05;
            bF = bF - 0.05;

        }
    }
    if(nF == 2)
    {
        if(rF<=1.0f&&gF<=1.0f&&bF<=1.0f)
        {
            rF = rF + 0.05;
            gF = gF + 0.05;
            bF = bF + 0.05;
        }
    }
    if(nF==0)
    {
        rF = 1.0f;
        gF = 1.0f;
        bF = 1.0f;
    }

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
        _angle =_angle-2.5f;
        angleRF=0;
        angleLF=0;
    }
    else if(angleRF==1)
    {
        _angle =_angle+2.5f;
        angleRF=0;
        angleLF=0;
    }

    if(up==1)
    {
        _angle =_angle-2.5f;
        up=0;
        down=0;
    }
    else if(down==1)
    {
        _angle =_angle+2.5f;
        up=0;
        down=0;
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
    glutInitWindowSize(1300, 650);

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
