#ifndef ERVADANINHA_H
#define ERVADANINHA_H

#include "Planta.h"

class ErvaDaninha : public Planta {
public:
    ErvaDaninha();
    virtual ~ErvaDaninha();
    virtual char simbolo() const override;
};

#endif
