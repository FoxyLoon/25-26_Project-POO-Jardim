#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <string>
#include <iostream>
#include <sstream>

#include "../jardim/Jardim.h"
#include "../jardineiro/Jardineiro.h"
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

    /* bool comandoEstado() const; */       // Não existe no enunciado

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
    bool comandoLplantas();                 // Não Implementado
    bool comandoLplanta(stringstream &ss);  // Não Implementado
    bool comandoLarea();                    // Não Implementado
    bool comandoLsolo(stringstream &ss);    // Não Implementado
    bool comandoLferr();                    // Não Implementado

    // ========================================================
    // ========================================================
    // ========================================================

    // Comandos para ações
    bool comandoColhe(stringstream &ss);    // Não Implementado
    bool comandoPlanta(stringstream &ss);   // Não Implementado
    bool comandoLarga();                    // Não Implementado
    bool comandoPega(stringstream &ss);     // Não Implementado
    bool comandoCompra(stringstream &ss);   // Não Implementado

    // ========================================================
    // ========================================================
    // ========================================================

    // Comandos para controlar o jardineiro
    bool comandoE();    // OK
    bool comandoD();    // OK
    bool comandoC();    // OK
    bool comandoB();    // OK
    bool comandoEntra(stringstream &ss);    // OK
    bool comandoSai();  // OK
    
    // ========================================================
    // ========================================================
    // ========================================================

    // Funções auxiliares

    // Valida posições no jardim
    static bool isPosicaoValida(const string &p);
    
    // Verifica se existe um Jardim
    static bool isJardimCriado(const bool &jm_c);

    // Verifica se existe um Jardineiro
    static bool isJardineiroCriado(const bool &jo_c);

    // Verifica se está fora dos limites
    /* static bool isForaDosLimites(const ); */
};

#endif
