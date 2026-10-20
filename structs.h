#pragma once
struct Pessoa {
	int id;
	int idade;
	char nome[100];
	char cidade[50];
};

struct Ocorrencia {
	int id;
	int gravidade;
	int ano;
	char tipo[50];
	char local[100];
};

struct Evidencia {
	int id;
	int idOcorrencia;
	int relevancia;
	int idEvidenciaPai; // Vamos modelar as evidencias relacionadas como uma árvore e atravessa-lá recursivamente
	char descricao[100];
};

struct Ordem {
	int *ord;
	int tamanho;

	Ordem(int tamanho) {
		this->tamanho = tamanho;
		this->ord = new int[tamanho];
		for (int i = 0; i < tamanho; i++) {
			this->ord[i] = i;
		}
	}

	~Ordem() {
		delete[] this->ord;
	}

	Ordem(const Ordem& outro) {
		this->tamanho = outro.tamanho;
		this->ord = new int[tamanho];
		for (int i = 0; i < tamanho; i++) {
			this->ord[i] = outro.ord[i];
		}
	}
};