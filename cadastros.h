#pragma once
#include "structs.h"

using namespace std;

void cadastrarPessoa(Pessoa pessoas[], int capacidade, int& totalPessoas);
void cadastrarOcorrencia(Ocorrencia ocorrencias[], int capacidade, int& totalOcorrencias);
void cadastrarEvidencia(Evidencia evidencias[], int capacidade, int& totalEvidencias, const int totalOcorrencias);