#include <iostream>
#include <fstream>
#include <iomanip>   // para controlar decimales
using namespace std ;

//CREAMOS LA ESTRUCTURA SOLICITADA
struct Venta{
    int idVenta ;
    int idVendedor ;
    int idProducto ;
    int cantidad ;
    double precioUnitario ;   // correcion a float
};

int main(){

    // Inicializamos el objeto y lo colocamos en la posicion final
    ifstream archivoBi("ventas.dat" , ios::binary | ios::ate) ;
    
    if(!archivoBi){ // como buena practica 
        cerr << " Error al abrir el archivo " << endl ;
        return 1 ;
    }

    //Para saber bytes totales 
    streampos registrosTotales = archivoBi.tellg() ;
    int tamanio = sizeof(Venta) ;
    int nRegistos = registrosTotales / tamanio ;

    //ahora volvemos al inicio 
    archivoBi.seekg(0 , ios::beg) ;

    float montoTotal = 0 ; //ahora son float
    float mayorRecaudacion = 0 ;
    int IDmejorVendedor = 0 ;

    int masVendido = 0 ;
    int IDproductoMasVendido = 0 ;

    Venta venta ;

    //PRIMERA LECTURA: SOLO CALCULOS
    for(int i = 0 ; i < nRegistos ; i ++){

        archivoBi.read(reinterpret_cast<char *>(&venta) , sizeof(Venta)) ;

        float monto = venta.cantidad * venta.precioUnitario ;
        montoTotal += monto ;

        // PARA DETERMINAR EL VENDEDOR CON MAYOR RECAUDACION 
        if(monto > mayorRecaudacion){
            mayorRecaudacion = monto ;
            IDmejorVendedor = venta.idVendedor ;
        }

        //PARA DETERMINAR EL PRODUCTO MAS VENDIDO 
        if(venta.cantidad > masVendido){
            masVendido = venta.cantidad ;
            IDproductoMasVendido = venta.idProducto ;
        }
    }

    archivoBi.close() ;

    //CREAMOS EL ARCHIVO REPORTE
    ofstream archivoNuevo("Reporte.txt") ;

    // Para que el dinero salga con 2 decimales
    archivoNuevo << fixed << setprecision(2);

    archivoNuevo << "---- REPORTE GENERAL DE VENTAS ----" << endl 
                 << "\nTotal registros : " << nRegistos << endl 
                 << "\nMONTO TOTAL VENDIDO : $" << montoTotal << endl  
                 << "\n----------------------------------" << endl 
                 << "\nVENDEDOR CON MAYOR RECAUDACION :" << endl 
                 << "ID Vendedor : " << IDmejorVendedor 
                 << "\nTotal vendido : $" << mayorRecaudacion << endl
                 << "\n----------------------------------" 
                 << "\nPRODUCTO MAS VENDIDO :" << endl
                 << "\nID Producto : " << IDproductoMasVendido
                 << "\nTotal unidades : " << masVendido << endl
                 << "\n---------------------------------" 
                 << "\nVENTAS SOSPECHOSAS (cantidad > 100):" << endl ;

    //SEGUNDA LECTURA PARA DETECTAR VENTAS SOSPECHOSAS
    ifstream archivoBi2("ventas.dat" , ios::binary) ;

    bool haySospechosas = false ;

    for(int i = 0 ; i < nRegistos ; i ++){

        archivoBi2.read(reinterpret_cast<char *>(&venta) , sizeof(Venta)) ;

        if(venta.cantidad > 100){

            haySospechosas = true ;

            archivoNuevo << "\nID Venta : " << venta.idVenta
                         << " | ID Vendedor : " << venta.idVendedor
                         << " | Producto : " << venta.idProducto
                         << " | Cantidad : " << venta.cantidad
                         << endl ;
        }
    }

    if(!haySospechosas){
        archivoNuevo << "\nNo hay ventas sospechosas registradas." << endl ;
    }

    archivoBi2.close() ;
    archivoNuevo.close() ;

    return 0 ;
}