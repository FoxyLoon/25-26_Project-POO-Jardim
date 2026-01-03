#ifndef PLANTA_H
#define PLANTA_H

#include <string>
#include <sstream>
#include "../jardim/Solo.h"
#include "../Settings.h"
using namespace std;

// Forward declaration para evitar dependências circulares no header
class Solo;

class Planta
{
private:
    int aguaInterna;
    int nutrientesInternos;
    string nomePlanta;
    char simbolo;
    string beleza;

public:
    // Construtor
    explicit Planta(const string nomePlanta, int agua_inicial, int nutrientes_inicial, char simbolo, const string beleza);
    virtual ~Planta() = default;

    // ========================================================

    // Informações sobre a planta

    const string getNomePlanta() const;
    const char getSimboloPlanta() const;
    const string getBelezaPlanta() const;
    virtual string getInfoPlanta() const = 0;
    virtual string getInfoExtraPlanta() const = 0;

    // ========================================================

    // Interação com a planta

    int getAguaInterna() const;
    void setAguaInterna(int valor);
    int getNutrientesInternos() const;
    void setNutrientesInternos(int valor);

    void adicionarAguaInterna(int quantidade);
    void adicionarNutrientesInternos(int quantidade);
    void removerAguaInterna(int quantidade);
    void removerNutrientesInternos(int quantidade);

    // ========================================================

    // Interação com o Solo

    int obterAgua(Solo &solo, int quantidade);
    int obterNutrientes(Solo &solo, int quantidade);
    int depositarAgua(Solo &solo, int quantidade);
    int depositarNutrientes(Solo &solo, int quantidade);

    // ========================================================

    // Processamento de cada instante
    virtual void processaInstante(Solo &s);

    // Interações Planta-Solo (implementados pelas espécies de plantas)
    virtual void removeRecursosSolo(Solo &s) = 0;
    virtual void adicionaRecursosPlanta(Solo &s) = 0;
    virtual void envelhecimento() = 0;
    virtual void removeRecursosPlanta() = 0;
    virtual void adicionaRecursosSolo(Solo &s) = 0;

    // ========================================================

    // Condições de Multiplicação (implementado na espécie da planta)
    virtual bool podeMultiplicar() const = 0;
    virtual Planta *gerarSemente() = 0;

    // ========================================================

    // Condições de Morte (implementado na espécie da planta)
    virtual bool verificaMorte(const Solo &s) = 0;
    virtual void aoMorrer(Solo &s) = 0;
};

#endif