#ifndef _RationalNumber_h
#define _RationalNumber_h
#include <string>

using namespace std;

/*this class will hold all numbers in original fractional form
  for better displaying format*/
class RationalNumber
{
      private:
              int numerator, denominator;
      public:
              //initialize a rational number with default value 0/1
              RationalNumber():numerator(0), denominator(1){}
              
              //initialize a rational number with default value no denominator
              RationalNumber(int a): numerator(a), denominator(1){}
              
              //initialize a rational number with values specified
              RationalNumber(int a, int b);
              
              //return numerator
              int getNumerator(){return numerator;}
              
              //return denominator
              int getDenominator(){return denominator;}
              
              //set numerator to a specified value
              void setNumerator(int a){numerator = a;}

              //set denominator to a specified value
              void setDenominator(int a){denominator =a;}

              //return value of rational number in a string format
              string getValue();
              
              //return value of rational number in decimal format
              double getDecimalValue(){return (double)numerator/denominator;}
              
              //reduce a rational number
              void reduce();
              
              //overload operator -
              RationalNumber operator-(RationalNumber rn);
              
              //overload operator +
              RationalNumber operator+(RationalNumber rn);
              
              //overload operator *
              RationalNumber operator*(RationalNumber rn);
              
              //overload operator /
              RationalNumber operator/(RationalNumber rn);
              
              //overload operator ==
              bool operator==(RationalNumber rn);
              
              //overload operator <=
              bool operator<=(RationalNumber rn);
              
              //overload operator >=
              bool operator>=(RationalNumber rn);
              
              //overload operator <
              bool operator<(RationalNumber rn);
              
              //overload operator >
              bool operator>(RationalNumber rn);
              
              //overload operator =
              RationalNumber operator=(RationalNumber rn);
};


#endif
