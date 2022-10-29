#include <iostream>
#include <fstream>
#include <cstdio>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <stdlib.h>
using namespace std;
struct point
{
        double x;
        double y;
        double z;
        

};
std::vector <point> points;
//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glColor3f(0.0f, 0.0f, 0.0f);
  glPointSize( 1.0 );
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-5.0,5.0,-5.0,5.0,-1.0,1.0);
}


void dino() {
     std::ifstream dino;
     dino.open("basicbar.3vn");
     //numero de vertices, normales y superficies
     int v=0,n = 0,s=0,iteraciones=0;
     dino >>v>>n>>s;
     iteraciones=v+n+s*3;
     cout<<iteraciones;
     glFrontFace(GL_CCW);
     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
     //comenzamos a iterar por el numero de polilineas y de vertices
     for(int i = 0; i<iteraciones; i++){
        if(i<v)
        {
            glBegin (GL_POLYGON);
            double x, y,z;
            dino >>x>>y>>z;
            glVertex3d(x,y,z);
            glEnd();
        }  
     }
     glFlush();
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void dibujar(void)
{
  glClear( GL_COLOR_BUFFER_BIT );
  glTranslatef(200.25f, 300.25f, 0.0f);
  glScalef(0.2f, 0.2f, 0.0f);
  dino();

  for(int i=45;i<=360;i=i+45)
  {
    glTranslatef(-200.25f, -300.25f, 0.0f);
    glRotatef(i, 0.0f, 0.0f, 1.0f);
    glTranslatef(cos(i*M_PI/180), sin(i*M_PI/180), 0.0f);
    glTranslatef(200.25f, 300.25f, 0.0f);
    dino();
  }


  
  
}



//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("EJERCICIO 5a");
  glutDisplayFunc(dibujar);
  iniciar();
  glutMainLoop();

  return 0;
}
