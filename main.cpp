#include "Include.h"

//this indicates the source input and output file for the matrix
char *fileName, *fileOut;

//a pointer to the visualization object to draw scenes
Visualization *v;

//these are pointers to appropriate matrix to be instantiated
payoffMatrix *pom; payoffMatrixN *pomn;

//keep track of whether the game is two person or more
bool nPerson = false;

//keep track of whether the game is a zero sum game
bool zeroSum = true;

//these are to keep track of the mouse motion
bool leftButton = false;

//this function is used to display OpenGL stuff
void display(void) {
  //begin display process
  v->beginDisplay();
  
  /*For 2D Initialization*/
  if(!nPerson)
  {
      //generate lines and draw
      LineCollection lc = v->buildLines(*pom);
      v->drawLines(lc);
      
      //set color
      v->color(1, 1, 1);
      
      //generate points and draw
      PointCollection<double> pc = v->buildPoints(*pom);
      v->drawPoints(pc);
      
      //generate texts and draw
      TextCollection tc = v->buildTexts(*pom);
      v->drawTexts(tc);
  }
  else
  {
      int nX = pomn->getNumX();
      int nY = pomn->getNumY();
      int nZ = pomn->getNumZ();
      int numPoints = nX * nY * nZ;
      int numLines = 3*nX*nY*nZ - nX*nY - nY*nZ - nZ*nX;
      v->drawPoints(v->buildPoints(*pomn), numPoints);
      v->drawLines(v->buildLines(*pomn), numLines+3);
      v->drawTexts(v->buildTexts(*pomn), numPoints);
      v->drawArrows(*pomn);
  }
  
  //end display process
  v->endDisplay();
}

void init(void) {
     v->init();
}

void my_keyboard(unsigned char key, int x, int y)
{
     //when user pressed escape, quit
     if (key == 27){
         exit(0);
     }
     if(nPerson){
        if(key == 'w')
        {
           v->TranslateZ(1);
        }
        if(key == 's')
        {
           v->TranslateZ(-1);
        }
        if(key == 'a')
        {
           v->TranslateX(1);
        }
        if(key == 'd')
        {
           v->TranslateX(-1);
        }
     }
     v->Refresh();
}

//these keep track of where the mouse was a moment ago
//in order to implement mouse dragged
int prevX, prevY;
void mouse(int button, int state, int x, int y) {
     //this takes care of the mouse action
     if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
     {
        leftButton = true;
        prevX = x;
        prevY = y;
     }
     if(state == GLUT_UP)
     {
        leftButton = false;
     }
     v->Refresh();
}

void mouse_dragged(int x, int y) {
     //this takes care of the rotating scene for a mouse
     v->RotateY(x-prevX);
     v->RotateX(y-prevY);
     prevX = x;
     prevY = y;
     v->Refresh();
}

//this is the menu for the GL scene
void myMenu(int value){
     if(!nPerson)
     {
         if (value == 1){
             v = new Envelope();
         }
         if (value == 2){
             v = new Flow();
         }
     }
     else
     {
         if (value == 1){
             v = new Flow3D();
         }
     }
     v->Refresh();
}

