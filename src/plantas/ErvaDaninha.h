#ifndef ERVADANINHA_H
#define ERVADANINHA_H

#include "Planta.h"
#include "../Settings.h"

class ErvaDaninha : public Planta {
private:
    int instantesVividos;              // conta quantos instantes a planta viveu
    int instantesDesdeUltimaMultiplicacao; // conta instantes desde última multiplicação

public:
    ErvaDaninha();
    virtual ~ErvaDaninha();

    virtual char simbolo() const override;
    virtual void atualizar(Solo &solo) override;

    // Verifica se deve morrer por idade
    bool deveMorrer() const;

    // Verifica se pode multiplicar-se (e mata a planta destino)
    bool podeMultiplicar() const;

    // Reseta o contador de multiplicação (chamado após multiplicar)
    void resetarMultiplicacao();

    // Getters para debug/info
    int getInstantesVividos() const { return instantesVividos; }
    int getInstantesDesdeUltimaMultiplicacao() const { return instantesDesdeUltimaMultiplicacao; }
};

#endif