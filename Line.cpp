#include "Line.h"
#include <string>
#include <iostream>

Point<RationalNumber>* Line::Intersect(Line& L)
{
   //if both slopes are valid then proceed with the compute value otherwise null
   if(slope->getNumerator() != 999 && L.getSlope()->getNumerator() != 999)
   {
      RationalNumber a1 = *slope;
      RationalNumber b1 = *intercept;
      RationalNumber a2 = *(L.getSlope());
      RationalNumber b2 = *(L.getIntercept());
      
      if(a1==a2)
      {
         return (Point<RationalNumber>*)NULL;
      }
      else
      {
          RationalNumber rnX = (b2-b1)/(a1-a2);
          RationalNumber* rnY = getHeight(rnX);
          
          //create the point of intersection to store in the Intersection object
          Point<RationalNumber> *p = new Point<RationalNumber>(rnX, *rnY);
          
          //if the intersection is inside the region 0<=x<=1 then return
          if(p->getX().getDecimalValue()>=0 && p->getX().getDecimalValue()<=1)
          return p;
          //else do not return
          else
          return (Point<RationalNumber>*)NULL;
      }
   }
   return (Point<RationalNumber>*)NULL;
}

void Line::findSlope()
{
   int a = start->getX();
   int b = start->getY();
   int c = end->getX();
   int d = end->getY();
   
   //if line is vertical then invalid
   if(c==a) slope = new RationalNumber(999);
   
   //else compute the slope
   else     slope = new RationalNumber(d-b, c-a);
}

void Line::findIntercept()
{
   int a = start->getX();
   int b = start->getY();
   int c = end->getX();
   int d = end->getY();
   
   //if line is vertical then invalid
   if(c==a) intercept = new RationalNumber(999);
   
   //else compute the intercept
   else     intercept = new RationalNumber(b*c-d*a, c-a);
}

string Line::getValue()
{
   char startX[5], startY[5], endX[5], endY[5];
   sprintf(startX, "%d", start->getX());
   sprintf(startY, "%d", start->getY());
   sprintf(endX, "%d", end->getX());
   sprintf(endY, "%d", end->getY());
   string s = "";
   s += "Line from: ("; s += startX; s += ","; s += startY;
   s += ") "; s += "to ("; s += endX; s += ","; s += endY;
   s += ")\n"; s += "y = ";

   //if slope or intercept has not been computed.
   if(slope == (RationalNumber*)NULL || intercept == (RationalNumber*)NULL)
   {
      s += "Slope or Intercept has not been computed.";
      return s;
   }
   //if slope or intercept is invalid meaning line is invalid, print message
   if(slope->getNumerator() == 999 || intercept->getNumerator() == 999)
   {
      s += "Invalid line.";
      return s;
   }
   //if slope is 1 then don't have to display
   if(slope->getNumerator() != 1 || slope->getDenominator() != 1)
   s += slope->getValue();
   s += "x";
   //if intercept already contains minus sign then no need to display it again
   if(intercept->getDecimalValue() < 0)
      s += intercept->getValue();
   //if intercept is positive then display plus sign
   if(intercept->getDecimalValue() > 0)
      s += "+" + intercept->getValue();
      
   //if intercept is zero then no need to display
   return s;
}

RationalNumber* Line::getHeight(RationalNumber& x)
{
   //get the value of these pointers so that operation * can apply
   RationalNumber rnSlope = (*slope);
   RationalNumber rnIntercept = (*intercept);
   RationalNumber rnReturn = rnSlope*x + rnIntercept;
   
   //return pointer
   return new RationalNumber(rnReturn.getNumerator(), rnReturn.getDenominator());
}

Line* Line::operator=(Line& rhs)
{
   *start = *(rhs.getStart());
   *end = *(rhs.getEnd());
   slope = rhs.getSlope();
   intercept = rhs.getIntercept();
   marked = !(rhs.isNotMarked());
}

void Line::mark()
{
   marked = true;
}

void Line::unmark()
{
   marked = false;
}
