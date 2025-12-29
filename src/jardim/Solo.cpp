#include "Solo.h"
#include "../plantas/Planta.h"
#include "../ferramentas/Ferramenta.h"

// Construtores
Solo::Solo() : agua(0), nutrientes(0), planta(nullptr), ferramenta(nullptr) {}

Solo::Solo(int agua_inicial, int nutrientes_iniciais)
    : agua(agua_inicial), nutrientes(nutrientes_iniciais), planta(nullptr), ferramenta(nullptr) {}

// Destrutor - NÃO liberta planta/ferramenta (responsabilidade do Jardim)
Solo::~Solo()
{
    // Não fazemos delete aqui - o Jardim é responsável pela gestão de memória
}

//===================================================================
//===================================================================
//===================================================================

// Gestão da Água
int Solo::getAgua() const
{
    return agua;
}

void Solo::setAgua(int valor)
{
    agua = (valor < 0) ? 0 : valor;
}

void Solo::adicionarAgua(int quantidade)
{
    if (quantidade > 0)
    {
        agua += quantidade;
    }
}

void Solo::removerAgua(int quantidade)
{
    if (quantidade > 0)
    {
        agua -= quantidade;
        if (agua < 0)
            agua = 0;
    }
}

//===================================================================
//===================================================================
//===================================================================

// Gestão dos Nutrientes
int Solo::getNutrientes() const
{
    return nutrientes;
}

void Solo::setNutrientes(int valor)
{
    nutrientes = (valor < 0) ? 0 : valor;
}

void Solo::adicionarNutrientes(int quantidade)
{
    if (quantidade > 0)
    {
        nutrientes += quantidade;
    }
}

void Solo::removerNutrientes(int quantidade)
{
    if (quantidade > 0)
    {
        nutrientes -= quantidade;
        if (nutrientes < 0)
            nutrientes = 0;
    }
}

//===================================================================
//===================================================================
//===================================================================

// Gestão de Planta
Planta *Solo::getPlanta() const
{
    return planta;
}

void Solo::setPlanta(Planta *p)
{
    planta = p;
}

bool Solo::temPlanta() const
{
    return planta != nullptr;
}

Planta *Solo::removerPlanta()
{
    Planta *temp = planta;
    planta = nullptr;
    return temp; // Retorna o ponteiro para o caller gerir a memória
}

//===================================================================
//===================================================================
//===================================================================

// Gestão de Ferramenta
Ferramenta *Solo::getFerramenta() const
{
    return ferramenta;
}

void Solo::setFerramenta(Ferramenta *f)
{
    ferramenta = f;
}

bool Solo::temFerramenta() const
{
    return ferramenta != nullptr;
}

Ferramenta *Solo::removerFerramenta()
{
    Ferramenta *temp = ferramenta;
    ferramenta = nullptr;
    return temp; // Retorna o ponteiro para o caller gerir a memória
}

//===================================================================
//===================================================================
//===================================================================

// Verifica se está vazio
bool Solo::estaVazio() const
{
    return !temPlanta() && !temFerramenta();
}

// Símbolo visível
char Solo::getSimboloVisivel() const
{
    // Prioridade de visualização: Planta > Ferramenta > vazio
    // (Jardineiro é tratado externamente na função mostrarComJardineiro)

    if (temPlanta())
    {
        return planta->simbolo();
    }

    if (temFerramenta())
    {
        return ferramenta->simbolo();
    }

    // Posição vazia
    return ' ';
}