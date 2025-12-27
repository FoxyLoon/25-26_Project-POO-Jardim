#ifndef ADUBO_H
#define ADUBO_H

#include "Ferramenta.h"
#include "../Settings.h"

/*
 * PACOTE DE ADUBO
 * - Aumenta nutrientes do solo em 10 unidades
 * - Capacidade inicial: 100 unidades
 * - Quando acaba, é levado pelo vento
 * - Símbolo: 'a'
 */
class Adubo : public Ferramenta {
private:
    int quantidadeDisponivel;

public:
    Adubo();
    virtual ~Adubo();

    virtual char simbolo() const override;
    virtual std::string nome() const override;
    virtual bool aplicar(Solo &solo) override;
    virtual bool estaUtilizavel() const override;
    virtual std::string getInfo() const override;

    int getQuantidadeDisponivel() const { return quantidadeDisponivel; }
};

#endif