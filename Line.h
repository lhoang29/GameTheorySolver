#ifndef _Line_H
#define _Line_H
#include "Point.h"
#include "RationalNumber.h"

using namespace std;

class Line
{
      private:
              //two pointers to define start and end of line
              Point<int> *start, *end;
              bool marked;
              
              //slope and intercept to describe the line geometry
              //these will NOT be computed automatically unless
              //findSlope or findIntercept has been called.
              RationalNumber *slope, *intercept;
      public:
              //constructor set start and end to default origin
              Line():start(new Point<int>(0,0)), end(new Point<int>(0,0))
              {
                 slope = intercept = (RationalNumber*)NULL;
                 marked = false;
              }
              
              //set start and end points to specified values
              Line(Point<int>& s, Point<int>& e)
              {
                 start=&s;
                 end=&e;
                 slope = intercept = (RationalNumber*)NULL;
                 marked = false;
              }
              
              //return the start point
              Point<int>* getStart(){return start;}
              
              //return the end point
              Point<int>* getEnd(){return end;}
              
              //compute slope for the line
              void findSlope();
              
              //compute intercept
              void findIntercept();
              
              //return line formula in the form y = ax + b
              string getValue();
              
              //return slope
              RationalNumber* getSlope(){return slope;}
              
              //return intercept
              RationalNumber* getIntercept(){return intercept;}
              
              //return the point of intersection with specified line
              Point<RationalNumber>* Intersect(Line& L);
              
              //find the height of the line at specified value x
              RationalNumber* getHeight(RationalNumber& x);
              
              //overload operator = assignment
              Line* operator=(Line& rhs);
              
              //this marks the object as marked
              void mark();
              
              //this restores the object
              void unmark();
              
              //return whether a line has been marked
              bool isNotMarked()
              {
                   return (marked==false);
              }
};

#endif
