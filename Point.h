#ifndef _Point_H
#define _Point_H

template <class T>
class Point
{
      private:
              T x, y;
      public:
              //default constructor set point to origin
              Point(){}
              
              //set point to specified value
              Point(T a, T b):x(a), y(b){}
              
              //set X value
              void setX(T a){x=a;}
              
              //set Y value
              void setY(T a){y=a;}
              
              //set coordinates
              void setXY(T a, T b){x=a;y=b;}
              
              //return X value
              T getX(){return x;}
              
              //return Y value
              T getY(){return y;}
              
              //overload operator = assignment
              Point<T>& operator=(Point<T>& rhs)
              {
                 x = rhs.getX();
                 y = rhs.getY();
                 return *this;
              }
};

#endif
