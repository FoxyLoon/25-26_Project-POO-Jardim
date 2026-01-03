#ifndef TESOURA_H
#define TESOURA_H

#include "Ferramenta.h"

/*
 * TESOURA DE PODA
 * - Elimina todas as plantas consideradas FEIAS na posição
 * - Nunca se desgasta (aço cromado)
 * - Símbolo: 't'
 */

class Tesoura : public Ferramenta {
public:
    Tesoura();
    virtual ~Tesoura() = default;

    void usar() override;                   // Não faz nada
    void aplicarNoSolo(Solo& s) override;
    bool estaGasta() const override;        // Sempre Falso
    string getInfoFerramenta() const override;
};

#endif