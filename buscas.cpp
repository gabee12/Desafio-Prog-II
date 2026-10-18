#include <iostream>
#include "buscas.h"

using namespace std;

// Busca pessoa pelo id, comparando um por um 
int buscaSequencialPessoa(const Pessoa pessoas[], int quantidade, int id)
{
    for (int i = 0; i < quantidade; i++)
    {
        if (pessoas[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

// Busca pessoa pelo id dividindo o vetor ao meio a cada passo
int buscaBinariaPessoa(const Pessoa pessoas[], int quantidade, int id)
{
    int inicio = 0;
    int fim = quantidade - 1;

    while (inicio <= fim)
    {
        int meio = inicio + (fim - inicio) / 2;

        if (pessoas[meio].id == id)
        {
            return meio;
        }

        if (pessoas[meio].id < id)
        {
            inicio = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }

    return -1;
}

// Busca ocorrencia pelo id comparando um por um
int buscaSequencialOcorrencia(const Ocorrencia ocorrencias[], int quantidade, int id)
{
    for (int i = 0; i < quantidade; i++)
    {
        if (ocorrencias[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

// Busca ocorrencia pelo id dividindo o vetor ao meio a cada passo
int buscaBinariaOcorrencia(const Ocorrencia ocorrencias[], int quantidade, int id)
{
    int inicio = 0;
    int fim = quantidade - 1;

    while (inicio <= fim)
    {
        int meio = inicio + (fim - inicio) / 2;

        if (ocorrencias[meio].id == id)
        {
            return meio;
        }

        if (ocorrencias[meio].id < id)
        {
            inicio = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }

    return -1;
}

// Percorre o vetor de evidencias e imprime as que pertencem a ocorrencia informada.
void listarEvidencias(const Evidencia evidencias[], int quantidade, int idOcorrencia)
{
    bool encontrou = false;

    for (int i = 0; i < quantidade; i++)
    {
        if (evidencias[i].idOcorrencia == idOcorrencia)
        {
            cout << "ID da evidencia: " << evidencias[i].id << endl;
            cout << "Descricao: " << evidencias[i].descricao << endl;
            cout << "Relevancia: " << evidencias[i].relevancia << endl;
            cout << endl;

            encontrou = true;
        }
    }

    if (!encontrou)
    {
        cout << "Nenhuma evidencia encontrada para essa ocorrencia." << endl;
    }
}