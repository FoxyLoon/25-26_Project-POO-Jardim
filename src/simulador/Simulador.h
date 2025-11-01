#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <string>

#include "../jardim/Jardim.h"
#include "../jardineiro/Jardineiro.h"

// NOTA: "std::stringstream" é usado APENAS para parsing textual, e não é uma coleção.
// É permitido segundo o enunciado, pois não armazena estruturas do jardim.


using namespace std;

// Classe responsável pela interação com o utilizador e pela coordenação
// entre Jardim, Jardineiro, Plantas e Ferramentas.
class Simulador {
public:
    Simulador();
    ~Simulador();
    bool processaComando(const string &linha);  // interpreta e executa comandos

private:
    Jardim *jardim;         // ponteiro para o jardim (pode ser nulo até o comando 'jardim' ser executado)
    Jardineiro jardineiro;  // jardineiro do simulador
    bool jardimCriado;
    bool jardineiroCriado;

    // Métodos privados para cada comando
    static bool comandoFim();
    bool comandoJardim(stringstream &ss);
    bool comandoEstado() const;
    bool comandoEntra(stringstream &ss);

    // ----- COMANDOS DO TEMPO SIMULADO -----
    bool comandoAvanca(stringstream &ss);

    // ----- COMANDOS DE LISTAGEM -----
    bool comandoLplantas();
    bool comandoLplanta(stringstream &ss);
    bool comandoLarea();
    bool comandoLsolo(stringstream &ss);
    bool comandoLferr();

    // ----- COMANDOS DE AÇÃO -----
    bool comandoColhe(stringstream &ss);
    bool comandoPlanta(stringstream &ss);
    bool comandoLarga();
    bool comandoPega(stringstream &ss);
    bool comandoCompra(stringstream &ss);

    // ----- COMANDOS DE MOVIMENTO -----
    bool comandoE();
    bool comandoD();
    bool comandoC();
    bool comandoB();
    bool comandoSai();

    // ----- COMANDOS GERAIS -----
    bool comandoGrava(stringstream &ss);
    bool comandoRecupera(stringstream &ss);
    bool comandoApaga(stringstream &ss);
    bool comandoExecuta(stringstream &ss);


    // Função auxiliar para validar posições
    static bool isPosicaoValida(const string &p);
};

#endif
