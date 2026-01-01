// ========== Jardim.h ==========
#ifndef JARDIM_H
#define JARDIM_H

#include "Solo.h"
#include "../plantas/Planta.h"
#include "../ferramentas/Ferramenta.h"
#include "../jardineiro/Jardineiro.h"

/**
 * Classe Jardim - Grelha retangular de Solo
 *
 * IMPORTANTE: NÃO USA COLEÇÕES STANDARD para armazenamento do solo
 * Usa array dinâmico puro (Solo**)
 */
class Jardim {
public:
    Jardim(int l, int c);
    ~Jardim();

    // Desabilitar cópia (por agora)
    Jardim(const Jardim&) = delete;
    Jardim& operator=(const Jardim&) = delete;

    // Acesso e visualização
    Solo* getSolo(int l, int c);
    void mostraJardim(const Jardineiro& j) const;

    // Simulação
    void avancarInstante();

    // Getters
    int getLinhas() const { return linhas; }
    int getColunas() const { return colunas; }

    void criarFerramentaAleatoria();  // ✅ Nova funcionalidade


private:
    int linhas, colunas;
    Solo** area;  // ✅ Array dinâmico puro - SEM VECTOR!

    // Métodos auxiliares
    void processarPlantas();
    void processarMortes();
    void processarMultiplicacoes();
    void multiplicarPlanta(int l, int c, Planta* mae);
    bool estaCercada(int l, int c) const;
};

#endif