#ifndef _Flow3D_h
#define _Flow3D_h
#include "Visualization.h"

class Flow3D : public Visualization
{
      private:
            //these define the boundary cube in which objects will be drawn
            double maxZ, minZ, maxY, minY, maxX, minX;
            double distanceLineToPoint, dNameToCube;
            //p holds locations for the points on the 3d screen
            double **pLocations;
            //e is the vector containing equilibrium positions
            vector<int*> e;
            bool gotE;
      public:
            Flow3D()
            {
               g = new OpenGL3D();
               minZ = minY = minX = -4.0;
               maxZ = maxY = maxX = 4.0;
               distanceLineToPoint = 0.3;
               dNameToCube = 1;
               pLocations = (double**)NULL;
               gotE = false;
            }
            
            void RotateX(int direction){ g->RotateX(direction); }
            
            void RotateY(int direction){ g->RotateY(direction); }
            
            void RotateZ(int direction){ g->RotateZ(direction); }
            
            virtual void TranslateX(double x)
            {
               g->TranslateX(x);        
            }
            
            virtual void TranslateY(double y)
            {
               g->TranslateY(y);
            }
            
            virtual void TranslateZ(double z)
            {
               g->TranslateZ(z);
            }
            
            virtual double** buildLines(payoffMatrixN& pm)
            {
               int numX = pm.getNumX();
               int numY = pm.getNumY();
               int numZ = pm.getNumZ();
               int numPoints = numX * numY * numZ;
               int numLines = 3 + 3 * numX * numY * numZ - numX * numY - numY * numZ - numZ * numX;
               double **lines = new double*[numLines];
               for(int i=0; i<numLines; i++)
               {
                  //contains x,y,z coordinates for two points forming the line
                  lines[i] = new double[6];
               }
               int index=0;
               //draw Larry's visual choices
               lines[index][0] = minX-dNameToCube;
               lines[index][1] = maxY;
               lines[index][2] = maxZ-dNameToCube;
               lines[index][3] = minX-dNameToCube;
               lines[index][4] = maxY;
               lines[index][5] = minZ+dNameToCube;
               index++;
               //draw Colin's visual choices
               lines[index][0] = minX+dNameToCube;
               lines[index][1] = maxY;
               lines[index][2] = maxZ+dNameToCube;
               lines[index][3] = maxX-dNameToCube;
               lines[index][4] = maxY;
               lines[index][5] = maxZ+dNameToCube;
               index++;
               //draw Rose's visual choices
               lines[index][0] = minX-dNameToCube;
               lines[index][1] = minY+dNameToCube;
               lines[index][2] = maxZ;
               lines[index][3] = minX-dNameToCube;
               lines[index][4] = maxY-dNameToCube;
               lines[index][5] = maxZ;
               index++;
               //if p is null then initialize values for p
               if(pLocations==(double**)NULL)
               {
                  pLocations = buildPoints(pm);
               }

               for(int i=0; i<numPoints; i++)
               {
                  //draw horizontal lines along x axis
                  if((i%numY)<(numY-1))
                  {
                     lines[index][0] = pLocations[i][0]+distanceLineToPoint;
                     lines[index][1] = pLocations[i][1];
                     lines[index][2] = pLocations[i][2];
                     lines[index][3] = pLocations[i+1][0]-distanceLineToPoint;
                     lines[index][4] = pLocations[i+1][1];
                     lines[index][5] = pLocations[i+1][2];
                     index++;
                  }
                  //draw vertical lines along y axis
                  if((i%(numX*numY))<numY*(numX-1))
                  {
                     lines[index][0] = pLocations[i][0];
                     lines[index][1] = pLocations[i][1]-distanceLineToPoint;
                     lines[index][2] = pLocations[i][2];
                     lines[index][3] = pLocations[i+numY][0];
                     lines[index][4] = pLocations[i+numY][1]+distanceLineToPoint;
                     lines[index][5] = pLocations[i+numY][2];
                     index++;
                  }
                  //draw inward lines along z axis
                  if((i%(numX*numY*numZ))<numX*numY*(numZ-1))
                  {
                     lines[index][0] = pLocations[i][0];
                     lines[index][1] = pLocations[i][1];
                     lines[index][2] = pLocations[i][2]-distanceLineToPoint;
                     lines[index][3] = pLocations[i+numX*numY][0];
                     lines[index][4] = pLocations[i+numX*numY][1];
                     lines[index][5] = pLocations[i+numX*numY][2]+distanceLineToPoint;
                     index++;
                  }
               }
               return lines;
            }
            
