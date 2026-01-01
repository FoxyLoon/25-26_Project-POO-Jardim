#include "Cacto.h"
#include "../jardim/Solo.h"
#include <sstream>
#include <algorithm>

Cacto::Cacto()
    : Planta(20, 20, 'c', "NEUTRA"),
      instantesAguaExcessiva(0),
      instantesSemNutrientes(0),
      totalNutrientesAbsorvidos(0) {}

// ========================================================
// PADRÃO DE 4 PASSOS - Implementação Simplificada
// ========================================================

void Cacto::removeRecursosSolo(Solo& s) {
    // Atualiza contadores ANTES de modificar o solo
    int aguaAntes = s.getAgua();
    int nutrientesAntes = s.getNutrientes();

    // Contadores para condições de morte
    if (aguaAntes > Settings::Cacto::morre_agua_solo_maior) {
        instantesAguaExcessiva++;
    } else {
        instantesAguaExcessiva = 0;
    }

    if (nutrientesAntes < Settings::Cacto::morre_nutrientes_solo_menor) {
        instantesSemNutrientes++;
    } else {
        instantesSemNutrientes = 0;
    }
}

void Cacto::adicionaRecursosPlanta(Solo& s) {
    // Absorve 25% da água do solo
    int aguaDisponivel = s.getAgua();
    int aguaAbsorver = (aguaDisponivel * Settings::Cacto::absorcao_agua_percentagem) / 100;
    int aguaAbsorvida = obterAgua(s, aguaAbsorver);

    // Absorve até 5 unidades de nutrientes
    int nutrientesAbsorvidos = obterNutrientes(s, Settings::Cacto::absorcao_nutrientes);
    totalNutrientesAbsorvidos += nutrientesAbsorvidos;
}

void Cacto::perdeRecursosInternos() {
    // Metabolismo mínimo: perde 1 de água
    removerAguaInterna(1);
}

void Cacto::forneceRecursosSolo(Solo& s) {
    // Cacto não fornece recursos ao solo enquanto vivo
}

// ========================================================
// CONDIÇÕES DE MORTE
// ========================================================

bool Cacto::verificaMorte(const Solo& s) const {
    // Regra 1: Água no solo demasiado alta por 3 instantes
    if (instantesAguaExcessiva >= Settings::Cacto::morre_agua_solo_instantes) {
        return true;
    }

    // Regra 2: Nutrientes no solo demasiado baixos por mais de 3 instantes
    if (instantesSemNutrientes > Settings::Cacto::morre_nutrientes_solo_instantes) {
        return true;
    }

    // Regra 3: Água interna a zero
    if (getAguaInterna() <= 0) {
        return true;
    }

    return false;
}

void Cacto::aoMorrer(Solo& s) {
    // Devolve TODOS os nutrientes absorvidos durante a vida
    s.adicionarNutrientes(totalNutrientesAbsorvidos);
    // Água não é devolvida
}

// ========================================================
// MULTIPLICAÇÃO
// ========================================================

bool Cacto::podeMultiplicar() const {
    return (getNutrientesInternos() > Settings::Cacto::multiplica_nutrientes_maior &&
            getAguaInterna() > Settings::Cacto::multiplica_agua_maior);
}

Planta* Cacto::gerarSemente() {
    // Cria novo cacto
    Cacto* filha = new Cacto();

    // Divide recursos em partes iguais
    int aguaMae = getAguaInterna();
    int nutrientesMae = getNutrientesInternos();

    setAguaInterna(aguaMae / 2);
    setNutrientesInternos(nutrientesMae / 2);

    filha->setAguaInterna(aguaMae / 2);
    filha->setNutrientesInternos(nutrientesMae / 2);

    return filha;
}

// ========================================================
// INFORMAÇÃO
// ========================================================

std::string Cacto::getInfo() const {
    std::ostringstream oss;
    oss << "[Cacto] ";
    oss << "Água: " << getAguaInterna() << " | ";
    oss << "Nutrientes: " << getNutrientesInternos() << " | ";
    oss << "Total Absorvido: " << totalNutrientesAbsorvidos << " | ";
    oss << "Instantes Água Alta: " << instantesAguaExcessiva << " | ";
    oss << "Instantes Sem Nutrientes: " << instantesSemNutrientes;
    return oss.str();
}