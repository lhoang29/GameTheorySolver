#ifndef _payoffEntryN_h
#define _payoffEntryN_h
#include <string>
using namespace std;

//represent a payoff entry in a n-person matrix
class payoffEntryN
{
      private:
             //entry will be 
             double* entry;
             int size;
      public:
             //default constructor will assume for 3-person game
             payoffEntryN():size(3){entry = new double[3];}
             payoffEntryN(int s):size(s){entry = new double[s];}
             payoffEntryN(double* e, int s):entry(e), size(s){}
             double getX(){return entry[0];}
             double getY(){return entry[1];}
             double getZ(){return entry[2];}
             void setX(double x){entry[0] = x;}
             void setY(double y){entry[1] = y;}
             void setZ(double z){entry[2] = z;}
             string getValue();
             bool IsZeroSumEntry();
             int getSize(){return size;}
};

#endif
