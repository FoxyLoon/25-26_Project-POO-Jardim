#ifndef JARDIM_H
#define JARDIM_H

#include "Solo.h"
#include "../jardineiro/Jardineiro.h"
#include "../../Settings.h"

// Representa o jardim (grelha retangular de Solo)
class Jardim {
private:
    int linhas, colunas;
    Solo **area;  // matriz dinâmica
public:
    Jardim(int l, int c);
    ~Jardim();

    void mostrar() const;
    void mostrarComJardineiro(const Jardineiro &j) const;

    // Acesso direto a posições
    Solo *getSolo(int l, int c);
};

#endif
