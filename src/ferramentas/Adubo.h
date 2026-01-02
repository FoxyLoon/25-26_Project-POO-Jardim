#ifndef ADUBO_H
#define ADUBO_H

#include "Ferramenta.h"

/*
 * PACOTE DE ADUBO
 * - Capacidade: 100 unidades
 * - Dose Por Uso: 10 unidades
 * - Aumenta nutrientes do solo em 10 unidades
 * - Quando acaba, é levado pelo vento
 * - Símbolo: 'a'
 */

class Adubo : public Ferramenta
{
    int nutrientesDisponiveis;

public:
    Adubo();
    virtual ~Adubo() = default;

    void usar() override;
    void aplicarNoSolo(Solo& s) override;
    bool estaGasta() const override;
    string getInfo() const override;
};
#endif