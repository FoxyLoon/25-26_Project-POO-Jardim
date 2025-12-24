#include "Adubo.h"
#include <sstream>

Adubo::Adubo() : Ferramenta(), quantidadeDisponivel(Settings::Adubo::capacidade) {}

Adubo::~Adubo() {}

char Adubo::simbolo() const {
    return 'a';
}

std::string Adubo::nome() const {
    return "Pacote de Adubo";
}

bool Adubo::aplicar(Solo &solo) {
    if (!estaUtilizavel()) {
        return false;  // ferramenta inútil
    }

    // Adiciona nutrientes ao solo
    solo.nutrientes += Settings::Adubo::dose;

    // Subtrai do pacote
    quantidadeDisponivel -= Settings::Adubo::dose;

    // Se ficou vazio, é levado pelo vento
    if (quantidadeDisponivel <= 0) {
        quantidadeDisponivel = 0;
        return false;  // deve ser descartado
    }

    return true;  // ainda utilizável
}

bool Adubo::estaUtilizavel() const {
    return quantidadeDisponivel > 0;
}

std::string Adubo::getInfo() const {
    std::ostringstream oss;
    oss << "Pacote de Adubo #" << getNumeroSerie()
        << " - Quantidade: " << quantidadeDisponivel
        << "/" << Settings::Adubo::capacidade;
    return oss.str();
}