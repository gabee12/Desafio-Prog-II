#include "structs.h";
#include "ordenacao.h"
#include <cstring>
#include <type_traits>

using namespace std;

template <typename T, typename M>
bool menorAtributo(const T& a, const T& b, M T::* atributo) {
	if constexpr (is_array_v<M> && is_same_v<remove_extent_t<M>, char>) { // Essa linha verifica se o atributo é do tipo char[];
		return strcmp(a.*atributo, b.*atributo) < 0;
	} else {
		return a.*atributo < b.*atributo;
	}
}

template <typename T, typename M>
void merge(const T *vector, int indices[], int auxiliar[], int init, int mid, int end, M T::*atributo){
    int i = init, j = mid+1, k = inicio;

    while (i <= mid && j <= end){
        if(menorAtributo(vector[indices[i]], vector[indices[j]], atributo)) {
            auxiliar[k++] = indices[j++];
        }else{
            auxiliar[k++] = vector[i++];
        }
    }

    while(i <= mid){
        auxiliar[k++] = vector[i++];
    }

    while(j <= end){
        auxiliar[k++] = vector[j++];
    }

    for(int i = inicio; i <= fim; i++){
        indices[i] = auxiliar[i]; 
    }
}

template <typename T, typename M>
void merge_sort(const T *vector, int indices[], int auxiliar[], int init, int end, M T::*atributo) {
    if(init >= end ) {
		return;
	}

	int mid = init + (end - init) / 2;

    merge_sort(vector, indices, auxiliar, init, mid, atributo);
    merge_sort(vector, indices, auxiliar, mid+1, end, atributo);

    merge(vector, indices, auxiliar, init, mid, end, atributo);
}

template <typename T, typename M>
void insertion_sort(const T* vetor, Ordem& ordem, int n, M T::* atributo) {
    for (int i = 1; i < n; i++) {
		int key = ordem.ord[i];
        
		int j = i - 1;

		while (j >= 0 && menorAtributo(vetor[key], vetor[ordem.ord[j]], atributo)) {
			ordem.ord[j+1] = ordem.ord[j];
			j--;
		}

		ordem.ord[j+1] = key;
    }
}