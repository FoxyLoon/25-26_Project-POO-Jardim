// ========== Roseira.cpp ==========
#include "Roseira.h"
#include "../jardim/Solo.h"
#include <sstream>

Roseira::Roseira()
    : Planta(Settings::Roseira::inicial_agua,
             Settings::Roseira::inicial_nutrientes,
             'r', "BONITA"),
      totalAguaAbsorvida(0),
      totalNutrientesAbsorvidos(0) {}

// ========================================================
// PADRÃO DE 4 PASSOS
// ========================================================

void Roseira::removeRecursosSolo(Solo& s) {
    // Roseira apenas absorve, não precisa de lógica adicional aqui
}

void Roseira::adicionaRecursosPlanta(Solo& s) {
    // Absorve 5 unidades de água
    int aguaAbsorvida = obterAgua(s, Settings::Roseira::absorcao_agua);
    totalAguaAbsorvida += aguaAbsorvida;

    // Absorve 8 unidades de nutrientes
    int nutrientesAbsorvidos = obterNutrientes(s, Settings::Roseira::absorcao_nutrientes);
    totalNutrientesAbsorvidos += nutrientesAbsorvidos;
}

void Roseira::perdeRecursosInternos() {
    // Metabolismo: perde 4 de água e 4 de nutrientes
    removerAguaInterna(Settings::Roseira::perda_agua);
    removerNutrientesInternos(Settings::Roseira::perda_nutrientes);
}

void Roseira::forneceRecursosSolo(Solo& s) {
    // Roseira não fornece recursos ao solo enquanto viva
}

// ========================================================
// CONDIÇÕES DE MORTE
// ========================================================

bool Roseira::verificaMorte(const Solo& s) const {
    // Regra 1: Água interna chegou a 0
    if (getAguaInterna() < Settings::Roseira::morre_agua_menor) {
        return true;
    }

    // Regra 2: Nutrientes internos chegaram a 0
    if (getNutrientesInternos() < Settings::Roseira::morre_nutrientes_menor) {
        return true;
    }

    // Regra 3: Nutrientes internos >= 200 (excesso)
    if (getNutrientesInternos() > Settings::Roseira::morre_nutrientes_maior) {
        return true;
    }

    // Regra 4: Cercada por vizinhos - será verificada pelo Jardim
    // (a planta não tem acesso aos vizinhos)

    return false;
}

void Roseira::aoMorrer(Solo& s) {
    // Devolve metade dos recursos absorvidos durante a vida
    s.adicionarAgua(totalAguaAbsorvida / 2);
    s.adicionarNutrientes(totalNutrientesAbsorvidos / 2);
}

// ========================================================
// MULTIPLICAÇÃO
// ========================================================

bool Roseira::podeMultiplicar() const {
    return (getNutrientesInternos() > Settings::Roseira::multiplica_nutrientes_maior);
}

Planta* Roseira::gerarSemente() {
    // Nova roseira
    int aguaMae = getAguaInterna();

    // Água da nova planta: 50% da mãe
    int aguaParaNova = (aguaMae * Settings::Roseira::nova_agua_percentagem) / 100;

    // Ajusta a mãe: fica com 100 nutrientes e 50% da água
    setNutrientesInternos(Settings::Roseira::original_nutrientes);
    setAguaInterna((aguaMae * Settings::Roseira::original_agua_percentagem) / 100);

    // Cria filha com 25 nutrientes e a água calculada
    Roseira* filha = new Roseira();
    filha->setAguaInterna(aguaParaNova);
    filha->setNutrientesInternos(Settings::Roseira::nova_nutrientes);

    return filha;
}

// ========================================================
// INFORMAÇÃO
// ========================================================

std::string Roseira::getInfo() const {
    std::ostringstream oss;
    oss << "[Roseira] ";
    oss << "Água: " << getAguaInterna() << " | ";
    oss << "Nutrientes: " << getNutrientesInternos() << " | ";
    oss << "Total Absorvido (A/N): " << totalAguaAbsorvida
        << "/" << totalNutrientesAbsorvidos;
    return oss.str();
}