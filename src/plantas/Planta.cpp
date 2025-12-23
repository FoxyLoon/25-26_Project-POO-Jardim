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
    aguaInterna += retirada;
    return retirada;
}

int Planta::obterNutrientes(Solo &solo, int quantidade) {
    if (quantidade <= 0) return 0;
    int retirada = my_min(quantidade, solo.nutrientes);
    solo.nutrientes -= retirada;
    nutrientesInternos += retirada;
    return retirada;
}

int Planta::depositarAgua(Solo &solo, int quantidade) {
    if (quantidade <= 0) return 0;
    int deposito = my_min(quantidade, aguaInterna);
    aguaInterna -= deposito;
    solo.agua += deposito;
    return deposito;
}

int Planta::depositarNutrientes(Solo &solo, int quantidade) {
    if (quantidade <= 0) return 0;
    int deposito = my_min(quantidade, nutrientesInternos);
    nutrientesInternos -= deposito;
    solo.nutrientes += deposito;
    return deposito;
}

void Planta::atualizar(Solo & /*solo*/) {
    // implementação por defeito: não faz nada. Espécies concretas podem sobrescrever.
}
