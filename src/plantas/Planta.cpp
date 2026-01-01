#include "Planta.h"

// Construtor
Planta::Planta(int agua_inicial, int nutrientes_inicial, char simbolo, const string beleza)
    : aguaInterna(agua_inicial), nutrientesInternos(nutrientes_inicial), simbolo(simbolo), beleza(beleza) {}

// ========================================================

// Informações sobre a planta

const char Planta::getSimbolo() const
{
    return simbolo;
}

const string Planta::getBeleza() const
{
    return beleza;
}

// ========================================================

// ==== Planta ====

// Obtem diretamente a água da planta
int Planta::getAguaInterna() const
{
    return aguaInterna;
}

// Define diretamente a água da planta
void Planta::setAguaInterna(int valor)
{
    aguaInterna = (valor < 0) ? 0 : valor;
}

// Obtem diretamente os nutrientes da planta
int Planta::getNutrientesInternos() const
{
    return nutrientesInternos;
}

// Define diretamente os nutrientes da planta
void Planta::setNutrientesInternos(int valor)
{
    nutrientesInternos = (valor < 0) ? 0 : valor;
}

// Adiciona água na planta
void Planta::adicionarAguaInterna(int quantidade)
{
    if (quantidade > 0)
    {
        aguaInterna += quantidade;
    }
}

// Adiciona nutrientes na planta
void Planta::adicionarNutrientesInternos(int quantidade)
{
    if (quantidade > 0)
    {
        nutrientesInternos += quantidade;
    }
}

// Remove água da planta
void Planta::removerAguaInterna(int quantidade)
{
    if (quantidade > 0)
    {
        aguaInterna -= quantidade;
        if (aguaInterna < 0)
            aguaInterna = 0;
    }
}

// Remove nutrientes da planta
void Planta::removerNutrientesInternos(int quantidade)
{
    if (quantidade > 0)
    {
        nutrientesInternos -= quantidade;
        if (nutrientesInternos < 0)
            nutrientesInternos = 0;
    }
}

// ========================================================

// ==== Solo ====

// Obtem (remove) água do solo
int Planta::obterAgua(Solo &solo, int quantidade)
{
    if (quantidade <= 0)
        return 0;

    // Pega até a quantidade pedida, ou o que houver disponível
    int retirada = min(quantidade, solo.getAgua());
    solo.removerAgua(retirada);
    adicionarAguaInterna(retirada);

    return retirada;
}

// Obtem (remove) nutrientes do solo
int Planta::obterNutrientes(Solo &solo, int quantidade)
{
    if (quantidade <= 0)
        return 0;

    int retirada = min(quantidade, solo.getNutrientes());
    solo.removerNutrientes(retirada);
    adicionarNutrientesInternos(retirada);

    return retirada;
}

// Deposita (adiciona) água no solo
int Planta::depositarAgua(Solo &solo, int quantidade)
{
    if (quantidade <= 0)
        return 0;

    // Não pode depositar mais do que tem
    int deposito = min(quantidade, getAguaInterna());
    removerAguaInterna(deposito);
    solo.adicionarAgua(deposito);

    return deposito;
}

// Deposita (adiciona) nutrientes no solo
int Planta::depositarNutrientes(Solo &solo, int quantidade)
{
    if (quantidade <= 0)
        return 0;

    int deposito = min(quantidade, getNutrientesInternos());
    removerNutrientesInternos(deposito);
    solo.adicionarNutrientes(deposito);

    return deposito;
}

// ========================================================

// Processamento de cada instante

void Planta::processaInstante(Solo &s)
{
    // Executa o ciclo
    removeRecursosSolo(s);     // 1. Consome do solo
    adicionaRecursosPlanta(s); // 2. Absorve para dentro
    removeRecursosPlanta();   // 3. Metabolismo
    adicionaRecursosSolo(s);    // 4. Produz para o solo (simbiose)
}