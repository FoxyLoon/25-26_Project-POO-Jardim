#ifndef PLANTAEXOTICA_H
#define PLANTAEXOTICA_H

#include "Planta.h"

/*
- Planta Exótica (x) - BAMBU LUNAR
        Planta exótica importada de um país distante no Oriente.

            - Beleza: BONITA

            - Começa no seu depósito:
                - Água = 30
                - Nutrientes = 30

            - Ciclos de crescimento:
                - Jovem: 0-20 instantes (absorve recursos)
                - Adulta: 21-40 instantes (equilíbrio)
                - Madura: 41+ instantes (produz nutrientes)

            - A cada instante:
                - Fase Jovem:
                    - Absorve 3 unidades de água do solo (se existir)
                    - Absorve 2 unidades de nutrientes do solo (se existir)

                - Fase Adulta:
                    - (Apenas existe e não faz nada)

                - Fase Madura:
                    - Produz 2 unidades de nutrientes para o solo
                    - Perde 2 unidades de água
                    - Perde 1 unidade de nutrientes

            - Condições de Morte
                - Água interna < 5
                - Nutrientes internos < 3
                - Após 80 instantes (ciclo de vida completo)

            - Pós-Morte
                - Deixa 75% dos seus recursos no solo

            - Multiplicação:
                - SE:
                    - Houver posições diagonais disponiveis vazias (NE, SE, SW, NW)
                    - Nutrientes da Exotica original > 70
                    - Água da Exotica Original > 60
                  - ENTÃO:
                      - Nova Exotica fica:
                        - Água = 30
                        - Nutrientes = 30
                      - E Exotica Original fica:
                        - Metade dos recursos que tinha no seu deposito
*/

class PlantaExotica : public Planta
{
private:
    int idade;

public:
    PlantaExotica();
    ~PlantaExotica() override = default;

    // Informação da Planta
    [[nodiscard]] string getInfoPlanta() const override;
    [[nodiscard]] string getInfoExtraPlanta() const override;

    // ========================================================

    // Processamento de cada instante
    void removeRecursosSolo(Solo &s) override;
    void adicionaRecursosPlanta(Solo &s) override;
    void envelhecimento() override;
    void removeRecursosPlanta() override;
    void adicionaRecursosSolo(Solo &s) override;

    // ========================================================

    // Condições de Multiplicação
    [[nodiscard]] bool podeMultiplicar() const override;
    Planta *gerarSemente() override;

    // ========================================================

    // Condições de Morte
    bool verificaMorte(const Solo &s) override;
    void aoMorrer(Solo &s) override;
};

#endif