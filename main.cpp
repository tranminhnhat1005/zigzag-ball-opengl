// main.cpp
#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"
#include <conio.h>
#include <stdio.h>
#include <sys/timeb.h>
#include <sys/utime.h>
#include <stdlib.h>
#include <math.h>
#include "sleep.h"
#include "random_float.h"
#include "random_int.h"
#include "cube.h"
#include "box.h"
using namespace std;

static int year = 0, day = 0;
const int length = 100;
int maxFrame = 120;
int chuky = 1000 / maxFrame;
int x = 1;
int direction = 1;
int border[length][4];
int road[length];
int crazyArray[length][4][2];
int score;
char scores[100];
double camX = -3.0, camY = 3.0, camZ = 3.0, centerX = 0.0, centerY = 0.0, centerZ = 0.0;
float x_ball = 0.0f, y_ball = 0.2f, z_ball = 0.0f, x_speed = 0.04f, y_speed = 0.04f, z_speed = 0.04f;
bool playing = false;
bool game_over = false;

/// <summary>
/// function to setting value for road
/// </summary>
void setting_road_value() {
    road[0] = 2;
    for (int i = 1; i < length; i++) {
        road[i] = int_rand(1, 5);
    }
}

/// <summary>
/// function to setting value for array
/// </summary>
void setting_array_value() {
    crazyArray[0][0][0] = 0;
    crazyArray[0][0][1] = 2;
    crazyArray[0][1][0] = 2;
    crazyArray[0][1][1] = 2;
    crazyArray[0][2][0] = 2;
    crazyArray[0][2][1] = 0;
    crazyArray[0][3][0] = 0;
    crazyArray[0][3][1] = 0;
    // setting border
    border[0][0] = 2;
    border[0][1] = 2;
    border[0][2] = 0;
    border[0][3] = 0;

    for (int i = 1; i < length; i++) {
        if (i % 2 == 1) {
            // A
            crazyArray[i][0][0] = crazyArray[i-1][0][0] + road[i-1] - 1;
            crazyArray[i][0][1] = crazyArray[i-1][0][1] + road[i];
            // B
            crazyArray[i][1][0] = crazyArray[i-1][1][0];
            crazyArray[i][1][1] = crazyArray[i-1][1][1] + road[i];
            // C
            crazyArray[i][2][0] = crazyArray[i-1][1][0];
            crazyArray[i][2][1] = crazyArray[i-1][1][1];
            // D
            crazyArray[i][3][0] = crazyArray[i-1][1][0] - 1;
            crazyArray[i][3][1] = crazyArray[i-1][1][1];
        } else {
            // A
            crazyArray[i][0][0] = crazyArray[i-1][1][0];
            crazyArray[i][0][1] = crazyArray[i-1][1][1];
            // B
            crazyArray[i][1][0] = crazyArray[i-1][1][0] + road[i];
            crazyArray[i][1][1] = crazyArray[i-1][1][1];
            // C
            crazyArray[i][2][0] = crazyArray[i-1][2][0] + road[i];
            crazyArray[i][2][1] = crazyArray[i-1][2][1] + road[i-1] - 1;
            // D
            crazyArray[i][3][0] = crazyArray[i-1][3][0] + 1;
            crazyArray[i][3][1] = crazyArray[i-1][3][1] + road[i-1] - 1;
        }
        border[i][0] = crazyArray[i][0][1];
        border[i][1] = crazyArray[i][2][0];
        border[i][2] = crazyArray[i][2][1];
        border[i][3] = crazyArray[i][0][0];
    }
}

/// <summary>
/// function to draw a rect with a[x, z], b[x, z], c[x, z], d[x, z]
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <param name="c"></param>
/// <param name="d"></param>
/// <param name="x_dir"></param>
/// <param name="y_dir"></param>
/// <param name="z_dir"></param>
void draw_rect(int a[2], int b[2], int c[2], int d[2], double x_dir, double y_dir, double z_dir) {
    glBegin(GL_QUADS);
        glNormal3d(x_dir, y_dir, z_dir);
        glVertex3f((GLfloat)a[0], 0.0f, -(GLfloat)a[1]);
        glVertex3f((GLfloat)b[0], 0.0f, -(GLfloat)b[1]);
        glVertex3f((GLfloat)c[0], 0.0f, -(GLfloat)c[1]);
        glVertex3f((GLfloat)d[0], 0.0f, -(GLfloat)d[1]);
    glEnd();
}

