#ifndef _LineCollection_h
#define _LineCollection_h
#include <vector>

class LineCollection : public Collection<Line>
{
    public:
           LineCollection():Collection<Line>(){}
           LineCollection(int s):Collection<Line>(s){} 
           
           virtual string getValue()
           {
              char t[3];
              string s="";
              for(int i=0; i<top; i++)
              {
                 sprintf(t, "%d. ", i+1);
                 s += t + elements[i].getValue();
                 if(i!=(top-1))
                 s += "\n";
              }
              return s;
           }
           
           //get the index of the line in the collection with highest value
           //at specified x-coordinate, return -1 if collection contains all disposed
           //lines or is empty
           int getHighestLine(RationalNumber& x)
           {
              int index = -1;
              int max = -999;
              for(int i=0; i<top; i++)
              {
                 if(elements[i].isNotMarked() && elements[i].getHeight(x)->getDecimalValue() >= max)
                 {
                    max = (int)elements[i].getHeight(x)->getDecimalValue();
                    index = i;
                 }
              }
              return index;
           }
           
           //get the index of the line in the collection with lowest value
           //at specified x-coordinate, return -1 if collection contains all disposed
           //lines or is empty
           int getLowestLine(RationalNumber& x)
           {
              int index = -1;
              int min = 999;
              for(int i=0; i<top; i++)
              {
                 if(elements[i].isNotMarked() && elements[i].getHeight(x)->getDecimalValue() <= min)
                 {
                    min = (int)elements[i].getHeight(x)->getDecimalValue();
                    index = i;
                 }
              }
              return index;
           }
           
           //this marks the line item at specified index
           void markLine(int lineIndex)
           {
              if(lineIndex >=0 && lineIndex < top)
              {
                 elements[lineIndex].mark();
              }
           }
           //this unmarks the line item at specified index
           void unmarkLine(int lineIndex)
           {
              if(lineIndex >=0 && lineIndex < top)
              {
                 elements[lineIndex].unmark();
              }
           }
           //get the highest intersection with other lines, return index
           //of the line that forms this intersection with a line of
           //given index, otherwise return -1 if the collection 
           //either is empty or contains all disposed lines
           int getHighestIntersection(int index)
           {
              Point<RationalNumber> d;
              RationalNumber p;
              return getHighestIntersection(index, d, false, p);
           }
           
           int getHighestIntersection(int index, Point<RationalNumber>& d, 
                                      bool needHeight, RationalNumber& previous)
           {
              Point<RationalNumber> initialD;
              d = initialD;
              int indexReturn = -1;
              if(elements[index].isNotMarked())
              {
                  RationalNumber max(-999);
                  Point<RationalNumber> *p, *tempP;
                  for(int i=0; i<top; i++)
                  {
                     if(i!=index && elements[i].isNotMarked())
                     {
                        //get intersection of line with other lines
                        p = elements[index].Intersect(elements[i]);
                        
                        //if they do intersect within valid region then continue
                        if(p!= (Point<RationalNumber>*)NULL)
                        {
                            RationalNumber height = p->getY();
                            if(height > max && p->getX() > previous)
                            {
                               tempP = p;
                               max = height;
                               indexReturn = i;
                            }
                        }
                     }
                  }
                  if(needHeight)
                  {
                     d = *(tempP);
                     previous = tempP->getX();
                  }
              }
              return indexReturn;
           }
           
           //get the lowest intersection with other lines, return index
           //of the line that forms this intersection with a line of
           //given index, otherwise return -1 if the collection 
           //either is empty or contains all disposed lines
           int getLowestIntersection(int index)
           {
              Point<RationalNumber> d;
              RationalNumber p;
              return getLowestIntersection(index, d, false, p);
           }
           
           int getLowestIntersection(int index, Point<RationalNumber>& d, 
                                     bool needHeight, RationalNumber& previous)
           { 
              Point<RationalNumber> initialD;
              d = initialD;
              int indexReturn = -1;
              if(elements[index].isNotMarked())
              {
                  RationalNumber min(999);
                  Point<RationalNumber> *p, *tempP;
                  for(int i=0; i<top; i++)
                  {
                     if(i!=index && elements[i].isNotMarked())
                     {
                        //get intersection of line with other lines
                        p = elements[index].Intersect(elements[i]);
                        
                        //if they do intersect within valid region then continue
                        if(p!= (Point<RationalNumber>*)NULL)
                        {
                            RationalNumber height = p->getY();
                            if(height < min && p->getX() > previous)
                            {
                               tempP = p;
                               min = height;
                               indexReturn = i;
                            }
                        }
                     }
                  }
                  if(needHeight)
                  {
                     d = *(tempP);
                     previous = tempP->getX();
                  }
              }
              return indexReturn;
           }
           
