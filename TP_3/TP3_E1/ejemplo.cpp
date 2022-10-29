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
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
//Esta funcion se llama muchas veces


struct punto
{
    float x=0;
    float y=0;
};

void dibujar(void)
{
    //Limpia la ventana con el color blanco
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);
    
    struct punto array[13]={punto{10,5},
                            punto {10,100},
                            punto{100,100},
                            punto{100,80},
                            punto{30,80},
                            punto{30,20},
                            punto{80,20},
                            punto{80,40},
                            punto{50,40},
                            punto{50,60},
                            punto{100,60},
                            punto{100,5},
                            punto{10,5},
                            };
    float m[2][2]={{1,1/tan(PI/4)},{0,1}};
    float mRotacion[2][2]={{1,1/tan(PI/4)},{0,1}};
    
    
    glBegin (GL_LINE_LOOP);   
        for (int  i = 0; i < 13; i++){
            glVertex2d(array[i].x,array[i].y);

        }          
        glColor3f(1.0f, 0.0f, 0.0f);


        for (int  i = 0; i < 13; i++){
            float resul_x=(array[i].x*m[0][0])+(array[i].y*m[0][1]);
            float resul_y=(array[i].x*m[1][0])+(array[i].y*m[1][1]);
            glVertex2d(resul_x,resul_y);
        }     
    glEnd ();
    
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
    glutCreateWindow("TP3-E1"); 
    //Registramos la funcion dibujar para que redibuje la pantalla
    glutDisplayFunc(dibujar);
    //inicializamos
    iniciar();
    //permite que glu dibuje
    glutMainLoop();
    return 0;
}

