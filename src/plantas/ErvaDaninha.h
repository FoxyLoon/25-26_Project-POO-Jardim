// ========== ErvaDaninha.h ==========
#ifndef ERVADANINHA_H
#define ERVADANINHA_H

#include "Planta.h"

/**
 * ERVA DANINHA
 * Beleza: FEIA
 *
 * Características:
 * - Inicialmente: 5 água, 5 nutrientes
 * - Absorve 1 água e 1 nutriente por instante
 * - Morre sozinha passados 60 instantes
 * - Multiplica-se a cada 5 instantes se nutrientes > 30
 * - Multiplicação: MATA a planta no destino
 * - Nova planta: 5 água, 5 nutrientes
 * - Original NÃO perde recursos na multiplicação
 */
class ErvaDaninha : public Planta {
private:
    int idade;
    int instantesDesdeUltimaMultiplicacao;

public:
    ErvaDaninha();
    virtual ~ErvaDaninha() = default;

    // Interface obrigatória
    std::string getInfo() const override;
    bool verificaMorte(const Solo& s) const override;
    void aoMorrer(Solo& s) override;
    bool podeMultiplicar() const override;
    Planta* gerarSemente() override;

    // Reseta contador após multiplicação
    void resetarMultiplicacao();

protected:
    // Padrão de 4 passos
    void removeRecursosSolo(Solo& s) override;
    void adicionaRecursosPlanta(Solo& s) override;
    void perdeRecursosInternos() override;
    void forneceRecursosSolo(Solo& s) override;
};

#endif