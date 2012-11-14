#include "OpenGL2D.h"

void OpenGL2D::init()
{
    /*set clearing (background) color*/
    glClearColor(0.0, 0.0, 0.0, 0.0);  
    /*initialize viewing values*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

void OpenGL2D::beginDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT); 
    glColor3f(1,1,0);
}

void OpenGL2D::endDisplay()
{
    /*process buffered OpenGL routines*/
    glFlush();
    glutSwapBuffers(); //changed
}

void OpenGL2D::color(double& r, double& g, double& b)
{
    glColor3f(r, g, b);
}

void OpenGL2D::drawLine(double& x1, double& y1, double& x2, double& y2)
{
    glBegin(GL_LINES);
     glVertex2f(x1, y1);
     glVertex2f(x2, y2);
    glEnd();
}
void OpenGL2D::drawPoint(double& x, double& y)
{
    glBegin(GL_POINTS);
     for(int t=1; t<=360; t++)
        glVertex2f(x + 3.0*cos(t), y + 3.0*sin(t));
    glEnd();
}
void OpenGL2D::drawText(double& x, double& y, string& s)
{
    glRasterPos2f(x, y);
    for (int i=0; i<strlen(&s[0]); i++){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
    }
}
