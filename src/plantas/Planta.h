#ifndef PLANTA_H
#define PLANTA_H

#include <string>
#include "../jardim/Solo.h"
using namespace std;

// Forward declaration para evitar dependências circulares no header
class Solo;

class Planta
{
private:
    const string nomePlanta;
    int aguaInterna;
    int nutrientesInternos;
    const char simbolo;
    const string beleza;

public:
    // Construtor
    explicit Planta(string nomePlanta, int agua_inicial, int nutrientes_inicial, char simbolo, string  beleza);
    virtual ~Planta() = default;

    // ========================================================

    // Informações sobre a planta

    [[nodiscard]] string getNomePlanta() const;
    [[nodiscard]] char getSimboloPlanta() const;
    [[nodiscard]] string getBelezaPlanta() const;
    [[nodiscard]] virtual string getInfoPlanta() const = 0;
    [[nodiscard]] virtual string getInfoExtraPlanta() const = 0;

    // ========================================================

    // Interação com a planta

    [[nodiscard]] int getAguaInterna() const;
    void setAguaInterna(int valor);
    [[nodiscard]] int getNutrientesInternos() const;
    void setNutrientesInternos(int valor);

    void adicionarAguaInterna(int quantidade);
    void adicionarNutrientesInternos(int quantidade);
    void removerAguaInterna(int quantidade);
    void removerNutrientesInternos(int quantidade);

    // ========================================================

    // Interação com o Solo

    static int obterAgua(Solo &solo, int quantidade);
    static int obterNutrientes(Solo &solo, int quantidade);
    static int depositarAgua(Solo &solo, int quantidade);
    static int depositarNutrientes(Solo &solo, int quantidade);

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
    [[nodiscard]] virtual bool podeMultiplicar() const = 0;
    virtual Planta *gerarSemente() = 0;

    // ========================================================

    // Condições de Morte (implementado na espécie da planta)
    virtual bool verificaMorte(const Solo &s) = 0;
    virtual void aoMorrer(Solo &s) = 0;
};

#endif