            virtual double** buildPoints(payoffMatrixN& pm)
            {
               if(!gotE)
               {
                  e = pm.getEquilibrium();
                  gotE = true;
               }
               int numX = pm.getNumX();
               int numY = pm.getNumY();
               int numZ = pm.getNumZ();
               int numPoints = numX * numY * numZ;
               double **points = new double*[numPoints];
               for(int i=0; i<numPoints; i++)
               {
                  points[i] = new double[3];
               }
               
               //this is to figure out which one is equilibrium
               int *corIndex = new int[e.size()];
               int corI = 0;
               vector<int*>::iterator it = e.begin();
               while(it!=e.end())
               {
                  int xe = (*it)[0];
                  int ye = (*it)[1];
                  int ze = (*it)[2];
                  corIndex[corI] = ze * numX * numY + xe * numY + ye;
                  it++;
                  corI++;
               }
               
               //these are the distances between each adjacent point
               double incrementZ = (maxZ-minZ)/(numZ-1);
               //these two are tricky because of the OpenGL
               //coordiante system
               double incrementY = (maxY-minY)/(numX-1);
               double incrementX = (maxX-minX)/(numY-1);
               
               //index will be the top of points array
               int index=0;
               
               //we'll start drawing the points by drawing each
               //face at z=z0, starting at z0=maXZ. First position
               //is default to the top left corner of the cube.
               double xPos=minX, yPos=maxY, zPos=maxZ;
               for(int k=0; k<numZ; k++)
               {
                  //zPos -= k*incrementZ;
                  for(int i=0; i<numX; i++)
                  {
                     //yPos -= i*incrementY;
                     for(int j=0; j<numY; j++)
                     {
                        //xPos += j*incrementX;
                        points[index][0] = xPos + j*incrementX;
                        points[index][1] = yPos - i*incrementY;
                        points[index][2] = zPos - k*incrementZ;
                        index++;
                     }
                     xPos = minX;
                  }
                  zPos = maxZ;
                  yPos = maxY;
               }
               
               //constructs points coordinates and draw
               //equilibrium points
               if(e.size() > 0)
               {
                  double **em = new double*[e.size()];
                  for(int i=0; i<e.size(); i++)
                  {
                     em[i] = new double[3];
                     em[i][0] = points[corIndex[i]][0];
                     em[i][1] = points[corIndex[i]][1];
                     em[i][2] = points[corIndex[i]][2];
                  }
                  drawCustomPoints(em, e.size(), 0.3);
               }
               pLocations = points;
               return points;
            }
            
            virtual string* buildTexts(payoffMatrixN& pm)
            {
               int numX = pm.getNumX();
               int numY = pm.getNumY();
               int numZ = pm.getNumZ();
               int numPoints = numX * numY * numZ;
               string *s = new string[numPoints];
               for(int i=0; i<numPoints; i++)
               {
                  ostringstream o;
                  int x = (i%(numX*numY))/numY;
                  int y = (i%numY);
                  int z = i/(numX*numY);
                  payoffEntryN *pen = pm.getPayoff(x,y,z);
                  o << "(" << pen->getX() << "," << pen->getY() << "," << pen->getZ() << ")";
                  s[i] = o.str();
               }
               return s;
            }
            
            virtual void drawLines(double** l, int size)
            {
               for(int i=0; i<size; i++)
               {
                  g->drawLine3D(l[i][0], l[i][1], l[i][2], l[i][3], l[i][4], l[i][5]);
               }        
            }
            
            virtual void drawPoints(double** p, int size)
            {
               for(int i=0; i<size; i++)
               {
                  g->drawPoint3D(p[i][0], p[i][1], p[i][2]);
               }
            }
            
            void drawCustomPoints(double **p, int size, double pointSize)
            {
               for(int i=0; i<size; i++)
               {
                  g->drawCustomPoint(p[i][0], p[i][1], p[i][2], pointSize);
               }
            }
            
