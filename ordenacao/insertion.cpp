#include "ordenacao.h"

/* A ideia é eu mandar a struct e qual atributo vai ser usado para comparação e troca
o argumento atributo vai ter o molde &struct::campo

*/
template <typename T, typename M>
void insertion_sort(T* vetor, int n, M T::* atributo) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && vetor[j].*atributo < vetor[j-1].*atributo; j--) {
            
            T aux = vetor[j-1];
            vetor[j-1] = vetor[j];
            vetor[j] = aux;
        }
    }
}