int main(int argc, char *argv[])
{
    string s;
    fileName = new char[50];
    cout << "Enter file name: " ;
    cin >> fileName;
    s = fileName;
    s = "Matrix Results For " + s;
    fileOut = &s[0];
    int matrixRows=-1,matrixCols=-1,matrixHeights=-1;
    
    //set matrix number of rows and columns
    //or set numX, numY, numZ for 3-person game if necessary
    ifstream inFile(fileName);
    //ifstream inFile(&s[0]);
    if(!inFile.is_open())
    {
       cout << "File does not exist or is corrupted." << endl;
       system("PAUSE");
       exit(0);
    }
    ofstream outFile(fileOut);
    if(!inFile.eof());
    inFile >> matrixRows;
    if(!inFile.eof());
    inFile >> matrixCols;
    if(!inFile.eof());
    inFile >> matrixHeights;
    inFile.close();
    if(matrixRows == -1 || matrixCols == -1)
    {
       cout << "File does not exist or have invalid matrix information." << endl;
       system("Pause");
       return EXIT_SUCCESS;
    }
    
    nPerson = baseMatrix::checkNPersonGame(fileName, matrixRows, matrixCols);
    zeroSum = baseMatrix::check2PersonZeroSum(fileName, matrixRows, matrixCols);
    //initialize payoff matrix
    if(!nPerson)
    {
        if(zeroSum)
        {
            payoffMatrix *Matrix = payoffMatrix::createGame(fileName, matrixRows, matrixCols);
            pom = Matrix;
            outFile << pom->getValue() << endl;
            pom->writeSolutions(outFile);
        }
        else
        {
            pom = payoffMatrix::createGameNzs(fileName, matrixRows, matrixCols);
            outFile << pom->getValueNzs() << endl;
            for(int i=1; i<=2; i++)
            {
                payoffMatrix* pmzs = pom->getZeroSumSubGame(i);
                outFile << "/////////////////////////////////////////////"<<endl;
                if(i==2) outFile << "Rose's equalizing game: " << endl;
                if(i==1) outFile << "Colin's equalizing game: " << endl;
                outFile << pmzs->getValue() << endl;
                pmzs->writeSolutions(outFile);
            }
        }
    }
    else
    {
        pomn = payoffMatrixN::createGame(fileName, matrixRows, matrixCols, matrixHeights);
        outFile << pomn->getValue() << endl;
        //if the game is zero sum n person game
        if(pomn->IsZeroSum())
        {
           for(int i=1; i<=3; i++)
           {
               //switch it to 2 person zero sum
               pom = pomn->get2PersonGame(i);
               outFile << "///////////////////////////////////////////////" << endl;
               if(i==1) outFile << "Rose's Game:" << endl; 
               if(i==2) outFile << "Colin's Game:" << endl;
               if(i==3) outFile << "Larry's Game:" << endl;
               if(pom!=(payoffMatrix*)NULL)
               {
                  //now solve the 2 person zero sum game
                  outFile << pom->getValue() << endl;
                  pom->writeSolutions(outFile);
               }
           }
        }
        //case of non zero sum n person game
        else
        {
           for(int i=1; i<=3; i++)
           {
              //first switch it to 2 person non zero sum game
              //using the idea of coalition
              pom = pomn->get2PersonGameNzs(i);
              if(pom != (payoffMatrix*)NULL)
              {
                 payoffMatrix* pmzs;
                 if(i==1) outFile << "Rose's prudential game: " << endl;
                 if(i==2) outFile << "Colin's prudential game: " << endl;
                 if(i==3) outFile << "Larry's prudential game: " << endl;
                 outFile << pom->getValueNzs() << endl;
                 for(int j=1; j<=2; j++)
                 {
                    if(i==1 && j==2) outFile << "Rose's equalizing game against Colin and Larry: " << endl;
                    if(i==1 && j==1) outFile << "Colin and Larry's equalizing game against Rose: " << endl;
                    if(i==2 && j==2) outFile << "Colin's equalizing game against Rose and Larry: " << endl;
                    if(i==2 && j==1) outFile << "Rose and Larry's equalizing game against Colin: " << endl;
                    if(i==3 && j==2) outFile << "Larry's equalizing game against Rose and Colin: " << endl;
                    if(i==3 && j==1) outFile << "Rose and Colin's equalizing game against Larry: " << endl;
                    //get the prudential strategy game solution
                    pmzs = pom->getZeroSumSubGame(j);
                    outFile << pmzs->getValue() << endl;
                    pmzs->writeSolutions(outFile);
                 }
              }
           }
        }
    }
/*---------------------------------------------------------------------------------*/
    
    //initialize visualization object pointer to default to the flow diagram
    if(!nPerson)
    {
        if(zeroSum)
        v = new Flow();
        else
        v = new FlowNzs();
    }
    else
        v = new Flow3D();
    
    //OpenGL loop
    glutInit(&argc, argv);
    
    //initialize the proper rendering mode for either 2D or 3D
    if(!nPerson)
       glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    else
       glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    
    glutInitWindowPosition(100,100);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("Game Theory");
    init();
    glutDisplayFunc(display);
    glutCreateMenu(myMenu);
    //change the menu accordingly to whether a 2-person or n-person game is loaded
    if(!nPerson)
    {
        if(zeroSum)
        {
            if(pom->Envelopable())
            glutAddMenuEntry("Envelope", 1);
            
            glutAddMenuEntry("Flow", 2);
        }
    }
    else
    {
        glutAddMenuEntry("Flow3D", 1);
    }
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutKeyboardFunc(my_keyboard);
    
    //this is for 3D only
    if(nPerson)
    {
        glutMotionFunc(mouse_dragged);
        glutMouseFunc(mouse);
    }
    
    glutMainLoop();
    outFile.close();
    system("PAUSE");
    return EXIT_SUCCESS;
}
