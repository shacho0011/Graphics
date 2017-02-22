

#include <iostream>
#include <stdlib.h>


#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>

#include "GL/imageloader.h"
#endif
#include<math.h>
#include <math.h>
#define PI 3.1415927
int flag=1;
int angleRF=0;
int angleLF=0;
//float _angle = -70.0f;
float zAxis = -6;

GLuint _textureIdbottom; //The id of the texture
GLuint _textureIdback; //The id of the texture
using namespace std;
const float BOX_SIZE = 7.0f;
//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
	}
}


GLuint loadTexture(Image* image) {
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


//Initializes 3D rendering
void initRendering() {

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	//glShadeModel(GL_SMOOTH); //Enable smooth shading

    glClearColor(0.70f, 0.90f, 0.113f,1.0f);

	Image* image = loadBMP("E:\\4.1\\glut\\SGMBj\\sky.bmp");
	_textureIdback = loadTexture(image);
	delete image;



}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float _angle = 0.0f;

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
glColor3f(1.0f,0.58f,0.39f);
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
//Draws the 3D scene
void drawScene() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat ambientColor[] = {0.1f, 0.1f, 0.1f, 1.0f}; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	//Add positioned light
	GLfloat lightColor0[] = {0.5f, 0.5f, 0.8f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {2.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	//Add directed light
	GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
//	Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = {1.0f, 0.5f, 0.5f, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);



    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdback);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    glBegin(GL_QUADS);
     glColor3f(1.0f,1.0f,1.0f);
    glNormal3f(0.0f,0.0f,1.0f);

	glVertex3f(-12.0f, 0.0f, -12.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(12.0f, 0.0f, -12.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(12.0f, 11.0f, -12.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-12.0f, 11.0f, -12.5f);
	glTexCoord2f(0.0f, 0.0f);

	glEnd();
	glDisable(GL_TEXTURE_2D);

//


	glTranslatef(0.0f, 0.0f, -10.0f);

	glPushMatrix();




	//Add ambient light

    glRotatef(_angle, 1.0f, 0.0f, 0.0f);
    glColor3f(0.50f, 0.25f, 0.25f);





	//left minar
    glPushMatrix();
    glTranslatef(-3.645f, -1.0f, 1.5f);
     glColor3f(1.0f,0.873f,0.763f);
    glPushMatrix();
   // glColor3f(1.3,1.3,1.3);
    glRotatef(-90.0,01.0,0.0,0.0);
    glRotatef(0.0,0.0,01.0,0.0);
    glRotatef(0.0,0.0,0.0,1.0);
    GLUquadricObj *n=gluNewQuadric();
    gluCylinder(n,.3,0.3,2.50,50,150);
    glPopMatrix();


   /* glPushMatrix();
    //glColor3f(1.0, 1.0, 1.0);
    glRotatef(-90.0,01.0,0.0,0.0);
    glRotatef(0.0,0.0,01.0,0.0);
    glRotatef(0.0,0.0,0.0,1.0);
    glScalef(1.0,1.0,1.1);
    GLUquadricObj *m=gluNewQuadric();
    gluCylinder(m,.31,.31,1.0,8.0,100.0);
    glPopMatrix();
    */

    /*glPushMatrix();
    glColor3f(0.0,0.0,0.0);
    glTranslatef(-4.0,1.1,1.5);
    glRotatef(90.0,1.0,0.0,0.0);
    glScalef(.8,0.8,1.0);
    glutSolidTorus(0.041,0.550,20,4.5);
    glPopMatrix();*/



    glPushMatrix();
    glTranslatef(3.645f, -1.0f, 1.5f);
    glColor3f(1.0f,0.873f,0.763f);
    glPushMatrix();
   // glColor3f(1.3,1.3,1.3);
    glRotatef(-90.0,01.0,0.0,0.0);
    glRotatef(0.0,0.0,01.0,0.0);
    glRotatef(0.0,0.0,0.0,1.0);
    GLUquadricObj *m=gluNewQuadric();
    gluCylinder(m,.3,0.3,2.50,50,150);
    glPopMatrix();


   /* glPushMatrix();
    //glColor3f(1.0, 1.0, 1.0);
    glRotatef(-90.0,01.0,0.0,0.0);
    glRotatef(0.0,0.0,01.0,0.0);
    glRotatef(0.0,0.0,0.0,1.0);
    glScalef(1.0,1.0,1.1);
    GLUquadricObj *m=gluNewQuadric();
    gluCylinder(m,.31,.31,1.0,8.0,100.0);
    glPopMatrix();
    */

    /*glPushMatrix();
    glColor3f(0.0,0.0,0.0);
    glTranslatef(3.5,1.1,-1.5);
    glRotatef(90.0,1.0,0.0,0.0);
    glScalef(.8,0.8,1.0);
    glutSolidTorus(0.041,0.550,20,25);
    glPopMatrix(); */


     glTranslatef(-3.6,1.5,1.6);
 drawHalfSphere(50, 50, 0.33);
 glTranslatef(3.6,-1.5,-1.6);


   glTranslatef(3.6,1.5,1.6);
 drawHalfSphere(50, 50, 0.33);
 glTranslatef(-3.60,-1.5,-1.6);



glPopMatrix();





glPushMatrix();


	glRotatef(_angle, 1.0f, 0.0f, 0.0f);
/*glTranslatef(3.12f, BOX_SIZE / BOX_SIZE, 0.0f);
drawHalfSphere(50, 50, 0.22);
glTranslatef(-3.12f, -BOX_SIZE / BOX_SIZE, 0.0f);*/

glTranslatef(3.20f, BOX_SIZE / BOX_SIZE, 0.0f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-3.20f, -BOX_SIZE / BOX_SIZE, 0.0f);

glTranslatef(3.20f, BOX_SIZE / BOX_SIZE, -1.2f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-3.20f, -BOX_SIZE / BOX_SIZE, 1.2f);

glTranslatef(3.20f, BOX_SIZE / BOX_SIZE, -0.8f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-3.20f, -BOX_SIZE / BOX_SIZE, 0.8f);

glTranslatef(3.20f, BOX_SIZE / BOX_SIZE, -0.4f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-3.20f, -BOX_SIZE / BOX_SIZE, 0.4f);

glTranslatef(3.20f, BOX_SIZE / BOX_SIZE, 1.2f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-3.20f, -BOX_SIZE / BOX_SIZE, -1.2f);

glTranslatef(3.20f, BOX_SIZE / BOX_SIZE, 0.8f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-3.20f, -BOX_SIZE / BOX_SIZE, -0.8f);

glTranslatef(3.20f, BOX_SIZE / BOX_SIZE, 0.4f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-3.20f, -BOX_SIZE / BOX_SIZE, -0.4f);



glTranslatef(2.56f, BOX_SIZE / BOX_SIZE, 0.0f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-2.56f, -BOX_SIZE / BOX_SIZE, 0.0f);

glTranslatef(2.56f, BOX_SIZE / BOX_SIZE, 0.4f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-2.56f, -BOX_SIZE / BOX_SIZE, -0.4f);

glTranslatef(2.56f, BOX_SIZE / BOX_SIZE, 0.8f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-2.56f, -BOX_SIZE / BOX_SIZE, -0.8f);

glTranslatef(2.56f, BOX_SIZE / BOX_SIZE, 1.2f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-2.56f, -BOX_SIZE / BOX_SIZE, -1.2f);

glTranslatef(2.56f, BOX_SIZE / BOX_SIZE, -0.4f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-2.56f, -BOX_SIZE / BOX_SIZE, 0.4f);

glTranslatef(2.56f, BOX_SIZE / BOX_SIZE, -0.8f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-2.56f, -BOX_SIZE / BOX_SIZE, 0.8f);

glTranslatef(2.56f, BOX_SIZE / BOX_SIZE, -1.2f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-2.56f, -BOX_SIZE / BOX_SIZE, 1.2f);


glTranslatef(1.92f, BOX_SIZE / BOX_SIZE, 0.0f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-1.92f, -BOX_SIZE / BOX_SIZE, 0.0f);

glTranslatef(1.92f, BOX_SIZE / BOX_SIZE, 0.4f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-1.92f, -BOX_SIZE / BOX_SIZE, -0.4f);

glTranslatef(1.92f, BOX_SIZE / BOX_SIZE, 0.8f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-1.92f, -BOX_SIZE / BOX_SIZE, -0.8f);

glTranslatef(1.92f, BOX_SIZE / BOX_SIZE, 1.2f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-1.92f, -BOX_SIZE / BOX_SIZE, -1.2f);

glTranslatef(1.92f, BOX_SIZE / BOX_SIZE, -0.4f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-1.92f, -BOX_SIZE / BOX_SIZE, 0.4f);

glTranslatef(1.92f, BOX_SIZE / BOX_SIZE, -0.8f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-1.92f, -BOX_SIZE / BOX_SIZE, 0.8f);

glTranslatef(1.92f, BOX_SIZE / BOX_SIZE, -1.2f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-1.92f, -BOX_SIZE / BOX_SIZE, 1.2f);

glTranslatef(1.28f, BOX_SIZE / BOX_SIZE, 0.0f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-1.28f, -BOX_SIZE / BOX_SIZE, 0.0f);

glTranslatef(1.28f, BOX_SIZE / BOX_SIZE, 0.4f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-1.28f, -BOX_SIZE / BOX_SIZE, -0.4f);

glTranslatef(1.28f, BOX_SIZE / BOX_SIZE, -0.4f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-1.28f, -BOX_SIZE / BOX_SIZE, 0.4f);

glTranslatef(1.28f, BOX_SIZE / BOX_SIZE, 0.8f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-1.28f, -BOX_SIZE / BOX_SIZE, -0.8f);

glTranslatef(1.28f, BOX_SIZE / BOX_SIZE, -0.8f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-1.28f, -BOX_SIZE / BOX_SIZE, 0.8f);

glTranslatef(1.28f, BOX_SIZE / BOX_SIZE, 1.2f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-1.28f, -BOX_SIZE / BOX_SIZE, -1.2f);

glTranslatef(1.28f, BOX_SIZE / BOX_SIZE, -1.2f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-1.28f, -BOX_SIZE / BOX_SIZE, 1.2f);

glTranslatef(0.64f, BOX_SIZE / BOX_SIZE, 0.0f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-0.64f, -BOX_SIZE / BOX_SIZE, 0.0f);


glTranslatef(0.64f, BOX_SIZE / BOX_SIZE, 0.4f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-0.64f, -BOX_SIZE / BOX_SIZE, -0.4f);

glTranslatef(0.64f, BOX_SIZE / BOX_SIZE, -0.4f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-0.64f, -BOX_SIZE / BOX_SIZE, 0.4f);

glTranslatef(0.64f, BOX_SIZE / BOX_SIZE, 0.8f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(-0.64f, -BOX_SIZE / BOX_SIZE, -0.8f);

glTranslatef(0.64f, BOX_SIZE / BOX_SIZE, -0.8f);
drawHalfSphere(50, 50, 0.200);
glTranslatef(-0.64f, -BOX_SIZE / BOX_SIZE, 0.8f);

glTranslatef(0.64f, BOX_SIZE / BOX_SIZE, 1.2f);
drawHalfSphere(50, 50, 0.200);
glTranslatef(-0.64f, -BOX_SIZE / BOX_SIZE, -1.2f);

glTranslatef(0.64f, BOX_SIZE / BOX_SIZE, -1.2f);
drawHalfSphere(50, 50, 0.200);
glTranslatef(-0.64f, -BOX_SIZE / BOX_SIZE, 1.2f);

glTranslatef(0.0f, BOX_SIZE / BOX_SIZE, 0.0f);
drawHalfSphere(50, 50, 0.380);
glTranslatef(0.0f, -BOX_SIZE / BOX_SIZE, 0.0f);

glTranslatef(0.0f, BOX_SIZE / BOX_SIZE, 0.9f);
drawHalfSphere(50, 50, 0.380);
glTranslatef(0.0f, -BOX_SIZE / BOX_SIZE, -0.9f);

glTranslatef(0.0f, BOX_SIZE / BOX_SIZE, -0.9f);
drawHalfSphere(50, 50, 0.380);
glTranslatef(0.0f, -BOX_SIZE / BOX_SIZE, 0.9f);


glTranslatef(-3.20f, BOX_SIZE / BOX_SIZE, 0.0f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(3.20f, -BOX_SIZE / BOX_SIZE, 0.0f);


glTranslatef(-3.20f, BOX_SIZE / BOX_SIZE, 0.4f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(3.20f, -BOX_SIZE / BOX_SIZE, -0.4f);

glTranslatef(-3.20f, BOX_SIZE / BOX_SIZE, -0.4f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(3.20f, -BOX_SIZE / BOX_SIZE, 0.4f);

glTranslatef(-3.20f, BOX_SIZE / BOX_SIZE, 0.8f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(3.20f, -BOX_SIZE / BOX_SIZE, -0.8f);

glTranslatef(-3.20f, BOX_SIZE / BOX_SIZE, -0.8f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(3.20f, -BOX_SIZE / BOX_SIZE, 0.8f);

glTranslatef(-3.20f, BOX_SIZE / BOX_SIZE, 1.2f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(3.20f, -BOX_SIZE / BOX_SIZE, -1.2f);

glTranslatef(-3.20f, BOX_SIZE / BOX_SIZE, -1.2f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(3.20f, -BOX_SIZE / BOX_SIZE, 1.2f);

glTranslatef(-2.56f, BOX_SIZE / BOX_SIZE, 0.0f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(2.56f, -BOX_SIZE / BOX_SIZE, 0.0f);

glTranslatef(-2.56f, BOX_SIZE / BOX_SIZE, 0.4f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(2.56f, -BOX_SIZE / BOX_SIZE, -0.4f);

glTranslatef(-2.56f, BOX_SIZE / BOX_SIZE, -0.4f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(2.56f, -BOX_SIZE / BOX_SIZE, 0.4f);

glTranslatef(-2.56f, BOX_SIZE / BOX_SIZE, 0.8f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(2.56f, -BOX_SIZE / BOX_SIZE, -0.8f);

glTranslatef(-2.56f, BOX_SIZE / BOX_SIZE, -0.8f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(2.56f, -BOX_SIZE / BOX_SIZE, 0.8f);

glTranslatef(-2.56f, BOX_SIZE / BOX_SIZE, 1.2f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(2.56f, -BOX_SIZE / BOX_SIZE, -1.2f);

glTranslatef(-2.56f, BOX_SIZE / BOX_SIZE, -1.2f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(2.56f, -BOX_SIZE / BOX_SIZE, 1.2f);

glTranslatef(-1.92f, BOX_SIZE / BOX_SIZE, 0.0f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(1.92f, -BOX_SIZE / BOX_SIZE, 0.0f);


glTranslatef(-1.92f, BOX_SIZE / BOX_SIZE, -0.4f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(1.92f, -BOX_SIZE / BOX_SIZE, 0.4f);

glTranslatef(-1.92f, BOX_SIZE / BOX_SIZE, 0.4f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(1.92f, -BOX_SIZE / BOX_SIZE, -0.4f);

glTranslatef(-1.92f, BOX_SIZE / BOX_SIZE, -0.8f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(1.92f, -BOX_SIZE / BOX_SIZE, 0.8f);

glTranslatef(-1.92f, BOX_SIZE / BOX_SIZE, 0.8f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(1.92f, -BOX_SIZE / BOX_SIZE, -0.8f);

glTranslatef(-1.92f, BOX_SIZE / BOX_SIZE, -1.2f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(1.92f, -BOX_SIZE / BOX_SIZE, 1.2f);

glTranslatef(-1.92f, BOX_SIZE / BOX_SIZE, 1.2f);
drawHalfSphere(50, 50, 0.20);
glTranslatef(1.92f, -BOX_SIZE / BOX_SIZE, -1.2f);

glTranslatef(-1.28f, BOX_SIZE / BOX_SIZE, 0.0f);
drawHalfSphere(50, 50, 0.200);
glTranslatef(1.28f, -BOX_SIZE / BOX_SIZE, 0.0f);


glTranslatef(-1.28f, BOX_SIZE / BOX_SIZE, -0.4f);
drawHalfSphere(50, 50, 0.200);
glTranslatef(1.28f, -BOX_SIZE / BOX_SIZE, 0.4f);

glTranslatef(-1.28f, BOX_SIZE / BOX_SIZE, 0.4f);
drawHalfSphere(50, 50, 0.200);
glTranslatef(1.28f, -BOX_SIZE / BOX_SIZE, -0.4f);

glTranslatef(-1.28f, BOX_SIZE / BOX_SIZE, -0.8f);
drawHalfSphere(50, 50, 0.200);
glTranslatef(1.28f, -BOX_SIZE / BOX_SIZE, 0.8f);

glTranslatef(-1.28f, BOX_SIZE / BOX_SIZE, 0.8f);
drawHalfSphere(50, 50, 0.200);
glTranslatef(1.28f, -BOX_SIZE / BOX_SIZE, -0.8f);

glTranslatef(-1.28f, BOX_SIZE / BOX_SIZE, -1.2f);
drawHalfSphere(50, 50, 0.200);
glTranslatef(1.28f, -BOX_SIZE / BOX_SIZE, 1.2f);

glTranslatef(-1.28f, BOX_SIZE / BOX_SIZE, 1.2f);
drawHalfSphere(50, 50, 0.200);
glTranslatef(1.28f, -BOX_SIZE / BOX_SIZE, -1.2f);

glTranslatef(-0.64f, BOX_SIZE / BOX_SIZE, 0.0f);
drawHalfSphere(50, 50, 0.200);
glTranslatef(0.64f, -BOX_SIZE / BOX_SIZE, 0.0f);

glTranslatef(-0.64f, BOX_SIZE / BOX_SIZE, 0.4f);
drawHalfSphere(50, 50, 0.200);
glTranslatef(0.64f, -BOX_SIZE / BOX_SIZE, -0.4f);


glTranslatef(-0.64f, BOX_SIZE / BOX_SIZE, -0.4f);
drawHalfSphere(50, 50, 0.200);
glTranslatef(0.64f, -BOX_SIZE / BOX_SIZE, 0.4f);

glTranslatef(-0.64f, BOX_SIZE / BOX_SIZE, 0.8f);
drawHalfSphere(50, 50, 0.200);
glTranslatef(0.64f, -BOX_SIZE / BOX_SIZE, -0.8f);


glTranslatef(-0.64f, BOX_SIZE / BOX_SIZE, -0.8f);
drawHalfSphere(50, 50, 0.200);
glTranslatef(0.64f, -BOX_SIZE / BOX_SIZE, 0.8f);

glTranslatef(-0.64f, BOX_SIZE / BOX_SIZE, 1.2f);
drawHalfSphere(50, 50, 0.200);
glTranslatef(0.64f, -BOX_SIZE / BOX_SIZE, -1.2f);


glTranslatef(-0.64f, BOX_SIZE / BOX_SIZE, -1.2f);
drawHalfSphere(50, 50, 0.200);
glTranslatef(0.64f, -BOX_SIZE / BOX_SIZE, 1.2f);



glPopMatrix();

glRotatef(_angle, 1.0f, 0.0f, 0.0f);

	glBegin(GL_QUADS);

	//Top face
	//glColor3f(1.0f,0.47,0.21f);
	glNormal3f(0.0, 1.0f, 0.0f);
	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / BOX_SIZE, -1.5f);

	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / BOX_SIZE, 1.5f);
	glVertex3f(BOX_SIZE / 2, BOX_SIZE / BOX_SIZE, 1.5f);
	glVertex3f(BOX_SIZE / 2, BOX_SIZE / BOX_SIZE, -1.5f);




	//Left face
	glNormal3f(-1.0, 0.0f, 0.0f);
	//glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / BOX_SIZE, -1.5f);
glColor3f(1.0f,0.47,0.21f);
	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / BOX_SIZE, 1.5f);
glColor3f(0.0f,0.0,0.00f);
	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / BOX_SIZE, 1.5f);
	glColor3f(1.0f,0.47,0.21f);
	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / BOX_SIZE, -1.5f);
	glColor3f(0.0f,0.0,0.0f);

	//Right face
	glNormal3f(1.0, 0.0f, 0.0f);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / BOX_SIZE, -1.5f);
	glColor3f(1.0f,0.47,0.21f);
	glVertex3f(BOX_SIZE / 2, BOX_SIZE / BOX_SIZE, -1.5f);
glColor3f(0.0f,0.0,0.00f);//glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(BOX_SIZE / 2, BOX_SIZE / BOX_SIZE, 1.5f);
	glColor3f(1.0f,0.47,0.21f);
	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / BOX_SIZE, 1.5f);
	glColor3f(0.0f,0.0,0.0f);



//Front face
    glNormal3f(0.0, 0.0f, 1.0f);
    	glColor3f(1.0f,0.47,0.21f);
    //glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / BOX_SIZE , 1.5f);
    glColor3f(0.0f,0.0,0.00f);
   // glTexCoord2f(1.0f, 0.0f);
    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / BOX_SIZE , 1.5f);
    glColor3f(1.0f,0.47,0.21f);
   // glTexCoord2f(1.0f, 1.0f);
    glVertex3f(BOX_SIZE / 2, BOX_SIZE / BOX_SIZE , 1.5f);
    //glTexCoord2f(0.0f, 1.0f);
    	glColor3f(1.0f,0.47,0.21f);

    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / BOX_SIZE , 1.5f);
    glColor3f(1.0f,0.47,0.21f);









    //Back face
    glNormal3f(0.0, 0.0f, -1.0f);
   // glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE /BOX_SIZE  , -1.5f);
   // glTexCoord2f(1.0f, 0.0f);
   glColor3f(0.0f,0.0,0.00f);
    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / BOX_SIZE , -1.5f);
   // glTexCoord2f(1.0f, 1.0f);
       glColor3f(1.0f,0.47,0.21f);

    glVertex3f(BOX_SIZE / 2, BOX_SIZE / BOX_SIZE , -1.5f);
   // glTexCoord2f(0.0f, 1.0f);
       glColor3f(1.0f,0.47,0.21f);

     glVertex3f(BOX_SIZE / 2, -BOX_SIZE / BOX_SIZE , -1.5f);





	glEnd();
glPushMatrix();

	glBegin(GL_TRIANGLES);
	//glNormal3f(0.0, 0.0f, 1.0f);
	glColor3f(1.0f,1.0f,0.44f);
	 glVertex3f(-3.3f, -1.0f, 1.53f);
	glColor3f(1.0f,1.0f,0.44f);

     glVertex3f(-2.9f, -1.0f, 1.53f);
   //lColor3f(0.0f,0.0,0.00f);
   glColor3f(0.0f,0.0,0.00f);
     glVertex3f(-3.3f, 0.0f, 1.53f);

     glVertex3f(-2.9f, -1.0f, 1.53f);
	glColor3f(1.0f,1.0f,0.44f);
     glVertex3f(-2.9f, 0.0f, 1.53f);
    // glColor3f(0.0f,0.0,0.00f);
    glColor3f(0.0f,0.0,0.00f);
     glVertex3f(-3.3f, 0.0f, 1.53f);
	glColor3f(1.0f,1.0f,0.44f);


     glVertex3f(-3.1f,   0.2f, 1.53f);

	//glColor3f(1.0f,1.0f,0.44f);
     glVertex3f(-2.9f, 0.0f, 1.53f);
    // glColor3f(0.0f,0.0,0.00f);
     glColor3f(0.0f,0.0,0.00f);
     glVertex3f(-3.3f,  0.0f, 1.53f);
	//glColor3f(1.0f,1.0f,0.44f);



     glVertex3f(-2.70f, -1.0f, 1.56f);
	glColor3f(1.0f,1.0f,0.44f);
     glVertex3f(-2.30f, -1.0f, 1.56f);
	glColor3f(1.0f,1.0f,0.44f);
     glVertex3f(-2.70f, 0.0f, 1.56f);

     glVertex3f(-2.30f, -1.0f, 1.56f);
	glColor3f(1.0f,1.0f,0.44f);
     glVertex3f(-2.30f, 0.0f, 1.56f);
     glVertex3f(-2.70f, 0.0f, 1.56f);

	glColor3f(1.0f,1.0f,0.44f);
     glVertex3f(-2.50f,   0.2f, 1.56f);
     glVertex3f(-2.30f, 0.0f, 1.56f);
     glVertex3f(-2.70f,  0.0f, 1.56f);



     glVertex3f(-2.10f, -1.0f, 1.57f);
     glVertex3f(-1.70f, -1.0f, 1.57f);
     glVertex3f(-2.10f, 0.0f, 1.57f);

     glVertex3f(-1.70f, -1.0f, 1.57f);
     glVertex3f(-1.70f, 0.0f, 1.57f);
     glVertex3f(-2.10f, 0.0f, 1.57f);

     glVertex3f(-1.90f,   0.2f, 1.57f);
     glVertex3f(-1.70f, 0.0f, 1.57f);
     glVertex3f(-2.10f,  0.0f, 1.57f);


     glVertex3f(-1.50f, -1.0f, 1.58f);
     glVertex3f(-1.10f, -1.0f, 1.58f);
     glVertex3f(-1.50f, 0.0f, 1.58f);

     glVertex3f(-1.10f, -1.0f, 1.58f);
     glVertex3f(-1.10f, 0.0f, 1.58f);
     glVertex3f(-1.50f, 0.0f, 1.58f);

     glVertex3f(-1.30f,   0.2f, 1.58f);
     glVertex3f(-1.10f, 0.0f, 1.58f);
     glVertex3f(-1.50f,  0.0f, 1.58f);

     glVertex3f(-0.90f, -1.0f, 1.59f);
     glVertex3f(-0.50f, -1.0f, 1.59f);
     glVertex3f(-0.90f, 0.0f, 1.59f);

     glVertex3f(-0.50f, -1.0f, 1.59f);
     glVertex3f(-0.50f, 0.0f, 1.59f);
     glVertex3f(-0.90f, 0.0f, 1.59f);

     glVertex3f(-0.70f,   0.2f, 1.59f);
     glVertex3f(-0.50f, 0.0f, 1.59f);
     glVertex3f(-0.90f,  0.0f, 1.59f);



     glVertex3f(-0.40f, -1.0f, 1.60f);
     glVertex3f(0.30f, -1.0f, 1.60f);
     glVertex3f(-0.40f, 0.0f, 1.60f);

     glVertex3f(0.30f, -1.0f, 1.60f);
     glVertex3f(0.30f, 0.0f, 1.60f);
     glVertex3f(-0.40f, 0.0f, 1.60f);

     glVertex3f(-0.05f,   0.5f, 1.60f);
     glVertex3f(0.30f, 0.0f, 1.60f);
     glVertex3f(-0.40f,  0.0f, 1.60f);


     glVertex3f(0.40f, -1.0f, 1.57f);
     glVertex3f(0.80f, -1.0f, 1.57f);
     glVertex3f(0.40f, 0.0f, 1.57f);

     glVertex3f(0.80f, -1.0f, 1.57f);
     glVertex3f(0.80f, 0.0f, 1.57f);
     glVertex3f(0.40f, 0.0f, 1.57f);

     glVertex3f(0.60f,   0.2f, 1.57f);
     glVertex3f(0.80f, 0.0f, 1.57f);
     glVertex3f(0.40f,  0.0f, 1.57f);


     glVertex3f(1.0f, -1.0f, 1.58f);
     glVertex3f(1.40f, -1.0f, 1.58f);
     glVertex3f(1.0f, 0.0f, 1.58f);

     glVertex3f(1.40f, -1.0f, 1.58f);
     glVertex3f(1.40f, 0.0f, 1.58f);
     glVertex3f(1.00f, 0.0f, 1.58f);

     glVertex3f(1.2f,   0.2f, 1.58f);
     glVertex3f(1.40f, 0.0f, 1.58f);
     glVertex3f(1.0f,  0.0f, 1.58f);



     glVertex3f(2.0f, -1.0f, 1.570f);
     glVertex3f(1.60f, -1.0f, 1.570f);
     glVertex3f(2.0f, 0.0f, 1.570f);

     glVertex3f(1.60f, -1.0f, 1.570f);
     glVertex3f(1.60f, 0.0f, 1.570f);
     glVertex3f(2.00f, 0.0f, 1.570f);

     glVertex3f(1.8f,   0.2f, 1.570f);
     glVertex3f(1.60f, 0.0f, 1.570f);
     glVertex3f(2.0f,  0.0f, 1.570f);


     glVertex3f(2.2f, -1.0f, 1.571f);
     glVertex3f(2.60f, -1.0f, 1.571f);
     glVertex3f(2.2f, 0.0f, 1.571f);

     glVertex3f(2.60f, -1.0f, 1.571f);
     glVertex3f(2.60f, 0.0f, 1.571f);
     glVertex3f(2.2f, 0.0f, 1.571f);

     glVertex3f(2.4f,   0.2f, 1.571f);
     glVertex3f(2.60f, 0.0f, 1.571f);
     glVertex3f(2.2f,  0.0f, 1.571f);


     glVertex3f(3.2f, -1.0f, 1.572f);
     glVertex3f(2.80f, -1.0f, 1.572f);
     glVertex3f(3.2f, 0.0f, 1.572f);

     glVertex3f(2.80f, -1.0f, 1.572f);
     glVertex3f(2.80f, 0.0f, 1.572f);
     glVertex3f(3.2f, 0.0f, 1.572f);

     glVertex3f(3.0f,   0.2f, 1.572f);
     glVertex3f(2.80f, 0.0f, 1.572f);
     glVertex3f(3.2f,  0.0f, 1.572f);







	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}

void update(int value) {
	_angle += 1.5f;
	if (_angle > 360) {
		_angle -= 360;
	}

	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(900, 700);

	//Create the window
	glutCreateWindow("project");
	glColor3f(0.517f, 0.756f, 1.0f);
	initRendering();

	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutTimerFunc(25, update, 0); //Add a timer

	glutMainLoop();
	return 0;
}









