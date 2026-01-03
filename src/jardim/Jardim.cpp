#include "Jardim.h"
#include <iostream>
#include <cstdlib>
#include <vector>

Jardim::Jardim(int l, int c, bool criarFerramentas) : linhas(l), colunas(c)
{
    srand(static_cast<unsigned>(time(nullptr)));
    // Alocação da matriz area no construtor
    area = new Solo *[linhas];
    for (int i = 0; i < linhas; ++i)
    {
        area[i] = new Solo[colunas];
    }

    // Inicialização: Criar as 3 ferramentas aleatórias iniciais
    if (criarFerramentas)
    {
        for (int i = 0; i < 3; ++i)
        {
            processaFerramentasAleatorias();
        }
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
            if (p->getSimboloPlanta() == 'r')
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
                cout << "[MORTE] >> A planta " << p->getSimboloPlanta() << " morreu na posição (" << i << "," << j << ")\n";
                p->aoMorrer(s);
                delete p;
                s.removerPlanta();
            }
        }
    }
}

void Jardim::processaMultiplicacao()
{
    // Criamos um vetor temporário para armazenar onde as novas plantas devem nascer
    // Isso evita processar uma planta que acabou de nascer no mesmo turno
    struct NovaPlanta
    {
        int l, c;
        Planta *semente;
    };
    vector<NovaPlanta> sementesParaPlantar;

    for (int l = 0; l < linhas; ++l)
    {
        for (int c = 0; c < colunas; ++c)
        {
            Solo &soloAtual = area[l][c];

            // 1. Verificar se existe planta e se ela pode multiplicar
            if (soloAtual.temPlanta() && soloAtual.getPlanta()->podeMultiplicar())
            {

                // 2. Procurar uma célula vizinha livre (Cima, Baixo, Esquerda, Direita)
                int vizinhosL[] = {l - 1, l + 1, l, l};
                int vizinhosC[] = {c, c, c - 1, c + 1};

                for (int i = 0; i < 4; ++i)
                {
                    int nl = vizinhosL[i];
                    int nc = vizinhosC[i];

                    // Verificar limites do jardim e se o solo está vazio
                    if (nl >= 0 && nl < linhas && nc >= 0 && nc < colunas)
                    {
                        if (area[nl][nc].estaVazio())
                        {
                            // Gera a semente (usa o método virtual da tua classe Planta)
                            Planta *novaSemente = soloAtual.getPlanta()->gerarSemente();

                            if (novaSemente != nullptr)
                            {
                                sementesParaPlantar.push_back({nl, nc, novaSemente});
                            }
                            // Para a Roseira/Cacto, talvez queiras apenas 1 semente por turno
                            break;
                        }
                    }
                }
            }
        }
    }

    // 3. Efetivar a plantação das sementes recolhidas
    for (auto &n : sementesParaPlantar)
    {
        // Verificação dupla para evitar que duas plantas vizinhas "nasçam" no mesmo lugar
        if (area[n.l][n.c].estaVazio())
        {
            area[n.l][n.c].setPlanta(n.semente);
        }
        else
        {
            delete n.semente; // Limpeza de memória se o lugar foi ocupado entretanto
        }
    }
}

void Jardim::processaFerramentasAleatorias()
{
    int total = 0;
    for (int i = 0; i < linhas; ++i)
    {
        for (int j = 0; j < colunas; ++j)
        {
            if (area[i][j].temFerramenta())
            {
                total++;
            }
        }
    }

    // Mantém sempre 3 ferramentas no chão
    while (total < 3)
    {
        int rl = rand() % linhas;
        int rc = rand() % colunas;
        if (area[rl][rc].estaVazio() && !area[rl][rc].possuiJardineiro())
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

int Jardim::getLinhas() const
{
    return linhas;
}

int Jardim::getColunas() const
{
    return colunas;
}

Solo &Jardim::getSolo(int l, int c)
{
    return area[l][c];
}