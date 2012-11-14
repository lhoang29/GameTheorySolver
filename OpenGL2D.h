#ifndef _OpenGL2D_h
#define _OpenGL2D_h
#include "OpenGL.h"
#include <math.h>
class OpenGL2D : public OpenGL
{
      public:
             OpenGL2D(){}
             virtual void init();
             virtual void beginDisplay();
             virtual void endDisplay();
             virtual void color(double&, double&, double&);
             virtual void drawLine(double& x1, double& y1, double& x2, double& y2); 
             virtual void drawPoint(double& x, double& y);
             virtual void drawText(double& x, double& y, string& s);
};

#endif
