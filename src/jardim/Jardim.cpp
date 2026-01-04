#include "Jardim.h"
#include <iostream>
#include <vector>
#include <random>

#include "../ferramentas/Regador.h"
#include "../ferramentas/Adubo.h"
#include "../ferramentas/Tesoura.h"
#include "../ferramentas/FerramentaZ.h"

Jardim::Jardim(int linhas, int colunas, bool criarFerramentas) : linhas(linhas), colunas(colunas)
{
    srand(static_cast<unsigned>(time(nullptr))); // NOLINT

    // Alocação da matriz area no construtor
    area = new Solo *[linhas];
    for (int linha_atual = 0; linha_atual < linhas; ++linha_atual)
    {
        area[linha_atual] = new Solo[colunas];
    }

    // Inicialização: Criar as 3 ferramentas aleatórias iniciais
    if (criarFerramentas)
    {
        for (int linha_atual = 0; linha_atual < 3; ++linha_atual)
        {
            processaFerramentasAleatorias();
        }
    }
}

Jardim::~Jardim()
{
    // Libertação da memória no destrutor
    for (int linha_atual = 0; linha_atual < linhas; ++linha_atual)
    {
        for (int coluna_atual = 0; coluna_atual < colunas; ++coluna_atual)
        {
            if (area[linha_atual][coluna_atual].temPlanta())
            {
                delete area[linha_atual][coluna_atual].getPlanta();
            }
            if (area[linha_atual][coluna_atual].temFerramenta())
            {
                delete area[linha_atual][coluna_atual].getFerramenta();
            }
        }
        delete[] area[linha_atual];
    }
    delete[] area;
}

void Jardim::avancaInstante() const
{
    processaRecursosPlantas();
    processaMortes();
    processaMultiplicacao();
    processaFerramentasAleatorias();
}

void Jardim::processaRecursosPlantas() const
{
    for (int linha_atual = 0; linha_atual < linhas; ++linha_atual)
    {
        for (int coluna_atual = 0; coluna_atual < colunas; ++coluna_atual)
        {
            if (area[linha_atual][coluna_atual].temPlanta())
            {
                area[linha_atual][coluna_atual].getPlanta()->processaInstante(area[linha_atual][coluna_atual]);
            }
        }
    }
}

void Jardim::processaMortes() const
{
    for (int linha_atual = 0; linha_atual < linhas; ++linha_atual)
    {
        for (int coluna_atual = 0; coluna_atual < colunas; ++coluna_atual)
        {
            if (!area[linha_atual][coluna_atual].temPlanta())
                continue;

            Solo &s = area[linha_atual][coluna_atual];
            Planta *p = s.getPlanta();
            bool deveMorrer = p->verificaMorte(s);

            // Condição Roseira
            if (p->getSimboloPlanta() == 'r')
            {
                int vizinhos = 0;
                // Procura ao redor da Roseira
                for (int linha_vizinha = -1; linha_vizinha <= 1; ++linha_vizinha)
                {
                    for (int coluna_vizinha = -1; coluna_vizinha <= 1; ++coluna_vizinha)
                    {
                        // Ignora o centro
                        if (linha_vizinha == 0 && coluna_vizinha == 0)
                            continue;

                        // Verifica se a vizinha existe
                        int posicao_linha = linha_atual + linha_vizinha, posicao_coluna = coluna_atual + coluna_vizinha;
                        if (posicao_linha >= 0 && posicao_linha < linhas && posicao_coluna >= 0 && posicao_coluna < colunas)
                        {
                            if (area[posicao_linha][posicao_coluna].temPlanta())
                                vizinhos++;
                        }
                    }
                }
                // Morre se tiver 8 vizinhos
                if (vizinhos == 8)
                    deveMorrer = true;
            }

            // Pós-Morte
            if (deveMorrer)
            {
                cout << "[MORTE] >> A planta " << p->getSimboloPlanta() << " morreu na posição (" << linha_atual << "," << coluna_atual << ")\n";
                p->aoMorrer(s);
                delete p;
                s.removerPlanta();
            }
        }
    }
}

