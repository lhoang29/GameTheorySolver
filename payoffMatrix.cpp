#include "payoffMatrix.h"
#include "LineCollection.h"
#include <iostream>
#include <string>

using namespace std;

payoffMatrix::payoffMatrix(double **m, int nr, int nc)
{
   matrix = m;
   numRows = nr;
   numCols = nc;
   ZeroSum = true;
}

payoffMatrix::payoffMatrix(payoffEntryN ***m, int nr, int nc)
{
   matrixNzs = m;
   numRows = nr;
   numCols = nc;
   ZeroSum = false;
}

void payoffMatrix::setValues(double **m)
{
   matrix = m;
}

payoffMatrix* payoffMatrix::transpose()
{
   payoffMatrix *pm = new payoffMatrix(numCols, numRows);
   for(int i=0; i<numRows; i++)
   {
      for(int j=0; j<numCols; j++)
      {
         pm->setPayoff(j, i, matrix[i][j]);
      }
   }
   return pm;
}

string payoffMatrix::getValue()
{
    string s = "Matrix initialized: \n";
    char t[2];
    for(int i=0; i<numRows; i++)
    {
       for(int j=0; j<numCols; j++)
       {
          sprintf(t, "%.0f\t", matrix[i][j]);
          s += t;
       }
       s += "\n";
    }
    return s;
}

string payoffMatrix::getValueNzs()
{
    string s = "Matrix initialized: \n";
    for(int i=0; i<numRows; i++)
    {
       for(int j=0; j<numCols; j++)
       {
          ostringstream o;
          o << "(" << matrixNzs[i][j]->getX() << "," << matrixNzs[i][j]->getY() << ")\t";
          s += o.str();
       }
       s += "\n";
    }
    return s;
}

double payoffMatrix::getPayoff(int x, int y)
{
   return matrix[x][y];
}

void payoffMatrix::setPayoff(int x, int y, double d)
{
   matrix[x][y] = d;
}

void payoffMatrix::setPayoffNzs(int x, int y, double dx, double dy)
{
   matrixNzs[x][y]->setX(dx);
   matrixNzs[x][y]->setY(dy);
}

vector<int> payoffMatrix::getRowMinimums(int x)
{
   vector<int> v;
   if(ZeroSum)
   {
       double tempMin = 1000.0;
       
       //first loop to find minimum value of row
       for(int i=0; i<numCols; i++)
       {
          if(matrix[x][i] <=tempMin)
          {
             tempMin = matrix[x][i];
          }
       }
       
       //second loop to find all values of minimums and add 'Y' positions to vector
       for(int i=0; i<numCols; i++)
       {
          if(matrix[x][i] == tempMin)
          {
             v.push_back(i);
          }
       }
   }
   return v;
}

vector<int> payoffMatrix::getColMaximums(int y)
{
   vector<int> v;
   double tempMax = -1000.0;
   
   //first loop to find maximum value of column
   for(int i=0; i<numRows; i++)
   {
      if(matrix[i][y] >= tempMax)
      {
         tempMax = matrix[i][y];
      }
   }
   
   //second loop to find all values of maximums and add 'X' positions to vector
   for(int i=0; i<numRows; i++)
   {
      if(matrix[i][y] == tempMax)
      {
         v.push_back(i);
      }
   }
   return v;
}

double payoffMatrix::getRowExtrema(bool min, int row, bool zeroSum)
{
   if(min)
   {
      double minValue = 1000.0;
      for(int j=0; j<numCols; j++)
      {
         if(zeroSum)
         {
             if(matrix[row][j]<=minValue)
             minValue = matrix[row][j];
         }
         else
         {
            if(matrixNzs[row][j]->getY()<=minValue)
            minValue = matrixNzs[row][j]->getY();
         }
      }
      return minValue;
   }
   else
   {
      double maxValue = -1000.0;
      for(int j=0; j<numCols; j++)
      {
         if(zeroSum)
         {
             if(matrix[row][j]>=maxValue)
             maxValue = matrix[row][j];
         }
         else
         {
            if(matrixNzs[row][j]->getY()>=maxValue)
            maxValue = matrixNzs[row][j]->getY();
         }
      }
      return maxValue;
   }
}

