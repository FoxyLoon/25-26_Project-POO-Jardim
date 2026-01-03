#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <string>
#include <iostream>
#include <sstream>

#include "../jardim/Jardim.h"
#include "../jardineiro/Jardineiro.h"
#include "../ferramentas/FerramentaZ.h"

#include "../plantas/Planta.h"
#include "../plantas/Cacto.h"
#include "../plantas/Roseira.h"
#include "../plantas/ErvaDaninha.h"
#include "../plantas/PlantaExotica.h"

// NOTA: "std::stringstream" é usado APENAS para parsing textual, e não é uma coleção.
// É permitido segundo o enunciado, pois não armazena estruturas do jardim.

using namespace std;

// Classe responsável pela interação com o utilizador e pela coordenação
// entre Jardim, Jardineiro, Plantas e Ferramentas.
class Simulador
{
public:
    Simulador();
    ~Simulador();

    // Recebe um comando do utilizador e o processa
    bool processaComando(const string &linha);

private:
    // ponteiro para o jardim (pode ser nulo até o comando 'jardim' ser executado)
    Jardim *jardim;

    // Jardineiro do simulador
    Jardineiro jardineiro;

    // Flags indicando se o jardim e o jardineiro foram criados
    bool jardimCriado;
    bool jardineiroCriado;

    /* bool comandoEstado() const; */ // Não existe no enunciado

    // ========================================================
    // ========================================================
    // ========================================================

    // Comandos Gerais
    bool comandoAvanca(stringstream &ss);   // Não Implementado
    static bool comandoFim();               // OK
    bool comandoJardim(stringstream &ss);   // OK
    bool comandoGrava(stringstream &ss);    // Não Implementado
    bool comandoRecupera(stringstream &ss); // Não Implementado
    bool comandoApaga(stringstream &ss);    // Não Implementado
    bool comandoExecuta(stringstream &ss);  // Não Implementado

    // ========================================================
    // ========================================================
    // ========================================================

    // Comandos para listar informação
    bool comandoLplantas();                // Não Implementado
    bool comandoLplanta(stringstream &ss); // Não Implementado
    bool comandoLarea();                   // Não Implementado
    bool comandoLsolo(stringstream &ss);   // Não Implementado
    bool comandoLferr();                   // Não Implementado

    // ========================================================
    // ========================================================
    // ========================================================

    // Comandos para ações
    bool comandoColhe(stringstream &ss);  // OK
    bool comandoPlanta(stringstream &ss); // OK
    bool comandoLarga();                  // Não Implementado
    bool comandoPega(stringstream &ss);   // Não Implementado
    bool comandoCompra(stringstream &ss); // Não Implementado

    // ========================================================
    // ========================================================
    // ========================================================

    // Comandos para controlar o jardineiro
    bool comandoE();                     // OK
    bool comandoD();                     // OK
    bool comandoC();                     // OK
    bool comandoB();                     // OK
    bool comandoEntra(stringstream &ss); // OK
    bool comandoSai();                   // OK

    // ========================================================
    // ========================================================
    // ========================================================

    // Funções auxiliares

    // Valida posições no jardim
    static bool isLetraPequena(const string &p);

    // Verifica se existe um Jardim
    bool isJardimCriado();

    // Verifica se existe um Jardineiro
    bool isJardineiroCriado();

    // Verifica se está fora dos limites
    bool isForaDosLimites(int linha, int coluna);
};

#endif
