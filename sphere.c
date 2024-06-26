// Function to draw text on the screen
#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <GL/freeglut.h>

// Constants
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

// Variables
GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;
float zoomFactor = 1.0f;
int lastMouseX;
int lastMouseY;
bool mouseDown = false;

void drawText(float x, float y, float z, char *text)
{
    glColor3f(1.0f, 1.0f, 1.0f); // Set text color to white
    float xStart = x;
    float yStart = y;

    glRasterPos3f(xStart, yStart, z);
    while (*text)
    {

        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text); // Using larger font size
        text++;
    }
}
// Function to draw a sphere
void drawSphere(float radius, int slices, int stacks, GLfloat color[3], GLfloat x, GLfloat y, GLfloat z, char *text)
{
    drawText(x + radius, y, z + 0.601, text);
    glEnable(GL_COLOR_MATERIAL); // Enable color tracking for ambient and diffuse properties
    glColor3fv(color);           // Set sphere color
    glPushMatrix();
    glTranslatef(x, y, z); // Move sphere
    glutSolidSphere(radius, slices, stacks);
    glPopMatrix();
}

// Function to draw a line between two points
void drawLine(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat color[3])
{
    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glEnable(GL_LIGHTING);   // Enable lighting
    glEnable(GL_LIGHT0);     // Enable light source 0 (adjust as needed)

    GLfloat lineThickness = 10.0f; // Adjust line thickness as needed

    glLineWidth(lineThickness); // Set line thickness

    // Set material properties (ambient, diffuse, specular)
    GLfloat materialAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat materialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat materialSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat materialShininess = 100.0f; // Adjust shininess as needed

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);

    // Set line color
    glColor3fv(color);

    // Define line vertices
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
    glEnable(GL_LIGHTING); // Enable lighting
    glEnable(GL_LIGHT0);   // Enable light source 0

    // Set light source properties
    GLfloat lightPosition[] = {10.0f, 10.0f, 10.0f, 1.0f}; // Position of the light source
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // Set material properties for the sphere
    GLfloat materialAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};  // Ambient reflection
    GLfloat materialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};  // Diffuse reflection
    GLfloat materialSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Specular reflection
    GLfloat materialShininess[] = {100.0f};                // Shininess (specular exponent)

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);

    glEnable(GL_DEPTH_TEST);              // Enable depth testing for 3D rendering
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

// Function to render scene
// void display()
// {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glLoadIdentity();
//     gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); // Set camera position

//     glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotate around X axis
//     glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotate around Y axis

//     // Draw first sphere (red)
//     GLfloat redColor[3] = {1.0f, 0.0f, 0.0f};
//     drawSphere(0.6f, 30, 30, redColor, -2.0f, 0.0f, 0.0f,"1");

//     // Draw second sphere (green)
//     GLfloat greenColor[3] = {0.0f, 1.0f, 0.0f};
//     drawSphere(0.6f, 30, 30, greenColor, 2.0f, 0.0f, 0.0f,"2" );

//     // Draw third sphere (blue)
//     GLfloat blueColor[3] = {0.0f, 0.0f, 1.0f};
//     drawSphere(0.6f, 30, 30, blueColor, 0.0f, 2.0f, 0.0f,"Bhavya" );
//     drawSphere(0.6f, 30, 30, blueColor, -3.0f, -2.0f, 0.0f,"4" );
//     drawSphere(0.6f, 30, 30, blueColor, -1.0f, -4.0f, 0.0f,"5" );
//     drawSphere(0.6f, 30, 30, greenColor, -1.0f, -2.0f, 0.0f,"6" );

//     // Draw connection line between the spheres
//     GLfloat lineColor[3] = {1.0f, 1.0f, 1.0f}; // White color
//     drawLine(-2.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, lineColor);
//     drawLine(2.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, lineColor);
//     drawLine(-2.0f, 0.0f, 0.0f, -3.0f, -2.0f, 0.0f, lineColor);
//     drawLine(-2.0f, 0.0f, 0.0f, -1.0f, -2.0f, 0.0f, lineColor);
//     drawLine(-1.0f, -2.0f, 0.0f, -1.0f, -4.0f, 0.0f, lineColor);

//     glutSwapBuffers();
// }

// Function to handle window resizing
void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void zoomIn()
{
    // Decrease the zoom factor
    zoomFactor *= 0.9f; // You can adjust the factor as needed

    // Update the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Apply the zoom factor
    gluPerspective(45.0f * zoomFactor, 16.0f / 9.0f, 0.1f, 100.0f); // Adjust the field of view angle (45.0f) based on your scene

    // Switch back to modelview matrix
    glMatrixMode(GL_MODELVIEW);

    // Request a redraw
    glutPostRedisplay();
}

void zoomOut()
{
    // Decrease the zoom factor
    zoomFactor /= 0.9f; // You can adjust the factor as needed

    // Update the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Apply the zoom factor
    gluPerspective(45.0f * zoomFactor, 16.0f / 9.0f, 0.1f, 100.0f); // Adjust the field of view angle (45.0f) based on your scene

    // Switch back to modelview matrix
    glMatrixMode(GL_MODELVIEW);

    // Request a redraw
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == '+')
    {
        zoomIn();
    }
    if (key == '-')
    {
        zoomOut();
    }
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
//     glutKeyboardFunc(keyboard);

//     initGL();

//     glutMainLoop();

//     return 0;
// }
//
