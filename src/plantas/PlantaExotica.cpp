#include "PlantaExotica.h"

PlantaExotica::PlantaExotica() 
    : Planta(30, 30, "BONITA"),  // 30 água, 30 nutrientes, bonita
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
    obterAgua(solo, 3);           // absorve 3 unidades de água
    obterNutrientes(solo, 2);     // absorve 2 unidades de nutrientes

    // Se estiver na fase MADURA, produz nutrientes para o solo (simbiose)
    if (getFase() == MADURA) {
        // Produz 2 nutrientes através de fotossíntese avançada
        // (desde que tenha recursos internos suficientes)
        if (getNutrientesInternos() >= 3) {
            solo.nutrientes += 2;
            // Não consome nutrientes internos para isso (energia vem do sol)
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
    // Morre se água interna muito baixa
    if (getAguaInterna() < 5) {
        return true;
    }

    // Morre se nutrientes internos muito baixos
    if (getNutrientesInternos() < 3) {
        return true;
    }

    // Morre de velhice após 80 instantes (ciclo de vida completo)
    if (instantesVividos >= 80) {
        return true;
    }

    return false;
}

bool PlantaExotica::podeMultiplicar() const {
    // Multiplica-se quando tem recursos abundantes
    return (getNutrientesInternos() > 70 && getAguaInterna() > 60);
}

void PlantaExotica::morrer(Solo &solo) {
    // Ao morrer, devolve 75% dos seus recursos ao solo
    solo.nutrientes += (getNutrientesInternos() * 75) / 100;
    solo.agua += (getAguaInterna() * 75) / 100;
}

void PlantaExotica::prepararMultiplicacao() {
    // A planta original mantém 50% dos recursos
    setAguaInterna(getAguaInterna() / 2);
    setNutrientesInternos(getNutrientesInternos() / 2);
    ciclosMultiplicacao++;
    
    // A nova planta começa com 30 água e 30 nutrientes (valores fixos)
}