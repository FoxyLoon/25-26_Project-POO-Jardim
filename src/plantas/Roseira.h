#ifndef ROSEIRA_H
#define ROSEIRA_H

#include "Planta.h"
#include "../Settings.h"

class Roseira : public Planta {
private:
    int totalAguaAbsorvida;        // total de água absorvida durante a vida
    int totalNutrientesAbsorvidos; // total de nutrientes absorvidos durante a vida

public:
    Roseira();
    virtual ~Roseira();

    virtual char simbolo() const override;
    virtual void atualizar(Solo &solo) override;

    // Verifica se a roseira deve morrer
    bool deveMorrer() const;

    // Verifica se pode multiplicar-se
    bool podeMultiplicar() const;

    // Ao morrer, devolve metade dos recursos ao solo
    void morrer(Solo &solo);

    // Preparar multiplicação: retorna água para a nova planta
    int prepararMultiplicacao();

    // Getters para debug/info
    int getTotalAguaAbsorvida() const { return totalAguaAbsorvida; }
    int getTotalNutrientesAbsorvidos() const { return totalNutrientesAbsorvidos; }
};

#endif