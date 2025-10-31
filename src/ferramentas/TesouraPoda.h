#ifndef TESOURAPODA_H
#define TESOURAPODA_H

#include "Ferramenta.h"

class TesouraPoda : public Ferramenta {
public:
    TesouraPoda(int id);
    virtual ~TesouraPoda();
    virtual char simbolo() const override;
};

#endif
