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

    if (cmd == "avanca") return comandoAvanca(ss);
    if (cmd == "lplantas") return comandoLplantas();
    if (cmd == "lplanta") return comandoLplanta(ss);
    if (cmd == "larea") return comandoLarea();
    if (cmd == "lsolo") return comandoLsolo(ss);
    if (cmd == "lferr") return comandoLferr();
    if (cmd == "colhe") return comandoColhe(ss);
    if (cmd == "planta") return comandoPlanta(ss);
    if (cmd == "larga") return comandoLarga();
    if (cmd == "pega") return comandoPega(ss);
    if (cmd == "compra") return comandoCompra(ss);
    if (cmd == "e") return comandoE();
    if (cmd == "d") return comandoD();
    if (cmd == "c") return comandoC();
    if (cmd == "b") return comandoB();
    if (cmd == "entra") return comandoEntra(ss);
    if (cmd == "sai") return comandoSai();
    if (cmd == "jardim") return comandoJardim(ss);
    if (cmd == "grava") return comandoGrava(ss);
    if (cmd == "recupera") return comandoRecupera(ss);
    if (cmd == "apaga") return comandoApaga(ss);
    if (cmd == "executa") return comandoExecuta(ss);
    if (cmd == "fim") return comandoFim();




    //Retorna "false" caso o comando não for nenhum dos de cima
    cout << "[ERRO] Comando desconhecido: " << cmd << "\n";
    return false;
}

// ========================================================

// --- Implementação de cada comando ---

bool Simulador::comandoFim() {
    cout << "A encerrar o simulador...\n";
    exit(0);
}

bool Simulador::comandoJardim(stringstream &ss) {
    int linhas, colunas;
    if (!(ss >> linhas >> colunas)) {
        cout << "[ERRO] Faltam valoresE!\n";
        return false;
    }
    if (linhas < 1 || linhas > 26){
        cout << "[ERRO] Número de Linhas Inválido!\n";
        return false;
    }
    if (colunas < 1 || colunas > 26){
        cout << "[ERRO] Número de Colunas Inválido!\n";
        return false;
    }

    if (jardimCriado) {
        cout << "[INFO] Já existe um jardim criado!\n";
        return false;
    }

    jardim = new Jardim(linhas, colunas);
    jardimCriado = true;
    cout << "[INFO] O Jardim foi criado com "
        << linhas << " linhas e "
        << colunas << " colunas.\n";

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