bool payoffMatrix::isRowMaximum(int row, int colIndex)
{
   if(!ZeroSum)
   {
      for(int j=0; j<numCols; j++)
      {
         if(j!=colIndex)
         {
            if(matrixNzs[row][j]->getY() > matrixNzs[row][colIndex]->getY())
            return false;
         }
      }
      
      return true;
   }
}

bool payoffMatrix::isColMaximum(int col, int rowIndex)
{
   if(!ZeroSum)
   {
      for(int i=0; i<numRows; i++)
      {
         if(i!=rowIndex)
         {
            if(matrixNzs[i][col]->getX() > matrixNzs[rowIndex][col]->getX())
            return false;
         }
      }
      return true;
   }
}

double payoffMatrix::getColExtrema(bool min, int col, bool zeroSum)
{
   if(min)
   {
      double minValue = 1000.0;
      for(int i=0; i<numRows; i++)
      {
         if(zeroSum)
         {
             if(matrix[i][col]<=minValue)
             minValue = matrix[i][col];
         }
         else
         {
            if(matrixNzs[i][col]->getX()<=minValue)
            minValue = matrixNzs[i][col]->getX();
         }
      }
      return minValue;
   }
   else
   {
      double maxValue = -1000.0;
      for(int i=0; i<numRows; i++)
      {
         if(zeroSum)
         {
             if(matrix[i][col]>=maxValue)
             maxValue = matrix[i][col];
         }
         else
         {
            if(matrixNzs[i][col]->getX()>=maxValue)
            maxValue = matrixNzs[i][col]->getX();
         }
      }
      return maxValue;
   }
}

vector<int*> payoffMatrix::getSaddlePoints()
{
   vector<int*> vReturn;
   if(ZeroSum)
   {
       for(int i=0; i<numRows; i++)
       {
          //get row minimums for row i
          vector<int> vRow = getRowMinimums(i);
          
          //get iterator to loop through
          vector<int>::iterator itRow = vRow.begin();
          while(itRow != vRow.end())
          {
             //get column maximums for this column
             vector<int> vCol = getColMaximums(*itRow);
             //get iterator to loop through
             vector<int>::iterator itCol = vCol.begin();
             while(itCol != vCol.end())
             {
                //check whether the value at this position also is the column maximum
                if(*itCol == i)
                {
                    int *tempValue = new int[2];
                    tempValue[0] = i;
                    tempValue[1] = *itRow;
                    vReturn.push_back(tempValue);
                }
                itCol++;
             }
             itRow++;
          }
       }
   }
   return vReturn;
}

Collection<Line>* payoffMatrix::generateLines()
{
   if(numRows != 2 && numCols != 2)
      return (Collection<Line>*)NULL;
   
   Collection<Line>* lineReturn;
   //for case of m x 2 matrix
   if(numRows != 2)
   {
       lineReturn = new Collection<Line>(numRows);
       for(int i=0; i<numRows; i++)
       {
          //for this row, grab the first and second column entry values
          int firstEntry = (int)(getPayoff(i, 0));
          int secondEntry = (int)(getPayoff(i, 1));
          
          //now create a point with proper coordinates out of these two values
          //first one always has '0' x-coordinate and second one always '1' x-coordinate
          Point<int> pStart(0, firstEntry);
          Point<int> pEnd(1, secondEntry);
          
          //then form a line starting at the first point ending at second point
          Line line(pStart, pEnd);
          line.findSlope();
          line.findIntercept();
          
          //then push this line onto the line collection
          lineReturn->push(line);
       }
   }
   //for case of 2 x m matrix
   else
   {
       lineReturn = new Collection<Line>(numCols);
       for(int i=0; i<numCols; i++)
       {
          //for this column, grab the first and second row entry values
          int firstEntry = (int)(getPayoff(0, i));
          int secondEntry = (int)(getPayoff(1, i));
          
          //now create a point with proper coordinates out of these two values
          //first one always has '0' x-coordinate and second one always '1' x-coordinate
          Point<int> pStart(0, firstEntry);
          Point<int> pEnd(1, secondEntry);
          
          //then form a line starting at the first point ending at second point
          Line line(pStart, pEnd);
          line.findSlope();
          line.findIntercept();
          
          //then push this line onto the line collection
          lineReturn->push(line);
       }
   }
   return lineReturn;
}