            virtual void drawTexts(string* s, int size)
            {
               double **p = pLocations;
               for(int i=0; i<size; i++)
               {
                  double x = p[i][0]+0.2;
                  double y = p[i][1]+0.4;
                  double z = p[i][2];
                  g->drawText3D(x, y, z, s[i]);
               }
               //for drawing names on screen
               double ntx, nty, ntz;
               string name;
               
               //Rose
               ntx = minX - dNameToCube - distanceLineToPoint;
               nty = 0;
               ntz = maxZ;
               name ="Rose";
               g->drawText3D(ntx, nty, ntz, name);

               //Colin
               ntx = 0;
               nty = maxY + distanceLineToPoint;
               ntz = maxZ + dNameToCube;
               name ="Colin";
               g->drawText3D(ntx, nty, ntz, name);
               
               //Larry
               ntx = minX - dNameToCube - distanceLineToPoint;
               nty = maxY + distanceLineToPoint;
               ntz = 0;
               name ="Larry";
               g->drawText3D(ntx, nty, ntz, name);
            }
            
            virtual void drawArrows(payoffMatrixN& pm)
            {
               int numX = pm.getNumX();
               int numY = pm.getNumY();
               int numZ = pm.getNumZ();
               int numPoints = numX * numY * numZ;
               double nax, nay, naz;
               //draw arrow for Rose
               nax = minX-dNameToCube;
               nay = maxY-dNameToCube;
               naz = maxZ;
               g->drawArrow3D(nax, nay, naz, 1);
               nax = minX-dNameToCube;
               nay = minY+dNameToCube;
               naz = maxZ;
               g->drawArrow3D(nax, nay, naz, 2);
               
               //draw arrow for Colin
               nax = minX+dNameToCube;
               nay = maxY;
               naz = maxZ+dNameToCube;
               g->drawArrow3D(nax, nay, naz, 3);
               nax = maxX-dNameToCube;
               nay = maxY;
               naz = maxZ+dNameToCube;
               g->drawArrow3D(nax, nay, naz, 4);
               
               //draw arrow for Larry
               nax = minX-dNameToCube;
               nay = maxY;
               naz = minZ+dNameToCube;
               g->drawArrow3D(nax, nay, naz, 5);
               nax = minX-dNameToCube;
               nay = maxY;
               naz = maxZ-dNameToCube;
               g->drawArrow3D(nax, nay, naz, 6);
               
               
               for(int i=0; i<numPoints; i++)
               {
                  int x = (i%(numX*numY))/numY;
                  int y = (i%numY);
                  int z = i/(numX*numY);
                  //along x axis
                  if((i%numY)<(numY-1))
                  {
                     if(pm.getPayoff(x,y,z)->getY() > pm.getPayoff(x,y+1,z)->getY())
                     {
                        double xc = pLocations[i][0]+0.5;
                        double yc = pLocations[i][1];
                        double zc = pLocations[i][2];
                        g->drawArrow3D(xc, yc, zc, 3);
                     }
                     if(pm.getPayoff(x,y,z)->getY() < pm.getPayoff(x,y+1,z)->getY())
                     {
                        double xc = pLocations[i+1][0]-0.5;
                        double yc = pLocations[i+1][1];
                        double zc = pLocations[i+1][2];
                        g->drawArrow3D(xc, yc, zc, 4);
                     }
                  }
                  //along y axis
                  if((i%(numX*numY))<numY*(numX-1))
                  {
                     if(pm.getPayoff(x,y,z)->getX() > pm.getPayoff(x+1,y,z)->getX())
                     {
                        double xc = pLocations[i][0];
                        double yc = pLocations[i][1]-0.5;
                        double zc = pLocations[i][2];
                        g->drawArrow3D(xc, yc, zc, 1);
                     }
                     if(pm.getPayoff(x,y,z)->getX() < pm.getPayoff(x+1,y,z)->getX())
                     {
                        double xc = pLocations[i+numY][0];
                        double yc = pLocations[i+numY][1]+0.5;
                        double zc = pLocations[i+numY][2];
                        g->drawArrow3D(xc, yc, zc, 2);
                     }
                  }
                  //along z axis
                  if((i%(numX*numY*numZ))<numX*numY*(numZ-1))
                  {
                     if(pm.getPayoff(x,y,z)->getZ() > pm.getPayoff(x,y,z+1)->getZ())
                     {
                        double xc = pLocations[i][0];
                        double yc = pLocations[i][1];
                        double zc = pLocations[i][2] - 0.5;
                        g->drawArrow3D(xc, yc, zc, 6);
                     }
                     if(pm.getPayoff(x,y,z)->getZ() < pm.getPayoff(x,y,z+1)->getZ())
                     {
                        double xc = pLocations[i+numX*numY][0];
                        double yc = pLocations[i+numX*numY][1];
                        double zc = pLocations[i+numX*numY][2] + 0.5;
                        g->drawArrow3D(xc, yc, zc, 5);
                     }
                  }
               }
            }
};

#endif
