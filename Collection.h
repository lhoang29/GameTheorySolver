#ifndef _collection_h
#define _collection_h
#include <string>
#include <iostream>

using namespace std;

template <class T>
class Collection
{
      protected:
              //elements is an array containing T items
              T* elements;
              //size of elements[]
              int size;
              //top points to the last element
              int top;
      public:
              Collection():size(-1){}
              //initialize the collection with specified size
              Collection(int s)
              {
                 size = s; top=0;
                 elements = new T[size];
              }
              
              //initialize the collection with specified size and array
              Collection(int s, T& e){size = s; top=0; elements = e;}
              
              //return the line element at the specified index
              T getElement(int index)
              { 
                 T toReturn;
                 //make sure the index is within allowable range
                 if(index < top)
                    toReturn = elements[index];
                 return toReturn;
              }
              
              /*All these virtual methods below are implemented so because
                these are specific to Collection<Line> class and for other
                class types, one can override these methods for different 
                functionalities.*/
              
              //add new element to the collection
              virtual void push(T& t)
              {
                 if(top < size)
                 {
                    elements[top] = t;
                    top++;
                 }
              }
              
              //get the top element
              virtual T pop()
              {
                  T toReturn;
                  if(top > 0)
                  {
                     toReturn = elements[top-1];
                     //decrease top to the next element
                     top--;
                  }
                  return toReturn;
              }
              
              //print out elements values
              virtual string getValue(){}
              
              bool isNull()
              {
                  return (size == -1);
              }
              
              int getTop(){return top;}
              int getSize(){return size;}
};
#endif
