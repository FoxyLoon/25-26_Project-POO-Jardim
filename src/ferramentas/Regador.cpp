#include "Regador.h"
#include <sstream>

Regador::Regador() : Ferramenta(), aguaDisponivel(Settings::Regador::capacidade) {}

Regador::~Regador() {}

char Regador::simbolo() const {
    return 'g';
}

std::string Regador::nome() const {
    return "Regador";
}

bool Regador::aplicar(Solo &solo) {
    if (!estaUtilizavel()) {
        return false;  // ferramenta inútil
    }

    // Adiciona água ao solo
    solo.agua += Settings::Regador::dose;

    // Subtrai do regador
    aguaDisponivel -= Settings::Regador::dose;

    // Se ficou sem água, torna-se inútil
    if (aguaDisponivel <= 0) {
        aguaDisponivel = 0;
        return false;  // deve ser descartado
    }

    return true;  // ainda utilizável
}

bool Regador::estaUtilizavel() const {
    return aguaDisponivel > 0;
}

std::string Regador::getInfo() const {
    std::ostringstream oss;
    oss << "Regador #" << getNumeroSerie()
        << " - Agua disponivel: " << aguaDisponivel
        << "/" << Settings::Regador::capacidade;
    return oss.str();
}