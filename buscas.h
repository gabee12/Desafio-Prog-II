#pragma once
#include "structs.h";

int buscaSequencialPessoa(const Pessoa pessoas[], int quantidade, int id);

int buscaBinariaPessoa(const Pessoa pessoas[], int quantidade, int id);

int buscaSequencialOcorrencia(const Ocorrencia ocorrencias[], int quantidade, int id);

int buscaBinariaOcorrencia(const Ocorrencia ocorrencias[], int quantidade, int id);

void listarEvidencias(const Evidencia evidencias[], int quantidade, int idOcorrencia);