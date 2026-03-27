#include <iostream>
using namespace std;

const int N = 4;//INIZIALICAMOS N = 4 YA QUE EL PROBLEMA NO ESPECIFICASI DEBEMOS PEDIRCELO AL USUARIO Y UILIZAREMOS LA MATRIZ DEL EJERCICIO

//PARA ESTRCTAMENTE DOMINANTE
bool esFilaDominanteEstricta(int (*M)[N], int f){
    bool mayor = false;
    for(int j = 0; j < N; j++){  //columnas
        for(int i = 0; i < N; i++){ //filas
            if(i == f) continue;
            if(*(*(M+f)+j) < *(*(M+i)+j)){ //condicion 1
                return false;
            }
            if(*(*(M+f)+j) > *(*(M+i)+j)){ //condicion 2
                mayor = true;
            }
        }
    }
    return mayor ;
}


//PARA FUERTEMENTE DOMINANTE
bool esFilaFuertementeDominante(int (*M)[N], int f){

    //COMPROBAR QUE SEA UNA FILA ESTRICTA
    if(!esFilaDominanteEstricta(M, f)){
        return false ;
    }

    int suma = 0 ;

    //SUMAMOS FILA
    for(int j = 0 ; j < N ; j++){
        suma += *(*(M+f)+j) ;
    }

    //COMPARAMOS
    for(int i = 0 ; i < N ; i++){

        if(i == f) continue ;

        int sumatemp = 0 ;

        for(int j = 0; j < N; j++){
            sumatemp += *(*(M+i)+j) ;
        }

        // debe ser estrictamente mayor que todas
        if(suma <= sumatemp){
            return false ;
        }
    }

    return true ;
}

int main(){
//INIZIALIZAMOS UNA MATRIZ N X N (Esto ya que el problema no especifica si debemos pedirselo al usuario)
    int M[N][N] = {
        {2,3,1,4},
        {1,2,3,2},
        {5,6,7,8},
        {0,1,2,1}
    };

    int (*MPtr)[N] = M ; //INIZIALICAMOS EL PUNTERO

    bool dominanteEstricta[N] ;
    bool fuertementeDominante[N] ;

    //EVALUAMOS PARA CADA FILA
    for(int f = 0 ; f < N ; f++){
        dominanteEstricta[f] = esFilaDominanteEstricta(MPtr, f) ;
        fuertementeDominante[f] = esFilaFuertementeDominante(MPtr, f) ;
    }

    //RESULTADOS
    cout << "Fila\tDominante Estricta\tFuertemente Dominante\n";
    cout << " ------------------------------------------------" << endl ;

    for(int f = 0 ; f < N ; f++){
        cout << f << "\t\t\t\t";

        if(dominanteEstricta[f]){
            cout << "SI\t\t\t\t\t\t" ;
        }
        else{
            cout << "NO\t\t\t\t\t\t" ;
        }

        if(fuertementeDominante[f]){ 
            cout << "SI" ;
        }
        else{
            cout << "NO" ;
        }

        cout << endl ;
    }

    return 0 ;
}
