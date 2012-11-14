#ifndef _FlowNzs_h
#define _FlowNzs_h
#include "Visualization.h"

class FlowNzs : public Visualization
{
      private:
              //these are the bounds of the graphics screen
              double leftBound, rightBound, topBound, bottomBound;
              
              //this is the array for the saddle
              //points in the matrix; the index is the top of the array
              int *Saddle, indexSaddle;
      public:
              //constructor initializes the screen boundary within which
              //the visualization will be drawn
              FlowNzs()
              {
                 g = new OpenGL2D();
                 leftBound   = WIDTH/8.0;
                 rightBound  = WIDTH*7.0/8.0;
                 topBound    = HEIGHT*7.0/8.0;
                 bottomBound = HEIGHT/8.0;
              }
              
              //draw all lines
              virtual void drawLines(LineCollection& lc)
              {
                 if(!lc.isNull())
                 for(int i=0; i<lc.getTop(); i++)
                 {
                    Line myLine = lc.getElement(i);
                    double x1 = myLine.getStart()->getX();
                    double y1 = myLine.getStart()->getY();
                    double x2 = myLine.getEnd()->getX();
                    double y2 = myLine.getEnd()->getY();
                    g->drawLine(x1, y1, x2, y2);
                 }
              }
              
              //draw all points
              virtual void drawPoints(PointCollection<double>& pc)
              {
                 color(0,1,1);
                 if(!pc.isNull())
                 for(int i=0; i<pc.getTop(); i++)
                 {
                    Point<double> p = pc.getElement(i);
                    double x = p.getX();
                    double y = p.getY();
                    //if the point is the saddle point then color it red
                    if(isSaddle(i))
                       color(1,0,0);
                    else
                       color(0,1,1);
                    g->drawPoint(x, y);
                 }    
              }
              
              //draw all texts
              virtual void drawTexts(TextCollection& tc)
              {
                 color(0.8, 0.5, 0);
                 if(!tc.isNull())
                 for(int i=0; i<tc.getTop(); i++)
                 {
                    if(i == tc.getTop()-2) color(1,1,1);
                    Text myText = tc.getElement(i);
                    double x = myText.getPosition().getX();
                    double y = myText.getPosition().getY();
                    string s = myText.getDescription();
                    g->drawText(x, y, s);
                 }
              }
              //this function conceptually constructs lines for drawing
              virtual LineCollection buildLines(payoffMatrix& pm)
              {
                 int numCol = pm.getNumCols();
                 int numRow = pm.getNumRows();
                 
                 //get the horizontal and vertical increment for the points
                 //being drawn
                 double verticalStep = (topBound - bottomBound)/(numRow - 1);
                 double horizontalStep = (rightBound - leftBound)/(numCol - 1);
                 
                 LineCollection lc(3*(2*numRow*numCol-numRow-numCol));
                 
                 for (int i=0; i<numRow; i++)
                 {
                    for(int j=0; j<numCol; j++)
                    {
                       if(j+1 < numCol)
                       {
                          Point<int> p1((int)(leftBound + j*horizontalStep + 10), 
                                        (int)(bottomBound + i*verticalStep));
                          Point<int> p2((int)(leftBound + (j+1)*horizontalStep - 10),
                                        (int)(bottomBound + i*verticalStep));
                          Line l(p1, p2);
                          lc.push(l);
                          
                          /*check and get appropriate arrows heads*/
                          
                          //if going right
                          if(pm.getPayoff(numRow-1-i, j,false)->getY() < pm.getPayoff(numRow-1-i, j+1,false)->getY())
                          {
                             if(pm.getPayoff(numRow-1-i,j+1,false)->getY() == pm.getRowExtrema(false,numRow-1-i,false))
                             {
                                 Point<int> p3((int)(leftBound + (j+1)*horizontalStep - 15),
                                               (int)(bottomBound + i*verticalStep + 5));
                                 Line l2(p3, p2);
                                 lc.push(l2);
                                 Point<int> p4((int)(leftBound + (j+1)*horizontalStep - 15),
                                               (int)(bottomBound + i*verticalStep - 5));
                                 Line l3(p4, p2);
                                 lc.push(l3);
                             }
                          }
                          //if going left
                          if(pm.getPayoff(numRow-1-i, j,false)->getY() > pm.getPayoff(numRow-1-i, j+1,false)->getY())
                          {
                             if(pm.getPayoff(numRow-1-i,j,false)->getY() == pm.getRowExtrema(false,numRow-1-i,false))
                             {   
                                 Point<int> p3((int)(leftBound + j*horizontalStep + 15), 
                                              (int)(bottomBound + i*verticalStep + 5));
                                 Line l2(p3, p1);
                                 lc.push(l2);
                                 Point<int> p4((int)(leftBound + j*horizontalStep + 15), 
                                            (int)(bottomBound + i*verticalStep - 5));
                                 Line l3(p4, p1);
                                 lc.push(l3);
                             }
                          }
                       }
                       if(i+1 < numRow)
                       {
                          Point<int> p1((int)(leftBound + j*horizontalStep), 
                                        (int)(bottomBound + i*verticalStep + 20));
                          Point<int> p2((int)(leftBound + j*horizontalStep),
                                        (int)(bottomBound + (i+1)*verticalStep - 10));
                          Line l(p1, p2);
                          lc.push(l);
                          
                          /*check and get appropriate arrows heads*/
                          
                          //if going up
                          if(pm.getPayoff(numRow-1-i, j,false)->getX() < pm.getPayoff(numRow-2-i, j,false)->getX())
                          {
                             if(pm.getPayoff(numRow-2-i, j,false)->getX()==pm.getColExtrema(false,j,false))
                             {
                                 Point<int> p3((int)(leftBound + j*horizontalStep - 5),
                                               (int)(bottomBound + (i+1)*verticalStep - 15));
                                 Line l2(p3, p2);
                                 lc.push(l2);
                                 Point<int> p4((int)(leftBound + j*horizontalStep + 5),
                                               (int)(bottomBound + (i+1)*verticalStep - 15));
                                 Line l3(p4, p2);
                                 lc.push(l3);
                             }
                          }
                          //if going down
                          if(pm.getPayoff(numRow-1-i, j,false)->getX() > pm.getPayoff(numRow-2-i, j,false)->getX())
                          {
                             if(pm.getPayoff(numRow-1-i, j, false)->getX()==pm.getColExtrema(false,j,false))
                             {
                                 Point<int> p3((int)(leftBound + j*horizontalStep - 5), 
                                               (int)(bottomBound + i*verticalStep + 25));
                                 Line l2(p3, p1);
                                 lc.push(l2);
                                 Point<int> p4((int)(leftBound + j*horizontalStep + 5), 
                                               (int)(bottomBound + i*verticalStep + 25));
                                 Line l3(p4, p1);
                                 lc.push(l3);
                             }
                          }
                       }
                    }
                 }
                 return lc;
              }
              
