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
        return false;
    }

    // Adiciona água ao solo
    solo.adicionarAgua(Settings::Regador::dose);  // ✅ CORRIGIDO: usar método

    // Subtrai do regador
    aguaDisponivel -= Settings::Regador::dose;

    // Se ficou sem água, torna-se inútil
    if (aguaDisponivel <= 0) {
        aguaDisponivel = 0;
        return false;
    }

    return true;
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