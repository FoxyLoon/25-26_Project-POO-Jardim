#ifndef ROSEIRA_H
#define ROSEIRA_H

#include "Planta.h"

/*
ROSEIRA
Beleza: BONITA

Comportamento:
- Absorve valores fixos de água e nutrientes do solo
- Tem perda metabólica constante (respiração/transpiração)
- Morre se tiver pouca água, poucos nutrientes ou excesso de nutrientes
- Ao morrer: devolve metade dos seus recursos ao solo
- Multiplicação baseada em nutrientes
*/

class Roseira : public Planta
{
private:
    // Idade da Planta
    int idade;

public:
    Roseira();
    virtual ~Roseira() = default;

    // Informação da Planta
    string getInfoPlanta() const override;
    string getInfoExtraPlanta() const override;

    // ========================================================

    // Processamento de cada instante
    void removeRecursosSolo(Solo &s) override;
    void adicionaRecursosPlanta(Solo &s) override;
    void envelhecimento() override;
    void removeRecursosPlanta() override;
    void adicionaRecursosSolo(Solo &s) override;

    // ========================================================

    // Condições de Multiplicação
    bool podeMultiplicar() const override;
    Planta *gerarSemente() override;

    // ========================================================

    // Condições de Morte
    bool verificaMorte(const Solo &s) override;
    void aoMorrer(Solo &s) override;
};

#endif