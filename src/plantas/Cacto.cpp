#include "Cacto.h"

Cacto::Cacto()
    : Planta(0, 0, "NEUTRA"),
      instantesAguaExcessiva(0),
      instantesSemNutrientes(0),
      totalNutrientesAbsorvidos(0)
{}

Cacto::~Cacto() {}

char Cacto::simbolo() const {
    return 'c';
}

void Cacto::atualizar(Solo &solo) {
    // Absorve 25% da água existente no solo
    int aguaDisponivel = solo.agua;
    int aguaAbsorver = (aguaDisponivel * Settings::Cacto::absorcao_agua_percentagem) / 100;
    if (aguaAbsorver > 0) {
        obterAgua(solo, aguaAbsorver);
    }

    // Absorve até 5 unidades de nutrientes do solo
    int nutrientesAbsorvidos = obterNutrientes(solo, Settings::Cacto::absorcao_nutrientes);
    totalNutrientesAbsorvidos += nutrientesAbsorvidos;

    // Verifica condições de morte
    // 1. Água no solo > 100 durante 3 instantes seguidos
    if (solo.agua > Settings::Cacto::morre_agua_solo_maior) {
        instantesAguaExcessiva++;
    } else {
        instantesAguaExcessiva = 0; // reset se a condição não se mantém
    }

    // 2. Nutrientes no solo = 0 durante mais de 3 instantes seguidos
    if (solo.nutrientes < Settings::Cacto::morre_nutrientes_solo_menor) {
        instantesSemNutrientes++;
    } else {
        instantesSemNutrientes = 0; // reset
    }
}

bool Cacto::deveMorrer(const Solo &solo) const {
    // Morre se água excessiva por 3 instantes
    if (instantesAguaExcessiva >= Settings::Cacto::morre_agua_solo_instantes) {
        return true;
    }

    // Morre se sem nutrientes por mais de 3 instantes
    if (instantesSemNutrientes > Settings::Cacto::morre_nutrientes_solo_instantes) {
        return true;
    }

    return false;
}

bool Cacto::podeMultiplicar() const {
    return (getNutrientesInternos() > Settings::Cacto::multiplica_nutrientes_maior &&
            getAguaInterna() > Settings::Cacto::multiplica_agua_maior);
}

void Cacto::morrer(Solo &solo) {
    // Ao morrer, deixa no solo todos os nutrientes que absorveu durante a vida
    solo.nutrientes += totalNutrientesAbsorvidos;
    // A água não é devolvida
}