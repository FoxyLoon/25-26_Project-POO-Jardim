#include "Adubo.h"
#include <sstream>
#include "../Settings.h"

Adubo::Adubo() : Ferramenta("Adubo", 'a')
{
    nutrientesDisponiveis = Settings::Adubo::capacidade;
}

// Usa a ferramenta
void Adubo::usar()
{
    if (nutrientesDisponiveis >= Settings::Adubo::dose)
    {
        nutrientesDisponiveis -= Settings::Adubo::dose;
    }
    else
    {
        nutrientesDisponiveis = 0;
    }
}

void Adubo::aplicarNoSolo(Solo &s)
{
    if (!estaGasta())
    {
        int doseNutrientes = Settings::Adubo::dose;

        // 1. Aumenta os nutrientes do solo
        s.setNutrientes(s.getNutrientes() + doseNutrientes);

        // 2. Consome nutrientes do adubo
        usar();
    }
}

// Retorna true se a ferramenta estiver gasta
bool Adubo::estaGasta() const
{
    return nutrientesDisponiveis <= 0;
}

// Retorna informacoes da ferramenta
string Adubo::getInfoFerramenta() const
{
    ostringstream oss;
    oss << "[" << getNomeFerramenta() << "]"
        << " (ID " << getNumeroSerieFerramenta() << ")"
        << " | Simbolo: " << getSimboloFerramenta()
        << " | Quantidade Atual/Capacidade Maxima: " << nutrientesDisponiveis << "/" << Settings::Adubo::capacidade
        << " | Dose por uso: " << Settings::Adubo::dose << endl;

    string informacao = oss.str();
    return informacao;
}

string Adubo::getInfoExtraFerramenta() const
{
    ostringstream oss;
    oss << "Função: Aumentar os nutrientes do solo" << endl;

    string informacaoExtra = oss.str();
    return informacaoExtra;
}