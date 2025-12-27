#include "Roseira.h"

Roseira::Roseira()
    : Planta(Settings::Roseira::inicial_agua,
             Settings::Roseira::inicial_nutrientes,
             "BONITA"),
      totalAguaAbsorvida(0),
      totalNutrientesAbsorvidos(0)
{}

Roseira::~Roseira() {}

char Roseira::simbolo() const {
    return 'r';
}

void Roseira::atualizar(Solo &solo) {
    // Perde 4 unidades de água e 4 de nutrientes
    removerAguaInterna(Settings::Roseira::perda_agua);
    removerNutrientesInternos(Settings::Roseira::perda_nutrientes);

    // Absorve 5 unidades de água do solo (se existir)
    int aguaAbs = obterAgua(solo, Settings::Roseira::absorcao_agua);
    totalAguaAbsorvida += aguaAbs;

    // Absorve 8 unidades de nutrientes do solo (se existir)
    int nutrientesAbs = obterNutrientes(solo, Settings::Roseira::absorcao_nutrientes);
    totalNutrientesAbsorvidos += nutrientesAbs;
}

bool Roseira::deveMorrer() const {
    // Morre se água acumulada chegar a 0
    if (getAguaInterna() < Settings::Roseira::morre_agua_menor) {
        return true;
    }

    // Morre se nutrientes acumulados chegarem a 0
    if (getNutrientesInternos() < Settings::Roseira::morre_nutrientes_menor) {
        return true;
    }

    // Morre se nutrientes acumulados atingirem 200 (>= 200 no Settings)
    if (getNutrientesInternos() > Settings::Roseira::morre_nutrientes_maior) {
        return true;
    }

    // A condição de "todas as posições vizinhas com planta" deve ser verificada
    // externamente pelo Jardim, pois a planta não tem acesso aos vizinhos

    return false;
}

bool Roseira::podeMultiplicar() const {
    return (getNutrientesInternos() > Settings::Roseira::multiplica_nutrientes_maior);
}

void Roseira::morrer(Solo &solo) {
    // Ao morrer deixa no solo metade dos nutrientes e metade da água absorvidos
    solo.adicionarNutrientes(totalNutrientesAbsorvidos / 2);  // ✅ CORRIGIDO
    solo.adicionarAgua(totalAguaAbsorvida / 2);              // ✅ CORRIGIDO
}

int Roseira::prepararMultiplicacao() {
    // A nova planta começa com 25 nutrientes e metade da água da original
    int aguaAtual = getAguaInterna();
    int aguaParaNova = aguaAtual * Settings::Roseira::nova_agua_percentagem / 100;

    // A roseira original fica com 100 nutrientes e metade da água que tinha
    int aguaParaOriginal = aguaAtual * Settings::Roseira::original_agua_percentagem / 100;

    setNutrientesInternos(Settings::Roseira::original_nutrientes);
    setAguaInterna(aguaParaOriginal);

    return aguaParaNova;
}