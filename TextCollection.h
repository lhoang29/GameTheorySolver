#ifndef _TextCollection_h
#define _TextCollection_h
#include "Text.h"

class TextCollection : public Collection<Text>
{
      public:
             TextCollection():Collection<Text>(){}
             TextCollection(int a):Collection<Text>(a){}
             virtual string getValue(){}
};

#endif
