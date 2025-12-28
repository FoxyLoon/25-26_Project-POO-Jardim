#include "Jardim.h"
#include <iostream>
#include <ctime>
#include "../Settings.h"

using namespace std;

// Esta classe representa o jardim (grelha retangular constituidas por diversos "Solo's")
Jardim::Jardim(int l, int c) : linhas(l), colunas(c)
{

    // Inicialização dos valores aleatórios
    srand(static_cast<unsigned>(time(nullptr)));

    // Criação da grelha/jaridm com vetores
    area = vector<vector<Solo>>(linhas, vector<Solo>(colunas));

    // Valores aleatórios (depende do header Settings.h)
    for (int i = 0; i < linhas; ++i)
    {
        for (int j = 0; j < colunas; ++j)
        {
            int agua = Settings::Jardim::agua_min + rand() % (Settings::Jardim::agua_max - Settings::Jardim::agua_min + 1);
            int nutrientes = Settings::Jardim::nutrientes_min + rand() % (Settings::Jardim::nutrientes_max - Settings::Jardim::nutrientes_min + 1);

            area[i][j].setAgua(agua);
            area[i][j].setNutrientes(nutrientes);
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

// Acesso individual a cada posição do Jardim
Solo *Jardim::getSolo(int l, int c)
{
    if (l < 0 || l >= linhas || c < 0 || c >= colunas)
        return nullptr;
    return &area[l][c];
}

// Mostra o Jardim
void Jardim::mostrar() const
{
    cout << "______";
    for (int c = 0; c < 2 * colunas; ++c)
        cout << "_";
    cout << "_";
    cout << "\n";

    cout << "| - | ";
    for (int c = 0; c < colunas; ++c)
        cout << char('A' + c) << " ";
    cout << "|";
    cout << "\n";

    cout << "======";
    for (int c = 0; c < 2 * colunas; ++c)
        cout << "=";
    cout << "=";
    cout << "\n";

    for (int i = 0; i < linhas; ++i)
    {
        cout << "| ";
        cout << char('A' + i) << " | ";
        for (int j = 0; j < colunas; ++j)
        {
            cout << area[i][j].getSimboloVisivel() << " ";
        }
        cout << "|";
        cout << '\n';
    }

    cout << "______";
    for (int c = 0; c < 2 * colunas; ++c)
        cout << "_";
    cout << "_";
    cout << "\n";
}

void Jardim::mostrarComJardineiro(const Jardineiro &j) const
{
    // Linha Superior
    cout << "______";
    for (int c = 0; c < 2 * colunas; ++c)
        cout << "_";
    cout << "_\n";

    cout << "| - | ";
    for (int c = 0; c < colunas; ++c)
        cout << char('A' + c) << " ";
    cout << "|\n";

    for (int i = 0; i < linhas; ++i)
    {
        cout << "| " << char('A' + i) << " | ";
        for (int k = 0; k < colunas; ++k)
        {
            if (j.isNoJardim() && j.getLinha() == i && j.getColuna() == k)
                cout << "*" << " "; // jardineiro tem prioridade visual
            else
                cout << area[i][k].getSimboloVisivel() << " ";
        }
        cout << "|\n";
    }

    cout << "______";
    for (int c = 0; c < 2 * colunas; ++c)
        cout << "_";
    cout << "_\n";
}

