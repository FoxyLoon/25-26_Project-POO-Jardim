// ========== ErvaDaninha.cpp ==========
#include "ErvaDaninha.h"
#include "../jardim/Solo.h"
#include <sstream>

ErvaDaninha::ErvaDaninha()
    : Planta(Settings::ErvaDaninha::inicial_agua,
             Settings::ErvaDaninha::inicial_nutrientes,
             'e', "FEIA"),
      idade(0),
      instantesDesdeUltimaMultiplicacao(0) {}

// ========================================================
// PADRÃO DE 4 PASSOS
// ========================================================

void ErvaDaninha::removeRecursosSolo(Solo& s) {
    // Incrementa contadores
    idade++;
    instantesDesdeUltimaMultiplicacao++;
}

void ErvaDaninha::adicionaRecursosPlanta(Solo& s) {
    // Absorve 1 água e 1 nutriente
    obterAgua(s, Settings::ErvaDaninha::absorcao_agua);
    obterNutrientes(s, Settings::ErvaDaninha::absorcao_nutrientes);
}

void ErvaDaninha::perdeRecursosInternos() {
    // Ervas daninhas são muito resistentes - não perdem recursos
}

void ErvaDaninha::forneceRecursosSolo(Solo& s) {
    // Não fornece recursos
}

// ========================================================
// CONDIÇÕES DE MORTE
// ========================================================

bool ErvaDaninha::verificaMorte(const Solo& s) const {
    // Morre sozinha passados 60 instantes
    return (idade >= Settings::ErvaDaninha::morre_instantes);
}

void ErvaDaninha::aoMorrer(Solo& s) {
    // Não devolve recursos ao solo
}

// ========================================================
// MULTIPLICAÇÃO
// ========================================================

bool ErvaDaninha::podeMultiplicar() const {
    // Multiplica-se se:
    // - Nutrientes > 30
    // - Passaram 5 instantes desde a última multiplicação
    return (getNutrientesInternos() > Settings::ErvaDaninha::multiplica_nutrientes_maior &&
            instantesDesdeUltimaMultiplicacao >= Settings::ErvaDaninha::multiplica_instantes);
}

Planta* ErvaDaninha::gerarSemente() {
    // Nova erva com valores iniciais
    ErvaDaninha* filha = new ErvaDaninha();

    // A MÃE NÃO PERDE RECURSOS (diferente das outras plantas)
    // Apenas reseta o contador de multiplicação

    return filha;
}

void ErvaDaninha::resetarMultiplicacao() {
    instantesDesdeUltimaMultiplicacao = 0;
}

// ========================================================
// INFORMAÇÃO
// ========================================================

std::string ErvaDaninha::getInfo() const {
    std::ostringstream oss;
    oss << "[Erva Daninha] ";
    oss << "Idade: " << idade << "/" << Settings::ErvaDaninha::morre_instantes << " | ";
    oss << "Água: " << getAguaInterna() << " | ";
    oss << "Nutrientes: " << getNutrientesInternos() << " | ";
    oss << "Próxima Multiplicação: " << instantesDesdeUltimaMultiplicacao
        << "/" << Settings::ErvaDaninha::multiplica_instantes;
    return oss.str();
}