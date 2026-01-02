#include "Tesoura.h"

// Construtor: Símbolo 'T', nome "Tesoura"
Tesoura::Tesoura() : Ferramenta("Tesoura", 't') {}

// Usa a ferramenta
void Tesoura::usar()
{
    // A tesoura não tem desgaste
}

void Tesoura::aplicarNoSolo(Solo& s) {
    // A tesoura só age se houver uma planta e se ela for "FEIA"
    if (s.temPlanta()) {
        if (s.getPlanta()->getBeleza() == "FEIA") {
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
string Tesoura::getInfo() const
{
    ostringstream oss;
    oss << "[Ferramenta: " << getNome() << "]\n"
        << " - ID: " << getNumeroSerie() << "\n"
        << " - Simbolo: " << getSimbolo() << "\n"
        << " - Durabilidade: Infinita (Aço Cromado)\n"
        << " - Função: Eliminar plantas consideradas de beleza 'FEIA'\n";
    return oss.str();
}