              //this function conceptually constructs points for drawing
              virtual PointCollection<double> buildPoints(payoffMatrix& pm)
              {
                 int numCol = pm.getNumCols();
                 int numRow = pm.getNumRows();
                 
                 //initialize the two arrays to maximum size
                 Saddle = new int[numRow*numCol];
                 
                 //set top of these arrays to zero
                 indexSaddle = 0;
                 
                 //get the horizontal and vertical increment for the points
                 //being drawn
                 double verticalStep = (topBound - bottomBound)/(numRow - 1);
                 double horizontalStep = (rightBound - leftBound)/(numCol - 1);
                 
                 //size of the point collection must be big enough to contain all points
                 PointCollection<double> pc(numCol * numRow);
                 
                 //draw points
                 for(int i=0; i<numRow; i++)
                 {
                    for(int j=0; j<numCol; j++)
                    {
                        Point<double> p(leftBound + j*horizontalStep, 
                                        bottomBound + i*verticalStep);
                        pc.push(p);
                        
                        //check if the point is a saddle point
                        //if all 4 of these conditions satisfy then the point
                        //at (i,j) is a saddle point
                        if((j-1>=0 && pm.getPayoff(i,j-1,false)->getY()<=pm.getPayoff(i,j,false)->getY()) || j-1<0)
                        if((j+1<=numCol-1 && pm.getPayoff(i,j+1,false)->getY()<=pm.getPayoff(i,j,false)->getY()) || j+1>=numCol)
                        if((i-1>=0 && pm.getPayoff(i-1,j,false)->getX()<=pm.getPayoff(i,j,false)->getX()) || i-1<0)
                        if((i+1<=numRow-1 && pm.getPayoff(i+1,j,false)->getX()<=pm.getPayoff(i,j,false)->getX()) || i+1>=numRow)
                        {
                           if(pm.isRowMaximum(i,j) && pm.isColMaximum(j,i))
                           {
                               //store this index in the array
                               Saddle[indexSaddle] = (numRow-i-1)*numCol+j;
                               indexSaddle++;
                           }
                        }
                    }
                 }
                 
                 return pc;
              }
              
              //this function conceptually constructs texts for drawing
              virtual TextCollection buildTexts(payoffMatrix& pm)
              {
                 int numCol = pm.getNumCols();
                 int numRow = pm.getNumRows();
                 
                 //get the horizontal and vertical increment for the points
                 //being drawn
                 double verticalStep = (topBound - bottomBound)/(numRow - 1);
                 double horizontalStep = (rightBound - leftBound)/(numCol - 1);
                 
                 TextCollection tc(numCol * numRow + 2);
                 
                 //draw texts
                 for(int i=0; i<numRow; i++)
                 {
                    for(int j=0; j<numCol; j++)
                    {
                        Point<double> p(leftBound + j*horizontalStep - 5, 
                                        bottomBound + i*verticalStep + 10);
                        ostringstream o;
                        o << "(" << pm.getPayoff(numRow-1-i, j,false)->getX() << "," 
                          << pm.getPayoff(numRow-1-i, j,false)->getY() << ")";
                        string s = o.str();
                        Text t(p, s);
                        tc.push(t);
                    }
                 }
                 
                 //draw names
                 Point<double> pRose(WIDTH/32.0, HEIGHT/2.0);
                 string s = "Rose";
                 Text tRose(pRose, s);
                 tc.push(tRose);
                 Point<double> pColin(WIDTH/2.0, HEIGHT*15.0/16.0);
                 s = "Colin";
                 Text tColin(pColin, s);
                 tc.push(tColin);
                 
                 return tc;
              }
              
              bool isSaddle(int a)
              {
                 for(int i=0; i<indexSaddle; i++)
                 {
                    if(a==Saddle[i])
                    {
                       return true;
                    }
                 }
                 return false;
              }
};
#endif
