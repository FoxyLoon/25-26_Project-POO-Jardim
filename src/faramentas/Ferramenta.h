#ifndef FERRAMENTA_H
#define FERRAMENTA_H

#include <string>

// Classe abstrata Ferramenta
class Ferramenta {
public:
    Ferramenta(int id);
    virtual ~Ferramenta();
    virtual char simbolo() const = 0;
    int getId() const;
protected:
    int id;
};

#endif
