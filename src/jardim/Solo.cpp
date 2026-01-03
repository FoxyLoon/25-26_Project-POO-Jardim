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

// Obtem diretamente a quantidade de água do solo
int Solo::getAgua() const
{
    return agua;
}

// Define diretamente a quantidade de água do solo
void Solo::setAgua(int valor)
{
    int valorFinal = (valor < 0) ? 0 : valor;
    agua = valorFinal;
}

// Obtem a direntamente a quantidade de nutrientes do solo
int Solo::getNutrientes() const
{
    return nutrientes;
}

// Define diretamente a quantidade de nutrientes do solo
void Solo::setNutrientes(int valor)
{
    int valorFinal = (valor < 0) ? 0 : valor;
    nutrientes = valorFinal;
}

// ========================================================

// Gestão de recursos (adição/remoção)

// Adiciona agua ao solo
void Solo::adicionarAgua(int quantidade)
{
    int novoValor = agua + quantidade;
    setAgua(novoValor);
}

// Remove agua do solo
void Solo::removerAgua(int quantidade)
{
    int novoValor = agua - quantidade;
    setAgua(novoValor);
}

// Adiciona nutrientes ao solo
void Solo::adicionarNutrientes(int quantidade)
{
    int novoValor = nutrientes + quantidade;
    setNutrientes(novoValor);
}

// Remove nutrientes do solo
void Solo::removerNutrientes(int quantidade)
{
    int novoValor = nutrientes - quantidade;
    setNutrientes(novoValor);
}

// ========================================================

// Gestão da Planta

// Verifica se existe uma planta no solo
bool Solo::temPlanta() const
{
    bool existe = (planta != nullptr);
    return existe;
}

// Define uma planta no solo
void Solo::setPlanta(Planta *p)
{
    if (!temPlanta())
    {
        planta = p;
    }
}

// Devolve uma planta do solo
Planta *Solo::getPlanta() const
{
    return planta;
}

// Remove uma planta do solo
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

// Verifica se existe uma ferramenta no solo
bool Solo::temFerramenta() const
{
    bool existe = (ferramenta != nullptr);
    return existe;
}

// Define uma ferramenta no solo
void Solo::setFerramenta(Ferramenta *f)
{
    if (!temFerramenta())
    {
        ferramenta = f;
    }
}

// Devolve uma ferramenta do solo
Ferramenta *Solo::getFerramenta() const
{
    return ferramenta;
}

// Remove uma ferramenta do solo
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

// Verifica se o solo está vazio (true = sem planta e sem ferramenta)
bool Solo::estaVazio() const
{
    bool semPlanta = (planta == nullptr);
    bool semFerramenta = (ferramenta == nullptr);
    bool resultado = (semPlanta && semFerramenta);
    return resultado;
}

// Obtem o símbolo que representa o solo (por prioridade)
char Solo::getSimboloPrioritario() const
{
    if (temJardineiro)
        return '*';

    if (temPlanta())
    {
        char simbPlanta = planta->getSimboloPlanta();
        return simbPlanta;
    }

    if (temFerramenta())
    {
        char simbFerramenta = ferramenta->getSimboloFerramenta();
        return simbFerramenta;
    }

    char simbVazio = ' ';
    return simbVazio;
}

// Obtem a informação do solo
string Solo::getInfoSolo() const
{
    int valAgua = getAgua();
    int valNutri = getNutrientes();

    ostringstream oss;
    oss << "\t\tÁgua: " << valAgua << " | Nutrientes: " << valNutri;

    if (temPlanta())
    {
        oss << " | Planta: Sim";
    }
    else
    {
        oss << " | Planta: Não";
    }

    if (temFerramenta())
    {
        oss << " | Ferramenta: Sim";
    }
    else
    {
        oss << " | Ferramenta: Não";
    }

    if (temJardineiro)
    {
        oss << " | [Jardineiro: Presente neste Solo]" << endl;
    }
    else
    {
        oss << " | [Jardineiro: Não]" << endl;
    }

    string infoFinal = oss.str();
    return infoFinal;
}