payoffMatrix* getSubGame(payoffMatrix *pm)
{
   //generate line collections for these types of matrices
   LineCollection *lc = (LineCollection*)pm->generateLines();
   Intersection *i = lc->getEnvelopeSolution(pm->getNumRows()!=2);
   if(i != (Intersection*)NULL)
   {
      payoffMatrix *subGame = new payoffMatrix(2, 2);
      double **m = new double*[2];
      m[0] = new double[2];
      m[1] = new double[2];
      if(i->getIndexLine1() < i->getIndexLine2())
      {
          m[0][0] = lc->getElement(i->getIndexLine1()).getStart()->getY();
          m[0][1] = lc->getElement(i->getIndexLine1()).getEnd()->getY();
          m[1][0] = lc->getElement(i->getIndexLine2()).getStart()->getY();
          m[1][1] = lc->getElement(i->getIndexLine2()).getEnd()->getY();
      }
      else
      {
          m[0][0] = lc->getElement(i->getIndexLine2()).getStart()->getY();
          m[0][1] = lc->getElement(i->getIndexLine2()).getEnd()->getY();
          m[1][0] = lc->getElement(i->getIndexLine1()).getStart()->getY();
          m[1][1] = lc->getElement(i->getIndexLine1()).getEnd()->getY();
      }
      subGame->setValues(m);
      if(pm->getNumRows() == 2)
      {
          subGame = subGame->transpose();
      }
      return subGame;
   }
   else
   {
      return (payoffMatrix*)NULL;
   }
}

//this function only solves game of type 2 x m or m x 2
//return null if not solvable, else return a two dimensional
//array containing each player's strategy
RationalNumber** solveSubGame(payoffMatrix *pm)
{
   //generate line collections for these types of matrices
   RationalNumber** rn = (RationalNumber**)NULL;
   payoffMatrix *subGame = getSubGame(pm);
   if(subGame!=(payoffMatrix*)NULL)
   {
      rn = subGame->solveMixedStrategyMatrix();
   }
   return rn;
}

RationalNumber** payoffMatrix::solveMixedStrategyMatrix()
{
   RationalNumber **toReturn = new RationalNumber*[2];
   toReturn[0] = new RationalNumber[2];
   toReturn[1] = new RationalNumber[2];
   
   if(this->getNumRows() != 2 || this->getNumCols() != 2)
   {
      // if the game is 2 x m or m x 2 then we have to determine and solve sub game
      if((this->getNumRows()==2 && this->getNumCols() != 2) || (this->getNumRows()!=2 && this->getNumCols() == 2))
      {
          toReturn = solveSubGame(this);
      }
      // if the game is m x n where m, n # 2 then can't solve
      else
      {
          cout << "Matrix or sub matrix not in proper form 2 x m or m x 2 to solve." << endl;
          toReturn = (RationalNumber**)NULL;
      }
   }
   // if the game is 2 x 2 then we can go ahead and solve the game
   else
   {
      double a = this->getPayoff(0,0);
      double b = this->getPayoff(0,1);
      double c = this->getPayoff(1,0);
      double d = this->getPayoff(1,1);
      if(a+d == b+c) 
      cout<<"Game cannot be solved with mixed strategies." << endl;
      else
      {
         RationalNumber RoseA((int)(d-c),(int)(a+d-b-c));
         RationalNumber ColinA((int)(d-b),(int)(a+d-b-c));
         toReturn[0][0] = RoseA;
         toReturn[0][1] = RationalNumber(1) - RoseA;
         toReturn[1][0] = ColinA;
         toReturn[1][1] = RationalNumber(1) - ColinA;
      }
   }
   return toReturn;
}

