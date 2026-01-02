#ifndef JARDIM_H
#define JARDIM_H

#include <vector>
#include "Solo.h"
#include "../ferramentas/Regador.h"
#include "../ferramentas/Adubo.h"
#include "../ferramentas/Tesoura.h"
#include "../ferramentas/FerramentaZ.h"

using namespace std;

class Jardim
{
private:
    int linhas;
    int colunas;
    Solo **area;

    // Funções auxiliares
    void processaRecursosPlantas();
    void processaMortes();
    void processaMultiplicacao();
    void processaFerramentasAleatorias();

    // Geração de ferramentas
    Ferramenta *gerarFerramentaAleatoria();

public:
    explicit Jardim(int l, int c);
    ~Jardim();

    void avancaInstante();
    void mostraJardim() const;

    // Getters
    int getLinhas() const { return linhas; }
    int getColunas() const { return colunas; }
    Solo &getSolo(int l, int c) { return area[l][c]; }
};

#endif