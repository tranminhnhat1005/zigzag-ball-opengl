// box.cpp
#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"
#include <stdio.h>

/// <summary>
/// make a 3d box
/// </summary>
/// <param name="length"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <returns></returns>
GLint MakeBox(const float length, const float width, const float height)
{
    GLint dp_list;
    dp_list = glGenLists(1);
    glNewList(dp_list, GL_COMPILE);
    float x = length;
    float y = height;
    float z = width;

    //Back
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(x, 0, 0);
    glVertex3f(x, y, 0);
    glVertex3f(0, y, 0);
    glEnd();

    // left
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, z);
    glVertex3f(0, y, z);
    glVertex3f(0, y, 0);
    glEnd();

    //front
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0, 0, z);
    glVertex3f(0, y, z);
    glVertex3f(x, y, z);
    glVertex3f(x, 0, z);
    glEnd();

    //// right
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(x, 0, z);
    glVertex3f(x, 0, 0);
    glVertex3f(x, y, 0);
    glVertex3f(x, y, z);
    glEnd();

    //Top
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0, y, 0);
    glVertex3f(x, y, 0);
    glVertex3f(x, y, z);
    glVertex3f(0, y, z);

    //Bottom
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(x, 0, 0);
    glVertex3f(x, 0, z);
    glVertex3f(0, 0, z);

    glEnd();

    glEndList();

    return dp_list;
}