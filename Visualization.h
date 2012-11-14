#ifndef _Visualization_h
#define _Visualization_h
#include "LineCollection.h"
#include "PointCollection.h"
#include "TextCollection.h"
#include "Graphics.h"
#include "payoffMatrix.h"
#include <sstream>

class Visualization
{
   protected: 
          Graphics* g;
          
   public:
          Visualization(){}
          
          //return the pointer to the graphics object
          virtual Graphics* G(){return g;}
          
          //initialize screen
          virtual void init(){g->init();}
          
          //this function prepares for onscreen display
          virtual void beginDisplay(){g->beginDisplay();}
          
          //this function ends display
          virtual void endDisplay(){g->endDisplay();}
          
          //this function refreshes the screen
          virtual void Refresh(){g->Refresh();}
          
          /****************This section is for 2D graphics*****************/
          
          //this virtual function conceptually constructs lines for drawing
          virtual LineCollection buildLines(payoffMatrix& pm){}
          
          //this virtual function conceptually constructs points for drawing
          virtual PointCollection<double> buildPoints(payoffMatrix& pm){}
          
          //this virtual function conceptually constructs texts for drawing
          virtual TextCollection buildTexts(payoffMatrix& pm){}
          
          //changes color being rendered
          virtual void color(double x, double y, double z)
          {
             g->color(x,y,z);
          }
          
          //draw all lines
          virtual void drawLines(LineCollection& lc){}
          
          //draw all points
          virtual void drawPoints(PointCollection<double>& pc){}
          
          //draw all texts
          virtual void drawTexts(TextCollection& tc){}
          
          /****************This section is for 3D graphics*****************/
          
          //color for 3 dimension with transparency value
          virtual void color3D(double x, double y, double z, double a)
          {
             g->color3D(x,y,z,a);
          }
          
          /*These functions conceptually do the same as those for 2D graphics*/
          /*The two dimensional array of double is a list of elements each has
            three double values corresponding to the x, y, and z coordinates*/
          virtual double** buildLines(payoffMatrixN& pm){}
          virtual double** buildPoints(payoffMatrixN& pm){}
          virtual string* buildTexts(payoffMatrixN& pm){}
          virtual void drawLines(double** l, int size){}
          virtual void drawPoints(double** p, int size){}
          
          //s indicates the string to be drawn
          virtual void drawTexts(string* s, int size){}
          virtual void drawArrows(payoffMatrixN& pm){}
          
          /*These functions rotate the scene accordingly*/
          virtual void RotateX(int direction){}
          virtual void RotateY(int direction){}
          virtual void RotateZ(int direction){}
          
          /*These functions translate the scene accordingly*/
          virtual void TranslateX(double x){}
          virtual void TranslateY(double y){}
          virtual void TranslateZ(double z){}
};

#endif
