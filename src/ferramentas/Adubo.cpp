#include "Adubo.h"

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

// Retorna true se a ferramenta estiver gastada
bool Adubo::estaGasta() const
{
    return nutrientesDisponiveis <= 0;
}

// Retorna informacoes da ferramenta
string Adubo::getInfo() const
{
    ostringstream oss;
    oss << "[Ferramenta: " << getNome() << "]\n"
        << " - ID: " << getNumeroSerie() << "\n"
        << " - Simbolo: " << getSimbolo() << "\n"
        << " - Capacidade Maxima: " << Settings::Adubo::capacidade << " unidades\n"
        << " - Dose por uso: " << Settings::Adubo::dose << " unidades\n"
        << " - Quantidade Atual: " << nutrientesDisponiveis << " unidades\n"
        << " - Funcao: Aumentar os nutrientes do solo\n";
    return oss.str();
}