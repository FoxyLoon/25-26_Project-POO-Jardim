#include "PlantaExotica.h"

PlantaExotica::PlantaExotica() 
    : Planta(30, 30, "BONITA"),
      instantesVividos(0),
      ciclosMultiplicacao(0)
{}

PlantaExotica::~PlantaExotica() {}

char PlantaExotica::simbolo() const {
    return 'x';
}

void PlantaExotica::atualizar(Solo &solo) {
    instantesVividos++;

    // Perda metabólica: perde 2 de água e 1 de nutrientes
    removerAguaInterna(2);
    removerNutrientesInternos(1);

    // Absorve recursos do solo
    obterAgua(solo, 3);
    obterNutrientes(solo, 2);

    // Se estiver na fase MADURA, produz nutrientes para o solo (simbiose)
    if (getFase() == MADURA) {
        if (getNutrientesInternos() >= 3) {
            solo.adicionarNutrientes(2);  // ✅ CORRIGIDO: usar método
        }
    }
}

PlantaExotica::Fase PlantaExotica::getFase() const {
    if (instantesVividos <= 20) {
        return JOVEM;
    } else if (instantesVividos <= 40) {
        return ADULTA;
    } else {
        return MADURA;
    }
}

bool PlantaExotica::deveMorrer() const {
    if (getAguaInterna() < 5) {
        return true;
    }

    if (getNutrientesInternos() < 3) {
        return true;
    }

    if (instantesVividos >= 80) {
        return true;
    }

    return false;
}

bool PlantaExotica::podeMultiplicar() const {
    return (getNutrientesInternos() > 70 && getAguaInterna() > 60);
}

void PlantaExotica::morrer(Solo &solo) {
    // Ao morrer, devolve 75% dos seus recursos ao solo
    solo.adicionarNutrientes((getNutrientesInternos() * 75) / 100);  // ✅ CORRIGIDO
    solo.adicionarAgua((getAguaInterna() * 75) / 100);              // ✅ CORRIGIDO
}

void PlantaExotica::prepararMultiplicacao() {
    setAguaInterna(getAguaInterna() / 2);
    setNutrientesInternos(getNutrientesInternos() / 2);
    ciclosMultiplicacao++;
}