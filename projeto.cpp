#include <iostream>
#include <string> 
using namespace std;

struct Pessoas{
    char nome[50]; 
    char vulgo[50];
    char sexo[10];
    int id;
    int idade;
    char cpf[12];
    char telefone[15];
    char telefone_emergencia[15];
    char Tipo_de_evolvimento[30];
    char cor_ou_raca[50];
    char profissao[100];
    char estado_civil[50];
    char endereco[50];
};

struct Ocorrencias{ 
    int numero_de_suspeitos;
    int id;
    char cpf[12];
    char cidade[50];
    char local_ocorrencia[50];
    char horario[6];
    int ano;
    int gravidade;
    char tipo_crime[1000];
    char tipo_da_vitima[30];
};

struct Evidencia{
    char testemunhas_oculares[50];
    char tipo_de_evidencia[100];/*digitais, documentais, testemunhas, biologicas, fisicas/materiais*/
    int idOcorrencia;
    int relevancia;
    int id;
};

int main(){
    Pessoas CapacidadePessoas[10000];
    Ocorrencias CapacidadeOcorrencias[5000];
    Evidencia CapacidadeEvidencia[20000];
    char nome[50];
    int TotalPessoas = 0;
    int TotalOcorrencias = 0;
    int TotalEvidencia = 0;

    int escolha; 

        cout << "================================" << endl;
        cout <<    "  SISTEMA ANALISTA CRIMINAL" << endl ;
        cout << "================================" << endl;
        cout << "Para dar inicio a busca/cadastro digite seu nome : " << endl;
        cin.getline(nome, 50);
    do {
        cout << "Selecione o servico desejado" << endl;
        cout << "1- Cadastrar Individuo" << endl;
        cout << "2- Cadastrar Ocorrencia" << endl;
        cout << "3- Cadastrar Evidencia" << endl;
        cout << endl;
        cout << "4- Buscar individuo" << endl;
        cout << "5- Buscar Ocorrencia" << endl;
        cout << endl;
        cout << "6- Ordenar Individuos" << endl;
        cout << "7- Ordenar Ocorrencias" << endl;
        cout << endl;
        cout << "8- Acompanhar julgamento" << endl;
        cout << endl;
        cout << "9- Exit";
        cin >> escolha;
    } while (escolha !=9); 
    
    return 0;
} 