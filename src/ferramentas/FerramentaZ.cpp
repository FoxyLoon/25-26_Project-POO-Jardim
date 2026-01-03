#include "FerramentaZ.h"
#include <cmath> // Para usar abs() se necessário

FerramentaZ::FerramentaZ() : Ferramenta("FerramentaZ", 'z')
{
    bateria = Settings::FerramentaZ::capacidade;
}

void FerramentaZ::usar()
{
    if (bateria > 0)
        bateria--;
}

void FerramentaZ::aplicarNoSolo(Solo &s)
{
    if (estaGasta())
        return;

    // Lógica da Água
    int aguaAtual = s.getAgua();
    int alvoAgua = Settings::FerramentaZ::otimo_agua;
    int ajusteMaxAgua = Settings::FerramentaZ::max_ajuste_agua;

    if (aguaAtual < alvoAgua)
    {
        int dif = alvoAgua - aguaAtual;
        s.setAgua(aguaAtual + (dif > ajusteMaxAgua ? ajusteMaxAgua : dif));
    }
    else if (aguaAtual > alvoAgua)
    {
        int dif = aguaAtual - alvoAgua;
        s.setAgua(aguaAtual - (dif > ajusteMaxAgua ? ajusteMaxAgua : dif));
    }

    // Lógica dos Nutrientes
    int nutriAtual = s.getNutrientes();
    int alvoNutri = Settings::FerramentaZ::otimo_nutrientes;
    int ajusteMaxNutri = Settings::FerramentaZ::max_ajuste_nutrientes;

    if (nutriAtual < alvoNutri)
    {
        int dif = alvoNutri - nutriAtual;
        s.setNutrientes(nutriAtual + (dif > ajusteMaxNutri ? ajusteMaxNutri : dif));
    }
    else if (nutriAtual > alvoNutri)
    {
        int dif = nutriAtual - alvoNutri;
        s.setNutrientes(nutriAtual - (dif > ajusteMaxNutri ? ajusteMaxNutri : dif));
    }

    usar(); // Consome 1 carga de bateria
}

bool FerramentaZ::estaGasta() const
{
    return bateria <= 0;
}

string FerramentaZ::getInfoFerramenta() const
{
    ostringstream oss;
    oss << "\t[" << getNomeFerramenta() << "]"
        << " (ID " << getNumeroSerieFerramenta() << ")"
        << " | Simbolo: " << getSimboloFerramenta()
        << " | Bateria Atual/Capacidade Maxima: " << bateria << "/" << Settings::FerramentaZ::capacidade << "\n"
        << "\t\tFunção: Equilibra o Solo ao adicionar ou remover recursos (Objetivo: 90 Água / 45 Nutrientes)" << endl;

    string informacao = oss.str();
    return informacao;
}