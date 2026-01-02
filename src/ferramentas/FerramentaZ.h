#ifndef FERRAMENTAZ_H
#define FERRAMENTAZ_H

#include "Ferramenta.h"

/*
HARMONIZADOR DE SOLO (FerramentaZ)

Ferramenta tecnológica avançada que equilibra o solo para condições ideais.

Funcionamento:
- Analisa o solo e ajusta água e nutrientes para valores ótimos
- Valores ótimos: água = 90, nutrientes = 45
- Cada uso consome 1 carga de bateria
- Capacidade: 50 cargas
- Quando a bateria acaba, deve ser reciclada

Efeito:
- Se água < 90: adiciona até 15 unidades (aproxima do ótimo)
- Se água > 90: remove até 15 unidades (aproxima do ótimo)
- Se nutrientes < 45: adiciona até 10 unidades
- Se nutrientes > 45: remove até 10 unidades

Símbolo: 'z'
*/

class FerramentaZ : public Ferramenta
{
    int bateria;

public:
    FerramentaZ();
    virtual ~FerramentaZ() = default;

    void usar() override;
    void aplicarNoSolo(Solo &s) override;
    bool estaGasta() const override;
    string getInfo() const override;
};

#endif