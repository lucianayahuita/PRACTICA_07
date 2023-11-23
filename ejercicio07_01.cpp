// Materia: Programaci�n I, Paralelo 1

// Autor: Luciana Yahuita

// Fecha creaci�n: 23/11/2023

// Fecha modificaci�n: 23/11/2023

// N�mero de ejericio: 1

// Problema planteado: *******
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;
const char*ARCHIVO="EquiposLPFB.bin";
int menudeopciones();
struct structEquiposLPFB
{
    char nombreEquipo[50];
    char colorCamiseta[50];
    char departamento[30];
    int anioCreacion;
};
struct structResultadosLPFB
{
    char nombreEquipoLocal[50];
    char nombreEquipoVisitante[50];
    int golesEquipoLocal;
    int golesEquipoVisitante;
    char fechaPartido[10];
};
structEquiposLPFB ingresardatosequipos();
structResultadosLPFB ingresardatosresultados();
void escribirdatosequipos(structEquiposLPFB);
void escribirresultados(structResultadosLPFB);
void mostrarEquiposDisponibles();
void mostrartabladeposiciones(structEquiposLPFB);
int main(){
    int opcion;
    structEquiposLPFB equipos;
    structResultadosLPFB resultados;
    do{
        opcion=menudeopciones();
        switch (opcion){
            case 1:
                escribirdatosequipos(ingresardatosequipos());
                break;
            case 2:
                escribirresultados(ingresardatosresultados());
                break;
            case 3:
                cout<<"Selecciono la opcion 3:"<<"";//mostrartabladeposiciones(resultados);
                break;
            case 0:
                exit(0);
                break;
        }
    }while(opcion!=0);
    return 0;
}
//Funcion para el menu
int menudeopciones(){
    int op;
    cout<<"**********************MENU DE OPCIONES**************************"<<endl;
    cout<<"\t\t 1. Ingreso de datos de los equipo de la LPFB."<<endl;
	cout<<"\t\t 2. Ingreso los resultados de los partidos."<<endl;
	cout<<"\t\t 3. Reporte de la tabla de posiciones"<<endl;
	cout<<"\t\t 0. Salir del Sistema"<<endl;
	cin>>op;
    return op;
}
//Funcion para ingresar los datos de los equipos
structEquiposLPFB ingresardatosequipos() {
    structEquiposLPFB equipos;
    cout << "***********INGRESO DE DATOS***********" << endl;
    char nombre[50];
    bool nombreRepetido;
    do {
        nombreRepetido = false;
        cout << "Ingrese el nombre del equipo" << endl;
        cin.ignore();
        cin.getline(nombre, 50);

        // Verificar si el nombre ya existe
        ifstream archivoLectura(ARCHIVO, ios::binary);
        while (archivoLectura.read((char*)&equipos, sizeof(structEquiposLPFB))) {
            if (strcmp(nombre, equipos.nombreEquipo) == 0) {
                cout << "Error: El nombre del equipo ya existe. Int�ntelo de nuevo." << endl;
                nombreRepetido = true;
                break;
            }
        }
        archivoLectura.close();
    } while (nombreRepetido);
    // Si el nombre no est� repetido, asignarlo al equipo
    strcpy(equipos.nombreEquipo, nombre);
    cout << "Ingrese el color de la camiseta" << endl;
    cin.getline(equipos.colorCamiseta, 30);
    cout << "Ingrese el departamento" << endl;
    cin.getline(equipos.departamento, 30);
    cout << "Ingrese el anio de creacion" << endl;
    cin >> equipos.anioCreacion;
    escribirdatosequipos(equipos);
    return equipos;
}
void escribirdatosequipos(structEquiposLPFB equipos){
    ofstream archivoEscritura;
    archivoEscritura.open(ARCHIVO,ios::app | ios::binary);
    archivoEscritura.write((char*)&equipos, sizeof(structEquiposLPFB));
    archivoEscritura.close();
}
void mostrarEquiposDisponibles() {
    structEquiposLPFB equipos;

    ifstream archivoLectura(ARCHIVO, ios::binary);

    if (!archivoLectura) {
        cout << "No se pudo abrir el archivo de equipos." << endl;
        return;
    }

    cout << "Equipos disponibles:" << endl;

    while (archivoLectura.read((char*)&equipos, sizeof(structEquiposLPFB))) {
        cout << "- " << equipos.nombreEquipo << endl;
    }

    archivoLectura.close();
}
structResultadosLPFB ingresardatosresultados() {
    structResultadosLPFB resultados;
    structEquiposLPFB equipos;

    cout << "***********INGRESO DE RESULTADOS***********" << endl;

    // Mostrar equipos disponibles
    cout << "Equipos disponibles:" << endl;
    mostrarEquiposDisponibles(); // Implementa esta funci�n para mostrar los equipos disponibles

    // Declarar las variables aqu� para que est�n en el �mbito correcto
    bool equipoLocalExiste;
    bool equipoVisitanteExiste;

    // Ingresar nombre del equipo local y verificar existencia
    do {
        equipoLocalExiste = false; // Declaraci�n aqu�
        cout << "Ingrese el nombre del equipo local" << endl;
        cin.ignore();
        cin.getline(resultados.nombreEquipoLocal, 50);

        ifstream archivoLectura(ARCHIVO, ios::binary);

        while (archivoLectura.read((char*)&equipos, sizeof(structEquiposLPFB))) {
            if (strcmp(resultados.nombreEquipoLocal, equipos.nombreEquipo) == 0) {
                equipoLocalExiste = true;
                break;
            }
        }

        archivoLectura.close();

        if (!equipoLocalExiste) {
            cout << "Error: El equipo local no existe. Int�ntelo de nuevo." << endl;
        }
    } while (!equipoLocalExiste);

    // Ingresar nombre del equipo visitante y verificar existencia
    do {
        equipoVisitanteExiste = false; // Declaraci�n aqu�
        cout << "Ingrese el nombre del equipo visitante" << endl;
        cin.getline(resultados.nombreEquipoVisitante, 50);

        ifstream archivoLectura(ARCHIVO, ios::binary);

        while (archivoLectura.read((char*)&equipos, sizeof(structEquiposLPFB))) {
            if (strcmp(resultados.nombreEquipoVisitante, equipos.nombreEquipo) == 0) {
                equipoVisitanteExiste = true;
                break;
            }
        }

        archivoLectura.close();

        if (!equipoVisitanteExiste) {
            cout << "Error: El equipo visitante no existe. Int�ntelo de nuevo." << endl;
        }
    } while (!equipoVisitanteExiste);
}
void escribirresultados(structResultadosLPFB resultados) {
    ofstream archivoEscritura("ResultadosLPFB.bin", ios::app | ios::binary);

    if (!archivoEscritura) {
        cout << "Error: No se pudo abrir el archivo de resultados." << endl;
        return;
    }

    archivoEscritura.write((char*)&resultados, sizeof(structResultadosLPFB));
    archivoEscritura.close();
}
