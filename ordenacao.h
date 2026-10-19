#pragma once
/*
T é o tipo da struct ou campo a ser ordenado
para usar o M T::* atributo
chama função &struct::nome_do_campo
*/

template <typename T, typename M>
void insertion_sort(const T* vetor, Ordem& ordem, int n, M T::* atributo);

template <typename T, typename M>
void merge_sort(const T *vector, int indices[], int auxiliar[], int init, int end, M T::*atributo);