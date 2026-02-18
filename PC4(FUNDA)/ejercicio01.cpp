#include <iostream>
using namespace std ;

// FUNCION EXTRA PARA FACILITAR LA IMPRESION :)
void imprimirPolinomio(int *coef , int gradoMax){
    for(int i = 0 ; i <= gradoMax ; i++){
        if(*(coef + i) != 0){
            cout << *(coef + i) << "x^" << gradoMax - i << " " ;
        }
    }
    cout << endl ;
}

// FUNCION PQUE SUMARA LOS POLINOMIOS
int *sumaPolinomios(int *p1 , int g1 , int *p2 , int g2 , int *gradoRes){
    int gmax ;
    if(g1 > g2){
        gmax = g1 ;
    }
    else{
        gmax = g2 ;
    }
    *gradoRes = gmax ;

    int *res = new int[gmax + 1] ; //asignamos memoria dinamica para el reultado
    for(int i = 0 ; i <= gmax ; i++){
        *(res + i) = 0 ; //inizializamos todo con 0  
        if(i <= g1){
            *(res + i) += *(p1 + (g1 - i)) ;
        }
        if(i <= g2){
            *(res + i) += *(p2 + (g2 - i)) ;
        }
    }

    return res ;
}

// FUNCION QUE MULTIPLICARA LOS RESULTADOS
int *multiplicaPolinomios(int *p1 , int g1 , int *p2 , int g2 , int *gradoRes){
    *gradoRes = g1 + g2 ;

    int *res = new int[*gradoRes + 1] ; // asignamos memoria dinamica
    for(int i = 0 ; i <= *gradoRes ; i++){
        *(res + i) = 0 ;    //inizializamos todo con 0  
    }

    for(int i = 0 ; i <= g1 ; i++){
        for(int j = 0 ; j <= g2 ; j++){
            *(res + (i + j)) += (*(p1 + i)) * (*(p2 + j)) ;
        }
    }

    return res ;
}

int main(){
    // POLINOMIOS DADOS EN EL PROBLEMA Y COEF DINAMICO
    // POLINOMIO 1 
    int grado1 = 2 ;
    int *coef1 = new int[grado1 + 1]{1 , 0 , 3} ;

    // POLINOMIO 2
    int grado2 = 2 ;
    int *coef2 = new int[grado2 + 1]{0 , 4 , 5} ;

    // POLINOMIO 3
    int grado3 = 2 ;
    int *coef3 = new int[grado3 + 1]{3 , 0 , 1} ;

    cout << "Polinomio 1: " ; imprimirPolinomio(coef1 , grado1) ;

    cout << "Polinomio 2: " ; imprimirPolinomio(coef2 , grado2) ;

    cout << "Polinomio 3: " ; imprimirPolinomio(coef3 , grado3) ;

    // AQUI SUMAMOS LOS POLINOMIOS DE FORMA "gradual" ( 2 en 2)
    int gradoSuma1 ;
    int *suma12 = sumaPolinomios(coef1 , grado1 , coef2 , grado2 , &gradoSuma1) ;

    int gradoSumaFinal ;
    int *sumaTotal = sumaPolinomios(suma12 , gradoSuma1 , coef3 , grado3 , &gradoSumaFinal) ;

    cout << "\nSuma de los tres polinomios:\n" ;
    imprimirPolinomio(sumaTotal , gradoSumaFinal) ;

    // MULTIPLICAMOS LOS POLINOSMIOS ( de forma gradual , de 2 en 2 )
    int gradoProd1 ;
    int *prod12 = multiplicaPolinomios(coef1 , grado1 , coef2 , grado2 , &gradoProd1) ;

    int gradoProdFinal ;
    int *prodTotal = multiplicaPolinomios(prod12 , gradoProd1 , coef3 , grado3 , &gradoProdFinal) ;

    cout << "\nProducto de los tres polinomios:\n" ; imprimirPolinomio(prodTotal , gradoProdFinal) ;

    // LIBERAMOS MEMORIA ;
    delete[] coef1 ;
    delete[] coef2 ;
    delete[] coef3 ;
    delete[] suma12 ;
    delete[] sumaTotal ;
    delete[] prod12 ;
    delete[] prodTotal ;

    //COMO BUENA PRACTICA LUEGO DE LIBERAR MEMORIA 
    coef1 = nullptr ;
    coef2 = nullptr ;
    coef3 = nullptr ;
    suma12 = nullptr ;
    sumaTotal = nullptr ;
    prod12 = nullptr ;
    prodTotal = nullptr ;

    return 0 ;
}
