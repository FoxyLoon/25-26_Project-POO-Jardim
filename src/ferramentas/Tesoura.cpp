#include "Tesoura.h"
#include <sstream>

// Construtor: Símbolo 'T', nome "Tesoura"
Tesoura::Tesoura() : Ferramenta("Tesoura", 't') {}

// Usa a ferramenta
void Tesoura::usar()
{
    // A tesoura não tem desgaste
}

void Tesoura::aplicarNoSolo(Solo &s)
{
    // A tesoura só age se houver uma planta e se ela for "FEIA"
    if (s.temPlanta())
    {
        if (s.getPlanta()->getBelezaPlanta() == "FEIA")
        {
            // Remove a planta do solo e liberta a memória
            s.removerPlanta();
        }
    }
}

// Retorna true se a ferramenta estiver gastada
bool Tesoura::estaGasta() const
{
    // A tesoura não tem desgaste
    return false;
}

// Retorna informacoes da ferramenta
string Tesoura::getInfoFerramenta() const
{
    ostringstream oss;
    oss << "[" << getNomeFerramenta() << "]"
        << " (ID " << getNumeroSerieFerramenta() << ")"
        << " | Simbolo: " << getSimboloFerramenta()
        << " | Quantidade Atual/Capacidade Maxima:  Infinita (Aço Cromado)" << endl;

    string informacao = oss.str();
    return informacao;
}

string Tesoura::getInfoExtraFerramenta() const
{
    ostringstream oss;
    oss << "Função: Eliminar plantas consideradas de beleza 'FEIA'" << endl;

    string informacaoExtra = oss.str();
    return informacaoExtra;
}