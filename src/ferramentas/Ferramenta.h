#ifndef FERRAMENTA_H
#define FERRAMENTA_H

#include <string>
#include "../jardim/Solo.h"

// Classe abstrata para ferramentas
class Ferramenta {
private:
    int numeroSerie;  // número único da ferramenta
    static int proximoNumeroSerie;  // contador estático para gerar números únicos

public:
    Ferramenta();
    virtual ~Ferramenta();

    // Símbolo visual da ferramenta
    virtual char simbolo() const = 0;

    // Nome da ferramenta (para listagens)
    virtual std::string nome() const = 0;

    // Ação da ferramenta (retorna true se ainda é utilizável, false se deve ser descartada)
    virtual bool aplicar(Solo &solo) = 0;

    // Verifica se a ferramenta ainda é utilizável
    virtual bool estaUtilizavel() const = 0;

    // Retorna informação detalhada sobre a ferramenta
    virtual std::string getInfo() const = 0;

    // Getter do número de série
    int getNumeroSerie() const { return numeroSerie; }

    // Factory method para criar ferramentas a partir de um tipo
    static Ferramenta* criar(char tipo);
};

#endif