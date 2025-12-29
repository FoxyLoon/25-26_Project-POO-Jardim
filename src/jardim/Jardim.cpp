#include "Jardim.h"
#include <iostream>
#include <ctime>
#include "../Settings.h"
#include "../plantas/Roseira.h"
#include "../plantas/Cacto.h"
#include "../plantas/ErvaDaninha.h"
#include "../plantas/PlantaExotica.h"
#include "../ferramentas/Regador.h"
#include "../ferramentas/Adubo.h"
#include "../ferramentas/Tesoura.h"
#include "../ferramentas/FerramentaZ.h"

using namespace std;

// Esta classe representa o jardim (grelha retangular constituidas por diversos "Solo's")
Jardim::Jardim(int l, int c) : linhas(l), colunas(c)
{

    // Inicialização dos valores aleatórios
    srand(static_cast<unsigned>(time(nullptr)));

    // Criação da grelha/jaridm com vetores
    area = vector<vector<Solo>>(linhas, vector<Solo>(colunas));

    // Valores aleatórios de Água e Nutrientes
    for (int i = 0; i < linhas; ++i)
    {
        for (int j = 0; j < colunas; ++j)
        {
            int agua = Settings::Jardim::agua_min + rand() % (Settings::Jardim::agua_max - Settings::Jardim::agua_min + 1);
            int nutrientes = Settings::Jardim::nutrientes_min + rand() % (Settings::Jardim::nutrientes_max - Settings::Jardim::nutrientes_min + 1);
            ;

            area[i][j].setAgua(agua);
            area[i][j].setNutrientes(nutrientes);

            // Probabilidade da Planta
            if ((rand() % 100) < Settings::Jardim::probabilidade_planta)
            {
                int tipo = rand() % 4;
                switch (tipo)
                {
                    case 0:
                        area[i][j].setPlanta(new Roseira()); // r
                        break;
                    case 1:
                        area[i][j].setPlanta(new Cacto()); // c
                        break;
                    case 2:
                        area[i][j].setPlanta(new ErvaDaninha()); // e
                        break;
                    case 3:
                        area[i][j].setPlanta(new PlantaExotica()); // x
                        break;
                    default:
                        break;
                }
            }

            // Probabilidade da Ferramenta
            if ((rand() % 100) < Settings::Jardim::probabilidade_ferramenta)
            {
                int tipo = rand() % 4;
                switch (tipo)
                {
                    case 0:
                        area[i][j].setFerramenta(new Regador()); // g
                        break;
                    case 1:
                        area[i][j].setFerramenta(new Adubo()); // a
                        break;
                    case 2:
                        area[i][j].setFerramenta(new Tesoura()); // t
                        break;
                    case 3:
                        area[i][j].setFerramenta(new FerramentaZ()); // z
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

Jardim::~Jardim()
{
    // Limpa todas as plantas e ferramentas do jardim
    // antes de destruir o Jardim por completo
    for (int i = 0; i < linhas; ++i)
    {
        for (int j = 0; j < colunas; ++j)
        {
            if (area[i][j].temPlanta())
            {
                delete area[i][j].getPlanta();
            }
            if (area[i][j].temFerramenta())
            {
                delete area[i][j].getFerramenta();
            }
        }
    }
}

Solo *Jardim::getSolo(int l, int c)
{
    if (l < 0 || l >= linhas || c < 0 || c >= colunas)
        return nullptr;
    return &area[l][c];
}

// Mostra o Jardim
void Jardim::mostraJardim(const Jardineiro &jardineiro) const
{
    // Linha Superior
    cout << "______";
    for (int c = 0; c < 2 * colunas; ++c)
        cout << "_";
    cout << "_\n";

    // Linhas de Letras
    cout << "| - | ";
    for (int c = 0; c < colunas; ++c)
        cout << char('A' + c) << " ";
    cout << "|\n";

    // Separador
    cout << "======";
    for (int c = 0; c < 2 * colunas; ++c)
        cout << "=";
    cout << "=\n";

    // Solo com Letras à esquerda
    for (int i = 0; i < linhas; ++i)
    {
        cout << "| " << char('A' + i) << " | ";
        for (int j = 0; j < colunas; ++j)
        {
            // Caso o Jardineiro esteja no jardim, mostrar o Jardineiro primeiro
            // Aqui deverá ser definido a prioridade a mostrar no Jardim!!!
            if (jardineiro.isNoJardim() && jardineiro.getLinha() == i && jardineiro.getColuna() == j)
                cout << "*" << " ";
            else
                cout << area[i][j].getSimboloVisivel() << " ";
        }
        cout << "|\n";
    }

    // Linha Inferior
    cout << "______";
    for (int c = 0; c < 2 * colunas; ++c)
        cout << "_";
    cout << "_\n";
}
