#include <iostream>
#include <string> 
#include "modularização/structs.h";
#include "modularização/cadastros.h";
#include "buscas.h";
#include "ordenacao/ordenacao.h";

using namespace std;

int main() {
	static int capacidadePessoas = 10000;
	static int capacidadeOcorrencias = 5000;
	static int capacidadeEvidencias = 20000; 
    
	Pessoa *RegistroPessoas = new Pessoa[capacidadePessoas];
	Ocorrencia *RegistroOcorrencias = new Ocorrencia[capacidadeOcorrencias];
	Evidencia *RegistroEvidencias = new Evidencia[capacidadeEvidencias];

    int TotalPessoas = 0;
    int TotalOcorrencias = 0;
    int TotalEvidencia = 0;
    int escolha;

    cout << "================================" << endl;
    cout << "   SISTEMA ANALISTA CRIMINAL    " << endl;
    cout << "================================" << endl;

    do {
        cout << "\nSelecione o servico desejado" << endl;
        cout << "1- Cadastrar Individuo" << endl;
        cout << "2- Cadastrar Ocorrencia" << endl;
        cout << "3- Cadastrar Evidencia" << endl;
        cout << "4- Buscar individuo" << endl;
        cout << "5- Buscar Ocorrencia" << endl;
        cout << "6- Ordenar Individuos" << endl;
        cout << "7- Ordenar Ocorrencias" << endl;
        cout << "8- Exit" << endl;
        cout << "escolha: ";

        cin >> escolha;
        cin.ignore();

        switch (escolha) {
            case 1:
                cadastrarPessoa(RegistroPessoas, capacidadePessoas, TotalPessoas);
                break;

            case 2:
                cadastrarOcorrencia(RegistroOcorrencias, capacidadeOcorrencias, TotalOcorrencias);
                break;

            case 3:
                cadastrarEvidencia(RegistroEvidencias, capacidadeEvidencias, TotalEvidencia, TotalOcorrencias);
                break;
            case 8:
                cout << "\nSaindo do sistema..." << endl;
                break;

            default:
                cout << "\nOpcao invalida!" << endl;
                break;
        } 

    } while (escolha != 8); 
    
    return 0;
}