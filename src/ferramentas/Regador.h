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
    ~Regador() override = default;

    void usar() override;
    void aplicarNoSolo(Solo &s) override;
    [[nodiscard]] bool estaGasta() const override;
    [[nodiscard]] string getInfoFerramenta() const override;
    [[nodiscard]] string getInfoExtraFerramenta() const override;
};
#endif