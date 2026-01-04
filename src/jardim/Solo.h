#ifndef SOLO_H
#define SOLO_H

#include <string>
#include "../plantas/Planta.h"
#include "../ferramentas/Ferramenta.h"

using namespace std;

class Planta;
class Ferramenta;

class Solo
{
private:
    int agua;
    int nutrientes;
    Planta *planta;
    Ferramenta *ferramenta;
    bool temJardineiro;

public:
    // Construtor e Destrutor
    Solo();
    ~Solo() = default;

    // Getters e Setters de recursos
    [[nodiscard]] int getAgua() const;
    void setAgua(int valor);
    [[nodiscard]] int getNutrientes() const;
    void setNutrientes(int valor);

    // Gestão de recursos (adição/remoção)
    void adicionarAgua(int quantidade);
    void removerAgua(int quantidade);
    void adicionarNutrientes(int quantidade);
    void removerNutrientes(int quantidade);

    // Gestão da Planta
    [[nodiscard]] bool temPlanta() const;
    void setPlanta(Planta *p);
    [[nodiscard]] Planta *getPlanta() const;
    Planta *removerPlanta();

    // Gestão da Ferramenta
    [[nodiscard]] bool temFerramenta() const;
    void setFerramenta(Ferramenta *f);
    [[nodiscard]] Ferramenta *getFerramenta() const;
    Ferramenta *removerFerramenta();

    // Gestão do Jardineiro (entrada/saída/movimento)
    [[nodiscard]] bool possuiJardineiro() const;
    void setJardineiro(bool estado);

    // Verificações de estado e símbolos
    [[nodiscard]] bool estaVazio() const;
    [[nodiscard]] char getSimboloPrioritario() const;
    [[nodiscard]] string getInfoSolo() const;
};

#endif