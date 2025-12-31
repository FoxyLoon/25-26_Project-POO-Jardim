#include "Jardim.h"
#include <iostream>
#include <ctime>
#include <vector>
#include "../Settings.h"
#include "../plantas/Roseira.h"
#include "../plantas/Cacto.h"
#include "../plantas/ErvaDaninha.h"
#include "../plantas/PlantaExotica.h"
#include "../ferramentas/Ferramenta.h"

using namespace std;

// ========================================================
// CONSTRUTOR E DESTRUTOR
// ========================================================

Jardim::Jardim(int l, int c) : linhas(l), colunas(c) {
    // Inicialização do gerador aleatório
    srand(static_cast<unsigned>(time(nullptr)));

    // Criação da grelha
    area = vector<vector<Solo>>(linhas, vector<Solo>(colunas));

    // Inicializar cada posição do solo
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            // Água e nutrientes aleatórios
            int agua = Settings::Jardim::agua_min +
                      rand() % (Settings::Jardim::agua_max - Settings::Jardim::agua_min + 1);
            int nutrientes = Settings::Jardim::nutrientes_min +
                           rand() % (Settings::Jardim::nutrientes_max - Settings::Jardim::nutrientes_min + 1);

            area[i][j].setAgua(agua);
            area[i][j].setNutrientes(nutrientes);

            // Probabilidade de planta inicial
            if ((rand() % 100) < Settings::Jardim::probabilidade_planta) {
                int tipo = rand() % 4;
                switch (tipo) {
                    case 0: area[i][j].setPlanta(new Roseira()); break;
                    case 1: area[i][j].setPlanta(new Cacto()); break;
                    case 2: area[i][j].setPlanta(new ErvaDaninha()); break;
                    case 3: area[i][j].setPlanta(new PlantaExotica()); break;
                }
            }

            // Probabilidade de ferramenta inicial
            if ((rand() % 100) < Settings::Jardim::probabilidade_ferramenta) {
                int tipo = rand() % 4;
                Ferramenta* f = nullptr;
                switch (tipo) {
                    case 0: f = Ferramenta::criar('g'); break;
                    case 1: f = Ferramenta::criar('a'); break;
                    case 2: f = Ferramenta::criar('t'); break;
                    case 3: f = Ferramenta::criar('z'); break;
                }
                if (f) area[i][j].setFerramenta(f);
            }
        }
    }
}

Jardim::~Jardim() {
    // Libertar todas as plantas e ferramentas
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (area[i][j].temPlanta()) {
                delete area[i][j].getPlanta();
                area[i][j].setPlanta(nullptr);
            }
            if (area[i][j].temFerramenta()) {
                delete area[i][j].getFerramenta();
                area[i][j].setFerramenta(nullptr);
            }
        }
    }
}

// ========================================================
// ACESSO AO SOLO
// ========================================================

Solo* Jardim::getSolo(int l, int c) {
    if (l < 0 || l >= linhas || c < 0 || c >= colunas) {
        return nullptr;
    }
    return &area[l][c];
}

// ========================================================
// VISUALIZAÇÃO
// ========================================================

void Jardim::mostraJardim(const Jardineiro& jardineiro) const {
    // Linha superior
    cout << "______";
    for (int c = 0; c < 2 * colunas; ++c) cout << "_";
    cout << "_\n";

    // Letras das colunas
    cout << "| - | ";
    for (int c = 0; c < colunas; ++c) {
        cout << char('A' + c) << " ";
    }
    cout << "|\n";

    // Separador
    cout << "======";
    for (int c = 0; c < 2 * colunas; ++c) cout << "=";
    cout << "=\n";

    // Solo com letras à esquerda
    for (int i = 0; i < linhas; ++i) {
        cout << "| " << char('A' + i) << " | ";
        for (int j = 0; j < colunas; ++j) {
            // Prioridade: Jardineiro > Planta > Ferramenta > vazio
            if (jardineiro.isNoJardim() &&
                jardineiro.getLinha() == i &&
                jardineiro.getColuna() == j) {
                cout << "*" << " ";
            } else {
                cout << area[i][j].getSimboloVisivel() << " ";
            }
        }
        cout << "|\n";
    }

    // Linha inferior
    cout << "______";
    for (int c = 0; c < 2 * colunas; ++c) cout << "_";
    cout << "_\n";
}

// ========================================================
// SIMULAÇÃO - AVANÇAR INSTANTE
// ========================================================

void Jardim::avancarInstante() {
    cout << "\n[SIMULAÇÃO] Processando instante...\n";

    // 1. PROCESSAR TODAS AS PLANTAS
    processarPlantas();

    // 2. VERIFICAR E PROCESSAR MORTES
    processarMortes();

    // 3. VERIFICAR E PROCESSAR MULTIPLICAÇÕES
    processarMultiplicacoes();

    cout << "[SIMULAÇÃO] Instante concluído.\n";
}

void Jardim::processarPlantas() {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (area[i][j].temPlanta()) {
                // Cada planta processa seu ciclo de vida
                area[i][j].getPlanta()->processaInstante(area[i][j]);
            }
        }
    }
}

