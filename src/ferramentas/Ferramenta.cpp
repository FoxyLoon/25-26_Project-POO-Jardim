#include "Ferramenta.h"

int Ferramenta::proximo_ID = 1;

Ferramenta::Ferramenta(string nome, char simbolo) : nomeFerramenta(nome), simboloFerramenta(simbolo)
{
    numeroSerieFerramenta_ID = proximo_ID++;
}

int Ferramenta::getNumeroSerie() const
{
    return numeroSerieFerramenta_ID;
}

string Ferramenta::getNome() const
{
    return nomeFerramenta;
}

char Ferramenta::getSimbolo() const
{
    return simboloFerramenta;
}