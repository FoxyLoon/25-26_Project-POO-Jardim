#include "Planta.h"

Planta::Planta(int agua_inicial, int nutrientes_inicial, const std::string &beleza)
    : aguaInterna(agua_inicial), nutrientesInternos(nutrientes_inicial), beleza(beleza) {}

Planta::~Planta() {}

int Planta::getAguaInterna() const { return aguaInterna; }
int Planta::getNutrientesInternos() const { return nutrientesInternos; }
const std::string &Planta::getBeleza() const { return beleza; }

static int my_min(int a, int b) { return (a < b) ? a : b; }

int Planta::obterAgua(Solo &solo, int quantidade) {
    if (quantidade <= 0) return 0;
    int retirada = my_min(quantidade, solo.agua);
    solo.agua -= retirada;
    adicionarAguaInterna(retirada);
    return retirada;
}

int Planta::obterNutrientes(Solo &solo, int quantidade) {
    if (quantidade <= 0) return 0;
    int retirada = my_min(quantidade, solo.nutrientes);
    solo.nutrientes -= retirada;
    adicionarNutrientesInternos(retirada);
    return retirada;
}

int Planta::depositarAgua(Solo &solo, int quantidade) {
    if (quantidade <= 0) return 0;
    int deposito = my_min(quantidade, getAguaInterna());
    removerAguaInterna(deposito);
    solo.agua += deposito;
    return deposito;
}

int Planta::depositarNutrientes(Solo &solo, int quantidade) {
    if (quantidade <= 0) return 0;
    int deposito = my_min(quantidade, getNutrientesInternos());
    removerNutrientesInternos(deposito);
    solo.nutrientes += deposito;
    return deposito;
}

void Planta::atualizar(Solo & /*solo*/) {
    // implementação por defeito: não faz nada. Espécies concretas podem sobrescrever.
}

// Métodos protegidos para manipulação controlada pelos derivados
void Planta::setAguaInterna(int valor) {
    aguaInterna = valor;
}

void Planta::setNutrientesInternos(int valor) {
    nutrientesInternos = valor;
}

void Planta::adicionarAguaInterna(int quantidade) {
    aguaInterna += quantidade;
}

void Planta::adicionarNutrientesInternos(int quantidade) {
    nutrientesInternos += quantidade;
}

void Planta::removerAguaInterna(int quantidade) {
    aguaInterna -= quantidade;
    if (aguaInterna < 0) aguaInterna = 0;
}

void Planta::removerNutrientesInternos(int quantidade) {
    nutrientesInternos -= quantidade;
    if (nutrientesInternos < 0) nutrientesInternos = 0;
}