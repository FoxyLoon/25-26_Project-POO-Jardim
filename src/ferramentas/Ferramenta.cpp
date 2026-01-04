#include "Ferramenta.h"

#include <utility>
#include <sstream>

int Ferramenta::proximo_ID = 1;

Ferramenta::Ferramenta(string nome, char simbolo) : nomeFerramenta(std::move(nome)), simboloFerramenta(simbolo)
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

void Ferramenta::setNumeroSerie(int novoNumero)
{
    numeroSerieFerramenta_ID = novoNumero;
}