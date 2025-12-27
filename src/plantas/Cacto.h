#ifndef CACTO_H
#define CACTO_H

#include "Planta.h"
#include "../Settings.h"

class Cacto : public Planta {
private:
    int instantesAguaExcessiva;      // contador para morte por água excessiva
    int instantesSemNutrientes;      // contador para morte por falta de nutrientes
    int totalNutrientesAbsorvidos;   // total absorvido durante a vida (para devolver ao morrer)

public:
    Cacto();
    virtual ~Cacto();

    virtual char simbolo() const override;
    virtual void atualizar(Solo &solo) override;

    // Verifica se o cacto deve morrer
    bool deveMorrer(const Solo &solo) const;

    // Verifica se pode e deve multiplicar-se
    bool podeMultiplicar() const;

    // Ao morrer, devolve nutrientes ao solo
    void morrer(Solo &solo);

    // Getters para debug/info
    int getInstantesAguaExcessiva() const { return instantesAguaExcessiva; }
    int getInstantesSemNutrientes() const { return instantesSemNutrientes; }
    int getTotalNutrientesAbsorvidos() const { return totalNutrientesAbsorvidos; }
};

#endif