void Jardim::processarMortes() {
    int totalMortes = 0;

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (!area[i][j].temPlanta()) continue;

            Planta* p = area[i][j].getPlanta();
            bool deveMorrer = false;

            // Verificação básica de morte
            if (p->verificaMorte(area[i][j])) {
                deveMorrer = true;
            }

            // Verificação especial para Roseira: cercada por vizinhos
            Roseira* roseira = dynamic_cast<Roseira*>(p);
            if (roseira && estaCercada(i, j)) {
                deveMorrer = true;
            }

            if (deveMorrer) {
                // Executar ações pós-morte
                p->aoMorrer(area[i][j]);

                // Remover e deletar planta
                delete p;
                area[i][j].setPlanta(nullptr);

                totalMortes++;
                cout << "  [MORTE] Planta em " << char('a' + i) << char('a' + j) << "\n";
            }
        }
    }

    if (totalMortes > 0) {
        cout << "[INFO] Total de plantas mortas: " << totalMortes << "\n";
    }
}

void Jardim::processarMultiplicacoes() {
    // IMPORTANTE: Usar lista temporária para evitar processar plantas recém-criadas
    struct Multiplicacao {
        int linha, coluna;
        Planta* plantaMae;
    };

    vector<Multiplicacao> multiplicacoes;

    // 1. IDENTIFICAR PLANTAS QUE PODEM MULTIPLICAR
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (area[i][j].temPlanta()) {
                Planta* p = area[i][j].getPlanta();
                if (p->podeMultiplicar()) {
                    multiplicacoes.push_back({i, j, p});
                }
            }
        }
    }

    // 2. PROCESSAR CADA MULTIPLICAÇÃO
    for (const auto& mult : multiplicacoes) {
        multiplicarPlanta(mult.linha, mult.coluna, mult.plantaMae);
    }
}

void Jardim::multiplicarPlanta(int l, int c, Planta* mae) {
    // Encontrar posição vizinha apropriada
    vector<pair<int, int>> posicoes;

    // Determinar padrão de multiplicação baseado no tipo de planta
    ErvaDaninha* erva = dynamic_cast<ErvaDaninha*>(mae);
    PlantaExotica* exotica = dynamic_cast<PlantaExotica*>(mae);

    if (exotica) {
        // Bambu Lunar: multiplica em diagonal (NE, SE, SW, NW)
        posicoes = {{l-1, c+1}, {l+1, c+1}, {l+1, c-1}, {l-1, c-1}};
    } else {
        // Outras plantas: vizinhos ortogonais (N, S, E, W)
        posicoes = {{l-1, c}, {l+1, c}, {l, c-1}, {l, c+1}};
    }

    // Embaralhar para aleatoriedade
    for (size_t i = posicoes.size() - 1; i > 0; --i) {
        size_t j = rand() % (i + 1);
        swap(posicoes[i], posicoes[j]);
    }

    // Tentar colocar em uma posição válida
    for (const auto& pos : posicoes) {
        int nl = pos.first;
        int nc = pos.second;

        // Verifica se está dentro dos limites
        if (nl < 0 || nl >= linhas || nc < 0 || nc >= colunas) {
            continue;
        }

        // Erva daninha MATA a planta que estiver no destino
        if (erva) {
            if (area[nl][nc].temPlanta()) {
                Planta* vitima = area[nl][nc].getPlanta();
                delete vitima;
                area[nl][nc].setPlanta(nullptr);
                cout << "  [MULTIPLICAÇÃO] Erva daninha matou planta em "
                     << char('a' + nl) << char('a' + nc) << "\n";
            }
        } else {
            // Outras plantas: precisa de espaço vazio
            if (area[nl][nc].temPlanta()) {
                continue;  // Posição ocupada, tentar próxima
            }
        }

        // CRIAR NOVA PLANTA
        Planta* filha = mae->gerarSemente();
        area[nl][nc].setPlanta(filha);

        // Resetar contador para erva daninha
        if (erva) {
            erva->resetarMultiplicacao();
        }

        cout << "  [MULTIPLICAÇÃO] Nova planta em "
             << char('a' + nl) << char('a' + nc)
             << " (mãe em " << char('a' + l) << char('a' + c) << ")\n";

        return;  // Sucesso - sair
    }

    // Se chegou aqui, não encontrou posição válida
    cout << "  [MULTIPLICAÇÃO] Falhou - sem espaço para "
         << char('a' + l) << char('a' + c) << "\n";
}

bool Jardim::estaCercada(int l, int c) const {
    // Verifica se TODAS as 4 posições ortogonais têm plantas
    int vizinhosComPlantas = 0;
    int vizinhosValidos = 0;

    vector<pair<int, int>> vizinhos = {{l-1, c}, {l+1, c}, {l, c-1}, {l, c+1}};

    for (const auto& viz : vizinhos) {
        int vl = viz.first;
        int vc = viz.second;

        // Ignora posições fora do jardim
        if (vl < 0 || vl >= linhas || vc < 0 || vc >= colunas) {
            continue;
        }

        vizinhosValidos++;

        if (area[vl][vc].temPlanta()) {
            vizinhosComPlantas++;
        }
    }

    // Está cercada se TODOS os vizinhos válidos têm plantas
    return (vizinhosValidos > 0 && vizinhosComPlantas == vizinhosValidos);
}