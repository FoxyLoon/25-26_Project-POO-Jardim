#include "Jardineiro.h"

using namespace std;

Jardineiro::Jardineiro() : linha(-1), coluna(-1), estaNoJardim(false), ferramentaNaMao(nullptr) {
    reiniciarTurno();
}

Jardineiro::~Jardineiro() {
    for (auto f : inventario) delete f;
    if (ferramentaNaMao) delete ferramentaNaMao;
}

void Jardineiro::reiniciarTurno() {
    movimentosRestantes = Settings::Jardineiro::max_movimentos;
    entradasSaidasRestantes = Settings::Jardineiro::max_entradas_saidas;
    plantacoesRestantes = Settings::Jardineiro::max_plantacoes;
    colheitasRestantes = Settings::Jardineiro::max_colheitas;
}

// ========================================================
// Verificadores de Estado e Recursos
// ========================================================

bool Jardineiro::verificarPresenca() const {
    if (estaNoJardim) return true;
    cout << "[AVISO] >> O jardineiro nao esta no jardim!" << endl;
    return false;
}

bool Jardineiro::podeMovimentar() {
    if (movimentosRestantes > 0) return true;
    cout << "[AVISO] >> O jardineiro esgotou os movimentos!" << endl;
    return false;
}

bool Jardineiro::podeEntrarSair() {
    if (entradasSaidasRestantes > 0) return true;
    cout << "[AVISO] >> O jardineiro esgotou as entradas/saidas!" << endl;
    return false;
}

bool Jardineiro::podePlantar() {
    if (plantacoesRestantes > 0) return true;
    cout << "[AVISO] >> O jardineiro nao pode plantar mais neste turno!" << endl;
    return false;
}

bool Jardineiro::podeColher() {
    if (colheitasRestantes > 0) return true;
    cout << "[AVISO] >> O jardineiro esgotou as colheitas!" << endl;
    return false;
}

// Getters de Recursos
int Jardineiro::getMovimentosRestantes() const { return movimentosRestantes; }
int Jardineiro::getEntradasSaidasRestantes() const { return entradasSaidasRestantes; }
int Jardineiro::getPlantacoesRestantes() const { return plantacoesRestantes; }
int Jardineiro::getColheitasRestantes() const { return colheitasRestantes; }

// ========================================================
// Ações de Movimento e Jardim
// ========================================================

void Jardineiro::usaMovimento(int novaL, int novaC, string direcao) {
    linha = novaL;
    coluna = novaC;
    movimentosRestantes--;
    cout << "[ACAO] >> O jardineiro moveu-se para " << direcao << ". (Restam: " << movimentosRestantes << ")" << endl;
}

void Jardineiro::usaEntrar(int l, int c) {
    linha = l;
    coluna = c;
    estaNoJardim = true;
    entradasSaidasRestantes--;
    cout << "[ACAO] >> O jardineiro entrou no jardim." << endl;
}

void Jardineiro::usaSair() {
    linha = -1;
    coluna = -1;
    estaNoJardim = false;
    entradasSaidasRestantes--;
    cout << "[ACAO] >> O jardineiro saiu do jardim." << endl;
}

void Jardineiro::usaPlantar(Solo &s, Planta *novaPlanta) {
    s.setPlanta(novaPlanta);
    plantacoesRestantes--;
    cout << "[ACAO] >> O jardineiro realizou uma plantacao." << endl;
}

void Jardineiro::usaColher(Solo &s) {
    Planta *p = s.removerPlanta();
    if (p) {
        delete p;
        colheitasRestantes--;
        cout << "[ACAO] >> O jardineiro colheu uma planta." << endl;
    }
}

// ========================================================
// Gestão de Inventário
// ========================================================

void Jardineiro::adicionarFerramenta(Ferramenta *f) {
    if (f) inventario.push_back(f);
}

void Jardineiro::selecionarFerramenta(int indice) {
    if (indice >= 0 && indice < (int)inventario.size()) {
        largarFerramenta(); // Guarda a atual antes de pegar na nova
        ferramentaNaMao = inventario[indice];
        inventario.erase(inventario.begin() + indice);
        cout << "[INFO] >> O jardineiro equipou: " << ferramentaNaMao->getNome() << endl;
    } else {
        cout << "[ERRO] >> Indice de inventario invalido!" << endl;
    }
}

void Jardineiro::largarFerramenta() {
    if (ferramentaNaMao) {
        inventario.push_back(ferramentaNaMao);
        cout << "[INFO] >> O jardineiro guardou a ferramenta na mochila." << endl;
        ferramentaNaMao = nullptr;
    }
}

Ferramenta* Jardineiro::removerFerramenta(int indice) {
    if (indice >= 0 && indice < (int)inventario.size()) {
        Ferramenta* f = inventario[indice];
        inventario.erase(inventario.begin() + indice);
        cout << "[INFO] >> Ferramenta removida definitivamente do inventario." << endl;
        return f;
    }
    return nullptr;
}

void Jardineiro::listarFerramentas() const {
    cout << "=== Inventario ===" << endl;
    if (inventario.empty()) cout << "(Mochila vazia)" << endl;
    for (size_t i = 0; i < inventario.size(); ++i) {
        cout << i << ". " << inventario[i]->getNome() << endl;
    }
}

Ferramenta* Jardineiro::getFerramentaNaMao() const {
    return ferramentaNaMao;
}

void Jardineiro::mostrarEstado() const {
    cout << "--- Jardineiro ---" << endl;
    cout << "Equipado: " << (ferramentaNaMao ? ferramentaNaMao->getNome() : "Mao vazia") << endl;
}

// Getters de Posição
int Jardineiro::getLinha() const { return linha; }
int Jardineiro::getColuna() const { return coluna; }
bool Jardineiro::getEstaNoJardim() const { return estaNoJardim; }