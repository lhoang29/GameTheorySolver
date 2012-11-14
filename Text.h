#ifndef _Text_h
#define _Text_h
#include "Point.h"
#include "RationalNumber.h"
#include <string>

using namespace std;

class Text
{
      private:
              Point<double> position;
              string description;
      public:
              Text()
              {
                 description = "";
                 position.setX(0);
                 position.setY(0);
              }
              Text(Point<double>& p, string& s):position(p), description(s){}
              void setPosition(Point<double>& p){ position = p; }
              void setDescription(string s){ description = s; }
              Point<double> getPosition() { return position; }
              string getDescription() { return description; }
              string getValue(){}
};


#endif
