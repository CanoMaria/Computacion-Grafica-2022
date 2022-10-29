
#include <GL/glu.h>
//GLut permite la gestion de Ventanas
#include <GL/glut.h>
#include <math.h>
#define PI 3.141592654
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
    gluOrtho2D(0.0, 5.0, 0.0, 5.0);
}


//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
//Esta funcion se llama muchas veces
void dibujar(void)
{
    //Limpia la ventana con el color blanco
    glClear(GL_COLOR_BUFFER_BIT);
    //Coloreamos los puntos
    glColor3f(1.0f, 0.0f, 0.0f);
    //Establecemos el tamaño de los puntos
    glPointSize(3);

    //Dibujamos los puntos
    glBegin (GL_POINTS);
        for (double i = 0; i < 4; i=i+0.005)
        {
            double x=i;
            double y=exp(-x)* cos(2*PI*x);
            glVertex2d(x,y+2.5);
        }
    
    glEnd ();
    //Refresca
    glFlush();
}


//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
void main(int argc, char** argv)
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
    glutCreateWindow("CG Ejemplo"); 
    //Registramos la funcion dibujar para que redibuje la pantalla
    glutDisplayFunc(dibujar);
    //inicializamos
    iniciar();
    //permite que glu dibuje
    glutMainLoop();
}

