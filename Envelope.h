#ifndef _Envelope_h
#define _Envelope_h
#include "Visualization.h"
#include "OpenGL2D.h"
#include "Intersection.h"

class Envelope : public Visualization
{
      public:
             Envelope(){ g = new OpenGL2D(); }
             virtual void drawTexts(TextCollection& tc)
             {
                color(0.8, 0.5, 0);
                if(!tc.isNull())
                for(int i=0; i<tc.getTop(); i++)
                {
                   Text myText = tc.getElement(i);
                   double x = myText.getPosition().getX();
                   double y = myText.getPosition().getY();
                   string s = myText.getDescription();
                   g->drawText(x, y, s);
                }
             }
             
             virtual void drawPoints(PointCollection<double>& pc)
             {
             
             }
             
             virtual void drawLines(LineCollection& lc)
             {
                  for(int i=0; i<lc.getTop(); i++)
                  {
                     Line myLine = lc.getElement(i);
                     double x1 = myLine.getStart()->getX();
                     double y1 = myLine.getStart()->getY();
                     double x2 = myLine.getEnd()->getX();
                     double y2 = myLine.getEnd()->getY();
                     
                     //change color to green for the last three lines
                     if(i == lc.getTop()-3)
                     color(0,1,0);
                     
                     g->drawLine(x1, y1, x2, y2);
                  }
             }
             virtual LineCollection buildLines(payoffMatrix& pm)
             {
                  //x1 and x2 are the two x-coordinates of two vertical lines
                  int x1 = WIDTH/6;
                  int x2 = 5*x1;
                  
                  //the y coordinate of the bottom line
                  int y = 50;
                  
                  //these below form the basic structure of the screen
                  Point<int> ps1(x1, y-20);
                  Point<int> pe1(x2, y-20);
                  Point<int> ps2(x1, y);
                  Point<int> pe2(x1, HEIGHT-y);
                  Point<int> ps3(x2, y);
                  Point<int> pe3(x2, HEIGHT-y);
                  Line l1(ps1, pe1);
                  Line l2(ps2, pe2);
                  Line l3(ps3, pe3);
                  
                  /*This block of code below transforms the line collection to those
                    with coordinates that fit the OpenGL 2D scene, then pushes these
                    lines onto the collection that will be passed in render*/
                  LineCollection *lcMain = (LineCollection*)pm.generateLines();
                  int min = lcMain->getMinY();
                  int max = lcMain->getMaxY();
                  
                  LineCollection lc(4 + (max + 1 - min)*2 + lcMain->getSize());
                  lc.push(l1);
                  lc.push(l2);
                  lc.push(l3);
                  
                  delete &l1, &l2, &l3;
                  
                  for(int i=0; i<max+1-min; i++)
                  {
                     int jump = (HEIGHT - 2*y)/(max + 1 - min);
                     Point<int> ps1(x1-5, y + jump * i);
                     Point<int> pe1(x1+5, y + jump * i);
                     Line l1(ps1, pe1);
                     lc.push(l1);
                     Point<int> ps2(x2-5, y + jump * i);
                     Point<int> pe2(x2+5, y + jump * i);
                     Line l2(ps2, pe2);
                     lc.push(l2);
                  }
                  
                  //prepare to get the envelope solution for rendering
                  Intersection *isolution = (Intersection*)NULL;
                  if(pm.getNumRows() == 2 && pm.getNumCols() != 2)
                     isolution = lcMain->getEnvelopeSolution(false);
                  else if(pm.getNumRows() != 2 && pm.getNumCols() == 2)
                     isolution = lcMain->getEnvelopeSolution(true);         
                  else if(pm.getNumRows() == 2 && pm.getNumCols() == 2)
                     isolution = lcMain->getEnvelopeSolution(true);
                  //if there's a solution then proceed to draw this
                  Line *lSolution = (Line*)NULL;
                  int index1=-1, index2=-1;
                  if(isolution!=(Intersection*)NULL)
                  {
                     //this is to get the mark for solution on the bottom horizontal line
                     double xLocationTemp = (isolution->getPoint().getX().getDecimalValue());
                     int xLocation = (int)(xLocationTemp*(x2-x1)+x1);
                     Point<int> xSolutionUpper(xLocation, y-15);
                     Point<int> xSolutionLower(xLocation, y-25);
                     lSolution = new Line(xSolutionUpper, xSolutionLower);
                     
                     //this is to keep track of the indexes of two lines that form
                     //envelope solution
                     index1 = isolution->getIndexLine1();
                     index2 = isolution->getIndexLine2();
                  }
                  
                  Line lTemp1, lTemp2;
                  int increment = (HEIGHT - 2*y)/(max + 1 - min);
                  for(int i=0; i<lcMain->getTop(); i++)
                  {
                     Line lTemp = lcMain->getElement(i);
                     int startY = lTemp.getStart()->getY();
                     int endY = lTemp.getEnd()->getY();
                     lTemp.getStart()->setX(x1);
                     lTemp.getStart()->setY(y+(startY-min)*increment);
                     lTemp.getEnd()->setX(x2);
                     lTemp.getEnd()->setY(y+(endY-min)*increment);
                     if(i!=index1 && i!=index2)
                     lc.push(lTemp);
                     else if(i==index1)
                     {
                        lTemp1 = lTemp;
                     }
                     else
                     {
                        lTemp2 = lTemp;
                     }
                  }
                  
                  if(index1 != -1)
                  {
                     lc.push(lTemp1);
                  }
                  if(index2 != -1)
                  {
                     lc.push(lTemp2);
                  }
                  if(lSolution != (Line*)NULL)
                  lc.push(*lSolution);
                  
                  return lc;
             }
             virtual PointCollection<double> buildPoints(payoffMatrix& pm)
             {
                return *(new PointCollection<double>());
             }
             virtual TextCollection buildTexts(payoffMatrix& pm)
             {
                  LineCollection *lcMain = (LineCollection*)pm.generateLines();
                  int min = lcMain->getMinY();
                  int max = lcMain->getMaxY();
                  
                  double x1 = WIDTH * 1.0/6;
                  double x2 = 5*x1;
                  double y = 50;
                  Point<double> p1(x1-5, 10);
                  Point<double> p2(x2-5, 10);
                  string s = "0";
                  Text t1(p1, s);
                  s = "1";
                  Text t2(p2, s);
                  
                  //initialize size for text collection
                  TextCollection tc(3 + (max - min + 1)*2);
                  tc.push(t1);
                  tc.push(t2);

                  for(int i=0; i< max + 1 - min; i++)
                  {
                      ostringstream o;
                      int jump = (int)(HEIGHT - 2*y)/(max + 1 - min);
                      
                      //this is to format how the numbers will be displayed on screen
                      if(min + i >= 0 && min + i < 10)
                         o << " " << min+i;
                      else
                         o << min + i;
                      s = o.str();
                      
                      Point<double> p3(x1-30, y - 5 + jump * i);
                      Text t3(p3, s);
                      Point<double> p4(x2+5, y - 5 + jump * i);
                      Text t4(p4, s);
                      tc.push(t3);
                      tc.push(t4);
                  }
                  
                  //prepare to get the envelope solution for rendering
                  Intersection *isolution = (Intersection*)NULL;
                  if(pm.getNumRows() == 2 && pm.getNumCols() != 2)
                     isolution = lcMain->getEnvelopeSolution(false);
                  else if(pm.getNumRows() != 2 && pm.getNumCols() == 2)
                     isolution = lcMain->getEnvelopeSolution(true);
                  else if(pm.getNumRows() == 2 && pm.getNumCols() == 2)
                     isolution = lcMain->getEnvelopeSolution(true);
                     
                  if(isolution != (Intersection*)NULL)
                  {
                      ostringstream o;
                      double x = isolution->getPoint().getX().getDecimalValue();
                      Point<double> p3(x1 + x*(x2-x1) - 10, y-40);
                      string s = isolution->getPoint().getX().getValue();
                      Text t3(p3, s);
                      tc.push(t3);
                  }
                  
                  return tc;
             }
};

#endif