void Jardim::processaMultiplicacao() const
{
    struct NovaPlanta
    {
        int linha_atual, coluna_atual;
        Planta *semente;
    };
    vector<NovaPlanta> sementesParaPlantar;

    for (int linha_atual = 0; linha_atual < linhas; ++linha_atual)
    {
        for (int coluna_atual = 0; coluna_atual < colunas; ++coluna_atual)
        {
            Solo &soloAtual = area[linha_atual][coluna_atual];

            if (soloAtual.temPlanta() && soloAtual.getPlanta()->podeMultiplicar())
            {
                Planta *plantaPai = soloAtual.getPlanta();
                char simbolo = plantaPai->getSimboloPlanta();

                vector<pair<int, int>> vizinhos;
                if (simbolo == 'x')
                { // Planta Exótica: Apenas Diagonais
                    vizinhos = {{linha_atual - 1, coluna_atual - 1}, {linha_atual - 1, coluna_atual + 1}, {linha_atual + 1, coluna_atual - 1}, {linha_atual + 1, coluna_atual + 1}};
                }
                else
                { // Outras: Cima, Baixo, Esquerda, Direita
                    vizinhos = {{linha_atual - 1, coluna_atual}, {linha_atual + 1, coluna_atual}, {linha_atual, coluna_atual - 1}, {linha_atual, coluna_atual + 1}};
                }

                // Escolher uma posição aleatória dos vizinhos válidos
                for (size_t i = 0; i < vizinhos.size(); ++i)
                {
                    size_t j = i + (rand() % (vizinhos.size() - i)); // NOLINT
                    swap(vizinhos[i], vizinhos[j]);
                }

                // Planta no primeiro vizinho
                for (auto &pos : vizinhos)
                {
                    int nova_linha = pos.first;
                    int nova_coluna = pos.second;

                    if (nova_linha >= 0 && nova_linha < linhas && nova_coluna >= 0 && nova_coluna < colunas)
                    {
                        Solo &soloDestino = area[nova_linha][nova_coluna];

                        // Erva Daninha: Se houver planta, mata-a
                        if (simbolo == 'e' || soloDestino.estaVazio())
                        {
                            Planta *novaSemente = plantaPai->gerarSemente();
                            if (novaSemente != nullptr)
                            {
                                sementesParaPlantar.push_back({nova_linha, nova_coluna, novaSemente});
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    // Plantar as sementes
    for (auto &n : sementesParaPlantar)
    {
        Solo &soloAlvo = area[n.linha_atual][n.coluna_atual];

        if (n.semente->getSimboloPlanta() == 'e')
        {
            // Erva Daninha: Se houver planta, mata-a (delete) e ocupa o lugar
            if (soloAlvo.temPlanta())
            {
                delete soloAlvo.removerPlanta();
            }
            soloAlvo.setPlanta(n.semente);
        }
        else if (soloAlvo.estaVazio())
        {
            // Plantas normais: Só ocupam se o solo continuar vazio
            soloAlvo.setPlanta(n.semente);
        }
        else
        {
            // Se o lugar foi ocupado entretanto (ex: por uma Erva Daninha), apaga a semente
            delete n.semente;
        }
    }
}

void Jardim::processaFerramentasAleatorias() const
{
    int total = 0;
    for (int linha_atual = 0; linha_atual < linhas; ++linha_atual)
    {
        for (int coluna_atual = 0; coluna_atual < colunas; ++coluna_atual)
        {
            if (area[linha_atual][coluna_atual].temFerramenta())
            {
                total++;
            }
        }
    }

    // Mantém sempre 3 ferramentas no chão
    while (total < 3)
    {
        int linha_aleatoria = rand() % linhas;   // NOLINT
        int coluna_aleatoria = rand() % colunas; // NOLINT
        if (area[linha_aleatoria][coluna_aleatoria].estaVazio() && !area[linha_aleatoria][coluna_aleatoria].possuiJardineiro())
        {
            area[linha_aleatoria][coluna_aleatoria].setFerramenta(gerarFerramentaAleatoria());
            total++;
        }
    }
}

Ferramenta *Jardim::gerarFerramentaAleatoria()
{
    switch (rand() % 4) // NOLINT
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
    for (int coluna_atual = 0; coluna_atual < 2 * colunas; ++coluna_atual)
        cout << "_";
    cout << "_\n";

    // Linhas de Letras
    cout << "| - | ";
    for (int coluna_atual = 0; coluna_atual < colunas; ++coluna_atual)
        cout << static_cast<char>('A' + coluna_atual) << " ";
    cout << "|\n";

    // Separador
    cout << "======";
    for (int coluna_atual = 0; coluna_atual < 2 * colunas; ++coluna_atual)
        cout << "=";
    cout << "=\n";

    // Jardim com Letras à esquerda
    for (int linha_atual = 0; linha_atual < linhas; ++linha_atual)
    {
        cout << "| " << static_cast<char>('A' + linha_atual) << " | ";

        for (int coluna_atual = 0; coluna_atual < colunas; ++coluna_atual)
        {
            cout << area[linha_atual][coluna_atual].getSimboloPrioritario() << " ";
        }
        cout << "|\n";
    }

    // Linha Inferior
    cout << "______";
    for (int coluna_atual = 0; coluna_atual < 2 * colunas; ++coluna_atual)
        cout << "_";
    cout << "_\n";
}

int Jardim::getLinhas() const
{
    return linhas;
}

int Jardim::getColunas() const
{
    return colunas;
}

Solo &Jardim::getSolo(int linha_solo, int coluna_solo) const
{
    return area[linha_solo][coluna_solo];
}