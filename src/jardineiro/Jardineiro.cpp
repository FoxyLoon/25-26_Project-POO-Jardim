#include "Jardineiro.h"

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

// ========================================================
// ========================================================
// ========================================================

void Jardineiro::reiniciarTurno()
{
    movimentosRestantes = Settings::Jardineiro::max_movimentos;
    entradasSaidasRestantes = Settings::Jardineiro::max_entradas_saidas;
    plantacoesRestantes = Settings::Jardineiro::max_plantacoes;
    colheitasRestantes = Settings::Jardineiro::max_colheitas;
}

// ========================================================
// ========================================================
// ========================================================

// Verificadores de Estado e Recursos

bool Jardineiro::verificarPresenca() const
{
    if (estaNoJardim)
        return true;
    cout << string(111, '=') << "\n[ERRO] >> O jardineiro nao esta no jardim!" << endl;
    return false;
}

bool Jardineiro::podeMovimentar()
{
    if (movimentosRestantes > 0)
        return true;
    cout << string(111, '=') << "\n[ERRO] >> Limite de movimentos esgotado! (" << Settings::Jardineiro::max_movimentos << " por turno)" << endl;
    return false;
}

bool Jardineiro::podeEntrarSair()
{
    if (entradasSaidasRestantes > 0)
        return true;
    cout << string(111, '=') << "\n[ERRO] >> Limite de entradas/saidas esgotado! (" << Settings::Jardineiro::max_entradas_saidas << " por turno)" << endl;
    return false;
}

bool Jardineiro::podePlantar()
{
    if (plantacoesRestantes > 0)
        return true;
    cout << string(111, '=') << "\n[ERRO] >> Limite de plantacoes esgotado! (" << Settings::Jardineiro::max_plantacoes << " por turno)" << endl;
    return false;
}

bool Jardineiro::podeColher()
{
    if (colheitasRestantes > 0)
        return true;
    cout << string(111, '=') << "\n[ERRO] >> Limite de colheitas esgotado! (" << Settings::Jardineiro::max_colheitas << " por turno)" << endl;
    return false;
}

// ========================================================
// ========================================================
// ========================================================

// Ações de Movimento e Jardim

void Jardineiro::usaMovimento(int novaL, int novaC, string direcao)
{
    linha = novaL;
    coluna = novaC;
    movimentosRestantes--;
    cout << string(111, '=') << "\n[AÇÃO] >> O jardineiro moveu-se para " << direcao << ". (Restam: " << movimentosRestantes << " movimentos)" << endl;
}

void Jardineiro::usaEntrar(int l, int c)
{
    linha = l;
    coluna = c;
    estaNoJardim = true;
    entradasSaidasRestantes--;
    cout << string(111, '=') << "\n[AÇÃO] >> O jardineiro entrou no jardim. (Restam: " << entradasSaidasRestantes << " entradas/saidas)" << endl;
}

void Jardineiro::usaSair()
{
    linha = -1;
    coluna = -1;
    estaNoJardim = false;
    entradasSaidasRestantes--;
    cout << string(111, '=') << "\n[AÇÃO] >> O jardineiro saiu do jardim. (Restam: " << entradasSaidasRestantes << " entradas/saidas)" << endl;
}

void Jardineiro::usaPlantar(Solo &s, Planta *novaPlanta)
{
    if (novaPlanta)
    {
        string nome = novaPlanta->getNomePlanta();
        s.setPlanta(novaPlanta);
        plantacoesRestantes--;
        cout << string(111, '=') << "\n[AÇÃO] >> O jardineiro plantou uma " << nome << ". (Restam: " << plantacoesRestantes << " plantacoes)" << endl;
    }
}

void Jardineiro::usaColher(Solo &s)
{
    Planta *p = s.removerPlanta();
    if (p)
    {
        string nome = p->getNomePlanta();
        delete p;
        colheitasRestantes--;
        cout << string(111, '=') << "\n[AÇÃO] >> O jardineiro colheu uma " << nome << ". (Restam: " << colheitasRestantes << " colheitas)" << endl;
    }
}

// ========================================================
// ========================================================
// ========================================================

// Gestão de Inventário

void Jardineiro::adicionarFerramenta(Ferramenta *f)
{
    if (f)
    {
        inventario.push_back(f);
        cout << string(111, '=') << "\n[INFO] >> Ferramenta adicionada: " << f->getNomeFerramenta() << ". (Mochila: " << inventario.size() << " itens)" << endl;
    }
}

void Jardineiro::selecionarFerramenta(int indice)
{
    if (indice >= 0 && indice < (int)inventario.size())
    {
        largarFerramenta();
        ferramentaNaMao = inventario[indice];
        inventario.erase(inventario.begin() + indice);
        cout << string(111, '=') << "\n[INFO] >> O jardineiro equipou a ferramenta " << ferramentaNaMao->getNomeFerramenta() << endl;
    }
    else
    {
        cout << string(111, '=') << "\n[ERRO] >> Posição do inventário inválido!" << endl;
    }
}

void Jardineiro::largarFerramenta()
{
    if (ferramentaNaMao)
    {
        string nome = ferramentaNaMao->getNomeFerramenta();
        inventario.push_back(ferramentaNaMao);
        ferramentaNaMao = nullptr;
        cout << string(111, '=') << "\n[INFO] >> O jardineiro desequipou a ferramenta: " << nome << endl;
    }
}

Ferramenta *Jardineiro::removerFerramenta(int indice)
{
    if (indice >= 0 && indice < (int)inventario.size())
    {
        Ferramenta *f = inventario[indice];
        string nome = f->getNomeFerramenta();
        inventario.erase(inventario.begin() + indice);
        cout << string(111, '=') << "\n[INFO] >> A ferramenta " << nome << " esgotou-se e saiu do inventario." << endl;
        return f;
    }
    return nullptr;
}

void Jardineiro::listarFerramentas() const
{
    cout << string(41, '=') << "[ INVENTARIO DO JARDINEIRO ]" << string(42, '=') << endl;
    if (inventario.empty())
    {
        cout << "[INFO] >> O inventário do jardineiro esta vazio." << endl;
    }
    else
    {
        for (size_t i = 0; i < inventario.size(); ++i)
        {
            cout << "[" << i + 1 << ".] " << inventario[i]->getNomeFerramenta() << " - " << i << ". " << inventario[i]->getInfoFerramenta() << endl;
        }
    }
}

Ferramenta *Jardineiro::getFerramentaNaMao() const { return ferramentaNaMao; }

// ========================================================

void Jardineiro::mostrarEstado() const
{
    cout << "--- Estado do Jardineiro ---" << endl;
    if (ferramentaNaMao)
    {
        cout << "Equipado: " << ferramentaNaMao->getNomeFerramenta() << endl;
        cout << "Detalhes: " << ferramentaNaMao->getInfoFerramenta() << endl;
    }
    else
    {
        cout << "Equipado: Nada (Mao vazia)" << endl;
    }
    cout << "Recursos Turno: Movimentos(" << movimentosRestantes << ") | Colheitas(" << colheitasRestantes << ")" << endl;
}

// ========================================================
// ========================================================
// ========================================================

int Jardineiro::getLinha() const { return linha; }

int Jardineiro::getColuna() const { return coluna; }

bool Jardineiro::getEstaNoJardim() const { return estaNoJardim; }