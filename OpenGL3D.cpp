#include "OpenGL3D.h"

void OpenGL3D::init()
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    /* enable lighting */
    
    glEnable(GL_LIGHTING);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    GLfloat material_ambient[] = {0.25f, 0.25f, 0.25f};
    GLfloat material_diffuse[] = {0.90f, 0.90f, 0.90f};
    GLfloat material_specular[]= {0.90f, 0.90f, 0.90f};
    GLfloat material_shininess = 25.0f;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, material_shininess);
    
    //set two lights, one white and one yellow
    GLfloat light0_diffuse[] = {0.0, 1.0, 0.0, 1.0};
    GLfloat light0_position[] = {0.0, 50.0, 50.0, 0.0};
    GLfloat light1_diffuse[] = {1.0, 1.0, 0.0, 1.0};
    GLfloat light1_position[] = {0.0, 50.0, -50.0, 0.0};
    
    //enable 2 light sources
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light1_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    
    //establish frustum
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1,1,-1,1,1,600);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGL3D::beginDisplay()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   glEnable(GL_TEXTURE_2D);
   glEnable(GL_DEPTH_TEST);
   gluLookAt(0,0,10,0,0,0,0,1,0);
   glTranslatef(translateX, translateY, translateZ);  
   glRotatef(rotateX, 1, 0, 0);
   glRotatef(rotateY, 0, 1, 0);
   glRotatef(rotateZ, 0, 0, 1);
}

void OpenGL3D::endDisplay()
{
   glFlush();
   glutSwapBuffers();
   glDisable(GL_TEXTURE_2D);
}

void OpenGL3D::color3D(double& x, double& y, double& z, double& a)
{
   glColor4f(x,y,z,a);
}

void OpenGL3D::drawLine3D(double& x1, double& y1, double& z1, double& x2, double& y2, double& z2)
{
   glBegin(GL_LINES);
      glVertex3f(x1, y1, z1);
      glVertex3f(x2, y2, z2);
   glEnd();
}

void OpenGL3D::drawPoint3D(double& x, double& y, double& z)
{
   glPushMatrix();
       glTranslatef(x,y,z);
       glutSolidSphere(0.1, 30, 30);
   glPopMatrix();
}

void OpenGL3D::drawCustomPoint(double& x, double& y, double& z, double& size)
{
   glPushMatrix();
       glTranslatef(x,y,z);
       glutWireSphere(size, 10, 10);
   glPopMatrix();
}

void OpenGL3D::drawText3D(double& x, double& y, double& z, string& s)
{
   glPushMatrix();
      glTranslatef(x,y,z);
      glScalef(0.0015, 0.0015, 0.0015);
      glRotatef(-rotateX, 1, 0, 0);
      glRotatef(-rotateY, 0, 1, 0);
      glRotatef(rotateZ, 0, 0, 1);
      for (int i=0; i<strlen(&s[0]); i++){
        glutStrokeCharacter(GLUT_STROKE_ROMAN,s[i]);
      }
   glPopMatrix();
}
void OpenGL3D::drawArrow3D(double& x, double& y, double& z, int direction)
{
   //direction: 1=up, 2=down, 3=left, 4=right, 5=inward, 6=outward
   glPushMatrix();
      glTranslatef(x,y,z);
      glScalef(0.1,0.1,0.1);
      if(direction==1)
         glRotatef(270, 1, 0, 0);
      if(direction==2)
         glRotatef(90, 1, 0, 0);
      if(direction==3)
         glRotatef(270, 0, 1, 0);
      if(direction==4)
         glRotatef(90, 0, 1, 0);
      if(direction==5)
         glRotatef(180,0, 1, 0);
      glutSolidCone(1.0,4.0,15,15);
   glPopMatrix();
}
void OpenGL3D::RotateX(int direction)
{
   rotateX += direction;
   if(rotateX >= 360) rotateX = 0;
}

void OpenGL3D::RotateY(int direction)
{
   rotateY += direction;
   if(rotateY >= 360) rotateY = 0;
}

void OpenGL3D::RotateZ(int direction)
{
   rotateZ += direction;
   if(rotateZ >= 360) rotateZ = 0;
}

void OpenGL3D::TranslateX(double x)
{
   translateX += x;
}

void OpenGL3D::TranslateY(double y)
{
   translateY += y;
}

void OpenGL3D::TranslateZ(double z)
{
   translateZ += z;
}
