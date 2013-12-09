/*
 * Adapted from: 
 * GL07BouncingBall.cpp: A ball bouncing inside the window
 ********************************************************************
 * Compile this with:
 * g++ -std=c++0x -c -o anim.o anim.cpp -D FREEGLUT_STATIC -I"C:\MinGW\freeglut\include"
 * g++ -std=c++0x -c -o Swarm.o Swarm.cpp
 * g++ -std=c++0x -o anim.exe anim.o Swarm.o -L"C:\MinGW\freeglut\lib" -lfreeglut_static -lopengl32 -lwinmm -lgdi32 -lglu32 -Wl,--subsystem,windows
 *
 */
#include <iostream>
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <Math.h>     // Needed for sin, cos
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "Swarm.h"
#define PI 3.14159265f
typedef std::vector< std::vector<float> > vvfloat;

// Global variables
char title[] = "Bouncing Ball (2D)";  // Windowed mode's title
int windowWidth  = 640;     // Windowed mode's width
int windowHeight = 480;     // Windowed mode's height
int windowPosX   = 50;      // Windowed mode's top-left corner x
int windowPosY   = 50;      // Windowed mode's top-left corner y
 
GLfloat ballRadius = 0.125f; // Radius of the bouncing ball
GLfloat ballX = 0.0f;         // Ball's center (x, y) position
GLfloat ballY = 0.0f;
GLfloat ballXMax, ballXMin, ballYMax, ballYMin; // Ball's center (x, y) bounds
GLfloat xSpeed = 0.02f;      // Ball's speed in x and y directions
GLfloat ySpeed = 0.007f;
int refreshMillis = 30;      // Refresh period in milliseconds
Swarm s = Swarm(10);

// Projection clipping area
GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;
 
/* Initialize OpenGL Graphics */
void initGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background (clear) color to black
}
 
/* Callback handler for window re-paint event */
void display() {
    int numSegments = 100;
    GLfloat angle;
    vvfloat v;
    v = s.getBoids();
    std::vector<float> firstboid = v[0];
    std::cout<<firstboid[0]<<" "<<firstboid[1]<<std::endl;
     
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer
    glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
    glLoadIdentity();              // Reset model-view matrix
 
    // glTranslatef(ballX, ballY, 0.0f);  // Translate to (xPos, yPos)
    glTranslatef((GLfloat)firstboid[0],
		 (GLfloat)firstboid[1],
		 0.0f);  // Translate to (xPos, yPos)

    // Use triangular segments to form a circle
    glBegin(GL_TRIANGLE_FAN);
    glColor3f((((float)rand() % RAND_MAX) / RAND_MAX),
	      (((float)rand() % RAND_MAX) / RAND_MAX),
	      (((float)rand() % RAND_MAX) / RAND_MAX)); // random colour
    
    glVertex2f(0.0f, 0.0f);       // Center of circle

     
    for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
	angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
	glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
    }
    glEnd();
 
    glutSwapBuffers();  // Swap front and back buffers (of double buffered mode)
}
 
/* Call back when the windows is re-sized */
void reshape(GLsizei width, GLsizei height) {
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);
 
    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset the projection matrix
    if (width >= height) {
	clipAreaXLeft   = -1.0 * aspect;
	clipAreaXRight  = 1.0 * aspect;
	clipAreaYBottom = -1.0;
	clipAreaYTop    = 1.0;
    } else {
	clipAreaXLeft   = -1.0;
	clipAreaXRight  = 1.0;
	clipAreaYBottom = -1.0 / aspect;
	clipAreaYTop    = 1.0 / aspect;
    }
    gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
    ballXMin = clipAreaXLeft + ballRadius;
    ballXMax = clipAreaXRight - ballRadius;
    ballYMin = clipAreaYBottom + ballRadius;
    ballYMax = clipAreaYTop - ballRadius;
}
 
/* Called back when the timer expired */
void Timer(int value) {
    glutPostRedisplay();    // Post a paint request to activate display()
    glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
    srand(time(NULL));
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(windowWidth, windowHeight);  // Initial window width and height
    glutInitWindowPosition(windowPosX, windowPosY); // Initial window top-left corner (x, y)
    glutCreateWindow(title);      // Create window with given title
    glutDisplayFunc(display);     // Register callback handler for window re-paint
    glutReshapeFunc(reshape);     // Register callback handler for window re-shape
    glutTimerFunc(0, Timer, 0);   // First timer call immediately
    initGL();                     // Our own OpenGL initialization
    glutMainLoop();               // Enter event-processing loop
    return 0;
}
