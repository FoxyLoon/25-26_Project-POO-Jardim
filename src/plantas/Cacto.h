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

    // Contabilização de recursos absorvidos durante a vida
    int totalNutrientesAbsorvidos;

public:
    Cacto();
    virtual ~Cacto() = default;

    // Interface obrigatória
    std::string getInfo() const override;
    bool verificaMorte(const Solo& s) const override;
    void aoMorrer(Solo& s) override;
    bool podeMultiplicar() const override;
    Planta* gerarSemente() override;

protected:
    // Padrão de 4 passos
    void removeRecursosSolo(Solo& s) override;
    void adicionaRecursosPlanta(Solo& s) override;
    void perdeRecursosInternos() override;
    void forneceRecursosSolo(Solo& s) override;
};

#endif