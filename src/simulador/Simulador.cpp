#include "Simulador.h"
#include <iostream>
#include <sstream>

using namespace std;

Simulador::Simulador() : jardim(nullptr), jardimCriado(false), jardineiroCriado(false) {}

Simulador::~Simulador() {
    delete jardim;
}

// --- Função auxiliar ---
bool Simulador::isPosicaoValida(const string &p) {
    return p.size() == 2 && islower(p[0]) && islower(p[1]);
}

// --- Processamento dos Comandos ---
bool Simulador::processaComando(const string &linha) {
    stringstream ss(linha);
    string cmd;

    //lê até ao primeiro espaço (apenas a primeira palavra)
    //Nota: Os parametros depois do espaço ficam e são usados mais tarde
    ss >> cmd;

    if (cmd == "fim") return comandoFim();
    if (cmd == "jardim") return comandoJardim(ss);
    if (cmd == "estado") return comandoEstado();
    if (cmd == "entra") return comandoEntra(ss);
    if (cmd == "sai") return comandoSai();

    //Retorna "false" caso o comando não for nenhum dos de cima
    return false;
}

// ========================================================

// --- Implementação de cada comando ---

bool Simulador::comandoFim() {
    cout << "A encerrar o simulador...\n";
    exit(0);
}

bool Simulador::comandoJardim(stringstream &ss) {
    int l, c;
    if (!(ss >> l >> c)) return false;
    if (l < 1 || l > 26 || c < 1 || c > 26) return false;

    if (jardimCriado) {
        cout << "O jardim já foi criado.\n";
        return false;
    }

    jardim = new Jardim(l, c);
    jardimCriado = true;
    cout << "Jardim criado com " << l << " linhas e " << c << " colunas.\n";
    jardim->mostrar();
    return true;
}

bool Simulador::comandoEstado() const {
    if (!jardimCriado) {
        cout << "[ERRO] E necessario criar o jardim antes de ver o seu estado.\n";
        return false;
    }
    jardim->mostrar();
    return true;
}

bool Simulador::comandoEntra(stringstream &ss) {
    if (!jardimCriado) {
        cout << "[ERRO] Nao e possivel adicionar um Jardineiro sem ter um jardim criado primeiro!\n";
        return false;
    }

    string pos;
    if (!(ss >> pos) || !isPosicaoValida(pos)) return false;

    jardineiroCriado = true;
    jardineiro.entrarNoJardim(pos[0]-'a', pos[1]-'a');
    cout << "Jardineiro entrou na posição " << pos << ".\n";
    jardim->mostrarComJardineiro(jardineiro);

    return true;
}

bool Simulador::comandoSai() {
    if (!jardimCriado) {
        cout << "[ERRO] Não e possivel remover um Jardineiro sem ter um jardim criado primeiro!\n";
        return false;
    }

    if (!jardineiroCriado) {
        cout << "[ERRO] Nao e possivel remover um Jardineiro que nao existe!\n";
        return false;
    }

    jardineiroCriado = false;
    jardineiro.sairDoJardim();
    cout << "Jardineiro saiu do jardim.\n";
    jardim->mostrar();
    return true;
}
