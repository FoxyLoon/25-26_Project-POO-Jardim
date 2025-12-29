#include "Jardineiro.h"
#include <iostream>

using namespace std;

Jardineiro::Jardineiro()
    : noJardim(false),
      linha(-1),
      coluna(-1),
      ferramentaNaMao(nullptr),
      movimentosRestantes(Settings::Jardineiro::max_movimentos),
      entradasSaidasRestantes(Settings::Jardineiro::max_entradas_saidas),
      plantacoesRestantes(Settings::Jardineiro::max_plantacoes),
      colheitasRestantes(Settings::Jardineiro::max_colheitas)
{}

Jardineiro::~Jardineiro() {
    // Libertar todas as ferramentas do inventário
    for (Ferramenta* f : inventario) {
        delete f;
    }
    inventario.clear();

    // A ferramentaNaMao está no inventário, já foi libertada acima
    ferramentaNaMao = nullptr;
}

// ========================================================
// Movimento e Posição
// ========================================================

void Jardineiro::entraNoJardim(int l, int c) {
    noJardim = true;
    moveNoJardim(l, c);
}

void Jardineiro::moveNoJardim(int l, int c) {
    linha = l;
    coluna = c;
}

void Jardineiro::saiDoJardim() {
    noJardim = false;
    linha = coluna = -1;
}

bool Jardineiro::isNoJardim() const {
    return noJardim;
}

int Jardineiro::getLinha() const {
    return linha;
}

int Jardineiro::getColuna() const {
    return coluna;
}

// ========================================================
// Sistema de Inventário
// ========================================================

void Jardineiro::adicionarFerramenta(Ferramenta* f) {
    if (f != nullptr) {
        inventario.push_back(f);
        cout << "[INFO] >> Ferramenta adicionada: " << f->getInfo() << "\n";
    }
}

bool Jardineiro::removerFerramenta(int numeroSerie) {
    int index = encontrarFerramentaNoInventario(numeroSerie);
    if (index == -1) {
        return false;  // Não encontrada
    }

    Ferramenta* f = inventario[index];

    // Se estava na mão, tirar da mão
    if (ferramentaNaMao == f) {
        ferramentaNaMao = nullptr;
    }

    // Remover do inventário
    inventario.erase(inventario.begin() + index);
    delete f;

    return true;
}

bool Jardineiro::pegarFerramenta(int numeroSerie) {
    int index = encontrarFerramentaNoInventario(numeroSerie);
    if (index == -1) {
        cout << "[ERRO] >> Ferramenta #" << numeroSerie << " nao encontrada no inventario.\n";
        return false;
    }

    // Se já tinha algo na mão, larga primeiro
    if (ferramentaNaMao != nullptr) {
        cout << "[INFO] >> Largando " << ferramentaNaMao->nome() << " #"
             << ferramentaNaMao->getNumeroSerie() << "\n";
    }

    ferramentaNaMao = inventario[index];
    cout << "[INFO] >> Pegou " << ferramentaNaMao->nome() << " #"
         << ferramentaNaMao->getNumeroSerie() << "\n";

    return true;
}

void Jardineiro::largarFerramenta() {
    if (ferramentaNaMao == nullptr) {
        cout << "[INFO] >> Nao tem nenhuma ferramenta na mao.\n";
        return;
    }

    cout << "[INFO] >> Largou " << ferramentaNaMao->nome() << " #"
         << ferramentaNaMao->getNumeroSerie() << "\n";
    ferramentaNaMao = nullptr;
}

void Jardineiro::aplicarFerramentaSeNaMao(Solo &solo) {
    if (ferramentaNaMao == nullptr) {
        return;  // Não tem ferramenta na mão
    }

    // Aplicar ferramenta
    bool aindaUtilizavel = ferramentaNaMao->aplicar(solo);

    // Se a ferramenta ficou inútil, descartá-la
    if (!aindaUtilizavel) {
        cout << "[INFO] >> " << ferramentaNaMao->nome() << " #"
             << ferramentaNaMao->getNumeroSerie() << " esgotou-se e foi descartado!\n";

        removerFerramenta(ferramentaNaMao->getNumeroSerie());
        ferramentaNaMao = nullptr;
    }
}

Ferramenta* Jardineiro::getFerramentaNaMao() const {
    return ferramentaNaMao;
}

const std::vector<Ferramenta*>& Jardineiro::getInventario() const {
    return inventario;
}

void Jardineiro::listarFerramentas() const {
    if (inventario.empty()) {
        cout << "[INFO] >> Inventario vazio.\n";
        return;
    }

    cout << "\n========== INVENTARIO ==========\n";

    for (const Ferramenta* f : inventario) {
        cout << "  " << f->getInfo();

        // Marcar se está na mão
        if (f == ferramentaNaMao) {
            cout << " [NA MAO]";
        }

        cout << "\n";
    }

    cout << "================================\n\n";
}

// ========================================================
// Contadores de Ações
// ========================================================

void Jardineiro::resetarContadores() {
    movimentosRestantes = Settings::Jardineiro::max_movimentos;
    entradasSaidasRestantes = Settings::Jardineiro::max_entradas_saidas;
    plantacoesRestantes = Settings::Jardineiro::max_plantacoes;
    colheitasRestantes = Settings::Jardineiro::max_colheitas;
}

bool Jardineiro::podeMovimentar() const {
    return movimentosRestantes > 0;
}

bool Jardineiro::podeEntrarSair() const {
    return entradasSaidasRestantes > 0;
}

bool Jardineiro::podePlantar() const {
    return plantacoesRestantes > 0;
}

bool Jardineiro::podeColher() const {
    return colheitasRestantes > 0;
}

void Jardineiro::usarMovimento() {
    if (movimentosRestantes > 0) {
        movimentosRestantes--;
    }
}

void Jardineiro::usarEntradaSaida() {
    if (entradasSaidasRestantes > 0) {
        entradasSaidasRestantes--;
    }
}

void Jardineiro::usarPlantacao() {
    if (plantacoesRestantes > 0) {
        plantacoesRestantes--;
    }
}

void Jardineiro::usarColheita() {
    if (colheitasRestantes > 0) {
        colheitasRestantes--;
    }
}

// ========================================================
// Métodos Privados Auxiliares
// ========================================================

int Jardineiro::encontrarFerramentaNoInventario(int numeroSerie) {
    for (size_t i = 0; i < inventario.size(); ++i) {
        if (inventario[i]->getNumeroSerie() == numeroSerie) {
            return static_cast<int>(i);
        }
    }
    return -1;  // Não encontrada
}