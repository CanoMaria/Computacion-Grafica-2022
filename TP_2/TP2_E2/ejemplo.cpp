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

int count=0;
struct punto
{
    float x=0;
    float y=0;
};
punto anterior={0,0};
punto actual={0,0};
void puntoMedio(punto punto1, punto punto2){
    //grafico los puntos intermedios
    int dx = (punto2.x - punto1.x);
    int dy = (punto2.y - punto1.y);
    int d = 2 * abs(dy - dx); // decision variable
    int incrE = (2 * dy);
    int incrNE = 2 * (dy - dx);
    punto variable=punto1;

    cout<<"dx"<<dx<<endl;
    cout<<"dy"<<dy<<endl;
    cout<<"d"<<d<<endl;
    cout<<"incrE"<<incrE<<endl;
    cout<<"incrNE"<<incrNE<<endl;

    while (variable.x <= punto2.x) {
        if (d <= 0) { // East Case
            d = d + incrE;
            if(variable.y>punto2.y){
                variable.y--;
            }
        } else { // North East Case
            d = d + incrNE;
            if(variable.y<punto2.y){
                variable.y++;
            }  
        }
       
        variable.x++;
        glBegin (GL_POINTS);   
            glVertex2d(variable.x,variable.y);
        glEnd ();
    } 
}



void mouse(int button, int state, int x, int y)
{
    //definimos el punto actual
    actual={float(x),float(y)};
    if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        
        glPointSize(20);
         actual.y=480-y;
         //si ya se armaron 2 puntos borro los puntos viejos
         if(count==2){
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            count=0;
            anterior.x=0;
            anterior.y=0;
        }
        //defino el 1er punto
        if(anterior.x==0 && anterior.y==0){
            anterior.x=actual.x;
            anterior.y=actual.y;
    
            glBegin (GL_POINTS);   
                glVertex2d(anterior.x,anterior.y);
            glEnd ();
            count++;
        }else{
        //defino el 2do punto
            glBegin (GL_POINTS);   
                glVertex2d(actual.x,actual.y);
            glEnd ();

            if(anterior.x<actual.x){
                puntoMedio(anterior,actual);
            }else{
                puntoMedio(actual,anterior);
            }

            //cout<<"[x_ant"<<anterior.x<<" x"<<actual.x<<"] [y_ant"<<anterior.y<<" y"<<actual.y<<"]"<<endl;
            count++;
        }        
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
    glutCreateWindow("Ejercicio 2- TP 2"); 
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

