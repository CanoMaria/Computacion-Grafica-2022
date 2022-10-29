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
    //gluOrtho2D(0.0, 640, 0.0, 480);
   
    gluPerspective(45, (float)640/480, 0.01f, 100);
   
    //glOrtho(-2.0,2.0,-2.0,2.0,-1.0,1.0);
   
   
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
struct punto
{
    double x=0;
    double y=0;
    double z=0;
};
string* splitString(string line){
    string* lineArray=new string[6];
    int pos=0;
    string number="";
    
    for (int j = 0; j < line.length(); j++)
    {
        if(line[j]==' '){
            
            lineArray[pos]=number;
            number="";
            pos++;
        }
        else
        {
            number=number+line[j];
        }

        if(j==line.length()-1){
            lineArray[pos]=number;
        }
        
    }
    return lineArray;
}

void dibujar(void)
{
    //Limpia la ventana con el color blanco
    glClear(GL_COLOR_BUFFER_BIT);
    // Levantamos el archivo
    string fileName = "prisma.3vn";
    ifstream file(fileName.c_str());
    string line = "";
    gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);

    //Coloreamos el eje x
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex3d(0, 0, 0);
        glVertex3d(1, 0, 0);
    glEnd();

    //Coloreamos el eje y
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex3d(0, 0, 0);
        glVertex3d(0, 1, 0);
    glEnd();

    //Coloreamos el eje z
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
        glVertex3d(0, 0, 0);
        glVertex3d(0, 0, 1);
    glEnd();
    //Coloreamos los puntos
    glColor3f(0.0f, 0.0f, 0.0f);
  
    //obtenemos la primera linea del archivo
    getline(file, line);
    //cout << "Linea leida:" << line<<endl;
    
    string* count=new string[3];
    count=splitString(line);

    int verticesCount=stoi(count[0]);
    int normalesCount=stoi(count[1]);
    int superficiesCount=stoi(count[2]);

    cout << " Cant.Vertices:" << verticesCount;
    cout << " Cant Normales:" << normalesCount;
    cout << " Cant Superficies:" << superficiesCount << endl;
    
  

    //Lista de Vertices
    punto vertices[verticesCount];
    for (int i = 0; i <verticesCount; i++)
    {
        getline(file, line);
        string* aux=new string[verticesCount];
        aux=splitString(line);
                    
        vertices[i].x = stod(aux[0]);
        vertices[i].y = stod(aux[1]);
        vertices[i].z= stod(aux[2]);
        //cout<<i<<"- ["<<vertices[i].x<<","<<vertices[i].y<<","<<vertices[i].z<<"]"<<endl;
    }

    //Lista de Normales
    punto normales[normalesCount];
    for (int i = 0; i <normalesCount; i++)
    {
        getline(file, line);
        string* aux=new string[normalesCount];
        aux=splitString(line);
                    
        normales[i].x = stod(aux[0]);
        normales[i].y = stod(aux[1]);
        normales[i].z= stod(aux[2]);
        //cout<<i<<"- ["<<normales[i].x<<","<<normales[i].y<<","<<normales[i].z<<"]"<<endl;
    }

    //Dibujo

    int lineCount=0;
    //double ang=120.0;
    //glRotatef(ang,0.0,1.0,0.0);
    for (int i = 0; i < 5; i++)
    {
        //obtengo la linea donde esta la cant de vertices (ej 4)
        getline(file, line);
        int tam=stoi(line);
        
        //cout<<tam<<endl;
        //DIBUJO VERTICES
        //obtengo la linea donde esta la lista de vertices
        getline(file, line);
        string* vList=new string[tam];
        vList=splitString(line);
        
        glBegin(GL_LINE_LOOP);
            //recorro el arreglo de lista 
            //cout<<"[";
            for (int j = 0; j < tam; j++)
            {
                int position=stoi(vList[j]);
                glVertex3d(vertices[position].x/2,vertices[position].y/2,vertices[position].z/2);
                //cout<<vList[j]<<",";
            }
            //cout<<"]"<<endl;
        glEnd();

        //DIBUJO NORMALES
        getline(file, line);
        string* nList=new string[tam];
        nList=splitString(line);
        glBegin(GL_LINE_LOOP);
            //recorro el arreglo de lista 
            //cout<<"[";
            for (int j = 0; j < tam; j++)
            {
                int position=stoi(nList[j]);
                glVertex3d(normales[position].x,normales[position].y,normales[position].z);
                //cout<<nList[j]<<",";
            }
            //cout<<"]"<<endl;
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

