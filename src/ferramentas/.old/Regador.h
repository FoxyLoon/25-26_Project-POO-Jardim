#ifndef REGADOR_H
#define REGADOR_H

#include "Ferramenta.h"
#include "../Settings.h"

/*
 * REGADOR
 * - Aumenta água do solo em 10 unidades
 * - Capacidade: 200 unidades
 * - Quando acaba, é descartado
 * - Símbolo: 'g'
 */
class Regador : public Ferramenta {
private:
    int aguaDisponivel;

public:
    Regador();
    virtual ~Regador();

    virtual char simbolo() const override;
    virtual std::string nome() const override;
    virtual bool aplicar(Solo &solo) override;
    virtual bool estaUtilizavel() const override;
    virtual std::string getInfo() const override;

    int getAguaDisponivel() const { return aguaDisponivel; }
};

#endif