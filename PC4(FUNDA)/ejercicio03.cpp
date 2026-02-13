#include <iostream>
#include <cstring>
#include <string>
using namespace std ;

struct Producto{
    int codigo ;
    char *nombre ; // cadena dinamica
    double precio ;
    int stock ;
};

Producto crearProducto(int codigo , const char *nombre , double precio , int stock){
    Producto a ;

    //GUARDAMOS EL CODIGO
    a.codigo = codigo ;

    //GUARDAMOS EL NOMBRE
    int n = strlen(nombre) ;
    a.nombre = new char[n + 1] ; 
    strcpy(a.nombre, nombre) ;

    //GUARDAMOS PRECIO
    a.precio = precio ;
    //GUARDAMOS STOCK
    a.stock = stock ;

    return a ;
}

Producto *crearInventario(int n){
    Producto *a = new Producto[n] ;

    for(int i = 0 ; i < n ; i++){
        int codigo ;
        char nombre[30] ;  //luego lo registraremos como dinamico en la siguiente funcion
        double precio ;
        int stock ;
        cout << "----------------- PRODUCTO " << i+1 << " -----------------" << endl ;
        cout << "Ingresar codigo: " ;
        cin >> codigo ;

        cout << "Ingresar nombre: " ;
        cin.ignore();
        cin.getline(nombre, 30) ;

        cout << "Ingresar precio: " ;
        cin >> precio ;

        cout << "Ingresar stock: " ;
        cin >> stock ;

        a[i] = crearProducto(codigo, nombre, precio, stock) ;
    }
    return a;
}

Producto *buscarProducto(Producto *inventario, int n, int codigoBuscado){
    for(int i = 0 ; i < n ; i++){
        if(codigoBuscado == inventario[i].codigo){
            return &inventario[i] ; // retornar el producto encontrado
        }
    }
    return nullptr ;
}

void liberarInventario(Producto *inventario, int n){
    for(int i = 0; i < n; i++){
        delete[] inventario[i].nombre ; // liberar cada nombre
    }
    delete[] inventario ; // liberar el arreglo de productos
}

int main(){
    int n ;
    cout << "Cuantos productos desea registrar: " ;
    cin >> n ;

    Producto *inventario = crearInventario(n) ;

    cout << "\nINVENTARIO\n" ;
    for(int i = 0; i < n; i++){
        cout << "Codigo: " << inventario[i].codigo << " | "
             << "Nombre: " << inventario[i].nombre << " | "
             << "Precio: " << inventario[i].precio << " | "
             << "Stock: " << inventario[i].stock << endl ;
    }

    int codigoBuscado ;
    cout << "\nCodigo a buscar: " ;
    cin >> codigoBuscado ;

    Producto *key = buscarProducto(inventario, n, codigoBuscado) ;

    if(key != nullptr){
        cout << "Producto encontrado: " << key->nombre
             << " | Precio: " << key->precio << endl ;
    } else {
        cout << "Producto no encontrado.\n" ;
    }

    liberarInventario(inventario, n);
    return 0;
}
