
#include <GL/glu.h>
//GLut permite la gestion de Ventanas
#include <GL/glut.h>


double x1=250,y1=400;
double x2=400,y2=100;
double x3=100,y3=100;
int count=0;
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
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
void drawTrinagles(double x1, double x2, double x3, double y1, double y2, double y3, int n_repet){
    //Dibujamos los puntos
                
    glBegin (GL_TRIANGLES);
        
        double xa=(x1+x3)/2, ya= (y1+y3)/2;
        double xb=(x2+x3)/2, yb= (y2+y3)/2;
        double xc=(x2+x1)/2, yc= (y2+y1)/2;

        glColor3f(1.0f, 1.0f, 1.0f);          
        glVertex2d(xa,ya);

        //glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2d(xb,yb);

        //glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2d(xc,yc);

        int cont=0;
        while(cont<n_repet){
            //Triangulo de arriba
             drawTrinagles(x1,xc,xa,y1,yc,ya,cont++);   
        }    
        cont=0;
        while(cont<n_repet){
            //Triangulo de la izquierda
             drawTrinagles(xa,xb,x3,ya,yb,y3,cont++);
        }    
        cont=0;
        while(cont<n_repet){
            //triangulo de la derecha
             drawTrinagles(xc,x2,xb,yc,y2,yb,cont++);
        }      
                   
    glEnd ();
    glFlush();
}
void mouse(int button, int state, int x, int y)
{
    y=480-y;
    if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        switch (count){
            case 0:
                x1=x,y1=y;
                count++;
                break;
            case 1:
                x2=x,y2=y;
                count++;
                break;
            case 2:
                x3=x,y3=y;
                glColor3f(0.0f, 0.0f, 0.0f);   
                dibujar();
                count=0;
                break;
        }
    }
    
}
void keyboard (unsigned char key, int x, int y)
{
    //color in red
    if(key=='r'){
        glColor3f(1.0f, 0.0f, 0.0f);      
    }
    if(key=='a'){
        glColor3f(0.0f, 0.0f, 1.0f);      
    }
    if(key=='v'){
        glColor3f(0.0f, 1.0f, 0.0f);      
    }
    dibujar();
    glFlush();

}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
//Esta funcion se llama muchas veces
void dibujar(void)
{
    //Limpia la ventana con el color blanco
    glClear(GL_COLOR_BUFFER_BIT);
   
    //Establecemos el tamaño de los puntos
    glPointSize(20);
    int n_repet=5;

    //Dibujamos los puntos
    glBegin (GL_TRIANGLES);
        glVertex2d (x1, y1);
        glVertex2d (x2, y2);
        glVertex2d (x3, y3);
    glEnd ();
    drawTrinagles(x1,x2,x3,y1,y2,y3,n_repet);
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
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    //permite que glu dibuje
    glutMainLoop();
}

