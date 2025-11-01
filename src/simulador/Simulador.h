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
    bool comandoSai();

    // Função auxiliar para validar posições
    static bool isPosicaoValida(const string &p);
};

#endif