/// <summary>
/// function to draw 4 rect around
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <param name="c"></param>
/// <param name="d"></param>
void draw_around_rect(int a[2], int b[2], int c[2], int d[2]) {
    glBegin(GL_QUADS);
        glNormal3d(0.0, 0.0, -1.0);
        glVertex3f((GLfloat)a[0], 0.0f, -(GLfloat)a[1]);
        glVertex3f((GLfloat)b[0], 0.0f, -(GLfloat)b[1]);
        glVertex3f((GLfloat)b[0],-5.0f, -(GLfloat)b[1]);
        glVertex3f((GLfloat)a[0],-5.0f, -(GLfloat)a[1]);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3d(1.0, 0.0, 0.0);
        glVertex3f((GLfloat)c[0], 0.0f, -(GLfloat)c[1]);
        glVertex3f((GLfloat)b[0], 0.0f, -(GLfloat)b[1]);
        glVertex3f((GLfloat)b[0],-5.0f, -(GLfloat)b[1]);
        glVertex3f((GLfloat)c[0],-5.0f, -(GLfloat)c[1]);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3d(0.0, 0.0, 1.0);
        glVertex3f((GLfloat)c[0], 0.0f, -(GLfloat)c[1]);
        glVertex3f((GLfloat)d[0], 0.0f, -(GLfloat)d[1]);
        glVertex3f((GLfloat)d[0],-5.0f, -(GLfloat)d[1]);
        glVertex3f((GLfloat)c[0],-5.0f, -(GLfloat)c[1]);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3d(-1.0, 0.0, 0.0);
        glVertex3f((GLfloat)a[0], 0.0f, -(GLfloat)a[1]);
        glVertex3f((GLfloat)d[0], 0.0f, -(GLfloat)d[1]);
        glVertex3f((GLfloat)d[0],-5.0f, -(GLfloat)d[1]);
        glVertex3f((GLfloat)a[0],-5.0f, -(GLfloat)a[1]);
    glEnd();
}

/// <summary>
/// function to draw the first rect in (0, 0, 0)
/// </summary>
void draw_first_rect() {
    glBegin(GL_QUADS);
        glNormal3d( 0.0, 1.0,  0.0);
        glVertex3f(-2.0, 0.0,  2.0);
        glVertex3f(-2.0, 0.0, -2.0);
        glVertex3f( 2.0, 0.0, -2.0);
        glVertex3f( 2.0, 0.0,  2.0);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3d(-1.0,  0.0,  0.0);
        glVertex3f(-2.0,  0.0,  2.0);
        glVertex3f(-2.0,  0.0, -2.0);
        glVertex3f(-2.0, -5.0, -2.0);
        glVertex3f(-2.0, -5.0,  2.0);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3d( 0.0,  0.0,  1.0);
        glVertex3f(-2.0,  0.0,  2.0);
        glVertex3f(-2.0, -5.0,  2.0);
        glVertex3f( 2.0, -5.0,  2.0);
        glVertex3f( 2.0,  0.0,  2.0);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3d( 1.0,  0.0,  0.0);
        glVertex3f( 2.0,  0.0,  2.0);
        glVertex3f( 2.0,  0.0, -2.0);
        glVertex3f( 2.0, -5.0, -2.0);
        glVertex3f( 2.0, -5.0,  2.0);
    glEnd();
}

/// <summary>
/// function to draw the road
/// </summary>
void draw_road() {

    glPushMatrix();
    glColor3f(0.25f, 0.5f, 0.9f);
    draw_first_rect();
    for (int i = 1; i < length; i++) {
        draw_rect(crazyArray[i][0], crazyArray[i][1], crazyArray[i][2], crazyArray[i][3], 0.0, 1.0, 0.0);
        draw_around_rect(crazyArray[i][0], crazyArray[i][1], crazyArray[i][2], crazyArray[i][3]);
    }
    
    glPopMatrix();
};

/// <summary>
/// draw string c in position (x, y, z)
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <param name="string"></param>
void draw_string(float x, float y, float z, char* string) {
    glRasterPos3f(x, y, z);
    for (char* c = string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);  // Updates the position
    }
}

int i, top, right, bottom, left;

/// <summary>
/// initial, clear color and set shade model
/// </summary>
/// <param name=""></param>
void Initialize(void)
{
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightPos[]     = { 25.0f, 25.0f, 25.0f, 0.0f };
    GLfloat spotDir[]      = { 0.0f, 0.0f, 0.0f, 0.0f };

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glClearColor(0.6f, 0.6f, 0.9f, 0.6f);

    setting_road_value();
    setting_array_value();
    i      = 0;
    top    = border[i][0];
    right  = border[i][1];
    bottom = border[i][2];
    left   = border[i][3];
    sprintf_s(scores, "Score: %d", score);
}

