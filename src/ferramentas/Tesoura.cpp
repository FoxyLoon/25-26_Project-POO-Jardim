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
    if (solo.temPlanta()) {
        if (solo.planta->getBeleza() == "FEIA") {
            // Remove a planta feia
            delete solo.planta;
            solo.planta = nullptr;
            // Podia deixar algo no solo (nutrientes), mas o enunciado não especifica
        }
    }

    return true;  // tesoura nunca se desgasta
}

bool Tesoura::estaUtilizavel() const {
    return true;  // sempre utilizável (aço cromado)
}

std::string Tesoura::getInfo() const {
    std::ostringstream oss;
    oss << "Tesoura de Poda #" << getNumeroSerie()
        << " - Durabilidade: infinita (aco cromado)";
    return oss.str();
}