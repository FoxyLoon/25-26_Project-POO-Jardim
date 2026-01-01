// ========== PlantaExotica.h ==========
#ifndef PLANTAEXOTICA_H
#define PLANTAEXOTICA_H

#include "Planta.h"

/**
 * BAMBU LUNAR (PlantaExotica)
 * Beleza: BONITA
 * Planta exótica importada do Oriente
 *
 * Fases de crescimento:
 * - JOVEM (0-20): Absorve 3 água, 2 nutrientes
 * - ADULTA (21-40): Dormência - não absorve nem produz
 * - MADURA (41+): Absorve recursos E produz 2 nutrientes para o solo
 *
 * Metabolismo: Perde 2 água e 1 nutriente por instante
 *
 * Morte:
 * - Água interna < 5, OU
 * - Nutrientes internos < 3, OU
 * - Idade >= 80 instantes
 *
 * Ao morrer: Devolve 75% dos recursos internos
 *
 * Multiplicação:
 * - Quando nutrientes > 70 E água > 60
 * - Multiplica em diagonal (NE, SE, SW, NW)
 * - Nova: 30 água, 30 nutrientes
 * - Original: mantém 50% dos recursos
 */
class PlantaExotica : public Planta {
private:
    int idade;

public:
    enum Fase { JOVEM, ADULTA, MADURA };

    PlantaExotica();
    virtual ~PlantaExotica() = default;

    // Interface obrigatória
    std::string getInfo() const override;
    bool verificaMorte(const Solo& s) const override;
    void aoMorrer(Solo& s) override;
    bool podeMultiplicar() const override;
    Planta* gerarSemente() override;

    // Mtodo auxiliar
    Fase getFase() const;

protected:
    // Padrão de 4 passos
    void removeRecursosSolo(Solo& s) override;
    void adicionaRecursosPlanta(Solo& s) override;
    void perdeRecursosInternos() override;
    void forneceRecursosSolo(Solo& s) override;
};

#endif