           //solve envelope to find 2x2 sub game
           //upper specifies whether to find upper envelope or lower
           Intersection* getEnvelopeSolution(bool upper)
           {
              vector<int> v;
              Intersection *iReturn = (Intersection*)NULL;
              if(upper)
              {
                 
                 RationalNumber r(0,1);
                 //get the starting line index of highest value at x=0
                 int sIndex = getHighestLine(r);
                 //if return value is valid
                 if(sIndex != -1)
                 {
                    int nIndex = sIndex;
                    Point<RationalNumber> d1;
                    Point<RationalNumber> d2;
                    
                    //stores the first line index
                    int tempIndex = nIndex;
                    
                    //push the index of the line onto the vector
                    v.push_back(tempIndex);
                    
                    //get first highest intersection and next line index
                    nIndex = getHighestIntersection(nIndex, d1, true, r);
                    
                    //set d2 to proper value for looping
                    d2 = d1;
                    
                    //while next line is valid and minimum not found yet
                    while(nIndex != -1 && d2.getY() <= d1.getY() && d2.getX() >= d1.getX())
                    {
                       //update value of d1 so that d1 always points to the one before d2
                       d1 = d2;
                       //remove previous line
                       markLine(tempIndex);
                       //save the line index
                       tempIndex = nIndex;
                       //push the index of the line onto the vector
                       v.push_back(tempIndex);
                       //get next line index
                       nIndex = getHighestIntersection(nIndex, d2, true, r);
                    }
                    iReturn = new Intersection();
                    iReturn->setIndexLine1(v.back());
                    v.pop_back();
                    iReturn->setIndexLine2(v.back());
                    iReturn->setPoint(d1);
                 }
              }
              else
              {
                 RationalNumber r(0,1);
                 //get the starting line index of highest value at x=0
                 int sIndex = getLowestLine(r);
                 //if return value is valid
                 if(sIndex != -1)
                 {
                    int nIndex = sIndex;
                    Point<RationalNumber> d1;
                    Point<RationalNumber> d2;
                    
                    //stores the first line index
                    int tempIndex = nIndex;
                    
                    //push the index of the line onto the vector
                    v.push_back(tempIndex);
                    
                    //get first lowest intersection and next line index
                    nIndex = getLowestIntersection(nIndex, d1, true, r);
                    //set d2 to proper value for looping
                    d2 = d1;
                    
                    //while next line is valid and minimum not found yet
                    while(nIndex != -1 && d2.getY() >= d1.getY() && d2.getX() >= d1.getX())
                    {
                       //update value of d1 so that d1 always points to the one before d2
                       d1 = d2;
                       //remove previous line
                       markLine(tempIndex);
                       //save the line index
                       tempIndex = nIndex;
                       //push the index of the line onto the vector
                       v.push_back(tempIndex);
                       //get next line index
                       nIndex = getLowestIntersection(nIndex, d2, true, r);
                    }
                    iReturn = new Intersection();
                    iReturn->setIndexLine1(v.back());
                    v.pop_back();
                    iReturn->setIndexLine2(v.back());
                    iReturn->setPoint(d1);
                 }
              }
              
              //this restores the line collection to all unmarked
              for(int i=0; i<top; i++)
                 elements[i].unmark();
              
              return iReturn;
           }
           
           int getMinY()
           {
               int min = 999;
               for(int i=0; i<size; i++)
               {
                  if(elements[i].getStart()->getY() <= min)
                     min = elements[i].getStart()->getY();
                  if(elements[i].getEnd()->getY() <= min)
                     min = elements[i].getEnd()->getY();
               }
               return min;
           }
           
           int getMaxY()
           {
               int max = -999;
               for(int i=0; i<size; i++)
               {
                  if(elements[i].getStart()->getY() >= max)
                     max = elements[i].getStart()->getY();
                  if(elements[i].getEnd()->getY() >= max)
                     max = elements[i].getEnd()->getY();
               }
               return max;
           }
           
};

#endif
