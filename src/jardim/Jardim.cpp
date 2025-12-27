#include "Jardim.h"
#include <iostream>
#include <ctime>
#include "../plantas/Planta.h"
#include "../ferramentas/Ferramenta.h"

using namespace std;

Jardim::Jardim(int l, int c) : linhas(l), colunas(c) {
    srand(static_cast<unsigned>(time(nullptr)));

    // Alocação dinâmica sem uso de coleções STL
    area = new Solo*[linhas];
    for (int i = 0; i < linhas; ++i) {
        area[i] = new Solo[colunas];
    }

    // Inicialização dos valores aleatórios com Settings
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            int agua = Settings::Jardim::agua_min +
                rand() % (Settings::Jardim::agua_max - Settings::Jardim::agua_min + 1);
            int nutrientes = Settings::Jardim::nutrientes_min +
                rand() % (Settings::Jardim::nutrientes_max - Settings::Jardim::nutrientes_min + 1);

            area[i][j].setAgua(agua);
            area[i][j].setNutrientes(nutrientes);
        }
    }
}

Jardim::~Jardim() {
    // Limpar todas as plantas e ferramentas
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (area[i][j].temPlanta()) {
                delete area[i][j].getPlanta();
            }
            if (area[i][j].temFerramenta()) {
                delete area[i][j].getFerramenta();
            }
        }
    }

    // Limpar a área
    for (int i = 0; i < linhas; ++i)
        delete[] area[i];
    delete[] area;
}

Solo *Jardim::getSolo(int l, int c) {
    if (l < 0 || l >= linhas || c < 0 || c >= colunas)
        return nullptr;
    return &area[l][c];
}

void Jardim::mostrar() const {
    cout << "______";
    for (int c = 0; c < 2*colunas; ++c)
        cout << "_";
    cout << "_";
    cout << "\n";

    cout << "| - | ";
    for (int c = 0; c < colunas; ++c)
        cout << char('A' + c) << " ";
    cout << "|";
    cout << "\n";

    cout << "======";
    for (int c = 0; c < 2*colunas; ++c)
        cout << "=";
    cout << "=";
    cout << "\n";

    for (int i = 0; i < linhas; ++i) {
        cout << "| ";
        cout << char('A' + i) << " | ";
        for (int j = 0; j < colunas; ++j) {
            cout << area[i][j].getSimboloVisivel() << " ";
        }
        cout << "|";
        cout << '\n';
    }

    cout << "______";
    for (int c = 0; c < 2*colunas; ++c)
        cout << "_";
    cout << "_";
    cout << "\n";
}

void Jardim::mostrarComJardineiro(const Jardineiro &j) const {
    cout << "______";
    for (int c = 0; c < 2*colunas; ++c)
        cout << "_";
    cout << "_";
    cout << "\n";

    cout << "| - | ";
    for (int c = 0; c < colunas; ++c)
        cout << char('A' + c) << " ";
    cout << "|";
    cout << "\n";

    for (int i = 0; i < linhas; ++i) {
        cout << "| ";
        cout << char('A' + i) << " | ";
        for (int k = 0; k < colunas; ++k) {
            if (j.isNoJardim() && j.getLinha() == i && j.getColuna() == k)
                cout << "*" << " ";  // jardineiro tem prioridade visual
            else
                cout << area[i][k].getSimboloVisivel() << " ";
        }
        cout << "|";
        cout << '\n';
    }

    cout << "______";
    for (int c = 0; c < 2*colunas; ++c)
        cout << "_";
    cout << "_";
    cout << "\n";
}