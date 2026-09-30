#ifndef ordenacao_H

#define ordenacao_H


/*
T é o tipo da struct ou campo a ser ordenado
para usar o M T::* atributo
chama função &struct::nome_do_campo
*/


template <typename T, typename M>
void insertion_sort(T* vetor, int n, M T::* atributo); 

template <typename T, typename M>
void merge_sort(T *vector, int init, int end, M T::*atributo);


#endif