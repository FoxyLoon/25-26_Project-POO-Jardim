#include "Planta.h"

#include <utility>
#include "../jardim/Solo.h"

Planta::Planta(string nome, int agua_inicial, int nutrientes_inicial, char simbolo, string  beleza)
    : nomePlanta(std::move(nome)),aguaInterna(agua_inicial), nutrientesInternos(nutrientes_inicial), simbolo(simbolo), beleza(std::move(beleza)) {}

// ========================================================

// Informações sobre a planta

// Obtem o nome da planta
string Planta::getNomePlanta() const
{
    return nomePlanta;
}

// Obtem o simbolo da planta
char Planta::getSimboloPlanta() const
{
    return simbolo;
}

// Obtem o tipo de beleza da planta
string Planta::getBelezaPlanta() const
{
    return beleza;
}

// ========================================================

// Interação com a planta

// Devolve a quantidade de água interna na planta
int Planta::getAguaInterna() const
{
    return aguaInterna;
}

// Define diretamente a quantidade de água interna na planta
void Planta::setAguaInterna(int valor)
{
    // Garante que o valor não é negativo
    aguaInterna = (valor < 0) ? 0 : valor;
}

// Devolve a quantidade de nutrientes internos na planta
int Planta::getNutrientesInternos() const
{
    return nutrientesInternos;
}

// Define diretamente a quantidade de nutrientes internos na planta
void Planta::setNutrientesInternos(int valor)
{
    // Garante que o valor não é negativo
    nutrientesInternos = (valor < 0) ? 0 : valor;
}

// Adiciona uma quantidade de água interna na planta
void Planta::adicionarAguaInterna(int quantidade)
{
    setAguaInterna(aguaInterna + quantidade);
}

// Adiciona uma quantidade de nutrientes internos da planta
void Planta::adicionarNutrientesInternos(int quantidade)
{
    setNutrientesInternos(nutrientesInternos + quantidade);
}

// Remove uma quantidade de água interna na planta
void Planta::removerAguaInterna(int quantidade)
{
    setAguaInterna(aguaInterna - quantidade);
}

// Remove uma quantidade de nutrientes internos na planta
void Planta::removerNutrientesInternos(int quantidade)
{
    setNutrientesInternos(nutrientesInternos - quantidade);
}

// ========================================================

// Interação com o Solo

// Obtem (remove) uma quantidade de água do solo
int Planta::obterAgua(Solo &solo, int quantidade)
{
    int aguaDisponivel = solo.getAgua();
    int aguaRemovidaDoSolo;
    if (aguaDisponivel < quantidade)
    {
        aguaRemovidaDoSolo = aguaDisponivel;
    }
    else
    {
        aguaRemovidaDoSolo = quantidade;
    }
    solo.setAgua(aguaDisponivel - aguaRemovidaDoSolo);
    return aguaRemovidaDoSolo;
}

// Obtem (remove) uma quantidade de nutrientes do solo
int Planta::obterNutrientes(Solo &solo, int quantidade)
{
    int nutrientesDisponiveis = solo.getNutrientes();
    int nutrientesRemovidosDoSolo;
    if (nutrientesDisponiveis < quantidade)
    {
        nutrientesRemovidosDoSolo = nutrientesDisponiveis;
    }
    else
    {
        nutrientesRemovidosDoSolo = quantidade;
    }
    solo.setNutrientes(nutrientesDisponiveis - nutrientesRemovidosDoSolo);
    return nutrientesRemovidosDoSolo;
}

// Deposita (adiciona) uma quantidade de água no solo
int Planta::depositarAgua(Solo &solo, int quantidade)
{
    solo.setAgua(solo.getAgua() + quantidade);
    return quantidade;
}

// Deposita (adiciona) uma quantidade de nutrientes no solo
int Planta::depositarNutrientes(Solo &solo, int quantidade)
{
    solo.setNutrientes(solo.getNutrientes() + quantidade);
    return quantidade;
}

// ========================================================

// Processamento de cada instante

void Planta::processaInstante(Solo &s)
{
    removeRecursosSolo(s);
    adicionaRecursosPlanta(s);
    envelhecimento();
    removeRecursosPlanta();
    adicionaRecursosSolo(s);
}
