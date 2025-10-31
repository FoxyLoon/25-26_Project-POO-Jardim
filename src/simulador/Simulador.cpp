#include "Simulador.h"
#include <iostream>
#include <cstdlib>

Simulador::Simulador() : jardim(nullptr), jardimCriado(false) {}

Simulador::~Simulador() {
    delete jardim;
}

// Função auxiliar para verificar se uma posição é válida (duas letras minúsculas)
bool isPosicaoValida(const std::string &p) {
    return p.size() == 2 &&
           std::islower(p[0]) &&
           std::islower(p[1]);
}

bool Simulador::processaComando(const std::string &linha) {
    std::stringstream ss(linha);
    std::string cmd;
    ss >> cmd;

    // --- Comando fim ---
    if (cmd == "fim") {
        std::cout << "Encerrando simulador...\n";
        std::exit(0);
    }

    // --- Criação do jardim ---
    if (cmd == "jardim") {
        int l, c;
        if (!(ss >> l >> c)) return false;
        if (l < 1 || l > 26 || c < 1 || c > 26) return false;

        if (jardimCriado) {
            std::cout << "O jardim já foi criado.\n";
            return false;
        }

        jardim = new Jardim(l, c);
        jardimCriado = true;
        std::cout << "Jardim criado com " << l << " linhas e " << c << " colunas.\n";
        jardim->mostrar();
        return true;
    }

    // --- Mostrar estado do jardim ---
    if (cmd == "larea") {
        if (!jardimCriado) {
            std::cout << "Crie primeiro o jardim.\n";
            return false;
        }
        jardim->mostrar();
        return true;
    }

    // --- Comando entra <pos> ---
    if (cmd == "entra") {
        if (!jardimCriado) return false;
        std::string pos;
        if (!(ss >> pos) || !isPosicaoValida(pos)) return false;
        jardineiro.entrarNoJardim(pos[0]-'a', pos[1]-'a');
        std::cout << "Jardineiro entrou na posição " << pos << ".\n";
        jardim->mostrarComJardineiro(jardineiro);
        return true;
    }

    // --- Comando sai ---
    if (cmd == "sai") {
        if (!jardimCriado) return false;
        jardineiro.sairDoJardim();
        std::cout << "Jardineiro saiu do jardim.\n";
        jardim->mostrar();
        return true;
    }

    std::cout << "Comando não reconhecido.\n";
    return false;
}
