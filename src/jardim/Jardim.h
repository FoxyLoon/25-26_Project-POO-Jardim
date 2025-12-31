#ifndef JARDIM_H
#define JARDIM_H

#include "Solo.h"
#include <vector>
#include "../plantas/Planta.h"
#include "../ferramentas/Ferramenta.h"
#include "../jardineiro/Jardineiro.h"

using namespace std;

/**
 * Classe Jardim - Grelha retangular de Solo
 *
 * Responsabilidades:
 * - Armazenar posições de solo (matriz 2D)
 * - Inicializar jardim com valores aleatórios
 * - Visualizar estado atual
 * - Gerenciar ciclo de vida das plantas:
 *   * Processar instantes
 *   * Verificar mortes
 *   * Processar multiplicações
 */
class Jardim {
public:
    Jardim(int l, int c);
    ~Jardim();

    // ========================================================
    // ACESSO E VISUALIZAÇÃO
    // ========================================================

    /**
     * Acessa uma posição específica do jardim
     * Retorna nullptr se fora dos limites
     */
    Solo* getSolo(int l, int c);

    /**
     * Mostra o estado atual do jardim na consola
     * Inclui a posição do jardineiro se estiver no jardim
     */
    void mostraJardim(const Jardineiro& j) const;

    // ========================================================
    // SIMULAÇÃO
    // ========================================================

    /**
     * Avança 1 instante no tempo simulado
     * - Processa todas as plantas (ciclo de vida)
     * - Verifica e processa mortes
     * - Verifica e processa multiplicações
     */
    void avancarInstante();

    // Getters para dimensões
    int getLinhas() const { return linhas; }
    int getColunas() const { return colunas; }

private:
    int linhas, colunas;
    vector<vector<Solo>> area;

    // ========================================================
    // MÉTODOS AUXILIARES PRIVADOS
    // ========================================================

    /**
     * Processa o ciclo de vida de todas as plantas
     * (absorção, metabolismo, etc.)
     */
    void processarPlantas();

    /**
     * Verifica condições de morte e remove plantas mortas
     * Executa aoMorrer() antes de remover
     */
    void processarMortes();

    /**
     * Identifica plantas que podem multiplicar
     * e cria novas plantas em posições vizinhas
     */
    void processarMultiplicacoes();

    /**
     * Multiplica uma planta específica
     * - Encontra posição vizinha válida
     * - Cria nova planta (semente)
     * - Trata casos especiais (Erva Daninha mata vizinho)
     */
    void multiplicarPlanta(int l, int c, Planta* mae);

    /**
     * Verifica se uma posição está cercada por plantas
     * (todas as 4 posições ortogonais ocupadas)
     * Usado para condição de morte da Roseira
     */
    bool estaCercada(int l, int c) const;
};

#endif