#include <iostream>
#include <fstream>
#include <cstring>
using namespace std ;

// FUNCION PARA CALCULAR LOS PROMEDIOS Y RETORNAR LA CANTIDAD DE ALUMNOS
int* promediosAlumnos(ifstream &archivoIn, int &cantidad) {
    int *promedios = new int[100] ; 
    cantidad = 0 ;

    int numeroDeAlumno ;
    char nombre[20] ;
    int nota1, nota2, nota3 ; // como sabemos que son 3 notas enotnces :

    while(archivoIn >> numeroDeAlumno >> nombre >> nota1 >> nota2 >> nota3){
        promedios[cantidad] = (nota1 + nota2 + nota3) / 3 ;
        cantidad++ ;
    }

    return promedios ;
}

int main(){
    // INICIALIZAMOS EL OBJETO Y LO CONECTAMOS
    ifstream archivoIn("notas.txt") ;

    if(!archivoIn){ // por buena practica agregamos :
        cerr << "Error al abrir Notas.txt" ;
        return 1;
    }

    int cantidadAlumnos = 0 ;

    // Calculamos los promedios usando la funcion
    int *promedios = promediosAlumnos(archivoIn, cantidadAlumnos);

    // ahora hacemos que vuelva esto a la posicion inicial por ello usamos :
    archivoIn.clear() ;
    archivoIn.seekg(0, ios::beg) ;

    //Creamos un nuevo objeto para escritura
    ofstream archivoNuevo("reporteAlumnos.txt") ;

    int numeroDeAlumno ;
    char nombre[20] ;
    int nota1, nota2, nota3 ;
    int i = 0 ;

    int mayorProm = promedios[0] , menorProm = promedios[0]; // inicializamos con valor arbitrario para luego comparar
    char mejorAlumno[20] ;
    char menorAlumno[20] ;


    while(archivoIn >> numeroDeAlumno >> nombre >> nota1 >> nota2 >> nota3){

        char condicion[100] ;

        if(promedios[i] >= 10){
            strcpy(condicion, "APROBADO") ;
        }
        else{
            if(nota1 < 5 || nota2 < 5 || nota3 < 5){
                strcpy(condicion, "DESAPROBADO POR REGLAMENTO") ;
            }
            else{
                strcpy(condicion, "DESAPROBADO") ;
            }
        }

        archivoNuevo << numeroDeAlumno << " "
                     << nombre << " " << promedios[i] << " "
                     << condicion << endl ;

        // Verificamos el mayor y menor prom para agregarlos al final
        if(promedios[i] > mayorProm){
            mayorProm = promedios[i] ;
            strcpy(mejorAlumno, nombre) ;
        }
        if(promedios[i] < menorProm){
            menorProm = promedios[i] ;
            strcpy(menorAlumno , nombre) ;
            
        }

        i++ ;
    }

    // Calcular promedio general
    int suma = 0 ;
    for(int j = 0 ; j < cantidadAlumnos ; j++){
        suma += promedios[j] ;
    }

    int promedioGeneral = suma / cantidadAlumnos ;

    archivoNuevo << endl << "Total de estudiantes : " << cantidadAlumnos << endl
                 << "Promedio general del curso : " << promedioGeneral << endl
                 << "Alumno con mayor promedio : " << mejorAlumno  << endl
                 << "El estudiante con menor promedio : " << menorAlumno << endl ;

    delete[] promedios ; // eliminamos el puntero

    archivoIn.close() ;
    archivoNuevo.close() ;

    return 0;
}