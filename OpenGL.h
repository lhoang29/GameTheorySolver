#ifndef _OpenGL_h
#define _OpenGL_h
#include "Graphics.h"
#include <GL/glut.h>

class OpenGL : public Graphics
{
      public:
             virtual void init() = 0;
             virtual void beginDisplay() = 0;
             virtual void endDisplay() = 0;
             virtual void color(double&, double&, double&){}
             virtual void drawLine(double& x1, double& y1, double& x2, double& y2){}
             virtual void drawPoint(double& x, double& y){}
             virtual void drawText(double& x, double& y, string& s){}
             virtual void Refresh()
             {
                glutPostRedisplay();
             }
};

#endif
