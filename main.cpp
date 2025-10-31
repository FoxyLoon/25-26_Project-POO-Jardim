#include <iostream>
#include "src/simulador/Simulador.h"

// Programa principal do simulador de jardim
// Responsável apenas por iniciar a execução e tratar o loop de comandos.
int main() {
    Simulador sim;
    std::string linha;

    std::cout << "Simulador de Jardim (Meta 1 - Instanciacao e Interacao)\n";

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, linha)) break;
        if (linha.empty()) continue;

        if (!sim.processaComando(linha)) {
            std::cout << "Comando inválido ou erro de sintaxe.\n";
        }
    }

    return 0;
}
