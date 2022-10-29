#include <GL/glu.h>
#include <GL/glut.h>

GLint puntos[][2]; //Array de puntos seleccionados con el mouse
GLint color [3] ={0.0,0.0,0.0}; //Array de color RGB
int cantidadPuntos = 0; //Cantidad de puntos

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(color[0],color[1],color[2]); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
    glClear(GL_COLOR_BUFFER_BIT);

}


//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void dibujar(void)
{
    
    glColor3f(color[0],color[1],color[2]); //Seteamos el color de los puntos
    glPointSize(2.0); //Seteamos el tamaño de los puntos

    if(cantidadPuntos == 1){
      glBegin(GL_POINTS);
        glVertex2f(puntos[0][0],puntos[0][1]);
      glEnd();
    }
    else{
      glBegin(GL_LINE_STRIP); //Comenzamos a dibujar segmentos
      
        glVertex2f(puntos[cantidadPuntos-2][0],puntos[cantidadPuntos-2][1]); 
        glVertex2f(puntos[cantidadPuntos-1][0],puntos[cantidadPuntos-1][1]); 
      
      glEnd();
    }
    glFlush();
}

//Deteccion del mouse. Se leen los puntos seleccionados con el mouse
void mouse(int button, int state, int x, int y)
{

  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    puntos[cantidadPuntos][0] = x;
    puntos[cantidadPuntos][1] = abs(480-y);
    cantidadPuntos++;
    dibujar();
    glFlush();
    
  }
}

//Deteccion del teclado. Con 'r' se selecciona el color rojo. Con 'v' se selecciona el color verde. Con 'a' se 
// selecciona el color azul
void teclado(char key, int x, int y)
{
  switch (key)
  {
  case 'r':
    color[0] = 255;
    color[1] = 0;
    color[2] = 0;
    break;
  case 'v':
    color[0] = 0;
    color[1] = 255;
    color[2] = 0;
    break;
  case 'a':
    color[0] = 0;
    color[1] = 0;
    color[2] = 255;
    break;
  }
  dibujar();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150); 
    glutCreateWindow("Ejercicio 6"); 
    glutDisplayFunc(dibujar);
    glutMouseFunc(mouse); 
    glutKeyboardFunc(teclado);
    iniciar();
    glutMainLoop();

}

