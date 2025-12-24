#include "Ferramenta.h"
#include "Regador.h"
#include "Adubo.h"
#include "Tesoura.h"
#include "FerramentaZ.h"

// Inicialização do contador estático
int Ferramenta::proximoNumeroSerie = 1;

Ferramenta::Ferramenta() {
    numeroSerie = proximoNumeroSerie++;
}

Ferramenta::~Ferramenta() {}

Ferramenta* Ferramenta::criar(char tipo) {
    switch(tipo) {
    case 'g': return new Regador();
    case 'a': return new Adubo();
    case 't': return new Tesoura();
    case 'z': return new FerramentaZ();
    default: return nullptr;
    }
}