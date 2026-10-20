#include "../structs.h"
#include "../buscas.h"
#include "../ordenacao.cpp"

#include <cassert>
#include <iostream>

static void testSearches() {
	Pessoa p[4]{};
	for (int i = 0; i < 4; i++) {
		p[i].id = i + 1;
	}

	Metricas s;

	assert(buscaSequencialPessoa(p, 4, 4, &s) == 3);
	assert(s.comparacoes == 4 && s.movimentos == 0);
	
	Metricas b;
	assert(buscaBinariaPessoa(p, 4, 4, &b) == 3);
	assert(b.comparacoes > 0 && b.comparacoes < s.comparacoes + 5);
	assert(buscaSequencialPessoa(p, 4, 5) == -1);
	assert(buscaBinariaPessoa(p, 4, 5) == -1);
	assert(buscaBinariaPessoa(p, 0, 1) == -1);
}

static void testSorters() {
	Pessoa p[5]{};

	for (int i = 0; i < 5; i++) {
		p[i].id = i + 1;
	}

	int original[5] = {4, 3, 2, 1, 0};
	Ordem insertion(5);

	for (int i = 0; i < 5; i++) {
		insertion.ord[i] = original[i];
	}

	Metricas mi;
	insertion_sort(p, insertion, 5, &Pessoa::id, &mi);
	assert(mi.comparacoes == 10);
	assert(mi.movimentos == 14);

	for (int i = 0; i < 5; i++) {
		assert(insertion.ord[i] == i);
	}

	int aux[5]{};

	Metricas mm;

	merge_sort(p, original, aux, 0, 4, &Pessoa::id, &mm);
	assert(mm.comparacoes > 0);
	assert(mm.movimentos > 0);

	for (int i = 0; i< 5; i++) {
		assert(original[i] == i);
		assert(p[i].id == i+1);
	}
}

static void testStabilityAndStrings() {
	Pessoa p[5]{};

	const int idades[5] = {30, 20, 20, 10, 20};

	for (int i = 0; i < 5; i++) {
		p[i].idade = idades[i];
	}

	int original[5] = {0, 2, 4, 1, 3};
	const int esperado[5] = {3, 2, 4, 1, 0};

	Ordem insertion(5);

	for (int i = 0; i < 5; i++) {
		insertion.ord[i] = original[i];
	}

	insertion_sort(p, insertion, 5, &Pessoa::idade);

	int aux[5]{};

	merge_sort(p, original, aux, 0, 4, &Pessoa::idade);

	for (int i = 0; i < 5; i++) {
		assert(insertion.ord[i] == esperado[i]);
		assert(original[i] == esperado[i]);
	}

	Pessoa nomes[3]{};

	nomes[0].nome[0] = 'Z'; nomes[0].nome[1] = '\0';
	nomes[1].nome[0] = 'A'; nomes[1].nome[1] = '\0';
	nomes[2].nome[0] = 'B'; nomes[2].nome[1] = '\0';

	int indices[3] = {0, 1, 2};
	int auxiliar[3]{};

	merge_sort(nomes, indices, auxiliar, 0, 2, &Pessoa::nome);
	assert(indices[0] == 1 && indices[1] == 2 && indices[2] == 0);
}

int main() {
	testSearches();
	testSorters();
	testStabilityAndStrings();
	cout << "OK: Teste das metricas, buscas e sorts OK!\n";
}