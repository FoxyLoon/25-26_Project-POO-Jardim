#include "Jardim.h"
#include <iostream>
#include <cstdlib>
#include <vector>

Jardim::Jardim(int l, int c) : linhas(l), colunas(c)
{
    srand(static_cast<unsigned>(time(nullptr)));
    // Alocação da matriz area no construtor
    area = new Solo *[linhas];
    for (int i = 0; i < linhas; ++i)
    {
        area[i] = new Solo[colunas];
    }

    // Inicialização: Criar as 3 ferramentas aleatórias iniciais
    for (int i = 0; i < 3; ++i)
    {
        processaFerramentasAleatorias();
    }
}

Jardim::~Jardim()
{
    // Libertação da memória no destrutor
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
        delete[] area[i];
    }
    delete[] area;
}

void Jardim::avancaInstante()
{
    processaRecursosPlantas();
    processaMortes();
    processaMultiplicacao();
    processaFerramentasAleatorias();
    mostraJardim();
}

void Jardim::processaRecursosPlantas()
{
    for (int i = 0; i < linhas; ++i)
    {
        for (int j = 0; j < colunas; ++j)
        {
            if (area[i][j].temPlanta())
            {
                area[i][j].getPlanta()->processaInstante(area[i][j]);
            }
        }
    }
}

void Jardim::processaMortes()
{
    for (int i = 0; i < linhas; ++i)
    {
        for (int j = 0; j < colunas; ++j)
        {
            if (!area[i][j].temPlanta())
                continue;

            Solo &s = area[i][j];
            Planta *p = s.getPlanta();
            bool deveMorrer = p->verificaMorte(s);

            // Condição Roseira ('r'): morre se rodeada por 8 plantas
            if (p->getSimbolo() == 'r')
            {
                int vizinhos = 0;
                for (int vi = -1; vi <= 1; ++vi)
                {
                    for (int vj = -1; vj <= 1; ++vj)
                    {
                        if (vi == 0 && vj == 0)
                            continue;
                        int ni = i + vi, nj = j + vj;
                        if (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas)
                        {
                            if (area[ni][nj].temPlanta())
                                vizinhos++;
                        }
                    }
                }
                if (vizinhos == 8)
                    deveMorrer = true;
            }

            if (deveMorrer)
            {
                cout << "[MORTE] Planta " << p->getSimbolo() << " em (" << i << "," << j << ")\n";
                p->aoMorrer(s);
                delete p;
                s.removerPlanta(); // Define nullptr internamente no Solo
            }
        }
    }
}

void Jardim::processaMultiplicacao()
{
    for (int i = 0; i < linhas; ++i)
    {
        for (int j = 0; j < colunas; ++j)
        {
            if (!area[i][j].temPlanta())
                continue;

            Planta *p = area[i][j].getPlanta();
            if (p->podeMultiplicar())
            {
                char simb = p->getSimbolo();

                // Caso Especial: Erva Daninha ('e')
                if (simb == 'e')
                {
                    int ni = i + (rand() % 3 - 1);
                    int nj = j + (rand() % 3 - 1);
                    if (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas && !(ni == i && nj == j))
                    {
                        if (area[ni][nj].temPlanta())
                            delete area[ni][nj].getPlanta();
                        area[ni][nj].setPlanta(p->gerarSemente());
                        cout << "[NASCIMENTO] Erva Daninha em (" << ni << "," << nj << ")\n";
                    }
                }
                else
                {
                    // Outras plantas: busca posição vazia aleatória
                    bool exotica = (simb == 'x');
                    vector<pair<int, int>> livres;
                    for (int vi = -1; vi <= 1; ++vi)
                    {
                        for (int vj = -1; vj <= 1; ++vj)
                        {
                            if (vi == 0 && vj == 0)
                                continue;
                            if (exotica && (vi == 0 || vj == 0))
                                continue; // diagonais
                            int ni = i + vi, nj = j + vj;
                            if (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas && area[ni][nj].estaVazio())
                            {
                                livres.push_back({ni, nj});
                            }
                        }
                    }
                    if (!livres.empty())
                    {
                        auto pos = livres[rand() % livres.size()];
                        area[pos.first][pos.second].setPlanta(p->gerarSemente());
                        cout << "[NASCIMENTO] " << simb << " em (" << pos.first << "," << pos.second << ")\n";
                    }
                }
            }
        }
    }
}

void Jardim::processaFerramentasAleatorias()
{
    int total = 0;
    // 1. Verificar se o jardineiro apanhou alguma e contar as existentes
    for (int i = 0; i < linhas; ++i)
    {
        for (int j = 0; j < colunas; ++j)
        {
            if (area[i][j].temFerramenta())
            {
                if (area[i][j].possuiJardineiro())
                {
                    cout << "[INFO] Jardineiro recolheu " << area[i][j].getFerramenta()->getNome() << "\n";
                    // Aqui passar o ponteiro para o inventário do jardineiro antes de anular no solo
                    area[i][j].removerFerramenta();
                }
                else
                {
                    total++;
                }
            }
        }
    }

    // 2. Repor ferramentas até ter 3 no chão
    while (total < 3)
    {
        int rl = rand() % linhas;
        int rc = rand() % colunas;
        if (!area[rl][rc].temFerramenta() && !area[rl][rc].possuiJardineiro())
        {
            area[rl][rc].setFerramenta(gerarFerramentaAleatoria());
            total++;
        }
    }
}

Ferramenta *Jardim::gerarFerramentaAleatoria()
{
    int tipo = rand() % 4;
    switch (tipo)
    {
    case 0:
        return new Regador();
    case 1:
        return new Adubo();
    case 2:
        return new Tesoura();
    case 3:
        return new FerramentaZ();
    default:
        return nullptr;
    }
}

void Jardim::mostraJardim() const
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

    // Jardim com Letras à esquerda
    for (int l = 0; l < linhas; ++l)
    {
        cout << "| " << char('A' + l) << " | ";

        for (int c = 0; c < colunas; ++c)
        {
            cout << area[l][c].getSimboloPrioritario() << " ";
        }
        cout << "|\n";
    }

    // Linha Inferior
    cout << "______";
    for (int c = 0; c < 2 * colunas; ++c)
        cout << "_";
    cout << "_\n";
}