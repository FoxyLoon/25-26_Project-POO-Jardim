#ifndef PLANTA_H
#define PLANTA_H

#include <string>
#include <sstream>
#include "../jardim/Solo.h"
#include "../Settings.h"
using namespace std;

// Declaração de classe porque Planta depende do Solo
class Solo;

class Planta
{
private:
    int aguaInterna;
    int nutrientesInternos;
    char simbolo;
    string beleza; // "BONITA", "FEIA", "NEUTRA"
public:
    // Construtor
    explicit Planta(int agua_inicial, int nutrientes_inicial, char simbolo, const string beleza);
    virtual ~Planta() = default;

    // ========================================================

    // Informações sobre a planta
    const char getSimbolo() const;
    const string getBeleza() const;

    virtual string getInfo() const = 0;

    // ========================================================

    // ==== Planta ====

    // Obtem diretamente a água da planta
    int getAguaInterna() const;
    // Define diretamente a água da planta
    void setAguaInterna(int valor);

    // Obtem diretamente os nutrientes da planta
    int getNutrientesInternos() const;
    // Define diretamente os nutrientes da planta
    void setNutrientesInternos(int valor);

    // Adiciona água na planta
    void adicionarAguaInterna(int quantidade);
    // Adiciona nutrientes na planta
    void adicionarNutrientesInternos(int quantidade);

    // Remove água da planta
    void removerAguaInterna(int quantidade);
    // Remove nutrientes da planta
    void removerNutrientesInternos(int quantidade);

    // ========================================================

    // ==== Solo ====

    // Obtem (remove) água do solo
    int obterAgua(Solo &solo, int quantidade);
    // Obtem (remove) nutrientes do solo
    int obterNutrientes(Solo &solo, int quantidade);

    // Deposita (adiciona) água no solo
    int depositarAgua(Solo &solo, int quantidade);
    // Deposita (adiciona) nutrientes no solo
    int depositarNutrientes(Solo &solo, int quantidade);

    // ========================================================

    // Processamento de Cada Instante (passado para a respetiva planta)

    // Executa os 4 métodos abaixo
    virtual void processaInstante(Solo &s);

    // Remove recursos do solo
    virtual void removeRecursosSolo(Solo &s) = 0;
    // Adiciona recursos removidos do solo à planta
    virtual void adicionaRecursosPlanta(Solo &s) = 0;

    // Remove recursos da planta
    virtual void removeRecursosPlanta() = 0;
    // Deposita recursos removidos da planta para o solo
    virtual void adicionaRecursosSolo(Solo &s) = 0;

    // ========================================================

    // ==== Multiplicação ====

    // Verifica se tem recursos para multiplicar
    virtual bool podeMultiplicar() const = 0;
    virtual Planta *gerarSemente() = 0;

    // ========================================================

    // ==== Morte ====

    // Verifica se a planta deve morrer
    virtual bool verificaMorte(const Solo &s) = 0;

    // Chama se a planta morrer no método verificaMorte
    // Devolve recursos ao solo
    virtual void aoMorrer(Solo &s) = 0;
};

#endif