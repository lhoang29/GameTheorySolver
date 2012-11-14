#include "payoffMatrixN.h"

string payoffMatrixN :: getValue()
{
    string s = "Matrix initialized: \n";
    char t[2];
    for(int k=0; k<numZ; k++)
    {
       for(int i=0; i<numX; i++)
       {
          for(int j=0; j<numY; j++)
          {
             s += matrix[i][j][k]->getValue() + "\t";
          }
          s += "\n";
       }
       if(k<numZ-1)
       s += "--------------------------------\n";
    }
    return s;
}

payoffEntryN* payoffMatrixN::getPayoff(int x, int y, int z)
{
    return matrix[x][y][z];
}

bool payoffMatrixN::IsZeroSum()
{
    for(int i=0; i<numX; i++)
    {
       for(int j=0; j<numY; j++)
       {
          for(int k=0; k<numZ; k++)
          {
             //if any entry is not zero sum then quit
             if(!matrix[i][j][k]->IsZeroSumEntry())
             return false;
          }
       }
    }
    return true;
}

payoffMatrix* payoffMatrixN::get2PersonGame(int player)
{
   if(numX == 2 && numY == 2 && numZ == 2)
   {
      payoffMatrix *toReturn = new payoffMatrix(2,4);
      for(int i=0; i<2; i++)
      {
         for(int j=0; j<4; j++)
         {
            //For Rose
            if(player==1)
            toReturn->setPayoff(i,j,matrix[i][j%2][j/2]->getX());
            //For Colin
            if(player==2)
            toReturn->setPayoff(i,j,matrix[j%2][i][j/2]->getY());
            //For Larry
            if(player==3)
            toReturn->setPayoff(i,j,matrix[j%2][j/2][i]->getZ());
         }
      }
      return toReturn;
   }
   return (payoffMatrix*)NULL;
}

payoffMatrix* payoffMatrixN::get2PersonGameNzs(int player)
{
   if(player == 1) // Rose
   {
       payoffMatrix* pmnzs = new payoffMatrix(numX, numY*numZ, false);
       for(int i=0; i<numX; i++)
       {
          int index=0;
          for(int k=0; k<numZ; k++)
          {
             for(int j=0; j<numY; j++)
             {
                payoffEntryN *pen = matrix[i][j][k];  
                pmnzs->setPayoffNzs(i, index, pen->getX(), pen->getY()+pen->getZ());
                index++;
             }
              
          }
       }
       return pmnzs;
   }
   
   if(player == 2) // Colin
   {
       payoffMatrix* pmnzs = new payoffMatrix(numY, numX*numZ, false);
       for(int j=0; j<numY; j++)
       {
          int index=0;
          for(int k=0; k<numZ; k++)
          {
             for(int i=0; i<numX; i++)
             {
                payoffEntryN *pen = matrix[i][j][k];  
                pmnzs->setPayoffNzs(j, index, pen->getY(), pen->getX()+pen->getZ());
                index++;
             }
              
          }
       }
       return pmnzs;
   }
   if(player == 3) // Larry
   {
       payoffMatrix* pmnzs = new payoffMatrix(numZ, numX*numY, false);
       for(int k=0; k<numZ; k++)
       {
          int index=0;
          for(int i=0; i<numX; i++)
          {
             for(int j=0; j<numY; j++)
             {
                payoffEntryN *pen = matrix[i][j][k];  
                pmnzs->setPayoffNzs(k, index, pen->getZ(), pen->getX()+pen->getY());
                index++;
             }
              
          }
       }
       return pmnzs;
   }
   return (payoffMatrix*)NULL;
}

bool payoffMatrixN::isEquilibrium(int x, int y, int z)
{  
   for(int i=0; i<numX; i++)
   {
      if(i!=x)
      {
         if(matrix[i][y][z]->getX() > matrix[x][y][z]->getX())
         {
            return false;
         }
      }
   }
   for(int j=0; j<numY; j++)
   {
      if(j!=y)
      {
         if(matrix[x][j][z]->getY() > matrix[x][y][z]->getY())
         {
            return false;
         }
      }
   }
   for(int k=0; k<numZ; k++)
   {
      if(k!=z)
      {
         if(matrix[x][y][k]->getZ() > matrix[x][y][z]->getZ())
         {
            return false;
         }
      }
   }
   return true;
}

vector<int*> payoffMatrixN::getEquilibrium()
{
   vector<int*> toReturn;
   for(int i=0; i<numX; i++)
   {
      for(int j=0; j<numY; j++)
      {
         for(int k=0; k<numZ; k++)
         {
            if(isEquilibrium(i,j,k))
            {
               int *temp = new int[3];
               temp[0] = i;
               temp[1] = j;
               temp[2] = k;
               toReturn.push_back(temp);
            }
         }
      }
   }
   return toReturn;
}
