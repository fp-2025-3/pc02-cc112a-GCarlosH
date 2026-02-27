#include <iostream>
#include <fstream>
using namespace std;
//CREAMOS LA ESRUCTURA SOLICITADA
struct Empleado{
    int id ;
    char nombre[30] ;
    double salario ;
};

int main(){
    //CREAMOS E INIZIALIZAMOS EL OBJETO
    fstream archivoBi("empleados.dat", ios::in | ios::out | ios::binary) ;

    if(!archivoBi){ //como buena practica 
        cout << "Error al abrir el archivo.";
        return 1;
    }

    Empleado empleado; 
    int ID;
    
    cout << "Ingrese ID del empleado: " ; cin >> ID ;
    int n = ID;

    // Colocamos el puntero de lectura en el empleado requerido 
    archivoBi.seekg((n-1) * sizeof(Empleado), ios::beg);

    // Leemos solo los datos del empleado con ID = n
    archivoBi.read(reinterpret_cast<char*>(&empleado), sizeof(Empleado));

    // IMPRIMOS LOS DATOS DEL EMPLEADDO
    cout << "\n--- DATOS DEL EMPLEADO ---";
    cout << "\nID: " << empleado.id;
    cout << "\nNombre: " << empleado.nombre;
    cout << "\nSalario: " << empleado.salario;

    // Actualizamos el salario
    double nuevoSalario;
    cout << "\n\nIngrese nuevo Salario: ";
    cin >> nuevoSalario;

    empleado.salario = nuevoSalario;

    // Ahora colocamos el puntero de escritura en la posicion requerida 
    archivoBi.seekp((n-1) * sizeof(Empleado), ios::beg);

    // esto sirve para ahora cambiar el nuevo salario usnado el empleado.salario 
    archivoBi.write(reinterpret_cast<char*>(&empleado), sizeof(Empleado));

    cout << "\n\nSalario actualizado correctamente.";

    archivoBi.close();

    return 0;
}