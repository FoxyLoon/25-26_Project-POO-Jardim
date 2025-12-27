#include <iostream>
#include "src/simulador/Simulador.h"

#ifndef NOMINMAX
#define NOMINMAX
#endif
#define byte win_byte_override
#include <windows.h>
#undef byte

using namespace std;

// Programa principal do simulador de jardim.
// Responsável apenas por iniciar a execução e tratar o “loop” de comandos.
int main() {
    SetConsoleOutputCP(CP_UTF8);
    Simulador sim;
    string linha;

    cout << "Simulador de Jardim (Meta 1 - Instanciacao e Interacao)\n";

    while (true) {
        cout << "> ";

        if (!getline(cin, linha)) break;

        //Mantem a “interface” mais limpa ao simular que limpou
        //o histórico de comandos
        for (int i=0; i<50; i++)
            cout << "=";
        cout << endl;

        if (linha.empty()) continue;

        if (!sim.processaComando(linha)) {
            cout << "\n";
        }

    }

    return 0;
}
