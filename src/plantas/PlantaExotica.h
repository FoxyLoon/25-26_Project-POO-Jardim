#ifndef PLANTAEXOTICA_H
#define PLANTAEXOTICA_H

#include "Planta.h"

/*
 * BAMBU LUNAR (PlantaExotica)
 * Planta exótica importada de um país distante no Oriente.
 * 
 * Características especiais:
 * - Beleza: BONITA
 * - Inicialmente: 30 água, 30 nutrientes
 * - Comportamento simbiótico: produz nutrientes para o solo
 * - Ciclos de crescimento: cresce em fases (jovem -> adulta -> madura)
 * - Multiplicação em espiral: multiplica para posições diagonais
 * 
 * A cada instante:
 * - Absorve 3 unidades de água do solo
 * - Absorve 2 unidades de nutrientes do solo
 * - Quando madura, produz 2 nutrientes para o solo (fotossíntese avançada)
 * - Perde 2 de água e 1 de nutrientes internos
 * 
 * Fases de crescimento:
 * - Jovem: 0-20 instantes (absorve recursos)
 * - Adulta: 21-40 instantes (equilíbrio)
 * - Madura: 41+ instantes (produz nutrientes)
 * 
 * Morre se:
 * - Água interna < 5, OU
 * - Nutrientes internos < 3, OU
 * - Viveu mais de 80 instantes (ciclo de vida completo)
 * 
 * Ao morrer: deixa 75% dos seus recursos no solo
 * 
 * Multiplica-se:
 * - Quando tem > 70 nutrientes E > 60 água
 * - Multiplica em diagonal (NE, SE, SW, NW) - padrão em espiral
 * - Nova planta: 30 água, 30 nutrientes
 * - Original: mantém 50% dos recursos
 */

class PlantaExotica : public Planta {
private:
    int instantesVividos;
    int ciclosMultiplicacao; // conta quantas vezes se multiplicou

public:
    PlantaExotica();
    virtual ~PlantaExotica();
    
    virtual char simbolo() const override;
    virtual void atualizar(Solo &solo) override;
    
    // Verifica fase de crescimento
    enum Fase { JOVEM, ADULTA, MADURA };
    Fase getFase() const;
    
    // Verifica se deve morrer
    bool deveMorrer() const;
    
    // Verifica se pode multiplicar
    bool podeMultiplicar() const;
    
    // Ao morrer, devolve 75% dos recursos ao solo
    void morrer(Solo &solo);
    
    // Prepara multiplicação (reduz recursos)
    void prepararMultiplicacao();
    
    // Getters
    int getInstantesVividos() const { return instantesVividos; }
    int getCiclosMultiplicacao() const { return ciclosMultiplicacao; }
};

#endif