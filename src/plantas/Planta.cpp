#include "Planta.h"
#include "../jardim/Solo.h"
#include <algorithm>

// Construtor
Planta::Planta(int agua_inicial, int nutrientes_inicial,
               char simbolo, const std::string& beleza)
    : aguaInterna(agua_inicial),
      nutrientesInternos(nutrientes_inicial),
      simbolo(simbolo),
      beleza(beleza) {}

// ========================================================
// GETTERS
// ========================================================

char Planta::getSimbolo() const {
    return simbolo;
}

const std::string& Planta::getBeleza() const {
    return beleza;
}

int Planta::getAguaInterna() const {
    return aguaInterna;
}

int Planta::getNutrientesInternos() const {
    return nutrientesInternos;
}

// ========================================================
// CICLO DE VIDA - Padrão de 4 Passos
// ========================================================

void Planta::processaInstante(Solo& s) {
    // Executa o ciclo de vida em 4 passos bem definidos
    removeRecursosSolo(s);       // 1. Consome do solo
    adicionaRecursosPlanta(s);   // 2. Absorve para dentro
    perdeRecursosInternos();     // 3. Metabolismo
    forneceRecursosSolo(s);      // 4. Produz para o solo (simbiose)
}

// ========================================================
// MÉTODOS UTILITÁRIOS PROTEGIDOS
// ========================================================

int Planta::obterAgua(Solo& solo, int quantidade) {
    if (quantidade <= 0) return 0;

    // Pega até a quantidade pedida, ou o que houver disponível
    int retirada = std::min(quantidade, solo.getAgua());
    solo.removerAgua(retirada);
    adicionarAguaInterna(retirada);

    return retirada;
}

int Planta::obterNutrientes(Solo& solo, int quantidade) {
    if (quantidade <= 0) return 0;

    int retirada = std::min(quantidade, solo.getNutrientes());
    solo.removerNutrientes(retirada);
    adicionarNutrientesInternos(retirada);

    return retirada;
}

int Planta::depositarAgua(Solo& solo, int quantidade) {
    if (quantidade <= 0) return 0;

    // Não pode depositar mais do que tem
    int deposito = std::min(quantidade, getAguaInterna());
    removerAguaInterna(deposito);
    solo.adicionarAgua(deposito);

    return deposito;
}

int Planta::depositarNutrientes(Solo& solo, int quantidade) {
    if (quantidade <= 0) return 0;

    int deposito = std::min(quantidade, getNutrientesInternos());
    removerNutrientesInternos(deposito);
    solo.adicionarNutrientes(deposito);

    return deposito;
}

// ========================================================
// MANIPULAÇÃO DE RECURSOS INTERNOS
// ========================================================

void Planta::setAguaInterna(int valor) {
    aguaInterna = (valor < 0) ? 0 : valor;
}

void Planta::setNutrientesInternos(int valor) {
    nutrientesInternos = (valor < 0) ? 0 : valor;
}

void Planta::adicionarAguaInterna(int quantidade) {
    if (quantidade > 0) {
        aguaInterna += quantidade;
    }
}

void Planta::adicionarNutrientesInternos(int quantidade) {
    if (quantidade > 0) {
        nutrientesInternos += quantidade;
    }
}

void Planta::removerAguaInterna(int quantidade) {
    if (quantidade > 0) {
        aguaInterna -= quantidade;
        if (aguaInterna < 0) aguaInterna = 0;
    }
}

void Planta::removerNutrientesInternos(int quantidade) {
    if (quantidade > 0) {
        nutrientesInternos -= quantidade;
        if (nutrientesInternos < 0) nutrientesInternos = 0;
    }
}