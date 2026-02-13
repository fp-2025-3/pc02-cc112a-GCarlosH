#include <iostream>
#include <cstring>
using namespace std;

struct Item{
    char *descripcion;   // memoria dinámica
    int cantidad;
    double precioUnitario;
};

struct Pedido{
    int numeroPedido;
    char *nombreCliente; // memoria dinámica
    Item *items;         // arreglo dinámico de items
    int cantidadItems;
};

Item* crearItem(int cantidadItems){
    Item *b = new Item[cantidadItems];
    const char *descripciones[] = {"Laptop", "Mouse", "Teclado"}; //Inicializamos de forma dinamica para no pedirlo por teclado

    for(int i = 0; i < cantidadItems; i++){
        //COPIAMOS DESCRI PARA QUE AHORA SEA DINAMICO
        int n = strlen(descripciones[i]);
        b[i].descripcion = new char[n + 1];
        strcpy(b[i].descripcion, descripciones[i]);

        b[i].cantidad = i + 1;
        b[i].precioUnitario = 100 * (i + 1);
    }

    return b;
}

double calcularTotal(const Pedido *p){
    double total = 0;
    for(int i = 0; i < p->cantidadItems; i++){
        total += p->items[i].cantidad * p->items[i].precioUnitario;
    }
    return total;
}

Pedido* crearPedido(int numero, const char *cliente, int cantidadItems){
    Pedido *a = new Pedido;

    a->numeroPedido = numero;
    a->cantidadItems = cantidadItems;

    int n = strlen(cliente);
    a->nombreCliente = new char[n + 1]; //para hacerlo de forma dinamica
    strcpy(a->nombreCliente, cliente); // copiamos

    a->items = crearItem(cantidadItems);

    return a;
}

Item* itemMasCaro(const Pedido *p){
    int indice = 0;
    double mascaro = p->items[0].precioUnitario;
    for(int i = 1; i < p->cantidadItems; i++){
        if(p->items[i].precioUnitario > mascaro){
            mascaro = p->items[i].precioUnitario;
            indice = i;
        }
    }
    return &p->items[indice];
}

void liberarPedido(Pedido *p){// ELIMNAMOS POR PARTES YA QUE TENEMOS ESTRUCTURAS CON ARREGLOS (PUNTEROS)
    for(int i = 0; i < p->cantidadItems; i++){
        delete[] p->items[i].descripcion;
    }
    delete[] p->items;
    delete[] p->nombreCliente;
    delete p;
}

int main(){
    int numero = 1;
    char cliente[30] = "Carlos Perez"; //luego lo hacemos dinamico en la funcion
    int cantidadItems = 3;

    Pedido *A = crearPedido(numero, cliente, cantidadItems);

    cout << "Pedido N°: " << A->numeroPedido << endl;
    cout << "Cliente: " << A->nombreCliente << endl;

    cout << "Items:" << endl;
    for(int i = 0; i < A->cantidadItems; i++){
        cout << " - " << A->items[i].descripcion
             << " | Cant: " << A->items[i].cantidad
             << " | Precio: " << A->items[i].precioUnitario << endl;
    }

    double total = calcularTotal(A);
    cout << "Total: " << total << endl;

    Item *caro = itemMasCaro(A);
    cout << "Item mas caro: " << caro->descripcion
         << " | Precio: " << caro->precioUnitario << endl;

    liberarPedido(A);

    return 0;
}
