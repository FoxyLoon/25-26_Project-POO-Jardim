#ifndef CACTO_H
#define CACTO_H

#include "Planta.h"

class Cacto : public Planta {
public:
    Cacto();
    virtual ~Cacto();
    virtual char simbolo() const override;
};

#endif
