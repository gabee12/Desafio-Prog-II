#include "cadastros.h"
#include <iostream>
#include <chrono>
#include <limits>

using namespace std;

void cadastrarPessoa(Pessoa pessoas[], int capacidade, int& totalPessoas) {
	if (totalPessoas < capacidade) {
		cout << "\n----CADASTRO DE INDIVIDUOS----" << endl;

		Pessoa nova{};
		nova.id = totalPessoas + 1;
		cout << "ID: " << nova.id << endl;

		cout << "Nome Completo: ";

		if (!cin.getline(nova.nome, sizeof(nova.nome))) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Nome invalido! Cadastro cancelado.\n";
			return;
		}

		cout << "Idade: ";
		
		while (!(cin >> nova.idade) || nova.idade < 0 || nova.idade > 120) {
			if (cin.eof()) {
				cout << "\nEntrada Encerrada. Cadastro Cancelado.\n";
				return;
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Idade invalida! A idade inserida deve estar entre 0 e 120. Digite novamente: ";
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Cidade: ";

		if (!cin.getline(nova.cidade, sizeof(nova.cidade))) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Cidade invalida! Cadastro cancelado.\n";
			return;
		}

		pessoas[totalPessoas] = nova;

		totalPessoas++;

		cout << "\nIndividuo cadastrado com sucesso!" << endl;
		cout << "Total de pessoas cadastradas: " << totalPessoas << endl;
	} else {
		cout << "\nCapacidade maxima (" << capacidade << ") de pessoas atingida!" << endl;
	}
}

void cadastrarOcorrencia(Ocorrencia ocorrencias[], int capacidade, int& totalOcorrencias) {
	if (totalOcorrencias < capacidade) {
		cout << "\n----CADASTRO DE OCORRENCIAS----" << endl;

		Ocorrencia nova {};
		nova.id = totalOcorrencias + 1;
		cout << "ID: " << nova.id << endl;

		auto now = chrono::system_clock::now();
		chrono::year_month_day ymd{chrono::floor<chrono::days>(now)};

		cout << "Insira o ano: ";
		while (!(cin >> nova.ano) || nova.ano < 1819 || nova.ano > static_cast<int>(ymd.year())) {
			if (cin.eof()) {
				cout << "\nEntrada Encerrada. Cadastro Cancelado.\n";
				return;
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Ano invalido! O ano inserido deve estar entre 1819 e " << static_cast<int>(ymd.year()) << ". Digite novamente: ";
		}

		cout << "Insira o nivel de gravidade (1=Baixo / 2=Médio / 3=Grave / 4=Crítico): ";

		while (!(cin >> nova.gravidade) || nova.gravidade <= 0 || nova.gravidade > 4) {
			if (cin.eof()) {
				cout << "\nEntrada Encerrada. Cadastro Cancelado.\n";
				return;
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Gravidade invalida! O numero inserido deve estar entre 1 e 4. Digite novamente: ";
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Tipo da ocorrencia: ";
		if (!cin.getline(nova.tipo, sizeof(nova.tipo))) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Tipo invalido! Cadastro cancelado.\n";
			return;
		}

		cout << "Local: ";
		if (!cin.getline(nova.local, sizeof(nova.local))) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Local invalido! Cadastro cancelado.\n";
			return;
		}

		ocorrencias[totalOcorrencias] = nova;

		totalOcorrencias++;

		cout << "\nOcorrencia cadastrada com sucesso!" << endl;
		cout << "Total de ocorrencias: " << totalOcorrencias << endl;
	} else {
		cout << "\nCapacidade maxima (" << capacidade << ") de ocorrencias atingida!" << endl;
	}
}

void cadastrarEvidencia(Evidencia evidencias[], int capacidade, int& totalEvidencias, const int totalOcorrencias) {
	if (totalEvidencias < capacidade) {
		int idProcurado;
		cout << "\n----CADASTRO DE EVIDENCIAS----" << endl;
		cout << "Insira o ID da Ocorrencia associada: ";
		if (!(cin >> idProcurado)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nErro: ID Inválido! Cadastro Cancelado\n";
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (idProcurado > totalOcorrencias || idProcurado < 1) {
			cout << "\nErro: Ocorrencia com ID " << idProcurado << " nao encontrada! Cadastro cancelado." << endl;
			return; 
		}

		cout << "Ocorrencia encontrada!" << endl;

		Evidencia nova{};

		nova.id = totalEvidencias + 1;
		nova.idOcorrencia = idProcurado;

		cout << "ID Evidencia: " << nova.id << endl;

		cout << "Insira a descricao da evidencia: ";
		
		if (!cin.getline(nova.descricao, sizeof(nova.descricao))) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Descricao invalida! Cadastro cancelado.\n";
			return;
		}

		cout << "Insira a relevancia da evidencia (1 a 5). Numeros maiores indicam mais relevancia: ";
		
		while (!(cin >> nova.relevancia) || nova.relevancia < 1 || nova.relevancia > 5) {
			if (cin.eof()) {
				cout << "\nEntrada Encerrada. Cadastro Cancelado.\n";
				return;
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Entrada invalida! Insira um numero entre 1 e 5: ";
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		evidencias[totalEvidencias] = nova;
		
		totalEvidencias++;

		cout << "\nEvidencia cadastrada com sucesso!" << endl;
		cout << "Total de evidencias: " << totalEvidencias << endl; 
	} else {
		cout << "\nCapacidade maxima (" << capacidade << ") de evidencias atingida!" << endl;
	}
}