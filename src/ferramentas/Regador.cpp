#include "Regador.h"

Regador::Regador() : Ferramenta("Regador", 'g')
{
    aguaDisponivel = Settings::Regador::capacidade;
}

// Usa a ferramenta
void Regador::usar()
{
    if (aguaDisponivel >= Settings::Regador::dose)
    {
        aguaDisponivel -= Settings::Regador::dose;
    }
    else
    {
        aguaDisponivel = 0;
    }
}

void Regador::aplicarNoSolo(Solo &s)
{
    if (!estaGasta())
    {
        int dose = Settings::Regador::dose;

        // 1. Adiciona água ao solo
        s.setAgua(s.getAgua() + dose);

        // 2. Consome água do regador
        usar();
    }
}

// Retorna true se a ferramenta estiver gastada
bool Regador::estaGasta() const
{
    return aguaDisponivel <= 0;
}

// Retorna informacoes da ferramenta
string Regador::getInfoFerramenta() const
{
    ostringstream oss;
    oss << "\t[" << getNomeFerramenta() << "]"
        << " (ID " << getNumeroSerieFerramenta() << ")"
        << " | Simbolo: " << getSimboloFerramenta()
        << " | Quantidade Atual/Capacidade Maxima: " << aguaDisponivel << "/" << Settings::Regador::capacidade
        << " | Dose por uso: " << Settings::Regador::dose << "\n"
        << "\t\tFunção: Aumentar a agua do solo" << endl;

    string informacao = oss.str();
    return informacao;
}