#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <string>

#include "../jardim/Jardim.h"
#include "../jardineiro/Jardineiro.h"

#include "../plantas/Planta.h"
// #include "../plantas/Cacto.h"
// #include "../plantas/Roseira.h"
// #include "../plantas/ErvaDaninha.h"
// #include "../plantas/PlantaExotica.h"

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

    // ‘Flags’ indicando se o jardim e o jardineiro foram criados
    bool jardimCriado;
    bool jardineiroNoJardim;

    // ========================================================
    // ========================================================
    // ========================================================

    // Comandos Gerais
    bool comandoAvanca(stringstream &ss);       // OK
    static bool comandoFim();                   // OK
    bool comandoJardim(stringstream &ss);       // OK
    bool comandoGrava(stringstream &ss) const;  // OK
    bool comandoRecupera(stringstream &ss);     // OK
    static bool comandoApaga(stringstream &ss); // OK
    bool comandoExecuta(stringstream &ss);      // OK

    // ========================================================
    // ========================================================
    // ========================================================

    // Comandos para listar informação
    [[nodiscard]] bool comandoLplantas() const;  // OK
    bool comandoLplanta(stringstream &ss) const; // OK
    [[nodiscard]] bool comandoLarea() const;     // OK
    bool comandoLsolo(stringstream &ss) const;   // OK
    [[nodiscard]] bool comandoLferr() const;     // OK

    // ========================================================
    // ========================================================
    // ========================================================

    // Comandos para ações
    bool comandoColhe(stringstream &ss);  // OK
    bool comandoPlanta(stringstream &ss); // OK
    bool comandoLarga();                  // OK
    bool comandoPega(stringstream &ss);   // OK
    bool comandoCompra(stringstream &ss); // OK

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
    [[nodiscard]] bool isJardimCriado() const;

    // Verifica se existe um Jardineiro
    [[nodiscard]] bool isJardineiroNoJardim() const;

    // Verifica se está fora dos limites
    [[nodiscard]] bool isForaDosLimites(int linha, int coluna) const;

    // ========================================================
    // ========================================================

    // Funções para Serialização/Deserialização

    [[nodiscard]] bool salvarJardimEmFicheiro(const string &nome) const;
    bool carregarJardimDeFicheiro(const string &nome);
    static bool apagarFicheiro(const string &nome);

    // Funções auxiliares para criar pastas
    static void criarPastaSeNaoExistir(const string &caminho);

    // Serialização de componentes
    static bool eNumeroValido(const string &str);

    static string serializarSolo(const Solo &s);
    static bool deserializarSolo(Solo &s, const string &dados);

    static string serializarPlanta(const Planta *p);
    static Planta *deserializarPlanta(const string &dados);

    static string serializarFerramenta(const Ferramenta *f);
    static Ferramenta *deserializarFerramenta(const string &dados);
};

#endif
