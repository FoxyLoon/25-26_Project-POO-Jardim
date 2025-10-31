#ifndef REGADOR_H
#define REGADOR_H

#include "Ferramenta.h"

class Regador : public Ferramenta {
public:
    Regador(int id);
    virtual ~Regador();
    virtual char simbolo() const override;
};

#endif
