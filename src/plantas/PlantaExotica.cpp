// ========== PlantaExotica.cpp ==========
#include "PlantaExotica.h"
#include "../jardim/Solo.h"
#include <sstream>

PlantaExotica::PlantaExotica()
    : Planta(30, 30, 'x', "BONITA"),
      idade(0) {}

// ========================================================
// PADRÃO DE 4 PASSOS - Com Fases
// ========================================================

void PlantaExotica::removeRecursosSolo(Solo& s) {
    idade++;
}

void PlantaExotica::adicionaRecursosPlanta(Solo& s) {
    Fase fase = getFase();

    // Apenas JOVEM e MADURA absorvem recursos
    if (fase == JOVEM || fase == MADURA) {
        obterAgua(s, 3);
        obterNutrientes(s, 2);
    }
    // ADULTA: dormência - não absorve
}

void PlantaExotica::perdeRecursosInternos() {
    // Todas as fases perdem recursos (metabolismo)
    removerAguaInterna(2);
    removerNutrientesInternos(1);
}

void PlantaExotica::forneceRecursosSolo(Solo& s) {
    // Apenas fase MADURA produz nutrientes (simbiose)
    if (getFase() == MADURA) {
        s.adicionarNutrientes(2);
    }
}

// ========================================================
// FASES
// ========================================================

PlantaExotica::Fase PlantaExotica::getFase() const {
    if (idade <= 20) {
        return JOVEM;
    } else if (idade <= 40) {
        return ADULTA;
    } else {
        return MADURA;
    }
}

// ========================================================
// CONDIÇÕES DE MORTE
// ========================================================

bool PlantaExotica::verificaMorte(const Solo& s) const {
    // Regra 1: Água interna < 5
    if (getAguaInterna() < 5) {
        return true;
    }

    // Regra 2: Nutrientes internos < 3
    if (getNutrientesInternos() < 3) {
        return true;
    }

    // Regra 3: Idade >= 80
    if (idade >= 80) {
        return true;
    }

    return false;
}

void PlantaExotica::aoMorrer(Solo& s) {
    // Devolve 75% dos recursos internos
    s.adicionarAgua((getAguaInterna() * 75) / 100);
    s.adicionarNutrientes((getNutrientesInternos() * 75) / 100);
}

// ========================================================
// MULTIPLICAÇÃO
// ========================================================

bool PlantaExotica::podeMultiplicar() const {
    return (getNutrientesInternos() > 70 && getAguaInterna() > 60);
}

Planta* PlantaExotica::gerarSemente() {
    // Cria nova planta
    PlantaExotica* filha = new PlantaExotica();

    // Original mantém 50% dos recursos
    setAguaInterna(getAguaInterna() / 2);
    setNutrientesInternos(getNutrientesInternos() / 2);

    // Nova planta começa com 30 água e 30 nutrientes
    filha->setAguaInterna(30);
    filha->setNutrientesInternos(30);

    return filha;
}

// ========================================================
// INFORMAÇÃO
// ========================================================

std::string PlantaExotica::getInfo() const {
    std::ostringstream oss;
    oss << "[Bambu Lunar] ";

    // Fase
    Fase fase = getFase();
    if (fase == JOVEM) oss << "JOVEM";
    else if (fase == ADULTA) oss << "ADULTA";
    else oss << "MADURA";

    oss << " | Idade: " << idade << "/80 | ";
    oss << "Água: " << getAguaInterna() << " | ";
    oss << "Nutrientes: " << getNutrientesInternos();

    return oss.str();
}