// coodinate.cpp
#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"
#include <stdio.h>

/// <summary>
/// draw coordinate
/// </summary>
void drawCoodinate()
{
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-10000.0, 0.0, 0.0);
    glVertex3f(10000.0, 0.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0, -10000.0, 0.0);
    glVertex3f(0.0, 10000.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0, 0.0, -10000.0);
    glVertex3f(0.0, 0.0, 10000.0);
    glEnd();
}