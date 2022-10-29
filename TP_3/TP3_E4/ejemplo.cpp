#include <stdio.h>
#include <iostream>
#include <fstream>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265
using namespace std;
//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
//Se llama antes de la funcion dibujar
void iniciar(void)
{
    //Colorea la ventana de color blanco
    glClearColor(1.0,1.0,1.0,0.0);
    //Color que quiero que pinte, color por defecto
    glColor3f(0.0f, 0.0f, 0.0f);
    //Matriz de proyeccion para que se pueda dibujar en 2d
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //Proeyccion ortogonal de 2d 
    gluOrtho2D(0.0, 640, 0.0, 480);
     glClear(GL_COLOR_BUFFER_BIT);
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
//Esta funcion se llama muchas veces


struct punto
{
    float x=0;
    float y=0;
};

int tam=21;
struct punto array [21] = {
                       punto{0, 2},
                       punto{50, 2},
                       punto{50, 27},
                       punto{55, 27},
                       punto{55, 2},
                       punto{75, 2},
                       punto{75, 17},
                       punto{80, 17},
                       punto{80, 2},
                       punto{100, 2},
                       punto{100, 0},
                       punto{100, -2},
                       punto{80, -2},
                       punto{80, -17},
                       punto{75, -17},
                       punto{75, -2},
                       punto{55, -2},
                       punto{55, -27},
                       punto{50, -27},
                       punto{50, -2},
                       punto{0, -2}                   
                      
                       };

    float m[2][2] = {{1 / tan(PI / 4), 0},
                       {1, 1}};
    float mRotacion[2][2];
    struct punto mResult[21];

void drawBranch(int x_rand,int y_rand){

    
    //Curvamos las ramitas
    for (int i = 0; i < tam; i++)
    {
        float resul_x=(array[i].x*m[0][0])+abs(array[i].y*m[1][0]);
        float resul_y=(array[i].x*m[0][1])+(array[i].y*m[1][1]);
        mResult[i]=punto{resul_x,resul_y};
    }
    //Rotamos la rama a la posicion que le corresponde
    for (int i = 0; i < tam; i++)
    {
        float resul_x=(mResult[i].x*mRotacion[0][0])+(mResult[i].y*mRotacion[0][1]);
        float resul_y=(mResult[i].x*mRotacion[1][0])+(mResult[i].y*mRotacion[1][1]);
        mResult[i]=punto{resul_x,resul_y};
    }

    glBegin (GL_LINE_LOOP);   
        for (int  i = 0; i < tam; i++){
            glVertex2d(x_rand+mResult[i].x,y_rand+mResult[i].y);
        }  
    glEnd ();   
}
void mouse(int button, int state, int x, int y)
{
    //definimos el punto actual
    if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN){
       glutPostRedisplay();
    }
    
}

void dibujar(void)
{
    //Limpia la ventana con el color blanco
   
    
    glColor3f(0.0f, 0.0f, 0.0f);
       
    int x_rand=rand()%640;
    int y_rand=rand()%480;
    double rand_scale=(2.0-0.20)*((double)rand()/RAND_MAX)+0.2;
    
    glScaled(rand_scale,rand_scale,0);
    int rot=rand()%10;
   
    glRotated(rot,0,0,1);
    for (int i = 1; i < 7; i++)
    {
        mRotacion[0][0] = cos(i * PI / 3);
        mRotacion[0][1] = -sin(i * PI / 3);
        mRotacion[1][0] = sin(i * PI / 3);
        mRotacion[1][1] = cos(i * PI / 3);

        drawBranch(x_rand,y_rand);
    }

    //Refresca
    glFlush();
}


//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
    //inicializamos las primitivas de las ventanas
    glutInit(&argc, argv);
    //trabaja en un modo de solo buffer y el modelo de color RGB
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
    //Dimensiones de la ventana
    glutInitWindowSize(640,480);
    //Posicion de la ventana, dentro de la resulucion de la pantalla
    glutInitWindowPosition(100, 150); 
    //Creamos la ventana y le ponemos un nombre
    glutCreateWindow("TP3-E4"); 
    //Registramos la funcion dibujar para que redibuje la pantalla
    glutDisplayFunc(dibujar);
    glutMouseFunc(mouse);
    //inicializamos
    iniciar();
    //permite que glu dibuje
    glutMainLoop();
    return 0;
}

