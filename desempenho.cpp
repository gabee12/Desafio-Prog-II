#include "desempenho.h"
#include "buscas.h"
#include "ordenacao.cpp"

#include <chrono>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <ostream>

using Clock = std::chrono::steady_clock;
using namespace std;

// Gerador simples com semente fixa, garante o mesmo conjunto de dados para os dois sorts, permitindo assim a comparação justa
uint32_t proximoAleatorio(uint32_t& estado) {
	estado ^= estado << 13;
	estado ^= estado >> 17;
	estado ^= estado << 5;
	return estado;
}

void embaralhar(int indices[], int n, uint32_t semente) {
	uint32_t estado = semente;
	for (int i = n - 1; i > 0; i--) {
		int j = static_cast<int>(proximoAleatorio(estado) % static_cast<uint32_t>(i+1));
		int aux = indices[i];
		indices[i] = indices[j];
		indices[j] = aux;
	}
}

bool verificarOrdem(const Pessoa registros[], const Ordem& ordem, int n) {
	for (int i = 0; i < n; i++) {
		if (registros[ordem.ord[i]].id != i+1) return false;
	}

	return true;
}

void escreverLinha(ostream& csv, const char* categoria, const char* algoritmo, int n, const char* cenario, int repeticoes, const Metricas& metricas, double tempoUs, bool correto) {
	csv << categoria << ',' << algoritmo << ',' << n << "," << cenario << ',' << repeticoes << ',' << metricas.comparacoes << ',' << metricas.movimentos << ',' << fixed << setprecision(3) << tempoUs << "," << (correto ? "OK" : "FALHA") << "\n";
}

void imprimirLinha(ostream& saida, const char* categoria, const char* algoritmo, int n, const char* cenario, int repeticoes, const Metricas& metricas, double tempoUs, bool correto) {
	saida << left << setw(11) << categoria << setw(12) << algoritmo << right << setw(7) << n << " " << left << setw(10) << cenario << right << setw(6) << repeticoes << setw(15) << metricas.comparacoes << setw(15) << metricas.movimentos << setw(14) << fixed << setprecision(3) << tempoUs << "   " << (correto ? "OK" : "FALHA") << "\n"; 
}

using FuncaoBusca = int (*)(const Pessoa[], int, int, Metricas *);

bool testarBusca(ostream& saida, ostream& csv, const Pessoa registros[], int n, const char* algoritmo, FuncaoBusca busca, const char* cenario, int id, int esperado) {
	constexpr int repeticoes = 1000;
	Metricas metricas;
	long long somaIndices = 0;

	auto inicio = Clock::now();

	for (int r = 0; r < repeticoes; r++) {
		somaIndices += busca(registros, n, id, &metricas);
	}

	auto fim = Clock::now();
	double tempoUs = chrono::duration<double, micro>(fim - inicio).count();
	bool correto = somaIndices == static_cast<long long>(repeticoes)*esperado;

	imprimirLinha(saida, "Busca", algoritmo, n, cenario, repeticoes, metricas, tempoUs, correto);
	escreverLinha(csv, "Busca", algoritmo, n, cenario, repeticoes, metricas, tempoUs, correto);

	return correto;
}

bool testarOrdenacao(ostream& saida, ostream& csv, const Pessoa registros[], Ordem& ordem, const int inicial[], int n, bool usarMerge) {
	for (int i = 0; i < n; i++) {
		ordem.ord[i] = inicial[i];
	}

	Metricas metricas;
	
	int *auxiliar = usarMerge ? new int[n] : nullptr;

	auto inicio = Clock::now();
	if (usarMerge) {
		merge_sort(registros, ordem.ord, auxiliar, 0, n - 1, &Pessoa::id, &metricas);
	} else {
		insertion_sort(registros, ordem, n, &Pessoa::id, &metricas);
	}
	auto fim = Clock::now();
	delete[] auxiliar;

	bool correto = verificarOrdem(registros, ordem, n);

	double tempoUs = chrono::duration<double, micro>(fim - inicio).count();
	const char *nome = usarMerge ? "MergeSort" : "InsertionSort";

	imprimirLinha(saida, "Ordenacao", nome, n, "Aleatorio", 1, metricas, tempoUs, correto);
	escreverLinha(csv, "Ordenacao", nome, n, "Aleatorio", 1, metricas, tempoUs, correto);

	return correto;
}

bool gerarRelatorio(ostream& saida, const char *caminhoCSV) {
	ofstream csv(caminhoCSV);
	
	if (!csv) {
		saida << "Erro: Nao foi possivel abrir '" << caminhoCSV << "'.\n";
		return false;
	}

	csv << "categoria,algoritmo,n,cenario,repeticoes,comparacoes,movimentos,tempo_total_us,resultado\n";
	saida << "\n=== RELATORIO DE DESEMPENHO ===\n" << "Dados sinteticos; ordenacao de INDICES por ID, entrada embaralhada (semente fixa).\n"
	<< "Tempo em microsegundos, sem preparo, E/S ou validacao.\n" << "Buscas executadas 1000 vezes cada; Comparacoes contadas no lote, divida por 1000 para uma aproximacao de 1 iteracao\n"
	<< "Movimentos contam escritas no vetor de indices apenas.\n\n" << left << setw(11) << "Categoria" << setw(12) << "Algoritmo" << right << setw(7) << "N"
	<< ' ' << left << setw(10) << "Cenario" << right << setw(6) << "Reps" << setw(15) << "Comparacoes" << setw(15) << "Movimentos" << setw(14) << "Tempo (us)" << "   Status\n";
	
	constexpr int tamanhos[] = {1000, 5000, 10000, 50000};
	bool tudoCorreto = true;

	for (int n : tamanhos) {
		saida << "Iniciando N=" << n << "\n";
		saida.flush();
		Pessoa* registros = new Pessoa[n]{};
		int *indicesIniciais = new int[n];
		Ordem ordem(n);

		for (int i = 0; i < n; i++) {
			registros[i].id = i +1;
			indicesIniciais[i] = i;
		}

		embaralhar(indicesIniciais, n, 0x86221Du ^ static_cast<uint32_t>(n));

		tudoCorreto = testarOrdenacao(saida, csv, registros, ordem, indicesIniciais, n, true) && tudoCorreto;
		tudoCorreto = testarOrdenacao(saida, csv, registros, ordem, indicesIniciais, n, false) && tudoCorreto;

		const struct {
			const char* nome;
			int id;
			int indiceEsperado;
		} casos[] = {
			{"primeiro", 1, 0},
			{"ultimo", n, n - 1},
			{"ausente", n+1, -1}
		};

		for (const auto& caso : casos) {
			tudoCorreto = testarBusca(saida, csv, registros, n, "Sequencial", buscaSequencialPessoa, caso.nome, caso.id, caso.indiceEsperado) && tudoCorreto;
			tudoCorreto = testarBusca(saida, csv, registros, n, "Binaria", buscaBinariaPessoa, caso.nome, caso.id, caso.indiceEsperado) && tudoCorreto;
		}

		delete[] indicesIniciais;
		delete[] registros;
	}

	saida << "\nCSV salvo em '" << caminhoCSV << "'\n" << "Resultado geral: " << (tudoCorreto ? "OK" : "FALHA") << "\n";

	if (!csv) {
		saida << "Falha na escrita do CSV\n";
		return false;
	}

	return tudoCorreto;
}
