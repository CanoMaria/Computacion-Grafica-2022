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
    punto p1=punto1;
    punto p2=punto2;
    punto variable=punto1;
    glColor3f(1.0f, 0.0f, 0.0f);
   
    glBegin (GL_POINTS);
        while (variable.x<p2.x){
            variable.x++;          
            glVertex2d(variable.x,p2.y);
            glVertex2d(variable.x,p1.y);
        }
    
        while (variable.y<p2.y){
            variable.y++;
            glVertex2d(p2.x,variable.y);
            glVertex2d(p1.x,variable.y);
        }
        while (variable.y>p2.y){
            variable.y--;
            glVertex2d(p2.x,variable.y);
            glVertex2d(p1.x,variable.y);
        }
    glEnd ();

    for (int i = punto1.x+1; i < punto2.x; i++)
    {
        if(punto1.y<punto2.y){
             for (int j = punto1.y+1; j < punto2.y; j++)
            {
                    glColor3f(1.0f, 1.0f, 0.0f);
                        glBegin (GL_POINTS);
                        glVertex2d(i,j);
                    glEnd ();
            }
        }else{
             for (int j = punto2.y+1; j < punto1.y; j++)
            {
                    glColor3f(1.0f, 1.0f, 0.0f);
                        glBegin (GL_POINTS);
                        glVertex2d(i,j);
                    glEnd ();
            }
        }
      
       
    }
    
}



void mouse(int button, int state, int x, int y)
{
    //definimos el punto actual
    anterior={float(x),float(y)};
    if(button==GLUT_LEFT_BUTTON ){
        
        glPointSize(20);
        anterior.y=480-y;

        glBegin (GL_POINTS);   
            glVertex2d(anterior.x,anterior.y);
        glEnd (); 
        glFlush();
    }  
    
}

void myMouseMove( int x, int y)
{
    glClear(GL_COLOR_BUFFER_BIT);
    actual={float(x),float((480-y))};
    
    if(anterior.x !=0 && anterior.y!=0){
        
        if(anterior.x<actual.x){
            puntoMedio(anterior,actual);
        }else{
            puntoMedio(actual,anterior);
           
        }
        cout<<"[x_ant"<<anterior.x<<" x"<<actual.x<<"] [y_ant"<<anterior.y<<" y"<<actual.y<<"]"<<endl;
    }
    glFlush();
    count ++;
    /*if(count==10){
        glutPostRedisplay();
        count=0;
    }*/
	
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
    glutPassiveMotionFunc( myMouseMove);
    glutKeyboardFunc(keyboard);
    //permite que glu dibuje
    glutMainLoop();
    return 0;
}

