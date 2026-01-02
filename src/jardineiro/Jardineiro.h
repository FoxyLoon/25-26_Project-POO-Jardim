#ifndef JARDINEIRO_H
#define JARDINEIRO_H

#include <vector>
#include <string>
#include "../jardim/Solo.h"
#include "../ferramentas/Ferramenta.h"
#include "../Settings.h"

class Jardineiro {
private:
    int linha, coluna;
    bool estaNoJardim;
    
    std::vector<Ferramenta*> inventario;
    Ferramenta* ferramentaNaMao;

    int movimentosRestantes;
    int entradasSaidasRestantes;
    int plantacoesRestantes;
    int colheitasRestantes;

public:
    Jardineiro();
    virtual ~Jardineiro();

    void reiniciarTurno();

    // Verificadores de Estado e Recursos
    bool verificarPresenca() const;
    bool podeMovimentar();
    bool podeEntrarSair();
    bool podePlantar();
    bool podeColher();

    // Ações de Movimento e Jardim
    void usaMovimento(int novaL, int novaC, int maxL, int maxC, std::string direcao);
    void usaEntrarSair(int l, int c, int maxL, int maxC);
    void usaPlantar(Solo& s, Planta* novaPlanta);
    void usaColher(Solo& s);

    // Gestão de Inventário
    void adicionarFerramenta(Ferramenta* f);
    void removerFerramenta(int indice);
    void selecionarFerramenta(int indice);
    void largarFerramenta();
    void listarFerramentas() const;
    Ferramenta* getFerramentaNaMao() const;

    void processaFerramentaAutomatica(Solo& s);
    
    // Getters
    bool getEstaNoJardim() const;
    int getLinha() const;
    int getColuna() const;
};

#endif