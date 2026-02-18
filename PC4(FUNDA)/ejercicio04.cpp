#include <iostream>
#include <cstring>
using namespace std ;

struct Item{
    char *descripcion ;   // memoria dinámica
    int cantidad ;
    double precioUnitario ;
};

struct Pedido{
    int numeroPedido ;
    char *nombreCliente ; // memoria dinámica
    Item *items ;         // arreglo dinámico de items
    int cantidadItems ;
};

// FUNCION PARA CREAR EL ITEM
Item crearItem(const char* descripcion, int cantidad, double precio){
    Item a ;

    int n = strlen(descripcion) ; //mide la cantidad de letras para poder asignar en el tamaño de la memoria dinamica
    a.descripcion = new char[n + 1];
    strcpy(a.descripcion, descripcion) ; //copia la descripcion

    a.cantidad = cantidad ;
    a.precioUnitario = precio ;

    return a ;
}

Pedido *crearPedido(int numero, const char* cliente, int cantidadItems){
    Pedido *a = new Pedido ;

    a->numeroPedido = numero ;
    a->cantidadItems = cantidadItems ;

    // GUARDAMOS AHORA EL NOMBRE EN FORMA DINAMICA
    int n = strlen(cliente) ; //cuenta la cantidad de letras para asiganrlo luego crear la memoria dinamica con espaio suficiente
    a->nombreCliente = new char[n + 1] ;
    strcpy(a->nombreCliente, cliente) ;

    // reservamos memoria dinaica
    a->items = new Item[cantidadItems] ;

    // inicializamos items llamando a crearItem (como pedía el ejercicio)
    const char *descripciones[] = {"Laptop", "Mouse", "Teclado"} ;

    for(int i = 0; i < cantidadItems; i++){
        a->items[i] = crearItem(descripciones[i], i + 1, 100 * (i + 1)) ; //forma simplificada (respecto a lo que presente en la pc)
    }

    return a ;
}

double calcularTotal(const Pedido *p){ //CALCULA EL PRECIO TOTAL REAIZANDO UNA SUMATORIA
    double total = 0 ;
    for(int i = 0; i < p->cantidadItems; i++){
        total += p->items[i].cantidad * p->items[i].precioUnitario;
    }
    return total;
}

//MEDIANTE COMPARACION SIMPLE ENCONTRAMOS EL ITEM MAS CARO
Item *itemMasCaro(const Pedido *p){
    int index = 0;
    double mascaro = p->items[0].precioUnitario;

    for(int i = 1; i < p->cantidadItems; i++){
        if(p->items[i].precioUnitario > mascaro){
            mascaro = p->items[i].precioUnitario;
            index = i;
        }
    }

    return &p->items[index];
}

void liberarPedido(Pedido *p){
    // AQUI LIBERAMOS LA MEMORIA PARA CADA DESCRIPCION YA QUE ESTE FUE CREADA DE FORMA DINAMICA
    for(int i = 0 ; i < p->cantidadItems ; i++){
        delete[] p->items[i].descripcion ; //eliminamos cada descri
    }

    delete[] p->items ; //eliminamos el espacio que opcuapaba
    delete[] p->nombreCliente ;
    delete p ;

}

int main(){
    int numero = 1 ;
    char cliente[30] = "Carlos Perez" ;
    int cantidadItems = 3 ;

    Pedido *A = crearPedido(numero, cliente, cantidadItems) ;

    cout << "Pedido N°: " << A->numeroPedido << endl ;
    cout << "Cliente: " << A->nombreCliente << endl ;

    //IMPRIMIMOS
    cout << "Items:" << endl;
    for(int i = 0; i < A->cantidadItems; i++){
        cout << " - " << A->items[i].descripcion
             << " | Cant: " << A->items[i].cantidad
             << " | Precio: " << A->items[i].precioUnitario << endl ;
    }

    double total = calcularTotal(A) ; //implementacion de la funcion que calcula el total
    cout << "Total: " << total << endl ;

    Item *caro = itemMasCaro(A) ; //iplementacion que busca lo mas caro
    cout << "Item mas caro: " << caro->descripcion
         << " | Precio: " << caro->precioUnitario << endl ;

    liberarPedido(A) ;
    //Y COMO BUENA PRACTICA HACEMOS QUE APUNTE A nullptr
    A = nullptr ;

    return 0 ;
}