/// <summary> 
/// render function
/// </summary>
void render(void) {
    int beginframe = getMilliCount();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ, centerX, centerY, centerZ, 0.0, 1.0, 0.0);
    draw_road();
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);
    glTranslatef(x_ball, y_ball, z_ball);
    glutSolidSphere(0.2, 400, 400);
    glPopMatrix();
    glColor3f(1.0f, 0.4f, 0.2f);
    draw_string((GLfloat)centerX, (GLfloat)centerY + 3.0f, (GLfloat)centerZ, scores);
    glutSwapBuffers();
    int timeDiff = getMilliCount() - beginframe;
    if (timeDiff < chuky)
    {
        sleep(chuky - timeDiff);
    }
    glFlush();
}

/// <summary>
/// reset the game
/// </summary>
void restart_game() {
    camX = -3.0, camY = 3.0, camZ = 3.0, centerX = 0.0, centerY = 0.0, centerZ = 0.0;
    x_ball = 0.0f, y_ball = 0.2f, z_ball = 0.0f, x_speed = 0.04f, y_speed = 0.04f, z_speed = 0.04f;
    setting_road_value();
    setting_array_value();
    score = 0;
    i = 0;
    top = border[i][0];
    right = border[i][1];
    bottom = border[i][2];
    left = border[i][3];
    playing = false;
    game_over = false;
}

/// <summary>
/// input function
/// </summary>
/// <param name="key"></param>
/// <param name="x"></param>
/// <param name="y"></param>
void input_keyboard(unsigned char key, int x, int y) {
    switch (key)
    {
    case 'a':
        if (!game_over) {
            if (!playing) {
                playing = true;
                if (direction == 1) {
                    z_speed = 0.04f;
                    x_speed = 0.0f;
                    direction = -direction;
                }
                else {
                    z_speed = 0.0f;
                    x_speed = 0.04f;
                    direction = -direction;
                }
                score += 1;
            }
            else {
                if (direction == 1) {
                    z_speed = 0.04f;
                    x_speed = 0.0f;
                    direction = -direction;
                }
                else {
                    z_speed = 0.0f;
                    x_speed = 0.04f;
                    direction = -direction;
                }
                score += 1;
            }
        }
        break;
    case 32:
        restart_game();
        break;
    default:
        break;
    } 
    glutPostRedisplay();
}

/// <summary>
/// function to reshape when window resize
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
void reshape(int w, int h) {
    if (h == 0)
    {
        h = 1;
    }
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    GLfloat aspect = (GLfloat)w / (GLfloat) h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.0, aspect, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ, centerX, centerY, centerZ, 0.0, 1.0, 0.0);
}

/// <summary>
/// update function
/// </summary>
void update() {
    if (playing) {
        // z
        z_ball  = z_ball    - z_speed;
        camZ    = camZ      - z_speed;
        centerZ = centerZ   - z_speed;
        // x
        x_ball  = x_ball    + x_speed;
        camX    = camX      + x_speed;
        centerX = centerX   + x_speed;

    }
    // detect ball out of road
   
    if (x_ball > right || z_ball < -top) {
        if (x_ball > right) {
            playing = false;
            game_over = true;
            x_ball = right + 0.3f;
            y_ball -= y_speed;
            if (y_ball < -15) {
                //y_speed = 0;
                restart_game();
            }
        }
        else {
            playing = false;
            game_over = true;
            z_ball = -(top + 0.3f);
            y_ball -= y_speed;
            if (y_ball < -15) {
                //y_speed = 0;
                restart_game();
            }
        }
    }
    if (x_ball > left && z_ball < -(top - 1)) { 
        i += 1; 
        top    = border[i][0];
        right  = border[i][1];
        bottom = border[i][2];
        left   = border[i][3];
    }
    sprintf_s(scores, "Score: %d", score);
    glutPostRedisplay();
}

/// <summary>
/// main function
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
    glutInitWindowSize(450, 800);

    glutInitWindowPosition(735, 40);
    glutCreateWindow("Zig Zag Ball");
    Initialize();
    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutIdleFunc(update);
    glutKeyboardFunc(input_keyboard);
    for (int i = 0; i < length; i++) {
        printf("\t%d", road[i]);
        printf("\t( %d, %d ), ( %d, %d ), ( %d, %d ), ( %d, %d )", 
            crazyArray[i][0][0], 
            crazyArray[i][0][1], 
            crazyArray[i][1][0], 
            crazyArray[i][1][1], 
            crazyArray[i][2][0], 
            crazyArray[i][2][1], 
            crazyArray[i][3][0], 
            crazyArray[i][3][1]
        );
        printf("\t( %d, %d, %d, %d )\n", border[i][0], border[i][1], border[i][2], border[i][3]);
    }
    glutMainLoop();
   
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
