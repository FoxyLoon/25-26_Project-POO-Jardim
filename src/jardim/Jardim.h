#ifndef JARDIM_H
#define JARDIM_H

#include <vector>
#include "Solo.h"
#include "../ferramentas/Ferramenta.h"
// #include "../ferramentas/Regador.h"
// #include "../ferramentas/Adubo.h"
// #include "../ferramentas/Tesoura.h"
// #include "../ferramentas/FerramentaZ.h"

using namespace std;

class Jardim
{
private:
    int linhas;
    int colunas;
    Solo **area;

    // Funções auxiliares
    void processaRecursosPlantas() const;
    void processaMortes() const;
    void processaMultiplicacao() const;

    // Geração de ferramentas
    static Ferramenta *gerarFerramentaAleatoria();

public:
    explicit Jardim(int l, int c, bool criarFerramentas = true);
    ~Jardim();

    void avancaInstante() const;
    void mostraJardim() const;
    void processaFerramentasAleatorias() const;

    // Getters
    [[nodiscard]] int getLinhas() const;
    [[nodiscard]] int getColunas() const;
    [[nodiscard]] Solo &getSolo(int l, int c) const;
};

#endif