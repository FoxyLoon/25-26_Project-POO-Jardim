#ifndef SOLO_H
#define SOLO_H

// Forward declarations
class Planta;
class Ferramenta;

// Estrutura para representar um pedaço de solo do jardim.
// Cada posição pode conter:
// - Propriedades do solo (água e nutrientes)
// - 0 ou 1 planta (ponteiro)
// - 0 ou 1 ferramenta (ponteiro)
class Solo {
public:
    int agua;
    int nutrientes;
    Planta* planta;           // ponteiro para planta (nullptr se não houver)
    Ferramenta* ferramenta;   // ponteiro para ferramenta (nullptr se não houver)

    // Construtor padrão
    Solo() : agua(0), nutrientes(0), planta(nullptr), ferramenta(nullptr) {}

    // Métodos auxiliares
    bool temPlanta() const { return planta != nullptr; }
    bool temFerramenta() const { return ferramenta != nullptr; }
    bool estaVazio() const { return !temPlanta() && !temFerramenta(); }

    // Retorna o símbolo a ser exibido (considerando prioridades)
    // Prioridade: Jardineiro > Planta > Ferramenta > vazio
    // Nota: Jardineiro é tratado externamente na visualização
    char getSimboloVisivel() const;
};

#endif