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
struct punto
{
    int x=0;
    int y=0;
};

punto anterior={0,0};
void dibujar(void)
{
    //Limpia la ventana con el color blanco
    glClear(GL_COLOR_BUFFER_BIT);

    // Levantamos el archivo
    string fileName = "dino.dat";
    ifstream file(fileName.c_str());
    string line = "";

    //Pasamos las lineas que no nos interesan
    for (int i = 0; i < 6; i++)
    {
       getline(file, line);
       cout << "Linea leida" << line<< endl;
    }    
    //Coloreamos los puntos
    glColor3f(1.0f, 0.0f, 0.0f);
    //Establecemos el tamaño de los puntos
    glPointSize(3);
    
    //Dibujamos los puntos
    for (int i = 0; i < 400; i++)
    {
     
        //obtenemos la parte del string que nos insteresa y lo convertimos en numero
        getline(file, line);
        
        if(line[0] != '#'){
            cout << "Linea leida:" << line<< endl;
            cout << "Largo Linea:" << line.length()<< endl;
            
            //Solo leermos las lineas que tienen x e y
            if(line.length()>3){
                double x = stoi(line.substr(0, line.find(' ')));
                double y = stoi(line.substr(line.find(' '), line.length()));
                if(anterior.x==0 && anterior.y==0){
                    anterior.x=x;
                    anterior.y=y;
                    cout << "ENTRA"<< endl;
                }else{
                    cout << "ENTRA2"<< endl;
                    glBegin (GL_LINES);
                        glVertex2d(anterior.x,anterior.y);
                        glVertex2d(x,y);
                    glEnd ();
                    anterior.x=x;
                    anterior.y=y;
                }
                
            }
        }
       
     
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
    glutCreateWindow("Ejercicio 5"); 
    //Registramos la funcion dibujar para que redibuje la pantalla
    glutDisplayFunc(dibujar);
    //inicializamos
    iniciar();
    //permite que glu dibuje
    glutMainLoop();
    return 0;
}

