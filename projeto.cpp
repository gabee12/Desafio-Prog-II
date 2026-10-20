#include <iostream>
#include <string> 
#include <climits>
#include "structs.h"
#include "cadastros.h"
#include "buscas.h"
#include "ordenacao.cpp"

using namespace std;

int main() {
	// Para alterar o número máximo de registros sem necessitar alterações estruturais
	static int capacidadePessoas = 10000;
	static int capacidadeOcorrencias = 5000;
	static int capacidadeEvidencias = 20000; 
    
	// Criar vetores dinâmicos para os registros
	Pessoa *RegistroPessoas = new Pessoa[capacidadePessoas];
	Ocorrencia *RegistroOcorrencias = new Ocorrencia[capacidadeOcorrencias];
	Evidencia *RegistroEvidencias = new Evidencia[capacidadeEvidencias];

	// Estruturas que guardam a ordem dos registros, facilita a busca pois os registros acima sempre ficam ordenados por ID
	Ordem OrdenacaoPessoas(capacidadePessoas);
	Ordem OrdenacaoOcorrencias(capacidadeOcorrencias);
	Ordem OrdenacaoEvidencias(capacidadeEvidencias);

	// Total de registros feitos;
    int TotalPessoas = 0;
    int TotalOcorrencias = 0;
    int TotalEvidencia = 0;

	// Menu
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
		cout << "8- Analisar Evidencias de Ocorrencia" << endl;
        cout << "9- Listar Evidencias de Ocorrencia" << endl;
		cout << "10- Sair do programa" << endl;
        cout << "escolha: ";

        cin >> escolha;
       	cin >> ws; // Consome o espaço branco renanescente. Ajuda a evitar problemas com a alternancia de cin >> e cin.getline

        switch (escolha) {
            case 1:
				// Cadastro de pessoas movido para função
                cadastrarPessoa(RegistroPessoas, capacidadePessoas, TotalPessoas);
                break;

            case 2:
				// Cadastro de ocorrencias movido para função
                cadastrarOcorrencia(RegistroOcorrencias, capacidadeOcorrencias, TotalOcorrencias);
                break;

            case 3:
				// Cadastro de evidencias movido para função
                cadastrarEvidencia(RegistroEvidencias, capacidadeEvidencias, TotalEvidencia, TotalOcorrencias);
                break;
			case 4: {
				cout << "----BUSCA DE PESSOAS----\n";
				cout << "Insira o ID da pessoa procurada: ";
				int id, escolhaInterna;
				cin >> id;
				cout << "Escolha o tipo de busca:\n";
				cout << "1 - Sequencial\n";
				cout << "2 - Binária\n";
				cin >> escolhaInterna;
				cin >> ws;
				switch (escolhaInterna) {
					case 1: {
						int idx = buscaSequencialPessoa(RegistroPessoas, TotalPessoas, id);
						if (idx == -1) {
							cout << "ID não encontrado! Cancelando busca...\n";
							break;
						}
						cout << "Pessoa encontrada!\n";
						cout << "ID: " << RegistroPessoas[idx].id << "\n";
						cout << "Idade: " << RegistroPessoas[idx].idade << "\n";
						cout << "Nome: " << RegistroPessoas[idx].nome << "\n";
						cout << "Cidade: " << RegistroPessoas[idx].cidade << "\n";
						break;
					}
					case 2: {
						int idx = buscaBinariaPessoa(RegistroPessoas, TotalPessoas, id);
						if (idx == -1) {
							cout << "ID não encontrado! Cancelando busca...\n";
							break;
						}
						cout << "Pessoa encontrada!\n";
						cout << "ID: " << RegistroPessoas[idx].id << "\n";
						cout << "Idade: " << RegistroPessoas[idx].idade << "\n";
						cout << "Nome: " << RegistroPessoas[idx].nome << "\n";
						cout << "Cidade: " << RegistroPessoas[idx].cidade << "\n";
						break;
					}
					default:
						cout << "Entrada Inválida! Cancelando busca...\n";
						break;
				}
				break;
			}
			case 5: {
				cout << "----BUSCA DE OCORRENCIAS----\n";
				cout << "Insira o ID da ocorrencia procurada: ";
				int id, escolhaInterna;
				cin >> id;
				cout << "Escolha o tipo de busca:\n";
				cout << "1 - Sequencial\n";
				cout << "2 - Binária\n";
				cin >> escolhaInterna;
				cin >> ws;
				switch (escolhaInterna) {
					case 1: {
						int idx = buscaSequencialOcorrencia(RegistroOcorrencias, TotalOcorrencias, id);
						if (idx == -1) {
							cout << "ID não encontrado! Cancelando busca...\n";
							break;
						}
						cout << "Ocorrencia encontrada!\n";
						cout << "ID: " << RegistroOcorrencias[idx].id << "\n";
						cout << "Gravidade: " << RegistroOcorrencias[idx].gravidade << "\n";
						cout << "Ano: " << RegistroOcorrencias[idx].ano << "\n";
						cout << "Tipo: " << RegistroOcorrencias[idx].tipo << "\n";
						cout << "Local: " << RegistroOcorrencias[idx].local << "\n";
						break;
					}
					case 2: {
						int idx = buscaBinariaOcorrencia(RegistroOcorrencias, TotalOcorrencias, id);
						if (idx == -1) {
							cout << "ID não encontrado! Cancelando busca...\n";
							break;
						}
						cout << "Ocorrencia encontrada!\n";
						cout << "ID: " << RegistroOcorrencias[idx].id << "\n";
						cout << "Gravidade: " << RegistroOcorrencias[idx].gravidade << "\n";
						cout << "Ano: " << RegistroOcorrencias[idx].ano << "\n";
						cout << "Tipo: " << RegistroOcorrencias[idx].tipo << "\n";
						cout << "Local: " << RegistroOcorrencias[idx].local << "\n";
						break;
					}
					default:
						cout << "Entrada Inválida! Cancelando busca...\n";
						break;
				}
				break;
			}
			case 6: {
				cout << "---ORDENAR INDIVIDUOS---\n";
				cout << "Escolha o tipo de ordenacao:\n";
				cout << "1 - MergeSort\n";
				cout << "2 - InsertionSort\n";
				int escolhaOrd;
				cin >> escolhaOrd >> ws;
				cout << "Escolha por qual campo ordenar os individuos:\n";
				cout << "1 - ID\n";
				cout << "2 - Idade\n";
				cout << "3 - Nome\n";
				cout << "4 - Cidade\n";
				int escolhaInterna;
				cin >> escolhaInterna >> ws;
				switch (escolhaInterna) {
					case 1: {
						cout << "Ordenando por ID....\n";
						if (escolhaOrd == 1) {
							int* auxiliar = new int[TotalPessoas];
							merge_sort(RegistroPessoas, OrdenacaoPessoas.ord, auxiliar, 0, TotalPessoas - 1, &Pessoa::id);
							delete[] auxiliar;
						} else if (escolhaOrd == 2) {
							insertion_sort(RegistroPessoas, OrdenacaoPessoas, TotalPessoas, &Pessoa::id);
						} else {
							cout << "Escolha de ordenacao invalida! Cancelando...\n";
							break;
						}
						cout << "Pessoas ordenadas por ID.\n";
						break;
					}
					case 2: {
						cout << "Ordenando por Idade...\n";
						if (escolhaOrd == 1) {
							int* auxiliar = new int[TotalPessoas];
							merge_sort(RegistroPessoas, OrdenacaoPessoas.ord, auxiliar, 0, TotalPessoas - 1, &Pessoa::idade);
							delete[] auxiliar;
						} else if (escolhaOrd == 2) {
							insertion_sort(RegistroPessoas, OrdenacaoPessoas, TotalPessoas, &Pessoa::idade);
						} else {
							cout << "Escolha de ordenacao invalida! Cancelando...\n";
							break;
						}
						cout << "Pessoas ordenadas por Idade.\n";
						break;
					}
					case 3: {
						cout << "Ordenando por Nome....\n";
						if (escolhaOrd == 1) {
							int* auxiliar = new int[TotalPessoas];
							merge_sort(RegistroPessoas, OrdenacaoPessoas.ord, auxiliar, 0, TotalPessoas - 1, &Pessoa::nome);
							delete[] auxiliar;
						} else if (escolhaOrd == 2) {
							insertion_sort(RegistroPessoas, OrdenacaoPessoas, TotalPessoas, &Pessoa::nome);
						} else {
							cout << "Escolha de ordenacao invalida! Cancelando...\n";
							break;
						}
						cout << "Pessoas ordenadas por Nome.\n";
						break;
					}
					case 4: {
						cout << "Ordenando por Cidade....\n";
						if (escolhaOrd == 1) {
							int* auxiliar = new int[TotalPessoas];
							merge_sort(RegistroPessoas, OrdenacaoPessoas.ord, auxiliar, 0, TotalPessoas - 1, &Pessoa::cidade);
							delete[] auxiliar;
						} else if (escolhaOrd == 2) {
							insertion_sort(RegistroPessoas, OrdenacaoPessoas, TotalPessoas, &Pessoa::cidade);
						} else {
							cout << "Escolha de ordenacao invalida! Cancelando...\n";
							break;
						}
						cout << "Pessoas ordenadas por Cidade.\n";
						break;
					}
					default:
						cout << "Escolha de campo invalida! Cancelando...\n";
						break;
				}
				break;
			}
			case 7: {
				cout << "---ORDENAR OCORRENCIAS---\n";
				cout << "Escolha o tipo de ordenacao:\n";
				cout << "1 - MergeSort\n";
				cout << "2 - InsertionSort\n";
				int escolhaOrd;
				cin >> escolhaOrd >> ws;
				cout << "Escolha por qual campo ordenar os individuos:\n";
				cout << "1 - ID\n";
				cout << "2 - Gravidade\n";
				cout << "3 - Ano\n";
				cout << "4 - Tipo\n";
				cout << "5 - Local\n";
				int escolhaInterna;
				cin >> escolhaInterna >> ws;
				switch (escolhaInterna) {
					case 1: {
						cout << "Ordenando por ID....\n";
						if (escolhaOrd == 1) {
							int* auxiliar = new int[TotalOcorrencias];
							merge_sort(RegistroOcorrencias, OrdenacaoOcorrencias.ord, auxiliar, 0, TotalOcorrencias - 1, &Ocorrencia::id);
							delete[] auxiliar;
						} else if (escolhaOrd == 2) {
							insertion_sort(RegistroOcorrencias, OrdenacaoOcorrencias, TotalOcorrencias, &Ocorrencia::id);
						} else {
							cout << "Escolha de ordenacao invalida! Cancelando...\n";
							break;
						}
						cout << "Ocorrencias ordenadas por ID.\n";
						break;
					}
					case 2: {
						cout << "Ordenando por Gravidade...\n";
						if (escolhaOrd == 1) {
							int* auxiliar = new int[TotalOcorrencias];
							merge_sort(RegistroOcorrencias, OrdenacaoOcorrencias.ord, auxiliar, 0, TotalOcorrencias - 1, &Ocorrencia::gravidade);
							delete[] auxiliar;
						} else if (escolhaOrd == 2) {
							insertion_sort(RegistroOcorrencias, OrdenacaoOcorrencias, TotalOcorrencias, &Ocorrencia::gravidade);
						} else {
							cout << "Escolha de ordenacao invalida! Cancelando...\n";
							break;
						}
						cout << "Ocorrencias ordenadas por Gravidade.\n";
						break;
					}
					case 3: {
						cout << "Ordenando por Ano....\n";
						if (escolhaOrd == 1) {
							int* auxiliar = new int[TotalOcorrencias];
							merge_sort(RegistroOcorrencias, OrdenacaoOcorrencias.ord, auxiliar, 0, TotalOcorrencias - 1, &Ocorrencia::ano);
							delete[] auxiliar;
						} else if (escolhaOrd == 2) {
							insertion_sort(RegistroOcorrencias, OrdenacaoOcorrencias, TotalOcorrencias, &Ocorrencia::ano);
						} else {
							cout << "Escolha de ordenacao invalida! Cancelando...\n";
							break;
						}
						cout << "Ocorrencias ordenadas por Ano.\n";
						break;
					}
					case 4: {
						cout << "Ordenando por Tipo....\n";
						if (escolhaOrd == 1) {
							int* auxiliar = new int[TotalOcorrencias];
							merge_sort(RegistroOcorrencias, OrdenacaoOcorrencias.ord, auxiliar, 0, TotalOcorrencias - 1, &Ocorrencia::tipo);
							delete[] auxiliar;
						} else if (escolhaOrd == 2) {
							insertion_sort(RegistroOcorrencias, OrdenacaoOcorrencias, TotalOcorrencias, &Ocorrencia::tipo);
						} else {
							cout << "Escolha de ordenacao invalida! Cancelando...\n";
							break;
						}
						cout << "Ocorrencias ordenadas por Tipo.\n";
						break;
					}
					case 5: {
						cout << "Ordenando por Local....\n";
						if (escolhaOrd == 1) {
							int* auxiliar = new int[TotalOcorrencias];
							merge_sort(RegistroOcorrencias, OrdenacaoOcorrencias.ord, auxiliar, 0, TotalOcorrencias - 1, &Ocorrencia::local);
							delete[] auxiliar;
						} else if (escolhaOrd == 2) {
							insertion_sort(RegistroOcorrencias, OrdenacaoOcorrencias, TotalOcorrencias, &Ocorrencia::local);
						} else {
							cout << "Escolha de ordenacao invalida! Cancelando...\n";
							break;
						}
						cout << "Ocorrencias ordenadas por Local.\n";
						break;
					}
					default:
						cout << "Escolha de campo invalida! Cancelando...\n";
						break;
				}
				break;
			}
			case 8: {
				cout << "ID da ocorrencia para analise: ";
				int idOcorrencia;
				
				if (!(cin >> idOcorrencia)) {
					if (!cin.eof()) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					cout << "ID Inválido! Análise cancelada\n";
					break;
				}

				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
				analisarOcorrencia(RegistroEvidencias, TotalEvidencia, idOcorrencia);
				break;
			}
			case 9: {
				cout << "ID da ocorrencia para listagem: ";
				int idOcorrencia;

				if (!(cin >> idOcorrencia)) {
					if (!cin.eof()) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					cout << "ID Inválido! Listagem cancelada\n";
					break;
				}

				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				if (idOcorrencia < 1 || idOcorrencia > TotalOcorrencias) {
					cout << "Ocorrencia nao encontrada!\n";
					break;
				}

				listarEvidencias(RegistroEvidencias, TotalEvidencia, idOcorrencia);
				break;
			}
            case 10:
                cout << "\nSaindo do sistema..." << endl;
                break;
            default:
                cout << "\nOpcao invalida!" << endl;
                break;
        } 

    } while (escolha != 10); 
    

	delete[] RegistroPessoas;
	delete[] RegistroOcorrencias;
	delete[] RegistroEvidencias;
    return 0;
}