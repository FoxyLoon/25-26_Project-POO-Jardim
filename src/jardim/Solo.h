#ifndef SOLO_H
#define SOLO_H

#include <string>
#include <sstream>
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
    int getAgua() const;
    void setAgua(int valor);
    int getNutrientes() const;
    void setNutrientes(int valor);

    // Gestão de recursos (adição/remoção)
    void adicionarAgua(int quantidade);
    void removerAgua(int quantidade);
    void adicionarNutrientes(int quantidade);
    void removerNutrientes(int quantidade);

    // Gestão da Planta
    bool temPlanta() const;
    void setPlanta(Planta *p);
    Planta *getPlanta() const;
    void removerPlanta();

    // Gestão da Ferramenta
    bool temFerramenta() const;
    void setFerramenta(Ferramenta *f);
    Ferramenta *getFerramenta() const;
    void removerFerramenta();

    // Gestão do Jardineiro (entrada/saída/movimento)
    bool possuiJardineiro() const;
    void setJardineiro(bool estado);

    // Verificações de estado e símbolos
    bool estaVazio() const;
    char getSimboloPrioritario() const;
    string getInfoSolo() const;
};

#endif