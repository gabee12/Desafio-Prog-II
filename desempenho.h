#pragma once
#include <iosfwd>

using namespace std;

bool gerarRelatorio(ostream& saida, const char *caminhoCSV = "relatorio_desempenho.csv");