/*Implementations to write solutions to out file indicated as parameter*/
void payoffMatrix::writeSolutions(ofstream& outFile)
{
    if(numRows >2 && numCols >2)
    {
       outFile << "The m x n type game where both m and n > 2 is not currently solvable." << endl;
       return;
    }
    //for getSaddlePoints function of class payoffMatrix
    vector<int*> saddleResult = getSaddlePoints();
    int size = saddleResult.size();
    if(size > 0)
    {
       //create list to store all saddle points locations
       int **listSaddle = new int*[size];
       for(int i=0; i<size; i++)
       {
          listSaddle[i] = new int[2];
       }
       vector<int*>::iterator it = saddleResult.begin();
       int id=0;
       while(it != saddleResult.end())
       {
          listSaddle[id][0] = (*it)[0];
          listSaddle[id][1] = (*it)[1];
          id++;
          it++;
       }
       outFile << "Matrix initialized with saddle points: " << endl;
       for(int i=0; i<numRows; i++)
       {
          for(int j=0; j<numCols; j++)
          {
             bool found = false;
             //print out matrix and check if the point is saddle then print brackets
             for(int k=0; k<size; k++)
             {
                if(i==listSaddle[k][0] && j==listSaddle[k][1])
                {
                   outFile << "[" <<matrix[i][j] << "]\t";
                   found = true;
                   k = size;
                }
             }
             if(found == false)
             outFile << matrix[i][j] << "\t";
          }
          outFile << endl << endl;
       }    
    }
    else
    {
        outFile << "No saddle points found." <<endl; 
        outFile << endl;
        payoffMatrix* subGame = getSubGame(this);
        outFile << "Sub game: " << endl;
        outFile << subGame->getValue() << endl;
        //for solveMixedStrategyMatrix function of class payoffMatrix
        RationalNumber **solution = subGame->solveMixedStrategyMatrix();
        if(solution != (RationalNumber**)NULL)
        {
            outFile << "First player's strategy: (" << solution[0][0].getValue() << ", " 
                 << solution[0][1].getValue() << ")" << endl;
            outFile << "Second player's strategy: (" << solution[1][0].getValue() << ", " 
                 << solution[1][1].getValue() << ")" << endl;
        }
        outFile << endl;
        delete subGame;
    }
}

//This function only applies to 2-person non zero sum game.
//Returns a zero sum payoff matrix with payoff to player specified by the parameter
payoffMatrix* payoffMatrix::getZeroSumSubGame(int player)
{
   if(!ZeroSum)
   {
        payoffMatrix *toReturn;
        //Rose
        if(player==1)
        {
            toReturn = new payoffMatrix(numRows, numCols);
            for(int i=0; i<numRows; i++)
            {
                 for(int j=0; j<numCols; j++)
                 {
                    toReturn->setPayoff(i,j,matrixNzs[i][j]->getX());
                 }
            }
            return toReturn;
        }
        //Colin
        if(player==2)
        {
            toReturn = new payoffMatrix(numRows, numCols);
            for(int i=0; i<numRows; i++)
            {
                 for(int j=0; j<numCols; j++)
                 {
                    toReturn->setPayoff(i,j,matrixNzs[i][j]->getY());
                 }
            }
            toReturn = toReturn->transpose();
            return toReturn;
        }
   }
   return (payoffMatrix*)NULL;
}
