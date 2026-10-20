#include "recursividade.h"
#include <iostream>
#include "structs.h"

using namespace std;

// Caso Base: Sem filhos, devolve a relevancia do nó (evidencia) atual
// Caso Recursivo: Soma as relevancias das subarvores filhas
int somarSubarvore(const Evidencia evidencias[], int indice, const int primeiroFilho[], const int proximoIrmao[]) {
	int soma = evidencias[indice].relevancia;
	for (int filho = primeiroFilho[indice]; filho != -1; filho = proximoIrmao[filho]) {
		soma += somarSubarvore(evidencias, filho, primeiroFilho, proximoIrmao);
	}
	return soma;
}

// Caso Base: Sem filhos. A melhor cadeia é o próprio nó
// Caso Recursivo: Escolhe a melhor cadeia dentre as dos seus filhos e guarda o filho escolhido para permitir a reconstrução da cadeia
int melhorCadeiaSubarvore(const Evidencia evidencias[], int indice, const int primeiroFilho[], const int proximoIrmao[], int melhorProximo[]) {
	int maiorFilho = 0;
	int filhoEscolhido = -1;

	for (int filho = primeiroFilho[indice]; filho != -1; filho = proximoIrmao[filho]) {
		int valor = melhorCadeiaSubarvore(evidencias, filho, primeiroFilho, proximoIrmao, melhorProximo);
		if (valor > maiorFilho || (valor == maiorFilho && (filhoEscolhido == -1 || evidencias[filho].id < evidencias[filhoEscolhido].id))) {
			maiorFilho = valor;
			filhoEscolhido = filho;
		}
	}

	melhorProximo[indice] = filhoEscolhido;
	return evidencias[indice].relevancia + maiorFilho;
} 

void analisarOcorrencia(const Evidencia evidencias[], int totalEvidencias, int idOcorrencia) {
	if (idOcorrencia < 1 || totalEvidencias <= 0) {
		cout << "Nenhuma evidencia encontrada para esta ocorrencia!\n";
		return;
	}

	// Listas de adjacencia baseadas nos indices do vetor. -1 = sem filhos/irmaos
	int *primeiroFilho = new int[totalEvidencias];
	int *proximoIrmao = new int[totalEvidencias];
	int *melhorProximo = new int[totalEvidencias];

	for (int i = 0; i < totalEvidencias; i++) {
		primeiroFilho[i] = -1;
		proximoIrmao[i] = -1;
		melhorProximo[i] = -1;
	}

	int quantidade = 0;
	bool relacaoInvalida = false;

	// Cada evidencia que possui pai é inserida na lista de filhos do pai
	// Como os ID são registrados de forma sequencial, o registro com ID k se encontra no indice k - 1;
	for (int i = 0; i < totalEvidencias; i++) {
		if (evidencias[i].idOcorrencia != idOcorrencia) { // Analisar apenas evidencias relacionadas a ocorrencia desejada
			continue;
		}

		quantidade++;

		int idPai = evidencias[i].idEvidenciaPai;
		if (idPai == 0) { // Evidencia é nó raiz, não possui pai
			continue;
		}

		int pai = idPai - 1;
		if (pai < 0 || pai >= i || evidencias[pai].id != idPai || evidencias[pai].idOcorrencia != idOcorrencia) {
			relacaoInvalida = true;
			break;
		}

		proximoIrmao[i] = primeiroFilho[pai];
		primeiroFilho[pai] = i;
	}

	if (relacaoInvalida) {
		cout << "ERRO: Relacionamento inconsistente detectado\n";
		delete[] primeiroFilho;
		delete[] proximoIrmao;
		delete[] melhorProximo;
		return;
	}

	if (quantidade == 0) {
		cout << "Nenhuma evidencia relacionada encontrada para essa ocorrencia\n";
		delete[] primeiroFilho;
		delete[] proximoIrmao;
		delete[] melhorProximo;
		return;
	}

	int totalRelevancia = 0;
	int maiorCadeia = -1;
	int raizMelhorCadeia = -1;

	// Uma ocorrencia pode ter varias raízes, por isso pode ser necessário percorrer mais de uma árvore
	for (int i = 0; i < totalEvidencias; i++) {
		if (evidencias[i].idOcorrencia != idOcorrencia || evidencias[i].idEvidenciaPai != 0) { // Tratar apenas evidencias raíz relacionadas à ocorrencia
			continue;
		}

		totalRelevancia += somarSubarvore(evidencias, i, primeiroFilho, proximoIrmao);
		int candidato = melhorCadeiaSubarvore(evidencias, i, primeiroFilho, proximoIrmao, melhorProximo);

		if (candidato > maiorCadeia || (candidato == maiorCadeia && (raizMelhorCadeia == -1 || evidencias[i].id < evidencias[raizMelhorCadeia].id))) {
			maiorCadeia = candidato;
			raizMelhorCadeia = i;
		}
	}

	cout << "---ANALISE RECURSIVA DA OCORRENCIA---\n";
	cout << "Quantidade de evidencias relacionadas: " << quantidade << "\n";
	cout << "Relevancia total: " << totalRelevancia << "\n";
	cout << "Maior relevancia em uma cadeia: " << maiorCadeia << "\n";
	cout << "Cadeia mais relevante (IDs): ";

	for (int indice = raizMelhorCadeia; indice != -1; indice = melhorProximo[indice]) {
		cout << evidencias[indice].id;
		if (melhorProximo[indice] != -1) {
			cout << " -> ";
		}
	}
	cout << "\n";

	delete[] melhorProximo;
	delete[] proximoIrmao;
	delete[] primeiroFilho;
}