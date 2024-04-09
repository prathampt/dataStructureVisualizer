// Function to draw text on the screen
#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>
#include<stdio.h>
// Constants
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Variables
GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;
int lastMouseX;
int lastMouseY;
bool mouseDown = false;

void drawText(float x, float y, float z, char* text)
{
    glColor3f(1.0f, 1.0f, 1.0f); // Set text color to white
    int xStart = x;
    int yStart = y;
 
    glRasterPos3f(xStart, yStart, z);
    while (*text)
    {

        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text); // Using larger font size
        text++;
    }
}
// Function to draw a sphere
void drawSphere(float radius, int slices, int stacks, GLfloat color[3], GLfloat x, GLfloat y, GLfloat z, char* text)
{
    drawText(x, y, z+0.75, text);
    drawText(x, y, z-0.75, text);
    glColor3fv(color); // Set sphere color
    glPushMatrix();
    glTranslatef(x, y, z); // Move sphere
    glutSolidSphere(radius, slices, stacks);
    glPopMatrix();
}

// Function to draw a line between two points
void drawLine(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat color[3])
{
    glColor3fv(color); // Set line color
    glBegin(GL_LINES);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glEnd();

}


// Function to handle mouse movement
void mouseMovement(int x, int y)
{
    if (mouseDown)
    {
        int deltaX = x - lastMouseX;
        int deltaY = y - lastMouseY;
        angleY += deltaX * 0.1f;
        angleX += deltaY * 0.1f;
        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}

// Function to handle mouse click
void mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            mouseDown = true;
            lastMouseX = x;
            lastMouseY = y;
        }
        else if (state == GLUT_UP)
        {
            mouseDown = false;
        }
    }
}

// Function to initialize OpenGL
void initGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
    glEnable(GL_DEPTH_TEST);              // Enable depth testing for 3D rendering
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

// Function to render scene
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); // Set camera position

    glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotate around X axis
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotate around Y axis

    // Draw first sphere (red)
    GLfloat redColor[3] = {1.0f, 0.0f, 0.0f};
    drawSphere(0.6f, 30, 30, redColor, -2.0f, 0.0f, 0.0f,"1");

    // Draw second sphere (green)
    GLfloat greenColor[3] = {0.0f, 1.0f, 0.0f};
    drawSphere(0.6f, 30, 30, greenColor, 2.0f, 0.0f, 0.0f,"2" );

    // Draw third sphere (blue)
    GLfloat blueColor[3] = {0.0f, 0.0f, 1.0f};
    drawSphere(0.6f, 30, 30, blueColor, 0.0f, 2.0f, 0.0f,"Bhavya" );
    drawSphere(0.6f, 30, 30, blueColor, -3.0f, -2.0f, 0.0f,"4" );
    drawSphere(0.6f, 30, 30, blueColor, -1.0f, -4.0f, 0.0f,"5" );
    drawSphere(0.6f, 30, 30, greenColor, -1.0f, -2.0f, 0.0f,"6" );

    // Draw connection line between the spheres
    GLfloat lineColor[3] = {1.0f, 1.0f, 1.0f}; // White color
    drawLine(-2.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, lineColor);
    drawLine(2.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, lineColor);
    drawLine(-2.0f, 0.0f, 0.0f, -3.0f, -2.0f, 0.0f, lineColor);
    drawLine(-2.0f, 0.0f, 0.0f, -1.0f, -2.0f, 0.0f, lineColor);
    drawLine(-1.0f, -2.0f, 0.0f, -1.0f, -4.0f, 0.0f, lineColor);

    glutSwapBuffers();
}

// Function to handle window resizing
void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

// int main(int argc, char **argv)
// {
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//     glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
//     glutCreateWindow("OpenGL Spheres with Connection Line");

//     glutDisplayFunc(display);
//     glutReshapeFunc(reshape);
//     glutMotionFunc(mouseMovement);
//     glutMouseFunc(mouseButton);

//     initGL();

//     glutMainLoop();

//     return 0;
// }
