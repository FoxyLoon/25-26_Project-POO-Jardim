#include "Ferramenta.h"

int Ferramenta::proximo_ID = 1;

Ferramenta::Ferramenta(string nome, char simbolo) : nomeFerramenta(nome), simboloFerramenta(simbolo)
{
    numeroSerieFerramenta_ID = proximo_ID++;
}

int Ferramenta::getNumeroSerieFerramenta() const
{
    return numeroSerieFerramenta_ID;
}

string Ferramenta::getNomeFerramenta() const
{
    return nomeFerramenta;
}

char Ferramenta::getSimboloFerramenta() const
{
    return simboloFerramenta;
}