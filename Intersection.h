#ifndef _intersection_h
#define _intersection_h
#include "Point.h"

//this class instantiates an object with a point of intersection
//between two lines whose indexes from the lines collection are stored
class Intersection
{
      private:
              //this point represents the point of intersection
              Point<RationalNumber> point;
              
              //these represent the indexes of the two lines in the line collection
              //that form the intersection
              int indexLine1, indexLine2;
      public:
              Intersection()
              {
                 indexLine1 = indexLine2 = -1;
              }
              Intersection(Point<RationalNumber>& p, int l1, int l2)
              {
                 point = p;
                 indexLine1 = l1;
                 indexLine2 = l2;
              }
              
              Point<RationalNumber>& getPoint() {return point;}
              int getIndexLine1() {return indexLine1;}
              int getIndexLine2() {return indexLine2;}
              void setPoint(Point<RationalNumber>& p){point = p;}
              void setIndexLine1(int i) {indexLine1 = i;}
              void setIndexLine2(int i) {indexLine2 = i;}
};


#endif
