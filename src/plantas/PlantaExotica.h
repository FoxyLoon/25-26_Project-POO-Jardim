#ifndef PLANTAEXOTICA_H
#define PLANTAEXOTICA_H

#include "Planta.h"

/*
PLANTA EXÓTICA (x) - BAMBU LUNAR
Beleza: BONITA

Comportamento por Fases:
- Jovem (0-20): Absorve 3 água e 2 nutrientes.
- Adulta (21-40): Dormência (não absorve nem produz).
- Madura (41+): Produz 2 nutrientes para o solo, perde 2 água e 1 nutriente internos.

Morte:
- Água interna < 5 ou Nutrientes internos < 3.
- Idade >= 80 instantes.
- Ao morrer: Devolve 75% dos recursos ao solo.
*/

class PlantaExotica : public Planta
{
private:
    int idade;

public:
    PlantaExotica();
    virtual ~PlantaExotica() = default;

    // Informação da Planta
    string getInfo() const override;

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