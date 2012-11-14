#ifndef _payoffMatrix_h
#define _payoffMatrix_h
#include "baseMatrix.h"
#include "RationalNumber.h"
#include "Intersection.h"
#include "Collection.h"
#include "Line.h"
#include "payoffEntryN.h"
#include <fstream>
#include <sstream>

using namespace std;
class payoffMatrix : public baseMatrix
{
      private:
              double **matrix;
              //matrixNzs is to hold the matrix information for non zero sum 2 person game
              payoffEntryN ***matrixNzs;
              int numRows, numCols;
              bool ZeroSum;
      public:
              payoffMatrix(int nr, int nc):numRows(nr), numCols(nc)
              {
                 matrix = new double*[nr];
                 for(int i=0; i<nr; i++)
                 {
                    matrix[i] = new double[nc];
                 }
                 ZeroSum = true;
              }
              
              payoffMatrix(int nr, int nc, bool zeroSum):numRows(nr), numCols(nc)
              {
                 if(zeroSum)
                 {
                     matrix = new double*[nr];
                     for(int i=0; i<nr; i++)
                     {
                        matrix[i] = new double[nc];
                     }
                 }
                 else
                 {
                     matrixNzs = new payoffEntryN**[nr];
                     for(int i=0; i<nr; i++)
                     {
                        matrixNzs[i] = new payoffEntryN*[nc];
                        for(int j=0; j<nc; j++)
                        {
                           matrixNzs[i][j] = new payoffEntryN(2);
                        }
                     }
                 }
                 ZeroSum = zeroSum;
              }
              
              payoffMatrix(double **m, int nr, int nc);
              
              payoffMatrix(payoffEntryN ***m, int nr, int nc);
              
              static payoffMatrix* createGameNzs(char* fileName, int row, int col)
              {
                payoffEntryN ***myGame = new payoffEntryN**[row];
                for(int i=0; i<row; i++)
                {
                   myGame[i] = new payoffEntryN*[col];
                   for(int j=0; j<col; j++)
                   {
                      myGame[i][j] = new payoffEntryN(2);
                   }
                }
                //Reads input from file and store in arrays
                ifstream inFile(fileName);
                if(inFile.is_open())
                {
                    int a;
                    inFile >> a >> a;
                    int i=0, j=0;
                    while(!inFile.eof())
                    {
                        inFile >> a;
                        myGame[i][j]->setX(a); // Rose
                        inFile >> a;             
                        myGame[i][j]->setY(a); // Colin
                        j++;
                        if(j==col)
                        {
                           j = 0;
                           i++;
                        }
                    }
                    inFile.close();
                }
                else
                {
                   cout << "File does not exist or is corrupted." << endl;
                   system("PAUSE");
                   exit(0);
                }
                return new payoffMatrix(myGame,row,col);
              }
              
              static payoffMatrix* createGame(char* fileName, int row, int col)
              {
                double **myGame = new double*[row];
                for(int i=0; i<row; i++)
                {
                   myGame[i] = new double[col];
                }
                //Reads input from file and store in arrays
                ifstream inFile(fileName);
                if(inFile.is_open())
                {
                    int a,b;
                    inFile >> a >> b;
                    delete &a, &b;
                    int i=0, j=0;
                    while(!inFile.eof())
                    {
                        inFile >> myGame[i][j];
                        j++;
                        if(j==col)
                        {
                           j = 0;
                           i++;
                        }
                    }
                    inFile.close();
                }
                else
                {
                   cout << "File does not exist or is corrupted." << endl;
                   system("PAUSE");
                   exit(0);
                }
                return new payoffMatrix(myGame,row,col);
              }
              
              //this will transpose the matrix
              payoffMatrix* transpose();
              
              //this set the matrix values to those of parameter m
              void setValues(double **m);
              
              //this returns a description of the matrix
              string getValue();
              string getValueNzs();
              
              //return number of rows
              int getNumRows()
              {return numRows;}
              
              //return whether the matrix is square
              bool isSquare()
              {return (numRows == numCols);}
              
              //return whether the matrix can be solved using envelope
              bool Envelopable()
              {
                 return(numRows == 2 || numCols == 2);
              }
              
              //return number of columns
              int getNumCols()
              {return numCols;}
              
              //return payoff at position x and y
              double getPayoff(int x, int y);
              payoffEntryN* getPayoff(int x, int y, bool zeroSum)
              {
                 if(!zeroSum)
                 return matrixNzs[x][y];
                 else
                 return (payoffEntryN*)NULL;
              }
              
              //set the payoff at position x and y to d
              void setPayoff(int x, int y, double d);
              void setPayoffNzs(int x, int y, double dx, double dy);
              
              //return a vector containing 'Y' positions of all row minimums
              vector<int> getRowMinimums(int x);
              
              //return a vector containing 'X' positions of all column maximums
              vector<int> getColMaximums(int y);
              
              //returns the row extrema
              double getRowExtrema(bool min, int row, bool zeroSum);
              
              //returns the column extrema
              double getColExtrema(bool min, int col, bool zeroSum);
              
              //return positions of all saddle points
              vector<int*> getSaddlePoints();
              
              //check whether an entry is the maximum of a row
              bool isRowMaximum(int row, int colIndex);
              
              //check whether an entry is the maximum of a column
              bool isColMaximum(int col, int rowIndex);
              
              //compute mixed strategy solution of game
              RationalNumber** solveMixedStrategyMatrix();
              
              //this function takes the coordinates of the matrix and generate
              //corresponding lines for visualization
              Collection<Line>* generateLines();
              
              //this write out to file all attempted solutions of the game
              void writeSolutions(ofstream& outFile);
              
              bool isZeroSum(){return ZeroSum;}
              
              //player = 1 then Rose, player = 2 then Colin
              payoffMatrix* getZeroSumSubGame(int player);
};



#endif
