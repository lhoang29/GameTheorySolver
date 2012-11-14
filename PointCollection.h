#ifndef _PointCollection_h
#define _PointCollection_h
#include "Collection.h"
#include "Point.h"
#include "RationalNumber.h"

template <class T>
class PointCollection : public Collection< Point<T> >
{
      public:
             PointCollection():Collection< Point<T> >(){}
             PointCollection(int s) : Collection< Point<T> >(s){}
             virtual string getValue(){}
};

#endif
