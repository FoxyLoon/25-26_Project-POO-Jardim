#ifndef FERRAMENTA_H
#define FERRAMENTA_H

#include <string>
#include <sstream>
#include "../jardim/Solo.h"
using namespace std;

class Solo;

class Ferramenta
{
private:
    static int proximo_ID;
    int numeroSerieFerramenta_ID;
    string nomeFerramenta;
    char simboloFerramenta;

public:
    Ferramenta(string nome, char simbolo);
    virtual ~Ferramenta() = default;

    // Getters
    int getNumeroSerie() const;
    string getNome() const;
    char getSimbolo() const;
    virtual string getInfo() const = 0;

    // Aplica a ferramenta no solo
    virtual void aplicarNoSolo(Solo& s) = 0;

    // Usa a ferramenta
    virtual void usar() = 0;

    // Verifica se a ferramenta está gastada (Adubo, Regador))
    virtual bool estaGasta() const = 0;
};

#endif