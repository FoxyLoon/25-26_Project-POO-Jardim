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
    virtual ~Tesoura();

    virtual char simbolo() const override;
    virtual std::string nome() const override;
    virtual bool aplicar(Solo &solo) override;
    virtual bool estaUtilizavel() const override;
    virtual std::string getInfo() const override;
};

#endif