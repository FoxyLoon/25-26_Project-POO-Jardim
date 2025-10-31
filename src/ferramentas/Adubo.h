#ifndef ADUBO_H
#define ADUBO_H

#include "Ferramenta.h"

class Adubo : public Ferramenta {
public:
    Adubo(int id);
    virtual ~Adubo();
    virtual char simbolo() const override;
};

#endif
