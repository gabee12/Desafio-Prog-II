#include "../recursividade.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string output(const Evidencia registros[], int total, int idOcorrencia) {
	ostringstream buffer;
	streambuf *old = cout.rdbuf(buffer.rdbuf());
	analisarOcorrencia(registros, total, idOcorrencia);
	cout.rdbuf(old);
	return buffer.str();
}

int main() {
	const Evidencia e[] = {
		{1, 1, 3, 0, "Root A"},
		{2, 1, 4, 0, "Root B"},
		{3, 1, 2, 1, "Child C"},
		{4, 1, 5, 1, "Child D"},
		{5, 1, 1, 2, "Child E"},
		{6, 2, 5, 0, "Other occurrence"}
	};

	auto s = output(e, 6, 1);
	assert(s.find("Quantidade de evidencias relacionadas: 5") != string::npos);
	assert(s.find("Relevancia total: 15") != string::npos);
	assert(s.find("Maior relevancia em uma cadeia: 8") != string::npos);
	assert(s.find("Cadeia mais relevante (IDs): 1 -> 4") != string::npos);

	auto other = output(e, 6, 2);
	assert(other.find("Quantidade de evidencias relacionadas: 1") != std::string::npos);
	assert(other.find("Relevancia total: 5") != std::string::npos);
	assert(other.find("Cadeia mais relevante (IDs): 6") != std::string::npos);

	auto empty = output(e, 6, 3);
    assert(empty.find("Nenhuma evidencia relacionada encontrada para essa ocorrencia") != std::string::npos);
    auto completelyEmpty = output(nullptr, 0, 1);
    assert(completelyEmpty.find("Nenhuma evidencia encontrada para esta ocorrencia!") != std::string::npos);

	// Detect inconsistent parent data (different occurrence).
    const Evidencia bad[] = {
        {1, 1, 2, 0, "A"},
        {2, 2, 3, 1, "B"}
    };
    assert(output(bad, 2, 2).find("ERRO: Relacionamento inconsistente detectado") != std::string::npos);

    // Deep chain: recursion visits all descendants.
    const Evidencia chain[] = {
        {1, 1, 2, 0, "A"},
        {2, 1, 3, 1, "B"},
        {3, 1, 4, 2, "C"},
        {4, 1, 1, 3, "D"},
    };
    auto ch = output(chain, 4, 1);
    assert(ch.find("Relevancia total: 10") != std::string::npos);
    assert(ch.find("Cadeia mais relevante (IDs): 1 -> 2 -> 3 -> 4") != std::string::npos);
    std::cout << "OK: 5 suites of recursion tests passed\n";
}

