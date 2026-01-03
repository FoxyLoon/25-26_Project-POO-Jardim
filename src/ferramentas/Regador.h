#ifndef REGADOR_H
#define REGADOR_H

#include "Ferramenta.h"

/*
 * REGADOR
 * - Capacidade: 200 unidades
 * - Dose Por Uso: 10 unidades
 * - Aumenta a água do Solo em 10 Unidades
 * - Quando acaba, é descartado
 * - Símbolo: 'g'
 */

class Regador : public Ferramenta
{
    int aguaDisponivel;

public:
    Regador();
    virtual ~Regador() = default;

    void usar() override;
    void aplicarNoSolo(Solo &s) override;
    bool estaGasta() const override;
    string getInfoFerramenta() const override;
    string getInfoExtraFerramenta() const override;
};
#endif