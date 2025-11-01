#include "Jardineiro.h"

Jardineiro::Jardineiro() : noJardim(false), linha(-1), coluna(-1) {}

void Jardineiro::entrarNoJardim(int l, int c) {
    noJardim = true;
    linha = l;
    coluna = c;
}

void Jardineiro::sairDoJardim() {
    noJardim = false;
    linha = coluna = -1;
}

bool Jardineiro::isNoJardim() const { return noJardim; }
int Jardineiro::getLinha() const { return linha; }
int Jardineiro::getColuna() const { return coluna; }

