#ifndef ERVADANINHA_H
#define ERVADANINHA_H

#include "Planta.h"

/*
ERVA DANINHA
Beleza: FEIA

Comportamento:
- Absorve recursos fixos do solo a cada instante.
- Não tem perda metabólica (não morre por falta de recursos).
- Morre apenas por idade (instantes de vida).
- Multiplica-se por tempo e recursos.
*/

class ErvaDaninha : public Planta
{
private:
    // Idade da Planta
    int idade;

    // Contador para condição de multiplicação
    int instantesDesdeUltimaMultiplicacao;

public:
    ErvaDaninha();
    virtual ~ErvaDaninha() = default;

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