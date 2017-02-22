#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <math.h>
/* Global variables */
char title[] = "3D Shapes with animation";
GLfloat anglePyramid = 0.0f;  // Rotational angle for pyramid [NEW]
GLfloat angleCube = 0.0f;     // Rotational angle for cube [NEW]
int refreshMills = 1000;        // refresh interval in milliseconds [NEW]

/* Initialize OpenGL Graphics */
void initGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
GLfloat angle = 0.0f;
GLfloat x = 1.8*cos(angle);
GLfloat y = 1.8*sin(angle);
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

    // Render a color-cube consisting of 6 quads with different colors
    glLoadIdentity();                 // Reset the model-view matrix
    glTranslatef(0.0f, 0.0f, -5.0f);  // Move right and into the screen
    //glRotatef(angleCube, 1.0f, 1.0f, 1.0f);  // Rotate about (1,1,1)-axis [NEW]
    // Rotate about the (1,1,0)-axis [NEW]

    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 1.0f);
    for(double i = 0.0; i<360.0; i=i+0.1)      // Select points as the primitive
    {
        glVertex3f(2.0*cos(i), 2.0*sin(i), 0.0f);

    }
    // Specify a point
    //glVertex3f(50.0f, 50.0f, 50.0f);   // Specify another point
    glEnd();

    // Done drawing the pyramid

    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 1.0f);
    for(double i = 0.0; i<=360.0; i=i+6.0)      // Select points as the primitive
    {
        glVertex3f(1.8*cos(i), 1.8*sin(i), 0.0f);

    }
    // Specify a point
    //glVertex3f(50.0f, 50.0f, 50.0f);   // Specify another point
    glEnd();


    glBegin(GL_LINES);
    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(angle, x, y, 1.0f);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(x, y, 0.0f);
    glEnd();

    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
    angle = anglePyramid + 1.0;
    x = 1.8*cos(angle);
    y = 1.8*sin(angle);
    // Update the rotational angle after each refresh [NEW]

}

/* Called back when timer expired [NEW] */
void timer(int value)
{
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height)    // GLsizei for non-negative integer
{
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(640, 480);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow(title);          // Create window with the given title
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    initGL();                       // Our own OpenGL initialization
    glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]
    glutMainLoop();                 // Enter the infinite event-processing loop
    return 0;
}
