#ifndef PLANTA_H
#define PLANTA_H

#include <string>
#include "../Settings.h"

// Forward declaration
class Solo;

/**
 * Classe abstrata Planta - Base para todas as espécies de plantas
 *
 * ARQUITETURA HÍBRIDA:
 * - Métodos utilitários (da V2) para transferência de recursos
 * - Padrão de 4 passos (da V1) para clareza do ciclo de vida
 */
class Planta {
public:
    // Construtor
    explicit Planta(int agua_inicial, int nutrientes_inicial,
                   char simbolo, const std::string& beleza);
    virtual ~Planta() = default;

    // ========================================================
    // INTERFACE PÚBLICA
    // ========================================================

    // Getters básicos
    char getSimbolo() const;
    const std::string& getBeleza() const;
    int getAguaInterna() const;
    int getNutrientesInternos() const;

    // Informação detalhada (para comandos lplanta, lplantas)
    virtual std::string getInfo() const = 0;

    // ========================================================
    // CICLO DE VIDA DA PLANTA (chamado pelo Jardim)
    // ========================================================

    /**
     * Metodo principal chamado a cada instante
     * Executa o padrão de 4 passos
     */
    void processaInstante(Solo& s);

    /**
     * Verifica se a planta deve morrer
     * IMPORTANTE: Algumas condições precisam ser verificadas pelo Jardim
     * (ex: Roseira cercada por vizinhos)
     */
    virtual bool verificaMorte(const Solo& s) const = 0;

    /**
     * Chamado quando a planta morre
     * Devolve recursos ao solo conforme a espécie
     */
    virtual void aoMorrer(Solo& s) = 0;

    // ========================================================
    // MULTIPLICAÇÃO
    // ========================================================

    /**
     * Verifica se tem recursos para multiplicar
     */
    virtual bool podeMultiplicar() const = 0;

    /**
     * Cria uma nova planta (semente)
     * A planta-mãe deve ajustar seus recursos internos aqui
     */
    virtual Planta* gerarSemente() = 0;

protected:
    // ========================================================
    // MÉTODOS UTILITÁRIOS (V2) - Usados pelos derivados
    // ========================================================

    /**
     * Tenta obter recursos do solo
     * Retorna quantidade efetivamente obtida (pode ser menor que pedido)
     */
    int obterAgua(Solo& solo, int quantidade);
    int obterNutrientes(Solo& solo, int quantidade);

    /**
     * Deposita recursos no solo
     * Retorna quantidade efetivamente depositada
     */
    int depositarAgua(Solo& solo, int quantidade);
    int depositarNutrientes(Solo& solo, int quantidade);

    // Manipulação direta dos recursos internos
    void setAguaInterna(int valor);
    void setNutrientesInternos(int valor);
    void adicionarAguaInterna(int quantidade);
    void adicionarNutrientesInternos(int quantidade);
    void removerAguaInterna(int quantidade);
    void removerNutrientesInternos(int quantidade);

    // ========================================================
    // PADRÃO DE 4 PASSOS (V1) - Interface clara do ciclo
    // ========================================================

    /**
     * Passo 1: Remove recursos do solo
     * Implementado pelas classes derivadas
     */
    virtual void removeRecursosSolo(Solo& s) = 0;

    /**
     * Passo 2: Adiciona recursos removidos à planta
     * Implementado pelas classes derivadas
     */
    virtual void adicionaRecursosPlanta(Solo& s) = 0;

    /**
     * Passo 3: Metabolismo - perde recursos internos
     * Implementado pelas classes derivadas
     */
    virtual void perdeRecursosInternos() = 0;

    /**
     * Passo 4: Fornece recursos ao solo (simbiose)
     * Implementado pelas classes derivadas
     */
    virtual void forneceRecursosSolo(Solo& s) = 0;

private:
    int aguaInterna;
    int nutrientesInternos;
    char simbolo;
    std::string beleza; // "BONITA", "FEIA", "NEUTRA"
};

#endif