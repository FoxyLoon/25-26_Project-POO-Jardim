#include "Tesoura.h"
#include "../plantas/Planta.h"
#include <sstream>

Tesoura::Tesoura() : Ferramenta() {}

Tesoura::~Tesoura() {}

char Tesoura::simbolo() const {
    return 't';
}

std::string Tesoura::nome() const {
    return "Tesoura de Poda";
}

bool Tesoura::aplicar(Solo &solo) {
    // Elimina plantas FEIAS
    if (solo.temPlanta()) {  // ✅ CORRIGIDO: usar método
        Planta* p = solo.getPlanta();  // ✅ CORRIGIDO: usar getter
        if (p->getBeleza() == "FEIA") {
            // Remove a planta feia
            solo.setPlanta(nullptr);  // ✅ CORRIGIDO: usar setter
            delete p;
        }
    }

    return true;  // tesoura nunca se desgasta
}

bool Tesoura::estaUtilizavel() const {
    return true;
}

std::string Tesoura::getInfo() const {
    std::ostringstream oss;
    oss << "Tesoura de Poda #" << getNumeroSerie()
        << " - Durabilidade: infinita (aco cromado)";
    return oss.str();
}