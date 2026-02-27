#include <iostream>
#include <cstring>
#include <fstream>
using namespace std ;
//CREAMOS LA ESTRUCTURA SOLICITADA
struct Venta{
    int idVenta ;
    int idVendedor ;
    int idProducto ;
    int cantidad ;
    double precioUnitario ;
};

int main(){
    // Inicializamos el objeto y lo colocamos en la posicion final
    ifstream archivoBi("ventas.dat" , ios::ate) ;
    Venta venta ;
    if(!archivoBi){ // como buena practica 
        cerr << " Error al abrir el archivo " ;
    }
    //Para saber bytes totales 
    streampos registrosTotales = archivoBi.tellg() ;
    int tamanio = sizeof(Venta) ; //tamaño de cada estructura
    int nRegistos = registrosTotales / tamanio ;

    //ahora volvemos al inicio 
    archivoBi.clear() ;
    archivoBi.seekg(0 , ios::beg) ;

    long int montoTotal = 0 ;

    long int mayorRecaudacion = 0 ; //valor arbitario
    int IDmejorVendedor ;

    int masVendido ;
    int IDproductoMasVendido ;

    for(int i = 0 ; i < nRegistos ; i ++){
        // Colocamos el puntero de lectura donde corresponda 
        archivoBi.seekg((i) * sizeof(Venta), ios::beg);
        archivoBi.read(reinterpret_cast<char *>(&venta) , sizeof(Venta)) ;

        //PARA CALCULAR EL MONTO TOTAL
        long int monto = venta.cantidad * venta.precioUnitario ;
        montoTotal += monto ;

        // PARA DETERINAR EL VENDEDOR CON MAYOR RECAUDACION 
        if(mayorRecaudacion < monto ){
            mayorRecaudacion = monto ;
            IDmejorVendedor = venta.idVendedor ;
        }

        //PARA DETERMINAR EL PRODUCTO MAS VENDIDO 
        if(masVendido < venta.cantidad){
            masVendido = venta.cantidad ;
            IDproductoMasVendido = venta.idProducto ;
        }
    }
    archivoBi.close() ;

    ofstream archivoNuevo("Reporte.txt") ;

    archivoNuevo << "---- REPORTE DENERAL DE VENTAS ----" << endl 
                 << "\nTotal registros : " << nRegistos << endl 
                 << "MONTO TOTAL VENDIDO : \n$ " << montoTotal << endl  
                 <<"\n----------------------------------" << endl 
                 << "VENDEDOR CON MAYOR RECAUDACION : " << endl 
                 << "ID Vendedor : " << IDmejorVendedor 
                 << "\nTotal vendido : $" << mayorRecaudacion << endl
                 <<"\n----------------------------------" 
                 <<"\nPRODUCTO MAS VENDIDO : " << endl
                 << "\nID Producto : " << IDproductoMasVendido
                 << "\nTotal unidades : " << masVendido<<endl
                 << "\n---------------------------------"
                 <<"\nVENTAS SOSPECHOSAS (cantidad > 100) :" ;

    return 0 ;
}