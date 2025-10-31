#ifndef ROSEIRA_H
#define ROSEIRA_H

#include "Planta.h"

class Roseira : public Planta {
public:
    Roseira();
    virtual ~Roseira();
    virtual char simbolo() const override;
};

#endif
