#include "Solo.h"
#include <cstdlib>


Solo::Solo() : planta(nullptr), ferramenta(nullptr), temJardineiro(false)
{
    int aguaMinima = Settings::Jardim::agua_min;
    int aguaMaxima = Settings::Jardim::agua_max;
    int nutrientesMinimo = Settings::Jardim::nutrientes_min;
    int nutrientesMaximo = Settings::Jardim::nutrientes_max;

    int aguaAleatoria = aguaMinima + (rand() % (aguaMaxima - aguaMinima + 1));
    int nutriAleatorio = nutrientesMinimo + (rand() % (nutrientesMaximo - nutrientesMinimo + 1));

    agua = aguaAleatoria;
    nutrientes = nutriAleatorio;
}

// ========================================================

// Getters e Setters de recursos
int Solo::getAgua() const
{
    return agua;
}

void Solo::setAgua(int valor)
{
    int valorFinal = (valor < 0) ? 0 : valor;
    agua = valorFinal;
}

int Solo::getNutrientes() const
{
    return nutrientes;
}

void Solo::setNutrientes(int valor)
{
    int valorFinal = (valor < 0) ? 0 : valor;
    nutrientes = valorFinal;
}

// ========================================================

// Gestão de recursos (adição/remoção)
void Solo::adicionarAgua(int quantidade)
{
    int novoValor = agua + quantidade;
    setAgua(novoValor);
}

void Solo::removerAgua(int quantidade)
{
    int novoValor = agua - quantidade;
    setAgua(novoValor);
}

void Solo::adicionarNutrientes(int quantidade)
{
    int novoValor = nutrientes + quantidade;
    setNutrientes(novoValor);
}

void Solo::removerNutrientes(int quantidade)
{
    int novoValor = nutrientes - quantidade;
    setNutrientes(novoValor);
}

// ========================================================

// Gestão da Planta
bool Solo::temPlanta() const
{
    bool existe = (planta != nullptr);
    return existe;
}

void Solo::setPlanta(Planta *p)
{
    if (!temPlanta())
    {
        planta = p;
    }
}

Planta *Solo::getPlanta() const
{
    return planta;
}

Planta *Solo::removerPlanta()
{
    if (planta == nullptr)
    {
        return nullptr;
    }

    // Guardar o ponteiro numa variável temporária
    Planta *temp = planta;

    // Retirar a referência do solo (ponteiro a null)
    // Importante: NÃO FAZER 'delete planta', senão o jardineiro
    // recebe um ponteiro para memória apagada!
    planta = nullptr;

    // Devolve o ponteiro para o Simulador/Jardineiro
    return temp;
}

// ========================================================

// Gestão da Ferramenta
bool Solo::temFerramenta() const
{
    bool existe = (ferramenta != nullptr);
    return existe;
}

void Solo::setFerramenta(Ferramenta *f)
{
    if (!temFerramenta())
    {
        ferramenta = f;
    }
}

Ferramenta *Solo::getFerramenta() const
{
    return ferramenta;
}

Ferramenta *Solo::removerFerramenta()
{
    if (ferramenta == nullptr)
    {
        return nullptr;
    }

    // Guardar o ponteiro numa variável temporária
    Ferramenta *temp = ferramenta;

    // Retirar a referência do solo (ponteiro a null)
    // Importante: NÃO FAZER 'delete ferramenta', senão o jardineiro
    // recebe um ponteiro para memória apagada!
    ferramenta = nullptr;

    // Devolver o ponteiro para o Simulador/Jardineiro
    return temp;
}

// ========================================================

// Gestão do Jardineiro (entrada/saída/movimento)
bool Solo::possuiJardineiro() const
{
    return temJardineiro;
}

void Solo::setJardineiro(bool estado)
{
    temJardineiro = estado;
}

// ========================================================

// Verificações de estado e símbolos
bool Solo::estaVazio() const
{
    bool semPlanta = (planta == nullptr);
    bool semFerramenta = (ferramenta == nullptr);
    bool resultado = (semPlanta && semFerramenta);
    return resultado;
}

char Solo::getSimboloPrioritario() const
{
    if (temJardineiro)
        return '*';

    if (temPlanta())
    {
        char simbPlanta = planta->getSimbolo();
        return simbPlanta;
    }

    if (temFerramenta())
    {
        char simbFerramenta = ferramenta->getSimbolo();
        return simbFerramenta;
    }

    char simbVazio = ' ';
    return simbVazio;
}

string Solo::getInfoSolo() const
{
    int valAgua = getAgua();
    int valNutri = getNutrientes();

    ostringstream oss;
    oss << "Água: " << valAgua << " | Nutrientes: " << valNutri;

    if (temPlanta())
    {
        string infoP = planta->getInfo();
        oss << " | Planta: " << infoP;
    }
    else
    {
        oss << " | Planta: Vazio";
    }

    if (temFerramenta())
    {
        oss << " | Ferramenta: Presente";
    }
    else
    {
        oss << " | Ferramenta: Vazio";
    }

    if (temJardineiro)
    {
        oss << " | [Jardineiro no Local]";
    }

    string infoFinal = oss.str();
    return infoFinal;
}