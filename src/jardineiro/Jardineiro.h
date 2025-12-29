#ifndef JARDINEIRO_H
#define JARDINEIRO_H

#include <vector>
#include "../ferramentas/Ferramenta.h"
#include "../jardim/Solo.h"
#include "../Settings.h"

// Representa o jardineiro e a sua posição dentro ou fora do jardim
class Jardineiro {
public:
    Jardineiro();
    ~Jardineiro();

    // ========================================================
    // Movimento e Posição
    // ========================================================

    void entraNoJardim(int l, int c);
    void moveNoJardim(int l, int c);
    void saiDoJardim();

    bool isNoJardim() const;
    int getLinha() const;
    int getColuna() const;

    // ========================================================
    // Sistema de Inventário
    // ========================================================

    // Adicionar ferramenta ao inventário (quando apanha ou compra)
    void adicionarFerramenta(Ferramenta* f);

    // Remover ferramenta do inventário pelo número de série
    bool removerFerramenta(int numeroSerie);

    // Colocar ferramenta na mão (do inventário)
    bool pegarFerramenta(int numeroSerie);

    // Tirar ferramenta da mão (volta para inventário)
    void largarFerramenta();

    // Aplicar ferramenta que está na mão (se houver)
    void aplicarFerramentaSeNaMao(Solo &solo);

    // Getters do inventário
    Ferramenta* getFerramentaNaMao() const;
    const std::vector<Ferramenta*>& getInventario() const;

    // Listar todas as ferramentas (inventário + mão)
    void listarFerramentas() const;

    // ========================================================
    // Contadores de Ações (limites por turno)
    // ========================================================

    // Resetar todos os contadores (chamado no início de cada instante)
    void resetarContadores();

    // Verificar se pode fazer ação
    bool podeMovimentar() const;
    bool podeEntrarSair() const;
    bool podePlantar() const;
    bool podeColher() const;

    // Usar/gastar uma ação
    void usarMovimento();
    void usarEntradaSaida();
    void usarPlantacao();
    void usarColheita();

    // Getters dos contadores (para debug/info)
    int getMovimentosRestantes() const { return movimentosRestantes; }
    int getEntradasSaidasRestantes() const { return entradasSaidasRestantes; }
    int getPlantacoesRestantes() const { return plantacoesRestantes; }
    int getColheitasRestantes() const { return colheitasRestantes; }

private:
    // Posição e estado
    bool noJardim;
    int linha, coluna;

    // Inventário de ferramentas
    std::vector<Ferramenta*> inventario;
    Ferramenta* ferramentaNaMao;

    // Contadores de ações por turno
    int movimentosRestantes;
    int entradasSaidasRestantes;
    int plantacoesRestantes;
    int colheitasRestantes;

    // Método auxiliar para encontrar ferramenta por número de série
    int encontrarFerramentaNoInventario(int numeroSerie);
};

#endif