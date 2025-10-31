#include "Jardim.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

Jardim::Jardim(int l, int c) : linhas(l), colunas(c) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Alocação dinâmica sem uso de coleções STL
    area = new Solo*[linhas];
    for (int i = 0; i < linhas; ++i) {
        area[i] = new Solo[colunas];
    }

    // Inicialização dos valores aleatórios com Settings
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            area[i][j].agua = Settings::Jardim::agua_min +
                std::rand() % (Settings::Jardim::agua_max - Settings::Jardim::agua_min + 1);
            area[i][j].nutrientes = Settings::Jardim::nutrientes_min +
                std::rand() % (Settings::Jardim::nutrientes_max - Settings::Jardim::nutrientes_min + 1);
        }
    }
}

Jardim::~Jardim() {
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
    std::cout << "   ";
    for (int c = 0; c < colunas; ++c)
        std::cout << char('A' + c);
    std::cout << "\n";

    for (int i = 0; i < linhas; ++i) {
        std::cout << char('A' + i) << " ";
        for (int j = 0; j < colunas; ++j)
            std::cout << ".";
        std::cout << "\n";
    }
}

void Jardim::mostrarComJardineiro(const Jardineiro &j) const {
    std::cout << "   ";
    for (int c = 0; c < colunas; ++c)
        std::cout << char('A' + c);
    std::cout << "\n";

    for (int i = 0; i < linhas; ++i) {
        std::cout << char('A' + i) << " ";
        for (int k = 0; k < colunas; ++k) {
            if (j.isNoJardim() && j.getLinha() == i && j.getColuna() == k)
                std::cout << "*";  // jardineiro tem prioridade visual
            else
                std::cout << ".";
        }
        std::cout << "\n";
    }
}
