#ifndef PLANTA_H
#define PLANTA_H

#include <string>
#include "../jardim/Solo.h"

// Classe abstrata Planta com interface mínima
class Planta {
public:
    // Construtor que permite valores iniciais para água/nutrientes e beleza (string)
    explicit Planta(int agua_inicial = 0, int nutrientes_inicial = 0, const std::string &beleza = "NEUTRA");
    virtual ~Planta();

    // símbolo usado na representação do jardim
    virtual char simbolo() const = 0;

    // getters (nomes no formato get<Atributo>)
    int getAguaInterna() const;
    int getNutrientesInternos() const;
    const std::string &getBeleza() const;

    // métodos para interagir com o solo: tentam transferir até "quantidade" unidades
    // retornam a quantidade efetivamente transferida
    int obterAgua(Solo &solo, int quantidade);
    int obterNutrientes(Solo &solo, int quantidade);
    int depositarAgua(Solo &solo, int quantidade);
    int depositarNutrientes(Solo &solo, int quantidade);

    // hook virtual para comportamento específico de cada espécie (p.ex. crescer, gastar recursos)
    virtual void atualizar(Solo &solo);

    // Métodos para classes derivadas manipularem os dados de forma controlada
    void setAguaInterna(int valor);
    void setNutrientesInternos(int valor);
    void adicionarAguaInterna(int quantidade);
    void adicionarNutrientesInternos(int quantidade);
    void removerAguaInterna(int quantidade);
    void removerNutrientesInternos(int quantidade);

private:
    // Dados privados - encapsulamento correto
    int aguaInterna;
    int nutrientesInternos;
    std::string beleza;
};

#endif