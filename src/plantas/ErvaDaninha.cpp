#include "ErvaDaninha.h"

ErvaDaninha::ErvaDaninha()
    : Planta(Settings::ErvaDaninha::inicial_agua,
             Settings::ErvaDaninha::inicial_nutrientes,
             "FEIA"),
      instantesVividos(0),
      instantesDesdeUltimaMultiplicacao(0)
{}

ErvaDaninha::~ErvaDaninha() {}

char ErvaDaninha::simbolo() const {
    return 'e';
}

void ErvaDaninha::atualizar(Solo &solo) {
    // Incrementa contadores
    instantesVividos++;
    instantesDesdeUltimaMultiplicacao++;

    // Absorve 1 unidade de água do solo (se existir)
    obterAgua(solo, Settings::ErvaDaninha::absorcao_agua);

    // Absorve 1 unidade de nutrientes do solo (se existir)
    obterNutrientes(solo, Settings::ErvaDaninha::absorcao_nutrientes);
}

bool ErvaDaninha::deveMorrer() const {
    // Morre sozinha passados 60 instantes
    return (instantesVividos >= Settings::ErvaDaninha::morre_instantes);
}

bool ErvaDaninha::podeMultiplicar() const {
    // Multiplica-se se:
    // - nutrientes acumulados > 30
    // - passaram 5 instantes desde a última multiplicação
    return (getNutrientesInternos() > Settings::ErvaDaninha::multiplica_nutrientes_maior &&
            instantesDesdeUltimaMultiplicacao >= Settings::ErvaDaninha::multiplica_instantes);
}

void ErvaDaninha::resetarMultiplicacao() {
    // Reseta o contador após multiplicação
    instantesDesdeUltimaMultiplicacao = 0;
    // A planta original não perde água nem nutrientes na multiplicação
}