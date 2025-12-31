// ========== Roseira.h ==========
#ifndef ROSEIRA_H
#define ROSEIRA_H

#include "Planta.h"

/**
 * ROSEIRA
 * Beleza: BONITA
 *
 * Características:
 * - Inicialmente: 25 água, 25 nutrientes
 * - Perde 4 água e 4 nutrientes por instante (metabolismo alto)
 * - Absorve 5 água e 8 nutrientes do solo
 * - Morre se água/nutrientes internos = 0
 * - Morre se nutrientes internos >= 200 (excesso)
 * - Morre se TODAS as posições vizinhas tiverem plantas
 * - Ao morrer: devolve metade dos recursos absorvidos durante a vida
 * - Multiplica-se se nutrientes > 100
 */
class Roseira : public Planta {
private:
    // Contabilização de recursos absorvidos durante a vida
    int totalAguaAbsorvida;
    int totalNutrientesAbsorvidos;

public:
    Roseira();
    virtual ~Roseira() = default;

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