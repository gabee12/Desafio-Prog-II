#include "structs.h"
#include "metricas.h"
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
void merge(const T *vector, int indices[], int auxiliar[], int init, int mid, int end, M T::*atributo, Metricas* metricas = nullptr) {
    int i = init, j = mid+1, k = init;

    while (i <= mid && j <= end){
		if (metricas) ++metricas->comparacoes;
        if (menorAtributo(vector[indices[j]], vector[indices[i]], atributo)) {
            auxiliar[k++] = indices[j++];
        } else{
            auxiliar[k++] = indices[i++];
        }
    }

    while(i <= mid){
        auxiliar[k++] = indices[i++];
    }

    while(j <= end){
        auxiliar[k++] = indices[j++];
    }

	if (metricas) metricas->movimentos += static_cast<uint64_t>(end - init + 1);

    for(int i = init; i <= end; i++){
        indices[i] = auxiliar[i];
		if (metricas) ++metricas->movimentos;
    }
}

template <typename T, typename M>
void merge_sort(const T *vector, int indices[], int auxiliar[], int init, int end, M T::*atributo, Metricas *metricas = nullptr) {
    if(init >= end ) {
		return;
	}

	int mid = init + (end - init) / 2;

    merge_sort(vector, indices, auxiliar, init, mid, atributo, metricas);
    merge_sort(vector, indices, auxiliar, mid+1, end, atributo, metricas);

    merge(vector, indices, auxiliar, init, mid, end, atributo, metricas);
}

template <typename T, typename M>
void insertion_sort(const T* vetor, Ordem& ordem, int n, M T::* atributo, Metricas *metricas = nullptr) {
    for (int i = 1; i < n; i++) {
		int key = ordem.ord[i];
        
		int j = i - 1;

		while (j >= 0) {
			if (metricas) ++metricas->comparacoes;
			if (!menorAtributo(vetor[key], vetor[ordem.ord[j]], atributo)) break;
			ordem.ord[j+1] = ordem.ord[j];
			if (metricas) ++metricas->movimentos;
			j--;
		}
		ordem.ord[j+1] = key;
		if (metricas) ++metricas->movimentos;
    }
}