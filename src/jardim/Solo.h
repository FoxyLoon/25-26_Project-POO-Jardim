#ifndef SOLO_H
#define SOLO_H

// Forward declarations
class Planta;
class Ferramenta;

// Classe Solo - representa um pedaço de solo do jardim
// Cada posição pode conter propriedades (água, nutrientes) e entidades (planta, ferramenta)
class Solo {
private:
    int agua;
    int nutrientes;
    Planta* planta;
    Ferramenta* ferramenta;

public:
    // Construtores
    Solo();
    Solo(int agua_inicial, int nutrientes_iniciais);

    // Destrutor - NÃO liberta planta/ferramenta (geridas pelo Jardim)
    ~Solo();

    // Getters para propriedades do solo
    int getAgua() const;
    int getNutrientes() const;

    // Setters para propriedades do solo (com validação)
    void setAgua(int valor);
    void setNutrientes(int valor);

    // Modificadores de água e nutrientes
    void adicionarAgua(int quantidade);
    void removerAgua(int quantidade);
    void adicionarNutrientes(int quantidade);
    void removerNutrientes(int quantidade);

    // Gestão de Planta
    Planta* getPlanta() const;
    void setPlanta(Planta* p);
    bool temPlanta() const;
    Planta* removerPlanta();  // Remove e retorna a planta (sem delete)

    // Gestão de Ferramenta
    Ferramenta* getFerramenta() const;
    void setFerramenta(Ferramenta* f);
    bool temFerramenta() const;
    Ferramenta* removerFerramenta();  // Remove e retorna a ferramenta (sem delete)

    // Verifica se está vazio
    bool estaVazio() const;

    // Retorna o símbolo a ser exibido (considerando prioridades)
    // Prioridade: Jardineiro > Planta > Ferramenta > vazio
    // Nota: Jardineiro é tratado externamente na visualização
    char getSimboloVisivel() const;
};

#endif