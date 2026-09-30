#include "ordenacao.h"


/*
PRECISA DE UM CONSTRUTOR PRA CADA STRUCT QUE VAI USAR POIS NEW T USA 

*/

template <typename T, typename M>
void merge(T *vector, int init, int mid, int end, M T::*atributo){
    int i = init, j = mid+1, k = 0;

    T* vecAux = new T[end-init + 1]; 

    while (i<=mid && j<=end){
        if(vector[i].*atributo <= vector[j].*atributo){
            vecAux[k] = vector[i];
            k++;
            i++; 
        }else{
            vecAux[k] = vector[j];
            k++;
            j++; 
        }
    }
    while(i<=mid){
        vecAux[k] = vector[i];
        k++;
        i++; 
    }
    while(j<=end){
        vecAux[k] = vector[j];
        k++;
        j++; 
    }

    for(int i = 0; i < end-init + 1; i++){
        vector[init+i] = vecAux[i];
    }

    delete[] vecAux; // libera antes de sair da função
}

template <typename T, typename M>
void merge_sort(T *vector, int init, int end, M T::*atributo){
    if( init < end ){

        int mid = init + (end-init)/2;

        merge_sort(vector,init,mid, atributo);
        merge_sort(vector,mid+1,end, atributo);

        merge(vector,init,mid,end, atributo);
    }
}