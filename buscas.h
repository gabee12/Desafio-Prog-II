#pragma once
#include "structs.h"
#include "metricas.h"

int buscaSequencialPessoa(const Pessoa pessoas[], int quantidade, int id, Metricas* metricas = nullptr);

int buscaBinariaPessoa(const Pessoa pessoas[], int quantidade, int id, Metricas* metricas = nullptr);

int buscaSequencialOcorrencia(const Ocorrencia ocorrencias[], int quantidade, int id, Metricas* metricas = nullptr);

int buscaBinariaOcorrencia(const Ocorrencia ocorrencias[], int quantidade, int id, Metricas* metricas = nullptr);

void listarEvidencias(const Evidencia evidencias[], int quantidade, int idOcorrencia);