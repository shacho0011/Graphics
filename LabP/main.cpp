/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* File for "Lighting" lesson of the OpenGL tutorial on
 * www.videotutorialsrock.com
 */



#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

int light = 0;
float fontBack = 1.0f;
float hc1=1.0f;
float hc2=-1.0f;


//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: //Escape key
        exit(0);
        break;
    case 'x':
        if (light == 0)
        {
            light = 1;
            hc1=-1.0f;
            hc2=1.0f;
        }
        else if(light == 1)
        {
            light = 0;
            hc1=1.0f;
            hc2=-1.0f;
        }
        break;

    case 'f':
        fontBack = 1.0f;
        break;
    case 'b':
        fontBack = -1.0f;
        break;
    }
    glutPostRedisplay();
}

//Initializes 3D rendering
void initRendering()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    //glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);
//    glEnable(GL_LIGHT2);
    glEnable(GL_NORMALIZE);
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

float xP=0.7f;
float xN=-0.7f;
int xF=0;
float r=1.0f;
float g=0.0f;
float b=0.0f;
int rF=1;
int gF=0;
int bF=0;

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -8.0f);

    //Add ambient light
    GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);



    GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    //Add directed light
    GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
    //Coming from the direction (-1, 0.5, 0.5)
    GLfloat lightPos1[] = {2.0f, 1.0f, 0.5f, -1.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);


    /*
            GLfloat lightColor3[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Color (0.5, 0.5, 0.5)
            GLfloat lightPos3[] = {-4.0f, xP, 8.0f, hc2}; //Positioned at (4, 0, 8)
            glLightfv(GL_LIGHT3, GL_DIFFUSE, lightColor3);
            glLightfv(GL_LIGHT3, GL_POSITION, lightPos3);
    */
    //Add directed light
    GLfloat lightColor4[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
    //Coming from the direction (-1, 0.5, 0.5)
    GLfloat lightPos4[] = {-3.5f, xP, -2.0f, hc2};
    glLightfv(GL_LIGHT4, GL_DIFFUSE, lightColor4);
    glLightfv(GL_LIGHT4, GL_POSITION, lightPos4);


    //Add positioned light
    glPushMatrix();
    glRotatef(45.0f,0.0f,1.0f,0.0f);
    glTranslatef(0.0f,1.0f,-2.0f);
    glBegin(GL_QUADS);

    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(-2.0f, xN, 0.0f);
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(-1.0f, xN, 0.0f);
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(-1.0f, xP, 0.0f);
    glColor3f(1.0f,0.0f,1.0f);
    glVertex3f(-2.0f, xP, 0.0f);
    glEnd();
    glPopMatrix();

//    glColor3f(1.0f,0.0f,1.0f);
    glColor3f(r,g,b);
    glBegin(GL_TRIANGLES);
    glVertex3f(2.0f, 0.5f, 0.0f);
    glVertex3f(1.5f, 1.5f, 0.0f);
    glVertex3f(2.5f, 0.5f, 0.0f);
    glEnd();

    glutSwapBuffers();
}

void update(int value)
{

    if(xF==0)
    {
        xP=xP+0.1;
        xN=xN+0.1;
        if(xP>=2.0)
        {
            xF=1;
        }
    }
    else if(xF==1)
    {
        xP=xP-0.1;
        xN=xN-0.1;
        if(xN<=-2.0)
        {
            xF=0;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(25,update,0);
}

void updateC(int value)
{
    if(rF==1)
    {
        r=1.0f;
        g=0.0f;
        b=0.0f;
        rF=0;
        gF=1;
        bF=0;
    }
    else if(gF==1)
    {
        r=0.0f;
        g=1.0f;
        b=0.0f;
        rF=0;
        gF=0;
        bF=1;
    }
    else if(bF==1)
    {
        r=0.0f;
        g=0.0f;
        b=1.0f;
        rF=0;
        gF=0;
        bF=0;
    }
    else if(rF==0&&gF==0&&bF==0)
    {
        r=0.0f;
        g=0.0f;
        b=0.0f;
        rF=1;
        gF=0;
        bF=0;
    }
    glutPostRedisplay();
    glutTimerFunc(1000,updateC,0);
}



int main(int argc, char** argv)
{
    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 600);

    //Create the window
    glutCreateWindow("Lighting - videotutorialsrock.com");
    initRendering();

    //Set handler functions
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);

    glutTimerFunc(25,update,0);
    glutTimerFunc(1000,updateC,0);

    glutMainLoop();
    return 0;
}









