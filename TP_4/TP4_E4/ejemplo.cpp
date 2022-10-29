#include <stdio.h>
#include <iostream>
#include <fstream>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstring>

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
    
    gluPerspective(45, (float)640/480, 0.01f, 100);
   
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
struct punto
{
    double x=0;
    double y=0;
    double z=0;
};

string* splitString(string line){
    string* lineArray=new string[2];
    lineArray[0]=line.substr(0, line.find(" "));
    lineArray[1]=line.substr(line.find(" "),line.length());
    return lineArray;
}

void dibujar(void)
{
    //Limpia la ventana con el color blanco
    glClear(GL_COLOR_BUFFER_BIT);
   
    // Levantamos el archivo
    string fileName = "mahal.dat";
    ifstream file(fileName.c_str());
    string line = "";
    gluLookAt(20,20,20, 0, 0, 0, 0, 1, 0);

    //Coloreamos el eje x
    
    glBegin(GL_POINTS);
        glVertex3d(0, 0, 0); 
        glVertex3d(1, 0, 0); 
    glEnd();
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex3d(0, 0, 0);
        glVertex3d(100, 0, 0);
    glEnd();

    //Coloreamos el eje y
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex3d(0, 0, 0);
        glVertex3d(0, 100, 0);
    glEnd();

    //Coloreamos el eje z
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
        glVertex3d(0, 0, 0);
        glVertex3d(0, 0, 100);
    glEnd();

    //Coloreamos los puntos
    glColor3f(0.0f, 0.0f, 0.0f);
  
    //obtenemos la primera linea del archivo
    getline(file, line);
        
    int verticesCount=stoi(line);
    cout << " Cant.Vertices:" << verticesCount<<endl;
   
    //Lista de Vertices
    punto vertices[verticesCount];
   
   for (int i = 0; i <verticesCount; i++)
    {
        getline(file, line);
        string* aux=new string[verticesCount];
        aux=splitString(line);
                    
        vertices[i].y = stod(aux[0]);
        vertices[i].x = stod(aux[1]);
    }
   
    //DIbujamos los vertices
    for (int a = 0; a < 360; a++)
    {
        glRotated(a,0,1,0);
        glBegin(GL_POLYGON);
            for (int i = 0; i < verticesCount; i++)
            {
                glVertex3d(vertices[i].x,vertices[i].y,0);
                //cout<<i<<"- ["<<vertices[i].x<<","<<vertices[i].y<<"]"<<endl;//<<","<<vertices[i].z
            }
            
        glEnd();
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
    glutCreateWindow("TP4-E2"); 
    //Registramos la funcion dibujar para que redibuje la pantalla
    glutDisplayFunc(dibujar);
    //inicializamos
    iniciar();
    //permite que glu dibuje
    glutMainLoop();
    return 0;
}

