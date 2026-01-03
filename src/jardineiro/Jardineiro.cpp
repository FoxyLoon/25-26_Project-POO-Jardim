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

// Adiciona uma ferramenta ao inventário
void Jardineiro::adicionarFerramentaAoInventario(Ferramenta *f)
{
    if (f)
    {
        inventario.push_back(f);
        cout << string(111, '=') << "\n"
             << "[INFO] >> Ferramenta adicionada: " << f->getNomeFerramenta() << ". (Iventário: " << inventario.size() << " itens)" << endl;
    }
}

// Seleciona uma ferramenta do inventário
void Jardineiro::selecionarFerramentaDoInventario(int ID_Ferramenta)
{
    // Procura a ferramenta no inventário pelo seu ID
    int posicaoNoVetor = -1;
    for (size_t i = 0; i < inventario.size(); ++i)
    {
        if (inventario[i]->getNumeroSerieFerramenta() == ID_Ferramenta)
        {
            posicaoNoVetor = i;
            break;
        }
    }

    if (posicaoNoVetor == -1)
    {
        cout << string(111, '=') << "\n[ERRO] >> O jardineiro nao transporta nenhuma ferramenta com o ID " << ID_Ferramenta << endl;
    }
    else
    {

        // Se existir, larga a ferramenta na mao
        depositarFerramentaDaMaoParaInventario();

        // 4. Move a ferramenta selecionada do inventário para a mão
        ferramentaNaMao = inventario[posicaoNoVetor];
        inventario.erase(inventario.begin() + posicaoNoVetor);

        cout << string(111, '=') << "\n[INFO] >> O Jardineiro equipou a ferramenta: " << ferramentaNaMao->getNomeFerramenta()
             << " (ID " << ID_Ferramenta << ")" << endl;
    }
}

// Larga a ferramenta na mao e deixa a mão vazia
void Jardineiro::depositarFerramentaDaMaoParaInventario()
{
    if (ferramentaNaMao != nullptr)
    {
        string nome = ferramentaNaMao->getNomeFerramenta();
        int id = ferramentaNaMao->getNumeroSerieFerramenta();

        inventario.push_back(ferramentaNaMao);
        ferramentaNaMao = nullptr;

        cout << string(111, '=') << "\n[INFO] >> O jardineiro desequipou a ferramenta: "
             << nome << " (ID " << id << ")" << endl;
    }
}

// Remove uma ferramenta do inventário pelo ID quando estiver esgotada (a validação não é feita aqui, apenas a remoção)
void Jardineiro::removerFerramentaDoInventario(int ID_Ferramenta)
{
    // Verifica se existe uma ferramenta na mão e se o ID coincide
    if (ferramentaNaMao != nullptr && ferramentaNaMao->getNumeroSerieFerramenta() == ID_Ferramenta)
    {
        string nome = ferramentaNaMao->getNomeFerramenta();

        // Remove a ferramenta da mao
        delete ferramentaNaMao;
        ferramentaNaMao = nullptr;

        cout << string(111, '=') << endl;
        cout << "[INFO] >> A ferramenta " << nome << " (ID: " << ID_Ferramenta << ") esgotou-se e foi removida da mao." << endl;
    }
}

// Listagem de ferramentas do inventário
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
            cout << "[" << i + 1 << ".] " << inventario[i]->getInfoFerramenta() << endl;
        }
    }
}

// Retorna a ferramenta equipada
Ferramenta *Jardineiro::getFerramentaNaMao() const { return ferramentaNaMao; }

// ========================================================

void Jardineiro::mostrarEstado() const
{
    if (ferramentaNaMao)
    {
        cout << "\n- Equipado: " << ferramentaNaMao->getNomeFerramenta() << endl;
        cout << "- " << ferramentaNaMao->getInfoExtraFerramenta() << endl;
    }
    else
    {
        cout << "\n- Equipado: Nada (Mao vazia)" << endl;
    }
}

// ========================================================
// ========================================================
// ========================================================

int Jardineiro::getLinha() const { return linha; }

int Jardineiro::getColuna() const { return coluna; }

bool Jardineiro::getEstaNoJardim() const { return estaNoJardim; }