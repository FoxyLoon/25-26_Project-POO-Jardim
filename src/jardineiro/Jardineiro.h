#ifndef JARDINEIRO_H
#define JARDINEIRO_H

#include <vector>
#include <string>
#include "../jardim/Solo.h"
#include "../ferramentas/Ferramenta.h"

using namespace std;

class Jardineiro
{
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

    // ========================================================

    void reiniciarTurno();

    // ========================================================

    // Verificadores de Estado e Recursos

    [[nodiscard]] bool verificarPresenca() const;
    [[nodiscard]] bool podeMovimentar() const;
    [[nodiscard]] bool podeEntrarSair() const;
    [[nodiscard]] bool podePlantar() const;
    [[nodiscard]] bool podeColher() const;

    // ========================================================
    // ========================================================
    // ========================================================

    // Ações de Movimento e Jardim

    void usaMovimento(int novaL, int novaC, const string &direcao);
    void usaEntrar(int l, int c);
    void usaSair();
    void usaPlantar(Solo &s, Planta *novaPlanta);
    void usaColher(Solo &s);

    // ========================================================
    // ========================================================
    // ========================================================

    // Gestão de Inventário

    void adicionarFerramentaAoInventario(Ferramenta *f);
    void selecionarFerramentaDoInventario(int ID_Ferramenta);
    void depositarFerramentaDaMaoParaInventario();
    void removerFerramentaDoInventario(int ID_Ferramenta);

    // Consultas de Inventário
    void listarFerramentas() const;
    [[nodiscard]] Ferramenta *getFerramentaNaMao() const;
    void mostrarEstado() const;

    // ========================================================
    // ========================================================
    // ========================================================

    // Getters de Posição
    [[nodiscard]] int getLinha() const;
    [[nodiscard]] int getColuna() const;
    [[nodiscard]] bool getEstaNoJardim() const;
};

#endif