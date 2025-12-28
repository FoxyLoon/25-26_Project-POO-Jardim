#include "Jardineiro.h"

Jardineiro::Jardineiro() : noJardim(false), linha(-1), coluna(-1) {}

Jardineiro::~Jardineiro()
{
    noJardim = false;
    linha = coluna = -1;
}

// Coloca o Jardineiro no Jardim e define os valores de linha e coluna
void Jardineiro::entraNoJardim(int l, int c)
{
    noJardim = true;
    moveNoJardim(l, c);
}

// Define os valores de linha e coluna
void Jardineiro::moveNoJardim(int l, int c)
{
    linha = l;
    coluna = c;
}

// Remove o Jardineiro do Jardim e define os valores de linha e coluna para -1
void Jardineiro::saiDoJardim()
{
    noJardim = false;
    linha = coluna = -1;
}

// Retorna se o Jardineiro está ou não no Jardim
bool Jardineiro::isNoJardim() const { return noJardim; }

// Retorna a linha atual do Jardineiro no Jardim
int Jardineiro::getLinha() const { return linha; }

// Retorna a coluna atual do Jardineiro no Jardim
int Jardineiro::getColuna() const { return coluna; }
