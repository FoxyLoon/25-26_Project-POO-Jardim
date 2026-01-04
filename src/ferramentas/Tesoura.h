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
    ~Tesoura() override = default;

    void usar() override;                   // Não faz nada
    void aplicarNoSolo(Solo& s) override;
    [[nodiscard]] bool estaGasta() const override;        // Sempre Falso
    [[nodiscard]] string getInfoFerramenta() const override;
    [[nodiscard]] string getInfoExtraFerramenta() const override;
};

#endif