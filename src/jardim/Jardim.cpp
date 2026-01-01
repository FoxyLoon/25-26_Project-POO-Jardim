// ========== Jardim.cpp ==========
#include "Jardim.h"
#include <iostream>
#include <ctime>
#include "../Settings.h"
#include "../plantas/Roseira.h"
#include "../plantas/Cacto.h"
#include "../plantas/ErvaDaninha.h"
#include "../plantas/PlantaExotica.h"
#include "../ferramentas/Ferramenta.h"

using namespace std;

// ========================================================
// CONSTRUTOR - ARRAY DINÂMICO SEM VECTOR
// ========================================================

Jardim::Jardim(int l, int c) : linhas(l), colunas(c) {
    srand(static_cast<unsigned>(time(nullptr)));

    // ✅ ALOCAÇÃO DINÂMICA PURA - SEM VECTOR!
    area = new Solo*[linhas];
    for (int i = 0; i < linhas; ++i) {
        area[i] = new Solo[colunas];
    }

    // Inicializar cada posição
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            // Água e nutrientes aleatórios
            int agua = Settings::Jardim::agua_min +
                      rand() % (Settings::Jardim::agua_max - Settings::Jardim::agua_min + 1);
            int nutrientes = Settings::Jardim::nutrientes_min +
                           rand() % (Settings::Jardim::nutrientes_max - Settings::Jardim::nutrientes_min + 1);

            area[i][j].setAgua(agua);
            area[i][j].setNutrientes(nutrientes);

            // Probabilidade de planta inicial (opcional, pode remover)
            if ((rand() % 100) < Settings::Jardim::probabilidade_planta) {
                int tipo = rand() % 4;
                Planta* p = nullptr;
                switch (tipo) {
                    case 0: p = new Roseira(); break;
                    case 1: p = new Cacto(); break;
                    case 2: p = new ErvaDaninha(); break;
                    case 3: p = new PlantaExotica(); break;
                }
                if (p) area[i][j].setPlanta(p);
            }
        }
    }

    // ✅ INICIAR COM EXATAMENTE 3 FERRAMENTAS (conforme enunciado)
    for (int i = 0; i < 3; ++i) {
        criarFerramentaAleatoria();
    }
}

// ========================================================
// DESTRUTOR - LIBERTAR MEMÓRIA
// ========================================================

Jardim::~Jardim() {
    // Libertar plantas e ferramentas
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

    // ✅ LIBERTAR ARRAY DINÂMICO
    for (int i = 0; i < linhas; ++i) {
        delete[] area[i];
    }
    delete[] area;
}

// ========================================================
// FERRAMENTA "POR MAGIA" (Enunciado)
// ========================================================

