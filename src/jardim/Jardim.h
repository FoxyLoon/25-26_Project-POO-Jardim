#ifndef JARDIM_H
#define JARDIM_H

#include "Solo.h"
#include <vector>

#include "../plantas/Planta.h"
#include "../ferramentas/Ferramenta.h"
#include "../jardineiro/Jardineiro.h"

using namespace std;


// Representa o jardim (grelha retangular de Solo)
class Jardim
{
public:
    Jardim(int l, int c);
    ~Jardim();

    void mostrar() const;
    void mostrarComJardineiro(const Jardineiro &j) const;

    // Acesso individual a cada posição do Jardim
    Solo *getSolo(int l, int c);

private:
    int linhas, colunas;
    vector<vector<Solo>> area;
};

#endif
