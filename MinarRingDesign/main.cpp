#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1415927

/************************** draw_cylinder() **************************
 * This function will draw the cylinder
 *
 *   @parameter1: radius = The radius of cylinder
 *   @parameter2: height = Height of the cylinder
 *   @parameter3: R = Red value of the cylinder's color
 *   @parameter4: G = Green value of the cylinder's color
 *   @parameter5: B = Blue value of the cylinder's color
 *
 *   @return: Nothing
 */

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

/**************************** display() ******************************
 * The glut callback function to draw the polygons on the screen.
 *
 *   @parameter1: Nothing
 *
 *   @return: Nothing
 */
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0,-0.4,-3.0);
    glRotatef(-70, 1.0, 0.0, 0.0);
    draw_ring_design(0.51, 1.00, 10, 10, 40);
    draw_ring_design(0.52, 1.01, 20, 20, 50);
    draw_ring_design(0.53, 1.02, 30, 30, 60);
    draw_ring_design(0.54, 1.03, 40, 40, 70);
    draw_ring_design(0.55, 1.04, 50, 50, 80);
    draw_ring_design(0.55, 1.05, 50, 50, 80);
    draw_ring_design(0.54, 1.06, 40, 40, 70);
    draw_ring_design(0.53, 1.07, 30, 30, 60);
    draw_ring_design(0.52, 1.08, 20, 20, 50);
    draw_ring_design(0.51, 1.09, 10, 10, 40);

    glFlush();
}

/**************************** reshape() ******************************
 * The glut callback function that responsible when the window is
 * resized.
 *
 *   @parameter1: width  = Current window's width
 *   @parameter2: height = Current window's height
 *
 *   @return: Nothing
 */
void reshape(int width, int height)
{
    if (width == 0 || height == 0) return;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLdouble)width/(GLdouble)height,
                   0.5, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, width, height);
}


int main(int argc, char **argv)
{
    /** Initialize glut */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutCreateWindow("Create Cylinder");
    glClearColor(0.0,0.0,0.0,0.0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
