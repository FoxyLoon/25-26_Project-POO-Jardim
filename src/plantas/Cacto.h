#ifndef CACTO_H
#define CACTO_H

#include "Planta.h"

/**
 * CACTO
 * Beleza: NEUTRA
 *
 * Comportamento:
 * - Absorve 25% da água do solo a cada instante
 * - Absorve até 5 unidades de nutrientes
 * - Morre se água do solo > 100 por 3 instantes seguidos
 * - Morre se nutrientes do solo = 0 por mais de 3 instantes seguidos
 * - Ao morrer: devolve TODOS os nutrientes absorvidos durante a vida
 * - Multiplica-se se nutrientes > 100 e água > 50
 */

class Cacto : public Planta {
private:
    // Contadores para condições de morte
    int instantesAguaExcessiva;
    int instantesSemNutrientes;

    // Contador de recursos absorvidos durante a vida
    int totalNutrientesAbsorvidos;

public:
    Cacto();
    virtual ~Cacto() = default;

    // Informação da Planta
    string getInfo() const override;
    
    // ========================================================

    // Processamento de cada instante
    void removeRecursosSolo(Solo& s) override;
    void adicionaRecursosPlanta(Solo& s) override;
    void removeRecursosPlanta() override;
    void adicionaRecursosSolo(Solo& s) override;

    // ========================================================

    // Condições de Multiplicação
    bool podeMultiplicar() const override;
    Planta* gerarSemente() override;

    // ========================================================
    
    // Condições de Morte
    bool verificaMorte(const Solo& s) override;
    void aoMorrer(Solo& s) override;
};

#endif