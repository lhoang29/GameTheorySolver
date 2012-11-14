#include "RationalNumber.h"
#include <iostream>
#include <math.h>

//return greatest common divisor of a and b integers
int gcd(int a, int b)
{
   if(a < b) return gcd(b, a);
   if(a%b == 0) return b;
   else
   return gcd(b, a%b);
}

//constructor accepting two values 
RationalNumber::RationalNumber(int a, int b)
{
   if(b==0 || a==0)
   {
      //if error set default values for rational number
      numerator = 0;
      denominator = 1;
   }
   else
   {
      numerator = a;
      denominator = b;
      //after initializing the rational number, automatically reduce
      reduce();
   }
}

//return string format of the rational number
string RationalNumber::getValue()
{
   char s[10];
   if(numerator==0)
      sprintf(s, "%d", numerator);
   else
       if(denominator != 1)
          sprintf(s, "%d/%d", numerator, denominator);
       else
          sprintf(s, "%d", numerator);
   return s;
}


//reduce the rational number
void RationalNumber::reduce()
{
     //using absolute value since % operation does not work with negative values
     int m = gcd(abs(numerator), abs(denominator));
     numerator = numerator/m;
     denominator = denominator/m;
     //after reducing, if they are both negative then can ignore minus sign
     //or if only denominator is negative then switch minus sign for better format
     if(denominator < 0)
     {
        numerator = -numerator;
        denominator = -denominator;
     }
 
}    

//definition for overload method operator -
RationalNumber RationalNumber::operator-(RationalNumber rn)
{
   return RationalNumber(numerator*rn.denominator-rn.numerator*denominator,denominator*rn.denominator);
}

//definition for overload method operator +
RationalNumber RationalNumber::operator+(RationalNumber rn)
{
   return RationalNumber(numerator*rn.denominator+rn.numerator*denominator,denominator*rn.denominator);
}

//definition for overload method operator *
RationalNumber RationalNumber::operator*(RationalNumber rn)
{
   return RationalNumber(numerator*rn.numerator, denominator*rn.denominator);
}

//definition for overload method operator /
RationalNumber RationalNumber::operator/(RationalNumber rn)
{
  return RationalNumber(numerator*rn.denominator, denominator*rn.numerator);
}

//definition for overload method operator ==
bool RationalNumber::operator==(RationalNumber rn)
{
   return((numerator==rn.numerator && denominator==rn.denominator) || 
          (numerator==rn.numerator && numerator==0));
}

//definition for overload method operator <=
bool RationalNumber::operator<=(RationalNumber rn)
{
   return(numerator*rn.getDenominator() <= denominator*rn.getNumerator());
}

//definition for overload method operator >=
bool RationalNumber::operator>=(RationalNumber rn)
{
   return(numerator*rn.getDenominator() >= denominator*rn.getNumerator());
}

//definition for overload method operator <
bool RationalNumber::operator<(RationalNumber rn)
{
   return (numerator*rn.getDenominator() < denominator*rn.getNumerator());
}

//definition for overload method operator >
bool RationalNumber::operator>(RationalNumber rn)
{
   return (numerator*rn.getDenominator() > denominator*rn.getNumerator());
}
//definition for overload method operator =
RationalNumber RationalNumber::operator=(RationalNumber rn)
{
   numerator = rn.numerator;
   denominator = rn.denominator;
}
