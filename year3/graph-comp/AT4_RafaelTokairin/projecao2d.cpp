#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int baseCoord = 300;
float pulseFactor = 1.0f;
float verticalShift = -100.0f;
float pulseDirection = 1.0f;
float horizontalShift = 100.0f;

void updateMovement(int value);
void drawTriangle();
void drawAxes();
void init(void);
void renderScene(void);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Transformações 2D");

    init();

    glutDisplayFunc(renderScene);
    glutTimerFunc(60, updateMovement, 0);

    glutMainLoop();
    return 0;
}

void drawTriangle() {
    glBegin(GL_TRIANGLES);
        glVertex2i(0, 50);
        glVertex2i(50, -50);
        glVertex2i(-50, -50);
    glEnd();
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 600, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
    drawAxes();
    
    glViewport(0, baseCoord, baseCoord, baseCoord);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
    glColor3f(0.6f, 0.1f, 0.1f); 
    drawTriangle();
    
    glViewport(baseCoord, baseCoord, baseCoord, baseCoord);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0f * pulseFactor, 100.0f * pulseFactor, -100.0f * pulseFactor, 100.0f * pulseFactor);
    glColor3f(0.1f, 0.6f, 0.1f); 
    drawTriangle();
    
    glViewport(baseCoord, 0, baseCoord, baseCoord);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0f + horizontalShift, 100.0f + horizontalShift, -100.0f, 100.0f);
    glColor3f(0.9f, 0.9f, 0.1f); 
    drawTriangle();
    
    glViewport(0, 0, baseCoord, baseCoord);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0f, 100.0f, -100.0f + verticalShift, 100.0f + verticalShift);
    glColor3f(0.1f, 0.1f, 0.6f); 
    drawTriangle();
    
    glutSwapBuffers();
}

void drawAxes() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(-100.0f, 0.0f);
        glVertex2f(100.0f, 0.0f);
        glVertex2f(0.0f, -100.0f);
        glVertex2f(0.0f, 100.0f);
    glEnd();
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void updateMovement(int value) {
    pulseFactor += 0.05f * pulseDirection;
    if (pulseFactor > 4.0f || pulseFactor < 0.5f) pulseDirection = -pulseDirection;
    horizontalShift -= 2.0f;
    if (horizontalShift < -200.0f) horizontalShift = 200.0f;
    verticalShift += 2.0f;
    if (verticalShift > 200.0f) verticalShift = -200.0f;
    glutPostRedisplay();
    glutTimerFunc(30, updateMovement, 0);
}
