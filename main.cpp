#include "src/simulador/Simulador.h"
#include <iostream>

// Para windows
#ifndef NOMINMAX
#define NOMINMAX
#endif
#define byte win_byte_override
#include <windows.h>
#undef byte

using namespace std;

// Programa principal do simulador de jardim.
// Responsável apenas por iniciar a execução e tratar o “loop” de comandos.
int main()
{
  // Para windows
  SetConsoleOutputCP(CP_UTF8);

  Simulador cmd;
  string linha;
  cout << "\n\n"
       << string(51, '=') << '\n'
       << "\t\tSimulador de Jardim\t\t\n"
       << string(51, '=') << '\n';

  while (cout << "\n> ", getline(cin, linha))
  {
    if (linha.empty())
    {
      cout << string(51, '=') << '\n';
      cout << "[INFO] >> Por favor, digite um comando!\n\n";
      continue;
    }
    cout << string(51, '=') << endl;

    if (!cmd.processaComando(linha))
      cout << '\n';
  }

  return 0;
}
