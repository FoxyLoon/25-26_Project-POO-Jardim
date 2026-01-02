#include "Jardineiro.h"
#include <iostream>

using namespace std;

Jardineiro::Jardineiro() : linha(-1), coluna(-1), estaNoJardim(false), ferramentaNaMao(nullptr)
{
    reiniciarTurno();
}

Jardineiro::~Jardineiro()
{
    for (auto f : inventario)
        delete f;
    if (ferramentaNaMao)
        delete ferramentaNaMao;
}

void Jardineiro::reiniciarTurno()
{
    movimentosRestantes = Settings::Jardineiro::max_movimentos;
    entradasSaidasRestantes = Settings::Jardineiro::max_entradas_saidas;
    plantacoesRestantes = Settings::Jardineiro::max_plantacoes;
    colheitasRestantes = Settings::Jardineiro::max_colheitas;
}

// ========================================================
// Verificadores

bool Jardineiro::verificarPresenca() const
{
    if (estaNoJardim)
        return true;
    cout << "[AVISO] >> O jardineiro nao esta no jardim para realizar esta acao!" << endl;
    return false;
}

bool Jardineiro::podeMovimentar()
{
    if (!verificarPresenca())
        return false;
    if (movimentosRestantes > 0)
        return true;
    cout << "[AVISO] >> Movimentos esgotados este turno!" << endl;
    return false;
}

bool Jardineiro::podeEntrarSair()
{
    if (entradasSaidasRestantes > 0)
        return true;
    cout << "[AVISO] >> Limite de entradas/saidas atingido!" << endl;
    return false;
}

bool Jardineiro::podePlantar()
{
    if (!verificarPresenca())
        return false;
    if (plantacoesRestantes > 0)
        return true;
    cout << "[AVISO] >> Limite de plantacoes atingido!" << endl;
    return false;
}

bool Jardineiro::podeColher()
{
    if (!verificarPresenca())
        return false;
    if (colheitasRestantes > 0)
        return true;
    cout << "[AVISO] >> Limite de colheitas atingido!" << endl;
    return false;
}

// ========================================================
// Ações

void Jardineiro::usaMovimento(int novaL, int novaC, string direcao)
{
    if (podeMovimentar())
    {
        linha = novaL;
        coluna = novaC;
        movimentosRestantes--;
        cout << "[ACAO] >> Moveu-se para " << direcao << ". (Restam: " << movimentosRestantes << ")" << endl;
    }
}

void Jardineiro::usaEntrar(int l, int c)
{
    if (!podeEntrarSair())
        return;
    linha = l;
    coluna = c;
    estaNoJardim = true;
    entradasSaidasRestantes--;
    cout << "[ACAO] >> O Jardineiro ENTROU no jardim em (" << l << "," << c << ")." << endl;
}

void Jardineiro::usaSair()
{
    if (!podeEntrarSair())
        return;
    linha = -1;
    coluna = -1;
    estaNoJardim = false;
    entradasSaidasRestantes--;
    cout << "[ACAO] >> O Jardineiro SAIU do jardim." << endl;
}

void Jardineiro::usaPlantar(Solo &s, Planta *novaPlanta)
{
    if (podePlantar())
    {
        if (!s.temPlanta())
        {
            s.setPlanta(novaPlanta);
            plantacoesRestantes--;
            cout << "[ACAO] >> Plantou " << novaPlanta->getSimbolo() << ". (Restam: " << plantacoesRestantes << ")" << endl;
        }
        else
        {
            cout << "[ERRO] >> Posicao ja ocupada!" << endl;
        }
    }
}

void Jardineiro::usaColher(Solo &s)
{
    if (podeColher())
    {
        if (s.temPlanta())
        {
            cout << "[ACAO] >> Colheu planta: " << s.getPlanta()->getSimbolo() << endl;
            delete s.getPlanta();
            s.removerPlanta();
            colheitasRestantes--;
        }
        else
        {
            cout << "[AVISO] >> Nao ha nada para colher aqui." << endl;
        }
    }
}

// ========================================================
// Gestão de Inventário e Getters

void Jardineiro::listarFerramentas() const
{
    cout << "\n--- INVENTARIO ---" << endl;
    if (ferramentaNaMao)
        cout << "[MAO] >> " << ferramentaNaMao->getNome() << " (Ativa)" << endl;

    if (inventario.empty())
    {
        cout << "[MOCHILA] >> Vazia" << endl;
    }
    else
    {
        for (size_t i = 0; i < inventario.size(); ++i)
        {
            cout << i << ". " << inventario[i]->getNome() << endl;
        }
    }
}

void Jardineiro::adicionarFerramenta(Ferramenta *f)
{
    if (f)
        inventario.push_back(f);
}

void Jardineiro::selecionarFerramenta(int indice)
{
    if (indice >= 0 && indice < (int)inventario.size())
    {
        largarFerramenta();
        ferramentaNaMao = inventario[indice];
        inventario.erase(inventario.begin() + indice);
    }
}

void Jardineiro::largarFerramenta()
{
    if (ferramentaNaMao)
    {
        inventario.push_back(ferramentaNaMao);
        ferramentaNaMao = nullptr;
    }
}

Ferramenta *Jardineiro::getFerramentaNaMao() const
{
    return ferramentaNaMao;
}

void Jardineiro::processaFerramentaAutomatica(Solo &s)
{
    if (estaNoJardim && ferramentaNaMao)
    {
        ferramentaNaMao->aplicarNoSolo(s);
        if (ferramentaNaMao->estaGasta())
        {
            delete ferramentaNaMao;
            ferramentaNaMao = nullptr;
        }
    }
}

bool Jardineiro::getEstaNoJardim() const
{
    return estaNoJardim;
}

int Jardineiro::getLinha() const
{
    return linha;
}

int Jardineiro::getColuna() const
{
    return coluna;
}