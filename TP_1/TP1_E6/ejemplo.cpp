#include <stdio.h>
#include <iostream>
#include <fstream>
#include <GL/glu.h>
#include <GL/glut.h>

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
float ant_x=0,ant_y=0,i=0; 
void mouse(int button, int state, int x, int y)
{
    
    if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        
        cout <<i++<< "x:" << x<< " y:" << y << "x_ant:" << ant_x << " y_ant:" << ant_y<< endl;
        glPointSize(20);
    
        glBegin (GL_LINES);   
            y=480-y;
            if(ant_x==0 && ant_y==0){
                ant_x=x;
                ant_y=y;
            }

            glVertex2d(ant_x,ant_y);
            glVertex2d(x,y);  
            ant_x=x;
            ant_y=y;
    
        glEnd ();
        glFlush();
    }
    
    
}
void keyboard (unsigned char key, int x, int y)
{
    //clear screen when press X
    if(key=='x'){
        glClearColor(1.0,1.0,1.0,0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    glFlush();

}

void dibujar(void)
{
    //Limpia la ventana con el color blanco
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin (GL_POINTS);       
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
    glutCreateWindow("Ejercicio 5"); 
    //Registramos la funcion dibujar para que redibuje la pantalla
    glutDisplayFunc(dibujar);
    //inicializamos
    iniciar();
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    //permite que glu dibuje
    glutMainLoop();
    return 0;
}

