#ifndef _baseMatrix_h
#define _baseMatrix_h
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class baseMatrix
{
      public:
             virtual string getValue() = 0;
             static bool checkNPersonGame(char *fileName, int firstEntry, int secondEntry)
             {
                bool nPerson = false;
                int temp;
                int count=0;
                ifstream inFile(fileName);
                inFile >> temp >> temp;
                while(!inFile.eof())
                {
                   count++;
                   inFile >> temp;
                }
                nPerson = (count > 2*firstEntry*secondEntry);
                inFile.close();
                return nPerson;
             }
             static bool check2PersonZeroSum(char *fileName, int firstEntry, int secondEntry)
             {
                bool zeroSum = true;
                int temp;
                int count=0;
                ifstream inFile(fileName);
                inFile >> temp >> temp;
                while(!inFile.eof())
                {
                   inFile >> temp;
                   count++;
                }
                zeroSum = (count < 2*firstEntry*secondEntry);
                inFile.close();
                return zeroSum;
             }
};


#endif
