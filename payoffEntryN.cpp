#include "payoffEntryN.h"

string payoffEntryN::getValue()
{
   string s="(";
   char t[2];
   sprintf(t, "%d, ", (int)entry[0]);
   s+=t;
   sprintf(t, "%d, ", (int)entry[1]);
   s+=t;
   sprintf(t, "%d)", (int)entry[2]);
   s+=t;
   return s;
}

bool payoffEntryN::IsZeroSumEntry()
{
   return ((int)entry[0]+(int)entry[1]+(int)entry[2]==0);
}
