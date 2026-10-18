#pragma once

/* struct Pessoas {
    char nome[50]; 
    char vulgo[50];
    char sexo[10];
    int id;
    int idade;
    char cpf[12];
    char telefone[15];
    char telefone_emergencia[15];
    char Tipo_de_envolvimento[30];
    char cor_ou_raca[50];
    char profissao[100];
    char estado_civil[50];
    char endereco[50];
};

struct Ocorrencias { 
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

struct Evidencia {
    char testemunhas_oculares[50];
    char descricao[100];
    int relevancia;
    int idOcorrencia; 
    int id;
}; */

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
	char descricao[100];
};