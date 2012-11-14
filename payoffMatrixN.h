#ifndef _payoffMatrixN_h
#define _payoffMatrixN_h
#include "baseMatrix.h"
#include "payoffMatrix.h"
#include "payoffEntryN.h"
#include <vector>

class payoffMatrixN : public baseMatrix
{
      private:
              //this holds the game in 3-dimensional array form
              //each entry of the matrix is an array of 3 doubles 
              //representing payoffs to three players.
              payoffEntryN ****matrix;
              
              //numX is number of choices for Rose
              //numY is number of choices for Colin
              //numZ is number of choices for Larry
              int numX, numY, numZ;
      public:
             ~payoffMatrixN(){delete matrix;}
             
              //create an empty 3-dimensional matrix with specified size
              //and uninitialized values
              payoffMatrixN(int nx, int ny, int nz) : numX(nx), numY(ny), numZ(nz)
              {
                 matrix = new payoffEntryN***[nx];
                 for(int i=0; i<nx; i++)
                 {
                    matrix[i] = new payoffEntryN**[ny];
                    for(int j=0; j<ny; j++)
                    {
                       matrix[i][j] = new payoffEntryN*[nz];
                       for(int k=0; k<nz; k++)
                       {
                          matrix[i][j][k] = new payoffEntryN(3);
                       }
                    }
                 }
              }
              
              //use the specified 3-dimensional array to create the
              //appropriate matrix and initialize values
              payoffMatrixN(payoffEntryN ****m, int nx, int ny, int nz)
              {
                 matrix = m;
                 numX = nx;
                 numY = ny;
                 numZ = nz;
              }
              
              //this static function reads the file using the file name and return
              //a pointer to the 3-person matrix game.
              static payoffMatrixN* createGame(char* fileName, int nx, int ny, int nz)
              {
                 payoffEntryN ****m = new payoffEntryN***[nx];
                 for(int i=0; i<nx; i++)
                 {
                    m[i] = new payoffEntryN**[ny];
                    for(int j=0; j<ny; j++)
                    {
                       m[i][j] = new payoffEntryN*[nz];
                       for(int k=0; k<nz; k++)
                       {
                          m[i][j][k] = new payoffEntryN(3);
                       }
                    }
                 }
                 ifstream inFile(fileName);
                 if(inFile.is_open())
                 {
                     double temp;
                     inFile >> temp >> temp >> temp;
                     int i=0, j=0, k=0;
                     while(!inFile.eof())
                     {
                        //initialize each payoff entry
                        inFile >> temp;
                        m[i][j][k]->setX(temp); //Rose
                        inFile >> temp;
                        m[i][j][k]->setY(temp); //Colin
                        inFile >> temp;
                        m[i][j][k]->setZ(temp); //Larry
                        
                        j++;
                        if(j==ny)
                        {
                           j=0;
                           i++;
                           if(i==nx)
                           {
                              i=0;
                              k++;
                           }
                        }
                     }
                     inFile.close();
                 }
                 else
                 {
                     cout << "File does not exist or is corrupted." << endl;
                     system("Pause");
                     exit(0);
                 }
                 return new payoffMatrixN(m, nx, ny, nz);
              }
              
              //returns a string description of the matrix
              string getValue();
              
              //returns the matrix dimension
              int getNumX(){return numX;}
              int getNumY(){return numY;}
              int getNumZ(){return numZ;}
              
              //returns whether the matrix is zero sum or not
              bool IsZeroSum();
              
              //returns a payoff entry at specified position
              payoffEntryN* getPayoff(int x, int y, int z);
              
              //returns the appropriate 2-person game to solve
              //if player=1 then Rose, player=2 then Colin, player=3 then Larry
              //returns a null pointer if the current matrix cannot be solved with this
              //strategy
              payoffMatrix* get2PersonGame(int player);
              payoffMatrix* get2PersonGameNzs(int player);
              
              //returns the equilibrium
              bool isEquilibrium(int, int, int);
              vector<int*> getEquilibrium();

};


#endif
