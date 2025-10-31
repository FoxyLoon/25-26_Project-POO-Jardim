#ifndef PLANTA_H
#define PLANTA_H

#include <string>

// Classe abstrata Planta com interface mínima
class Planta {
public:
    Planta();
    virtual ~Planta();
    virtual char simbolo() const = 0;
    // propriedades internas (água e nutrientes) disponibilizadas na Meta 2
};

#endif
