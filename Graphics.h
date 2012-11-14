#ifndef _Graphics_h
#define _Graphics_h
#define WIDTH 800
#define HEIGHT 600
#include <string>

using namespace std;

class Graphics
{
      public:
             Graphics(){}
             virtual void init() = 0;
             virtual void beginDisplay() = 0;
             virtual void endDisplay() = 0;
             virtual void color(double&, double&, double&){}
             virtual void color3D(double&, double&, double&, double&){}
             virtual void drawLine(double& x1, double& y1, double& x2, double& y2){}
             virtual void drawPoint(double& x, double& y){}
             virtual void drawText(double& x, double& y, string& s){}
             virtual void drawLine3D(double& x1, double& y1, double& z1, double& x2, double& y2, double& z2){}
             virtual void drawPoint3D(double& x, double& y, double& z){}
             virtual void drawCustomPoint(double&, double&, double&, double&){}
             virtual void drawText3D(double& x, double& y, double& z, string& s){}
             virtual void drawArrow3D(double&, double&, double&, int){}
             virtual void RotateX(int direction){}
             virtual void RotateY(int direction){}
             virtual void RotateZ(int direction){}
             virtual void TranslateX(double x){}
             virtual void TranslateY(double y){}
             virtual void TranslateZ(double z){}
             virtual void Refresh(){}
};

#endif
