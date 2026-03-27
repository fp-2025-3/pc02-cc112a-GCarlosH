#include <iostream>
#include <cstring>
using namespace std ;

struct Producto{
    int codigo ;
    char *nombre ;   // cadena dinamica
    double precio ;
    int stock ;
};

// FUNCION PARA CREAR PRODUCTO ( de forma dinamica )
Producto crearProducto(int codigo , const char *nombre , double precio , int stock){
    Producto a ;

    a.codigo = codigo ; //asignamos el codigo

    // ASIGNAMOS LA MEMORIA DINAMICA PARA EL NOMBRE
    int n = strlen(nombre) ;
    a.nombre = new char[n + 1] ;
    strcpy(a.nombre , nombre) ;

    //ASIGNAMOS PRECIO Y STOCK
    a.precio = precio ;
    a.stock = stock ;

    return a ;
}

// CREAMOS LA MEMORIA DE FORMA DINAMICA PARA CREAR EL INVENTARIO
Producto *crearInventario(int n){
    Producto *a = new Producto[n] ;

    for(int i = 0 ; i < n ; i++){
        int codigo ;
        char nombre[30] ;
        double precio ;
        int stock ;

        cout << "----------------- PRODUCTO " << i + 1 << " -----------------" << endl ;
        // SOLICITAMOS LOS DATOS
        cout << "Ingresar codigo: " ; cin >> codigo ;

        cout << "Ingresar nombre: " ; cin.ignore() ; cin.getline(nombre , 30) ;

        cout << "Ingresar precio: " ; cin >> precio ;

        cout << "Ingresar stock: " ; cin >> stock ;

        // USAMOS LA FUNCION crearProducto 
        a[i] = crearProducto(codigo , nombre , precio , stock) ;
    }

    return a ;
}

// FUNCION QUE BUSCARA EL CODIGO QUE SE SOICITARA
Producto *buscarProducto(Producto *inventario , int n , int codigoBuscado){
    for(int i = 0 ; i < n ; i++){
        if(inventario[i].codigo == codigoBuscado){
            return &inventario[i] ;
        }
    }
    return nullptr ;
}

// LIBERAR MEMORIA DEL INVENTARIO
void liberarInventario(Producto *inventario , int n){
    // LIBERARA CADA NOMBRE YA QUE LO GUARDAMOS DE FORMA DINAMICA (y es un arreglo)
    for(int i = 0 ; i < n ; i++){
        delete[] inventario[i].nombre ;
    }

    // LIBERAMOS EL ARREGLO DE PRODUCTOS DEL INVENTARIO
    delete[] inventario ;
}

int main(){
    int n ;

    cout << "Cuantos productos desea registrar: " ; cin >> n ;

    Producto *inventario = crearInventario(n) ; //creamos memoria de forma dinamica

    cout << "\nINVENTARIO\n" ;

    // IMPRIME LO REGISTRADO
    for(int i = 0 ; i < n ; i++){
        cout << "Codigo: " << inventario[i].codigo << " | "
             << "Nombre: " << inventario[i].nombre << " | "
             << "Precio: " << inventario[i].precio << " | "
             << "Stock: " << inventario[i].stock << endl ;
    }

    int codigoBuscado ;
    cout << "\nCodigo a buscar: " ;
    cin >> codigoBuscado ;

    Producto *key = buscarProducto(inventario , n , codigoBuscado) ;    //producto que buscaremos

    // emprime si se encontro una direccion usando la funcion "busacarcodigo"
    if(key != nullptr){
        cout << "Producto encontrado: " << key->nombre
             << " | Precio: " << key->precio << endl ;
    }
    else{
        cout << "Producto no encontrado.\n" ;
    }

    liberarInventario(inventario , n) ;

    //POR BUENA PRACTICA
    inventario = nullptr ;

    return 0 ;
}

