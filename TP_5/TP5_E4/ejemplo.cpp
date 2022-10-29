#include <stdio.h>
#include <iostream>
#include <fstream>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstring>

using namespace std;
//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
//Se llama antes de la funcion dibujar

string  material="default";
string figure="wineglas.3vn";
void iniciar(void)
{
    GLfloat mat_specular[]= { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 128.0 };
    GLfloat light_position[] = { 50.0, 50.0, 50.0, 1.0 };
    GLfloat direccion[] = {-25.0, 50.0, 0.0};

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    //Definimos el material
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv (GL_LIGHT0, GL_SPOT_DIRECTION, direccion);
    //Definimos la luz
   
    
    //Activamos la iluminacion
    glEnable(GL_LIGHTING);
    //Activamos el foco numero 0
    glEnable(GL_LIGHT0);
    //Habilitamos el uso de Z-buffer
    glEnable(GL_DEPTH_TEST);
    //Habilitamos la dependecia de color
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
struct punto
{
    double x=0;
    double y=0;
    double z=0;
};

//----Codigo para separ por espacios
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

//---Codifgo para pargar archivos 3vn
void load3VN(string fileNam,string color){
    
    // Levantamos el archivo
    string fileName = fileNam;
    ifstream file(fileName.c_str());
    string line = "";
   
  
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
        vertices[i].z = stod(aux[2]);
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

    //Coloreamos los puntos
    if (color=="white")
    {
        glColor3f(1.0f, 1.0f, 1.0f);
    }

    //Dibujo
    int lineCount=0;
    for (int i = 0; i < superficiesCount; i++)
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

        glBegin(GL_POLYGON);
            //recorro el arreglo de lista 
            //cout<<"[";
            for (int j = 0; j < tam; j++)
            {
                int position=stoi(vList[j]);
                glVertex3d(vertices[position].x,vertices[position].y,vertices[position].z);
                //cout<<vList[j]<<",";
            }
            //cout<<"]"<<endl;
        glEnd();

        //DIBUJO NORMALES
        getline(file, line);
        string* nList=new string[tam];
        nList=splitString(line);

        glBegin(GL_POLYGON);
            //recorro el arreglo de lista 
            //cout<<"[";
            for (int j = 0; j < tam; j++)
            {
                int position=stoi(nList[j]);
                
                glNormal3f(normales[position].x,normales[position].y,normales[position].z);
                //cout<<nList[j]<<",";
            }
            //cout<<"]"<<endl;
        glEnd();
    }
    file.close();
}



//---Codigo para cargar archivos. dat
void loadDat(string fileNam,string color){

    //Coloreamos los puntos
    if (color=="white")
    {
        glColor3f(1.0f, 1.0f, 1.0f);
    }

    string fileName = "mahal.dat";
    ifstream file(fileName.c_str());
    string line = "";
    

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
        string* lineArray=new string[2];
        lineArray[0]=line.substr(0, line.find(" "));
        lineArray[1]=line.substr(line.find(" "),line.length());
        aux=lineArray;
                    
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

    file.close();   
}
double posX=3;
double posY=3;
double posZ=3;

void dibujar(void)
{
    //Limpia la ventana con el color blanco
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    gluLookAt(posX, posY, posZ, 0, 0, 0, 0, 1, 0);
    
    cout<<"Material:"<<material<<endl;
    glEnable (GL_COLOR_MATERIAL);
    
    glColorMaterial (GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    // reflectancia ambiental y difusa del material
    if (material=="blackPlastic")
    {
       glColor3f (0.5, 0.5, 0.5);
    }
    
    if (material=="brass")
    {
       glColor3f (0.992157, 0.941176, 0.807843);
    }

    if (material=="bronze")
    {
       glColor3f (0.393548, 0.271906, 0.166721);
    }
    if (material=="chrome")
    {
        glColor3f (0.774597, 0.774597, 0.774597);
    }
    if (material=="copper")
    {
        glColor3f (0.256777, 0.137622, 0.086014);
    }
    if (material=="gold")
    {
        glColor3f (0.628281, 0.55, 0.36);
    }
    if (material=="pewter")
    {
        glColor3f (0.3333, 0.3333, 0.521569);
    }
    if (material=="silver")
    {
        glColor3f (0.508273, 0.508273, 0.508273);
    }
    if (material=="polishedSilver")
    {
        glColor3f (0.773911, 0.773911, 0.773911);
    }
    // Desactivar el tracking de color
    glDisable (GL_COLOR_MATERIAL);
    
    if (figure=="mahal.dat")
    {
        loadDat(figure,"white");
        //
    }else if (figure=="salon")
    {
        load3VN("pared_1.3vn","white");
        load3VN("pared_2.3vn","white");
        load3VN("piso.3vn","white");
        load3VN("mesa.3vn","white");
        load3VN("pelota.3vn","white");
        load3VN("silla.3vn","white");
        //glutSolidSphere (1.0, 20, 16);
    }else{
        //glRotated(40.0,0,1,0);
        load3VN(figure,"white");
        //glutSolidSphere (1.0, 20, 16);
    }
    //Refresca
    glFlush();
   
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)640/480, 0.1f, 100);
    //glOrtho (-1.5*(GLfloat)w/(GLfloat)h, 1.5*(GLfloat)w/(GLfloat)h, -1.5, 2.0, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//Funcion de Teclado
void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 'z':
        posX=3;
        posY=3;
        posZ=3;
        figure="wineglas.3vn";
        break;
    case 'x':
        posX=20;
        posY=20;
        posZ=3;
        figure="mahal.dat";
        break;
    case 'c':
        posX=7;
        posY=4;
        posZ=3;
        figure="salon";
        break;
    case '1':
        material="blackPlastic";
        break;
    case '2':
        material="brass";
        break;
    case '3':
        material="bronze";
        break;
    case '4':
        material="chrome";
        break;
    case '5':
        material="copper";
        break;
    case '6':
        material="gold";
        break;
    case '7':
        material="pewter";
        break;
    case '8':
        material="silver";
        break;
    case '9':
        material="polishedSilver";
        break;
    case '0':
        material="default";
        break;
    case 'w':
        posY=posY+0.5;
        break;

    case 's':
        posY=posY-1.0;
        break;

    case 'a':
        posX = posX+0.5;
        break;

    case 'd':
        posX = posX-0.5;
        break;

    case 'q':
        posZ =posZ+0.5;
        break;
    case 'e':
        posZ =posZ-0.5;
        break;
  }
  cout << "[" << posX << "," << posY << "," << posZ << "]" << endl;
  glutPostRedisplay();
}
//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
    //inicializamos las primitivas de las ventanas
    glutInit(&argc, argv);
    //trabaja en un modo de solo buffer y el modelo de color RGB
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   //Dimensiones de la ventana
    glutInitWindowSize(640,480);
    //Posicion de la ventana, dentro de la resulucion de la pantalla
    glutInitWindowPosition(150, 100); 
    //Creamos la ventana y le ponemos un nombre
    glutCreateWindow("TP5-E4"); 
    //Registramos la funcion dibujar para que redibuje la pantalla
    glutDisplayFunc(dibujar);
    //Permitimos ingresar comandos de teclado
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    //inicializamos
    iniciar();
    //permite que glu dibuje
    glutMainLoop();

   
    return 0;
}

