#ifndef _OpenGL3D_h
#define _OpenGL3D_h
#include "OpenGL.h"

class OpenGL3D : public OpenGL
{
      private:
             double rotateX, rotateY, rotateZ;
             double translateX, translateY, translateZ;
      public:
             OpenGL3D(){
                rotateX = rotateY = rotateZ = 0;
                translateX = translateY = translateZ = 0;
             }
             virtual void init();
             virtual void beginDisplay();
             virtual void endDisplay();
             virtual void color3D(double&, double&, double&, double&);
             virtual void drawLine3D(double& x1, double& y1, double& z1, double& x2, double& y2, double& z2);
             virtual void drawPoint3D(double& x, double& y, double& z);
             virtual void drawCustomPoint(double&, double&, double&, double&);
             virtual void drawText3D(double& x, double& y, double& z, string& s);
             virtual void drawArrow3D(double&, double&, double&, int);
             virtual void RotateX(int direction);
             virtual void RotateY(int direction);
             virtual void RotateZ(int direction);
             virtual void TranslateX(double x);
             virtual void TranslateY(double y);
             virtual void TranslateZ(double z);
};

#endif
