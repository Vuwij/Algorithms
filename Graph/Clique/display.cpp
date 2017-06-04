/* 
 * File:   display.cpp
 * Author: vuwij
 * 
 * Created on June 18, 2016, 6:47 PM
 */

#include "display.h"
#include <math.h>
#include <string>

using namespace std;

#define PI 3.1415926535897932384626433832795
#define NODERADIUS 3

void drawNode(int x, int y, string color) {
    glBegin(GL_QUADS);
    glVertex2i(x-NODERADIUS, x-NODERADIUS);
    glVertex2i(x-NODERADIUS, x+NODERADIUS);
    glVertex2i(x+NODERADIUS, x+NODERADIUS);
    glVertex2i(x+NODERADIUS, x-NODERADIUS);
    glEnd();
}

void display(void) {

    //clear white, draw with black
    glClearColor(255, 255, 255, 0);
    glColor3d(0, 0, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //this draws a square using vertices
    
    drawNode(0,0,"");
    drawNode(15,15,"");
    drawNode(30,30,"");
    
    glutSwapBuffers();
}

void reshape(int width, int height) {

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //set the coordinate system, with the origin in the top left
    gluOrtho2D(0, width, height, 0);
    glMatrixMode(GL_MODELVIEW);

}

void idle(void) {

    glutPostRedisplay();
}

int mainGL(int argc, char** argv) {

    //a basic set up...
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);

    //create the window, the argument is the title
    glutCreateWindow("GLUT program");

    //pass the callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();

    //we never get here because glutMainLoop() is an infinite loop
    return 0;

}