void Jardim::criarFerramentaAleatoria() {
    // Tipos disponíveis
    char tipos[] = {'g', 'a', 't', 'z'};
    char tipo = tipos[rand() % 4];

    // Criar ferramenta
    Ferramenta* nova = Ferramenta::criar(tipo);
    if (!nova) return;

    // Encontrar posição aleatória vazia
    // (Tentar até 100 vezes para evitar loop infinito)
    for (int tentativas = 0; tentativas < 100; ++tentativas) {
        int l = rand() % linhas;
        int c = rand() % colunas;

        if (!area[l][c].temFerramenta()) {
            area[l][c].setFerramenta(nova);
            cout << "  [SISTEMA] Nova ferramenta (" << nova->nome()
                 << ") apareceu em " << char('a' + l) << char('a' + c) << "\n";
            return;
        }
    }

    // Se não encontrou posição, descartar
    delete nova;
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
// SIMULAÇÃO
// ========================================================

void Jardim::avancarInstante() {
    cout << "\n[SIMULAÇÃO] Processando instante...\n";

    processarPlantas();
    processarMortes();
    processarMultiplicacoes();

    cout << "[SIMULAÇÃO] Instante concluído.\n";
}

void Jardim::processarPlantas() {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (area[i][j].temPlanta()) {
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

            // Verificação básica
            if (p->verificaMorte(area[i][j])) {
                deveMorrer = true;
            }

            // Roseira cercada
            Roseira* roseira = dynamic_cast<Roseira*>(p);
            if (roseira && estaCercada(i, j)) {
                deveMorrer = true;
            }

            if (deveMorrer) {
                p->aoMorrer(area[i][j]);
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
    // Estrutura simples para guardar multiplicações
    struct Mult {
        int l, c;
        Planta* mae;
    };

    // Array dinâmico para multiplicações (máximo: todas as posições)
    int maxMult = linhas * colunas;
    Mult* multiplicacoes = new Mult[maxMult];
    int numMult = 0;

    // Identificar plantas que podem multiplicar
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (area[i][j].temPlanta()) {
                Planta* p = area[i][j].getPlanta();
                if (p->podeMultiplicar()) {
                    multiplicacoes[numMult].l = i;
                    multiplicacoes[numMult].c = j;
                    multiplicacoes[numMult].mae = p;
                    numMult++;
                }
            }
        }
    }

    // Processar cada multiplicação
    for (int i = 0; i < numMult; ++i) {
        multiplicarPlanta(multiplicacoes[i].l, multiplicacoes[i].c, multiplicacoes[i].mae);
    }

    delete[] multiplicacoes;
}

void Jardim::multiplicarPlanta(int l, int c, Planta* mae) {
    // Array de posições vizinhas
    int vizinhos[4][2];
    int numVizinhos = 0;

    // Determinar padrão
    ErvaDaninha* erva = dynamic_cast<ErvaDaninha*>(mae);
    PlantaExotica* exotica = dynamic_cast<PlantaExotica*>(mae);

    if (exotica) {
        // Diagonais
        int diag[4][2] = {{l-1, c+1}, {l+1, c+1}, {l+1, c-1}, {l-1, c-1}};
        for (int i = 0; i < 4; ++i) {
            vizinhos[numVizinhos][0] = diag[i][0];
            vizinhos[numVizinhos][1] = diag[i][1];
            numVizinhos++;
        }
    } else {
        // Ortogonais
        int ort[4][2] = {{l-1, c}, {l+1, c}, {l, c-1}, {l, c+1}};
        for (int i = 0; i < 4; ++i) {
            vizinhos[numVizinhos][0] = ort[i][0];
            vizinhos[numVizinhos][1] = ort[i][1];
            numVizinhos++;
        }
    }

    // Embaralhar
    for (int i = numVizinhos - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int tempL = vizinhos[i][0];
        int tempC = vizinhos[i][1];
        vizinhos[i][0] = vizinhos[j][0];
        vizinhos[i][1] = vizinhos[j][1];
        vizinhos[j][0] = tempL;
        vizinhos[j][1] = tempC;
    }

    // Tentar colocar
    for (int i = 0; i < numVizinhos; ++i) {
        int nl = vizinhos[i][0];
        int nc = vizinhos[i][1];

        if (nl < 0 || nl >= linhas || nc < 0 || nc >= colunas) continue;

        // Erva mata
        if (erva) {
            if (area[nl][nc].temPlanta()) {
                delete area[nl][nc].getPlanta();
                area[nl][nc].setPlanta(nullptr);
                cout << "  [MULTIPLICAÇÃO] Erva matou planta em "
                     << char('a' + nl) << char('a' + nc) << "\n";
            }
        } else {
            if (area[nl][nc].temPlanta()) continue;
        }

        // Criar semente
        Planta* filha = mae->gerarSemente();
        area[nl][nc].setPlanta(filha);

        if (erva) {
            erva->resetarMultiplicacao();
        }

        cout << "  [MULTIPLICAÇÃO] Nova planta em "
             << char('a' + nl) << char('a' + nc) << "\n";
        return;
    }
}

bool Jardim::estaCercada(int l, int c) const {
    int vizinhosComPlantas = 0;
    int vizinhosValidos = 0;

    int viz[4][2] = {{l-1, c}, {l+1, c}, {l, c-1}, {l, c+1}};

    for (int i = 0; i < 4; ++i) {
        int vl = viz[i][0];
        int vc = viz[i][1];

        if (vl < 0 || vl >= linhas || vc < 0 || vc >= colunas) continue;

        vizinhosValidos++;
        if (area[vl][vc].temPlanta()) {
            vizinhosComPlantas++;
        }
    }

    return (vizinhosValidos > 0 && vizinhosComPlantas == vizinhosValidos);
}