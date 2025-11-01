#include <iostream>
#include "src/simulador/Simulador.h"

using namespace std;

// Programa principal do simulador de jardim.
// Responsável apenas por iniciar a execução e tratar o loop de comandos.
int main() {
    Simulador sim;
    string linha;

    cout << "Simulador de Jardim (Meta 1 - Instanciacao e Interacao)\n";

    while (true) {
        cout << "> ";
        if (!getline(cin, linha)) break;
        if (linha.empty()) continue;

        if (!sim.processaComando(linha)) {
            cout << "Comando inválido ou erro de sintaxe.\n";
        }
    }

    return 0;
}
