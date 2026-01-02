#ifndef JARDINEIRO_H
#define JARDINEIRO_H

#include <vector>
#include <string>
#include <iostream>
#include "../jardim/Solo.h"
#include "../ferramentas/Ferramenta.h"
#include "../Settings.h"

using namespace std;

class Jardineiro {
private:
    int linha, coluna;
    bool estaNoJardim;

    vector<Ferramenta *> inventario;
    Ferramenta *ferramentaNaMao;

    int movimentosRestantes;
    int entradasSaidasRestantes;
    int plantacoesRestantes;
    int colheitasRestantes;

public:
    Jardineiro();
    virtual ~Jardineiro();

    void reiniciarTurno();

    // ========================================================
    // Verificadores de Estado e Recursos
    // ========================================================
    bool verificarPresenca() const;
    bool podeMovimentar();
    bool podeEntrarSair();
    bool podePlantar();
    bool podeColher();

    // Getters de Recursos (Limites)
    int getMovimentosRestantes() const;
    int getEntradasSaidasRestantes() const;
    int getPlantacoesRestantes() const;
    int getColheitasRestantes() const;

    // ========================================================
    // Ações de Movimento e Jardim
    // ========================================================
    void usaMovimento(int novaL, int novaC, string direcao);
    void usaEntrar(int l, int c);
    void usaSair();
    void usaPlantar(Solo &s, Planta *novaPlanta);
    void usaColher(Solo &s);

    // ========================================================
    // Gestão de Inventário
    // ========================================================
    void adicionarFerramenta(Ferramenta *f);
    void selecionarFerramenta(int indice);
    void largarFerramenta();
    Ferramenta* removerFerramenta(int indice);
    
    // Consultas de Inventário
    void listarFerramentas() const;
    Ferramenta* getFerramentaNaMao() const;
    void mostrarEstado() const;

    // Getters de Posição
    int getLinha() const;
    int getColuna() const;
    bool getEstaNoJardim() const;
};

#endif