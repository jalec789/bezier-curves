// Name:
// Quarter, Year:
// Lab:
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include <vector>
#include <cstdio>
#include <math.h>
#include "vec.h"
#include <iostream>

using namespace std;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

std::vector<GLfloat> point_x;
std::vector<GLfloat> point_y;

int factorial(int n)
{
    int result = 1;
    for (int i = n; i != 0; i--)
    {
        result *= i;
    }
    return result;
}

void GL_render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);

    // TODO: just for example, you will need to change this.
    //    glVertex2f(-.5f,-.5f);
    //    glVertex2f(.5f,-.5f);
    //    glVertex2f(.5f,.5f);
    //    glVertex2f(-.5f,.5f);

    if (point_x.size() >= 2){
        std::vector<GLfloat> gl_point_x;
        std::vector<GLfloat> gl_point_y;
        float n = point_x.size() - 1;
        for (float t = 0.00; t <= 1; t = t + .01){
            float point_i_x = 0;
            float point_i_y = 0;

            // Calculate summation of the polynomial
            for (unsigned i = 0; i < point_x.size(); i++){
                //n! / i!(n - i)!
                float combination = factorial(n) / (factorial(i) *factorial(n - i));
                float power = pow(t, i);
                if (t == 0.00){
                    power = 1;
                }

                float solution_x = point_x[i];
                float solution_y = point_y[i];
                solution_x = combination * pow((1 - t), n - i) * power * solution_x;
                solution_y = combination * pow((1 - t), n - i) * power * solution_y;

                if (i == 0){
                    point_i_x = solution_x;
                    point_i_y = solution_y;
                }
                else{
                    point_i_x = point_i_x + solution_x;
                    point_i_y = point_i_y + solution_y;
                }
            }
            if(t != 0.00){
                gl_point_x.push_back(point_i_x);
                gl_point_y.push_back(point_i_y);
            }
            for (unsigned j = 1; j < gl_point_x.size(); j++){
                glVertex2f(gl_point_x[j - 1], gl_point_y[j - 1]);
                glVertex2f(gl_point_x[j], gl_point_y[j]);
            }
        }
    }

    glEnd();
    glFlush();
}

void GL_mouse(int button, int state, int x, int y)
{
    y = WINDOW_HEIGHT - y;
    GLdouble mv_mat[16];
    GLdouble proj_mat[16];
    GLint vp_mat[4];
    glGetDoublev(GL_MODELVIEW_MATRIX, mv_mat);
    glGetDoublev(GL_PROJECTION_MATRIX, proj_mat);
    glGetIntegerv(GL_VIEWPORT, vp_mat);

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        double px, py, dummy_z; // we don't care about the z-value but need something to pass in
        gluUnProject(x, y, 0, mv_mat, proj_mat, vp_mat, &px, &py, &dummy_z);
        // TODO: the mouse click coordinates are (px,py).

        glutPostRedisplay();

        if ((point_x.size() == 0) || (point_x[point_x.size() - 1] != px || point_y[point_y.size() - 1] != py)){
            point_x.push_back(px);
            point_y.push_back(py);
        }
    }
}

//Initializes OpenGL attributes
void GLInit(int *argc, char **argv)
{
    glutInit(argc, argv);
    //glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    //glMatrixMode(GL_PROJECTION_MATRIX);
    //glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
    glutCreateWindow("CS 130 - <Insert Name Here>");
    glutDisplayFunc(GL_render);
    glutMouseFunc(GL_mouse);
}

int main(int argc, char **argv)
{
    GLInit(&argc, argv);
    glutMainLoop();
    return 0;
}
