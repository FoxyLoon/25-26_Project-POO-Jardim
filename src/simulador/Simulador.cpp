#include "Simulador.h"
#include "fstream"
#include <sys/stat.h>
#include <iostream>
#include <sstream>

#include "../plantas/Cacto.h"
#include "../plantas/Roseira.h"
#include "../plantas/ErvaDaninha.h"
#include "../plantas/PlantaExotica.h"

#include "../ferramentas/Regador.h"
#include "../ferramentas/Adubo.h"
#include "../ferramentas/Tesoura.h"
#include "../ferramentas/FerramentaZ.h"

using namespace std;

Simulador::Simulador() : jardim(nullptr), jardimCriado(false), jardineiroNoJardim(false) {}

Simulador::~Simulador()
{
    delete jardim;
}

// ================================================================
// ================================================================
// ================================================================

// ================================================================
// ================================================================
// ================================================================

// --- Processamento dos Comandos ---
bool Simulador::processaComando(const string &linha)
{
    stringstream ss(linha);
    string cmd;

    // lê até ao primeiro espaço (apenas a primeira palavra)
    // Nota: Os parametros depois do espaço ficam e são usados mais tarde
    ss >> cmd;

    // ========================================================

    // Comando para avançar o tempo/instantes
    if (cmd == "avanca")
        return comandoAvanca(ss);

    // ========================================================

    // Comandos Gerais
    if (cmd == "fim")
        return comandoFim();
    if (cmd == "jardim")
        return comandoJardim(ss);
    if (cmd == "grava")
        return comandoGrava(ss);
    if (cmd == "recupera")
        return comandoRecupera(ss);
    if (cmd == "apaga")
        return comandoApaga(ss);
    if (cmd == "executa")
        return comandoExecuta(ss);

    // ========================================================

    // Comandos para listar informação
    if (cmd == "lplantas")
        return comandoLplantas();
    if (cmd == "lplanta")
        return comandoLplanta(ss);
    if (cmd == "larea")
        return comandoLarea();
    if (cmd == "lsolo")
        return comandoLsolo(ss);
    if (cmd == "lferr")
        return comandoLferr();

    // ========================================================

    // Comandos para ações
    if (cmd == "colhe")
        return comandoColhe(ss);
    if (cmd == "planta")
        return comandoPlanta(ss);
    if (cmd == "larga")
        return comandoLarga();
    if (cmd == "pega")
        return comandoPega(ss);
    if (cmd == "compra")
        return comandoCompra(ss);

    // ========================================================

    // Comandos para controlar o jardineiro
    if (cmd == "e")
        return comandoE();
    if (cmd == "d")
        return comandoD();
    if (cmd == "c")
        return comandoC();
    if (cmd == "b")
        return comandoB();
    if (cmd == "entra")
        return comandoEntra(ss);
    if (cmd == "sai")
        return comandoSai();

    // ========================================================

    // Retorna "false" caso o comando não for nenhum dos de cima
    cout << string(111, '=') << "\n[ERRO] >> Comando desconhecido: " << cmd << "\n";
    return false;
}

// ========================================================

// Comandos Gerais

bool Simulador::comandoAvanca(stringstream &ss)
{
    if (!isJardimCriado())
        return false;

    // Verifica se o utilizador quer avançar mais de um instante
    int totalInstantesParaAvancar = 1;
    if (ss >> totalInstantesParaAvancar)
    {
        if (totalInstantesParaAvancar <= 0)
        {
            cout << string(111, '=') << "\n[ERRO] >> O numero de instantes deve ser um valor positivo." << endl;
            return false;
        }
    }

    // Feedback: Instantes
    for (int instante_atual = 0; instante_atual < totalInstantesParaAvancar; ++instante_atual)
    {
        cout << "\n"
             << string(60, '=') << "\n"
             << "[ INSTANTE " << (instante_atual + 1) << " / " << totalInstantesParaAvancar << " ]\n"
             << string(60, '=') << endl;

        // Atualiza as trocas de recursos do jardim
        jardim->avancaInstante();

        // Verifica se o jardineiro está no jardim
        if (jardineiro.verificarPresenca())
        {
            Ferramenta *ferramentaNaMao = jardineiro.getFerramentaNaMao();

            if (ferramentaNaMao != nullptr)
            {
                // Obtém o solo onde o jardineiro está parado
                Solo &soloAtual = jardim->getSolo(jardineiro.getLinha(), jardineiro.getColuna());

                // Aplica o efeito da ferramenta (Regar, Adubar, etc.)
                ferramentaNaMao->aplicarNoSolo(soloAtual);

                // Elimina a ferramenta da mão do jardineiro se ela estiver gasta
                if (ferramentaNaMao->estaGasta())
                {
                    int ID_FerramentaGasta = ferramentaNaMao->getNumeroSerieFerramenta();
                    jardineiro.removerFerramentaDoInventario(ID_FerramentaGasta);
                }
            }
            else
            {
                cout << "[AVISO] >> Mao vazia: nenhuma ferramenta usada neste instante." << endl;
            }
        }

        // Reinicia limites de ações do Jardineiro
        jardineiro.reiniciarTurno();

        // F. Mostra o jardim atualizado após este instante
        jardim->mostraJardim();
    }

    return true;
}

bool Simulador::comandoFim()
{
    cout << "A encerrar o simulador...\n";
    exit(0);
}

bool Simulador::comandoJardim(stringstream &ss)
{
    int linhas, colunas;
    string extra;
    if (jardimCriado)
    {
        cout << string(111, '=') << "\n[ERRO] Já existe um jardim criado!\n";
        return false;
    }
    else if (!(ss >> linhas >> colunas))
    {
        cout << string(111, '=') << "\n[ERRO] >> Faltam valores!\n";
        return false;
    }
    else if (ss >> extra)
    {
        cout << string(111, '=') << "\n[ERRO] >> Existem parametros a mais!\n";
        return false;
    }
    else if (linhas < 1 || linhas > 26)
    {
        cout << string(111, '=') << "\n[ERRO] >> Número de LINHAS Inválido!\n";
        return false;
    }
    else if (colunas < 1 || colunas > 26)
    {
        cout << string(111, '=') << "\n[ERRO] >> Número de COLUNAS Inválido!\n";
        return false;
    }

    jardim = new Jardim(linhas, colunas);
    jardimCriado = true;
    cout << string(111, '=') << "\n[INFO] >> Foi criado um Jardim com "
         << linhas << " linhas e "
         << colunas << " colunas.\n";

    jardim->mostraJardim();
    return true;
}

// ========================================================

bool Simulador::comandoGrava(stringstream &ss) const
{
    if (!isJardimCriado())
    {
        cout << "[ERRO] >> Não existe um jardim para guardar.\n";
        return false;
    }

    string nome;
    if (!(ss >> nome))
    {
        cout << "[ERRO] >> É necessário fornecer um nome para a cópia.\n";
        return false;
    }

    if (salvarJardimEmFicheiro(nome))
    {
        cout << "[INFO] >> Jardim guardado com sucesso como '" << nome << "'.\n";
        jardim->mostraJardim();
        return true;
    }

    cout << "[ERRO] >> Erro ao guardar o jardim.\n";
    return false;
}

// ========================================================

bool Simulador::comandoRecupera(stringstream &ss)
{
    string nome;
    if (!(ss >> nome))
    {
        cout << "[ERRO] >> É necessário fornecer um nome para a cópia a recuperar.\n";
        return false;
    }

    if (carregarJardimDeFicheiro(nome))
    {
        cout << "[INFO] >> Jardim recuperado com sucesso de '" << nome << "'.\n";
        jardimCriado = true;
        jardim->mostraJardim();
        return true;
    }

    cout << "[ERRO] >> Erro ao recuperar o jardim.\n";
    return false;
}

// ========================================================

bool Simulador::comandoApaga(stringstream &ss)
{
    string nome;
    if (!(ss >> nome))
    {
        cout << "[ERRO] >> É necessário fornecer um nome para a cópia a apagar.\n";
        return false;
    }

    if (apagarFicheiro(nome))
    {
        cout << "[INFO] >> Cópia '" << nome << "' apagada com sucesso.\n";
        return true;
    }

    cout << "[ERRO] >> Erro ao apagar a cópia.\n";
    return false;
}

// ========================================================

bool Simulador::comandoExecuta(stringstream &ss)
{
    string nomeFicheiro;
    if (!(ss >> nomeFicheiro)) // Extrai nome do ficheiro
    {
        cout << "[ERRO] >> É necessário fornecer um nome de ficheiro.\n";
        return false;
    }

    ifstream ficheiro(nomeFicheiro); // Abre para leitura
    if (!ficheiro.is_open())
    {
        cout << "[ERRO] >> Ficheiro '" << nomeFicheiro << "' não encontrado.\n";
        return false;
    }

    string linha;
    int numeroLinha = 0;

    // Lê e executa cada linha
    while (getline(ficheiro, linha))
    {
        numeroLinha++;

        // Ignora linhas vazias e comentários (#)
        if (linha.empty() || linha[0] == '#')
            continue;

        // Remove espaços no início e fim
        size_t inicio = linha.find_first_not_of(" \t");
        size_t fim = linha.find_last_not_of(" \t");

        if (inicio == string::npos)
            continue;

        linha = linha.substr(inicio, fim - inicio + 1);

        // Executa o comando
        cout << "[LINHA " << numeroLinha << "] > " << linha << "\n";
        if (!processaComando(linha))
        {
            cout << "[AVISO] >> Comando na linha " << numeroLinha << " falhou.\n";
        }
    }

    ficheiro.close();
    cout << "[INFO] >> Ficheiro '" << nomeFicheiro << "' executado com sucesso.\n";
    return true;
}

// ========================================================
// ========================================================
// ========================================================

// Comandos para listar informação

// Lista todas as plantas
bool Simulador::comandoLplantas() const
{
    if (!isJardimCriado())
        return false;

    bool encontrouPlantas = false;
    int contadorPlantas = 0;

    cout << "\n"
         << string(40, '=') << "[ LISTA DAS PLANTAS NO JARDIM ]" << string(40, '=') << endl;

    // Percorre todas as linhas do jardim
    for (int linha_atual = 0; linha_atual < jardim->getLinhas(); ++linha_atual)
    {
        // Percorre todas as colunas do jardim
        for (int coluna_atual = 0; coluna_atual < jardim->getColunas(); ++coluna_atual)
        {
            Solo &solo = jardim->getSolo(linha_atual, coluna_atual);

            // Verifica se este solo possui uma planta
            if (solo.temPlanta())
            {
                encontrouPlantas = true;
                contadorPlantas++;
                Planta *plantaNoSolo = solo.getPlanta();

                // Conversão de indices inteiros para letras
                char letraLinha = static_cast<char>('a' + linha_atual);
                char letraColuna = static_cast<char>('a' + coluna_atual);

                cout << string(111, '-') << "\n"
                     << contadorPlantas << "ª Planta - Posicao ( " << letraLinha << " , " << letraColuna << " )" << "\n"
                     << "{Planta}\t" << plantaNoSolo->getInfoPlanta() << "\t\t"
                     << plantaNoSolo->getInfoExtraPlanta()
                     << "{Solo}\t\t" << solo.getInfoSolo();
            }
        }
    }

    if (!encontrouPlantas)
    {
        cout << "[INFO] >> Nao existem plantas no jardim no momento." << endl;
    }

    cout << string(111, '-') << "\n"
         << string(111, '=') << endl;

    return true;
}

// ========================================================

// Lista uma planta numa posição especifica
bool Simulador::comandoLplanta(stringstream &ss) const
{
    if (!isJardimCriado())
    {
        return false;
    }

    string posicao;
    if (!(ss >> posicao) || !isLetraPequena(posicao))
    {
        cout << string(111, '=') << "\n[ERRO] >> Formato de posicao invalido! Use duas letras minusculas (ex: lplanta aa)." << endl;
        return false;
    }

    // Conversão de letras para índices inteiros
    int linha = posicao[0] - 'a';
    int coluna = posicao[1] - 'a';
    if (isForaDosLimites(linha, coluna))
    {
        return false;
    }

    Solo &solo = jardim->getSolo(linha, coluna);
    if (!solo.temPlanta())
    {
        cout << string(111, '=') << "\n[ERRO] >> Nao existe nenhuma planta na posicao ( "
             << posicao[0] << " , " << posicao[1] << " )." << endl;
        return false;
    }

    // ========================================================

    Planta *plantaNoSolo = solo.getPlanta();

    cout << "\n"
         << string(44, '=') << "[ DETALHE DA PLANTA ]" << string(44, '=') << "\n"
         << string(111, '-') << "\n"
         << "Posicao ( " << posicao[0] << " , " << posicao[1] << " )" << "\n"
         << "{Planta}\t" << plantaNoSolo->getInfoPlanta() << "\t\t"
         << plantaNoSolo->getInfoExtraPlanta()
         << string(111, '-') << "\n"
         << string(111, '=') << endl;

    return true;
}

// ========================================================

// Lista todas as areas ocupadas do Solo
bool Simulador::comandoLarea() const
{
    if (!isJardimCriado())
    {
        return false;
    }

    cout << "\n"
         << string(41, '=') << "[ LISTA DAS ÁREAS OCUPADAS ]" << string(42, '=') << endl;

    bool encontrouSoloOcupado = false;
    int contadorSolos = 0;

    // Percorre todas as linhas do jardim
    for (int linha_atual = 0; linha_atual < jardim->getLinhas(); ++linha_atual)
    {
        // Percorre todas as colunas do jardim
        for (int coluna_atual = 0; coluna_atual < jardim->getColunas(); ++coluna_atual)
        {
            Solo &solo = jardim->getSolo(linha_atual, coluna_atual);

            // Verifica se este solo tem conteudo
            if (!solo.estaVazio())
            {
                encontrouSoloOcupado = true;
                contadorSolos++;

                // Conversão de indices inteiros para letras
                char letraLinha = static_cast<char>('a' + linha_atual);
                char letraColuna = static_cast<char>('a' + coluna_atual);

                cout << string(111, '-') << "\n"
                     << contadorSolos << "ª Area Ocupada - Posicao ( " << letraLinha << " , " << letraColuna << " )" << "\n"
                     << "{Solo}\t\t" << solo.getInfoSolo();
            }
        }
    }

    // Nota: Condição tecnicamente impossivel, pois o jardim sempre terá 3 ferramentas
    if (!encontrouSoloOcupado)
    {
        cout << "[INFO] >> Não existem plantas ou ferramentas no jardim." << endl;
    }

    cout << string(111, '-') << "\n"
         << string(111, '=') << endl;

    return true;
}

// ========================================================

bool Simulador::comandoLsolo(stringstream &ss) const
{
    if (!isJardimCriado())
    {
        return false;
    }

    string posicaoCentral;
    if (!(ss >> posicaoCentral) || !isLetraPequena(posicaoCentral))
    {
        cout << string(111, '=') << "\n[ERRO] >> O comando lsolo requer pelo menos uma posicao (ex: lsolo aa [numero_opcional])." << endl;
        return false;
    }

    // Tenta ler o raio opcional.
    // Se não existir, "ss >> raioBusca" falha e raioBusca mantém-se com o valor 0
    int raioBusca = 0;
    ss >> raioBusca;

    // Conversão de letras para índices inteiros
    int linhaCentral = posicaoCentral[0] - 'a';
    int colunaCentral = posicaoCentral[1] - 'a';

    // Limites do raio do quadrado
    int linhaInicial = linhaCentral - raioBusca;
    int linhaFinal = linhaCentral + raioBusca;
    int colunaInicial = colunaCentral - raioBusca;
    int colunaFinal = colunaCentral + raioBusca;

    cout << "\n"
         << string(43, '=') << "[ PROPRIEDADES DO SOLO ]" << string(44, '=') << endl;

    bool encontrouSoloOcupado = false;
    int contadorSolos = 0;

    // Procura de todos os solos dentro do raio especificado
    // Começa no canto superior esquerdo e termina no canto inferior direito
    // Se raioBusca = 0 ou não for especificado, devolve apenas o solo central (escrito no comando)
    for (int linha_atual = linhaInicial; linha_atual <= linhaFinal; ++linha_atual)
    {
        for (int coluna_atual = colunaInicial; coluna_atual <= colunaFinal; ++coluna_atual)
        {
            // Verifica se o solo está fora dos limites
            // Está condição é a mesma de isForaDosLimites() mas sem o cout para não spammar na consola
            if (linha_atual < 0 || linha_atual >= jardim->getLinhas() || coluna_atual < 0 || coluna_atual >= jardim->getColunas())
            {
                continue;
            }

            Solo &solo = jardim->getSolo(linha_atual, coluna_atual);

            // Verifica se este solo tem conteudo
            if (!solo.estaVazio())
            {
                encontrouSoloOcupado = true;
                contadorSolos++;

                // Verifica se o solo está fora dos limites
                if (isForaDosLimites(linha_atual, coluna_atual))
                {
                    contadorSolos--;
                    continue;
                }

                // Conversão de indices inteiros para letras
                char letraLinha = static_cast<char>('a' + linha_atual);
                char letraColuna = static_cast<char>('a' + coluna_atual);
                Planta *plantaNoSolo = solo.getPlanta();
                Ferramenta *ferramentaNoSolo = solo.getFerramenta();

                cout << string(111, '-') << "\n"
                     << contadorSolos << "ª Area Ocupada - Posicao ( " << letraLinha << " , " << letraColuna << " )" << "\n";

                // Propriedades do Solo
                cout << "{Solo}\t\t" << solo.getInfoSolo();

                // Propriedades da Planta (se existir)
                if (solo.temPlanta())
                {
                    cout << "\n{Planta}\t" << plantaNoSolo->getInfoPlanta() << "\t\t"
                         << plantaNoSolo->getInfoExtraPlanta();
                }

                // Propriedades da Ferramenta (se existir)
                if (solo.temFerramenta())
                {
                    cout << "\n{Ferramenta}\t" << ferramentaNoSolo->getInfoFerramenta() << "\t\t"
                         << ferramentaNoSolo->getInfoExtraFerramenta();
                }
            }
        }
    }

    // Nota: Condição tecnicamente impossivel, pois o jardim sempre terá 3 ferramentas
    if (!encontrouSoloOcupado)
    {
        cout << "[INFO] >> Não existem plantas ou ferramentas na posição especificada ou na área indicada do jardim." << endl;
    }

    cout << string(111, '-') << "\n"
         << string(111, '=') << endl;
    return true;
}

// ========================================================

// verificar se o inventario apresenta a ferramenta equipada
bool Simulador::comandoLferr() const
{
    if (!isJardimCriado())
        return false;

    jardineiro.listarFerramentas();

    cout << string(111, '-') << endl;

    Ferramenta *ferramentaEquipada = jardineiro.getFerramentaNaMao();
    if (ferramentaEquipada != nullptr)
    {
        cout << "FERRAMENTA EQUIPADA:" << "\n"
             << ferramentaEquipada->getInfoFerramenta() << endl;
    }
    else
    {
        cout << "FERRAMENTA EQUIPADA:\n[INFO] >> O jardineiro está com as mãos vazias!" << endl;
    }

    cout << string(111, '=') << endl;

    return true;
}

// ========================================================
// ========================================================
// ========================================================

// Comandos para ações

bool Simulador::comandoColhe(stringstream &ss)
{
    // Validações

    // Verifica se o jardim foi criado
    if (!isJardimCriado())
    {
        return false;
    }

    // Verifica se o comando tem o formato correto
    string posicao;
    if (!(ss >> posicao) || !isLetraPequena(posicao))
    {
        cout << string(111, '=') << "\n[ERRO] >> O comando colhe requer uma posição (ex: colhe aa)." << endl;
        return false;
    }

    int linha = posicao[0] - 'a';
    int coluna = posicao[1] - 'a';
    if (isForaDosLimites(linha, coluna))
    {
        return false;
    }

    // Verifica se o jardineiro pode colher
    if (!jardineiro.podeColher())
    {
        return false;
    }

    Solo &solo = jardim->getSolo(linha, coluna);
    if (!solo.temPlanta())
    {
        cout << string(111, '=') << "\n[ERRO] >> Não existe nenhuma planta na posição " << posicao << "!" << endl;
        return false;
    }

    // ========================================================

    jardineiro.usaColher(solo);

    jardim->mostraJardim();
    return true;
}

// ========================================================

bool Simulador::comandoPlanta(stringstream &ss)
{
    // Validações

    // Verifica se o jardim foi criado
    if (!isJardimCriado())
        return false;

    // Verifica se o comando tem o formato correto
    string posicao;
    char tipoPlanta;
    if (!(ss >> posicao >> tipoPlanta) || !isLetraPequena(posicao))
    {
        cout << string(111, '=') << "\n[ERRO] >> O comando planta requer posicao e tipo (ex: planta aa c)." << endl;
        return false;
    }

    int linha = posicao[0] - 'a';
    int coluna = posicao[1] - 'a';
    if (isForaDosLimites(linha, coluna))
    {
        return false;
    }

    // Verifica se o jardineiro pode plantar
    if (!jardineiro.podePlantar())
    {
        return false;
    }

    Solo &solo = jardim->getSolo(linha, coluna);
    if (solo.temPlanta())
    {
        cout << "[ERRO] >> Ja existe uma planta na posicao " << posicao << "!" << endl;
        return false;
    }

    // ========================================================

    // Criação da planta conforme o tipo fornecido
    Planta *novaPlanta = nullptr;
    tipoPlanta = static_cast<char>(tolower(static_cast<unsigned char>(tipoPlanta)));

    switch (tipoPlanta)
    {
    case 'c': // Cacto
        novaPlanta = new Cacto();
        break;
    case 'r': // Roseira
        novaPlanta = new Roseira();
        break;
    case 'e': // Erva-Daninha
        novaPlanta = new ErvaDaninha();
        break;
    case 'x': // Planta Exotica
        novaPlanta = new PlantaExotica();
        break;
    default:
        cout << string(111, '=') << "\n[ERRO] >> Tipo de planta desconhecido: " << tipoPlanta << "(use c, r, e ou x)" << endl;
    }

    // ========================================================

    // Caso "novaPlanta" deixe de ser um nullptr, o jardineiro planta a planta
    if (novaPlanta != nullptr)
    {
        jardineiro.usaPlantar(solo, novaPlanta);

        jardim->mostraJardim();
        return true;
    }

    return false;
}

// ========================================================

bool Simulador::comandoLarga()
{
    if (!isJardimCriado())
        return false;

    if (jardineiro.getFerramentaNaMao() == nullptr)
    {
        cout << string(111, '=') << "\n[ERRO] >> O jardineiro não tem ferramentas equipadas para largar!" << endl;
        return false;
    }

    jardineiro.depositarFerramentaDaMaoParaInventario();
    jardineiro.mostrarEstado();
    jardim->mostraJardim();
    return true;
}

// ========================================================

bool Simulador::comandoPega(stringstream &ss)
{
    if (!isJardimCriado())
    {
        return false;
    }

    int ID_Ferramenta;
    if (!(ss >> ID_Ferramenta))
    {
        cout << string(111, '=') << "\n[ERRO] >> O comando pega requer o id da ferramenta (ex: pega 1)." << endl;
        return false;
    }

    // Seleciona a ferramenta do inventário
    jardineiro.selecionarFerramentaDoInventario(ID_Ferramenta);
    jardineiro.mostrarEstado();
    jardim->mostraJardim();
    return true;
}

// ========================================================

bool Simulador::comandoCompra(stringstream &ss)
{
    // Validações

    // Verifica se o jardim foi criado
    if (!isJardimCriado())
        return false;

    // Verifica se o comando tem o formato correto
    char tipoFerramenta;
    if (!(ss >> tipoFerramenta))
    {
        cout << string(111, '=') << "\n[ERRO] >> O comando compra requer o tipo: g (regador), a (adubo), t (tesoura) ou z (FerramentaZ)." << endl;
        return false;
    }

    // ========================================================

    // Criação da ferramenta conforme o tipo fornecido
    Ferramenta *novaFerramenta = nullptr;
    tipoFerramenta = static_cast<char>(tolower(static_cast<unsigned char>(tipoFerramenta)));

    switch (tipoFerramenta)
    {
    case 'g':
        novaFerramenta = new Regador();
        break;
    case 'a':
        novaFerramenta = new Adubo();
        break;
    case 't':
        novaFerramenta = new Tesoura();
        break;
    case 'z':
        novaFerramenta = new FerramentaZ();
        break;
    default:
        cout << "[ERRO] >> Tipo de ferramenta desconhecido: '" << tipoFerramenta << "'. Use g, a, t ou z." << endl;
    }

    // 3. Entrega a ferramenta ao jardineiro
    if (novaFerramenta != nullptr)
    {
        // O método adicionarFerramenta já coloca no vector e dá o feedback visual
        jardineiro.adicionarFerramentaAoInventario(novaFerramenta);
        cout << "[INFO] >> " << novaFerramenta->getNomeFerramenta() << " (ID "
             << novaFerramenta->getNumeroSerieFerramenta()
             << ") comprado com sucesso!" << endl;
        return true;
    }

    return false;
}

// ========================================================
// ========================================================
// ========================================================

// Comandos para controlar o jardineiro

bool Simulador::comandoE()
{
    // Validações

    // Verifica se o jardim foi criado
    if (!isJardimCriado())
    {
        return false;
    }

    // Verifica se o jardineiro foi criado
    if (!isJardineiroNoJardim())
    {
        return false;
    }

    // Verifica se o jardineiro pode se mover no jardim
    if (!jardineiro.podeMovimentar())
    {
        return false;
    }

    int linha_atual = jardineiro.getLinha();
    int coluna_atual = jardineiro.getColuna();
    int nova_coluna = coluna_atual - 1;

    // Valida se o movimento está dentro dos limites
    if (isForaDosLimites(linha_atual, nova_coluna))
    {
        return false;
    }

    // =================================================

    // Execução do movimento

    // Remove o jardineiro do antigo solo
    jardim->getSolo(linha_atual, coluna_atual).setJardineiro(false);

    // Move o jardineiro
    jardineiro.usaMovimento(linha_atual, nova_coluna, "ESQUERDA");

    // Adiciona o jardineiro no novo solo
    Solo &novoSolo = jardim->getSolo(linha_atual, nova_coluna);
    novoSolo.setJardineiro(true);

    // Se houver ferramenta no solo, o jardineiro apanha-a
    if (novoSolo.temFerramenta())
    {
        Ferramenta *ferramenta = novoSolo.removerFerramenta();
        jardineiro.adicionarFerramentaAoInventario(ferramenta);
        jardim->processaFerramentasAleatorias();
        cout << "[INFO] >> O jardineiro encontrou e apanhou uma ferramenta!" << endl;
    }

    // Mostra o Jardim
    jardim->mostraJardim();
    return true;
}

// ========================================================

bool Simulador::comandoD()
{
    // Validações

    // Verifica se o jardim foi criado
    if (!isJardimCriado())
    {
        return false;
    }

    // Verifica se o jardineiro foi criado
    if (!isJardineiroNoJardim())
    {
        return false;
    }

    // Verifica se o jardineiro pode se mover no jardim
    if (!jardineiro.podeMovimentar())
    {
        return false;
    }

    int linha_atual = jardineiro.getLinha();
    int coluna_atual = jardineiro.getColuna();
    int nova_coluna = coluna_atual + 1;

    // Valida se o movimento está dentro dos limites
    if (isForaDosLimites(linha_atual, nova_coluna))
    {
        return false;
    }

    // =================================================

    // Execução do movimento

    // Remove o jardineiro do antigo solo
    jardim->getSolo(linha_atual, coluna_atual).setJardineiro(false);

    // Move o jardineiro
    jardineiro.usaMovimento(linha_atual, nova_coluna, "DIREITA");

    // Adiciona o jardineiro no novo solo
    Solo &novoSolo = jardim->getSolo(linha_atual, nova_coluna);
    novoSolo.setJardineiro(true);

    // Se houver ferramenta no solo, o jardineiro apanha-a
    if (novoSolo.temFerramenta())
    {
        Ferramenta *ferramenta = novoSolo.removerFerramenta();
        jardineiro.adicionarFerramentaAoInventario(ferramenta);
        jardim->processaFerramentasAleatorias();
        cout << "[INFO] >> O jardineiro encontrou e apanhou uma ferramenta!" << endl;
    }

    // Mostra o Jardim
    jardim->mostraJardim();
    return true;
}

// ========================================================

bool Simulador::comandoC()
{
    // Validações

    // Verifica se o jardim foi criado
    if (!isJardimCriado())
    {
        return false;
    }

    // Verifica se o jardineiro foi criado
    if (!isJardineiroNoJardim())
    {
        return false;
    }

    // Verifica se o jardineiro pode se mover no jardim
    if (!jardineiro.podeMovimentar())
    {
        return false;
    }

    int linha_atual = jardineiro.getLinha();
    int coluna_atual = jardineiro.getColuna();
    int nova_linha = linha_atual - 1;

    // Valida se o movimento está dentro dos limites
    if (isForaDosLimites(nova_linha, coluna_atual))
    {
        return false;
    }

    // =================================================

    // Execução do movimento

    // Remove o jardineiro do antigo solo
    jardim->getSolo(linha_atual, coluna_atual).setJardineiro(false);

    // Move o jardineiro
    jardineiro.usaMovimento(nova_linha, coluna_atual, "CIMA");

    // Adiciona o jardineiro no novo solo
    Solo &novoSolo = jardim->getSolo(nova_linha, coluna_atual);
    novoSolo.setJardineiro(true);

    // Se houver ferramenta no solo, o jardineiro apanha-a
    if (novoSolo.temFerramenta())
    {
        Ferramenta *ferramenta = novoSolo.removerFerramenta();
        jardineiro.adicionarFerramentaAoInventario(ferramenta);
        jardim->processaFerramentasAleatorias();
        cout << "[INFO] >> O jardineiro encontrou e apanhou uma ferramenta!" << endl;
    }

    // Mostra o Jardim
    jardim->mostraJardim();
    return true;
}

// // ========================================================

bool Simulador::comandoB()
{
    // Validações

    // Verifica se o jardim foi criado
    if (!isJardimCriado())
    {
        return false;
    }

    // Verifica se o jardineiro foi criado
    if (!isJardineiroNoJardim())
    {
        return false;
    }

    // Verifica se o jardineiro pode se mover no jardim
    if (!jardineiro.podeMovimentar())
    {
        return false;
    }

    int linha_atual = jardineiro.getLinha();
    int coluna_atual = jardineiro.getColuna();
    int nova_linha = linha_atual + 1;

    // Valida se o movimento está dentro dos limites
    if (isForaDosLimites(nova_linha, coluna_atual))
    {
        return false;
    }

    // =================================================

    // Execução do movimento

    // Remove o jardineiro do antigo solo
    jardim->getSolo(linha_atual, coluna_atual).setJardineiro(false);

    // Move o jardineiro
    jardineiro.usaMovimento(nova_linha, coluna_atual, "BAIXO");

    // Adiciona o jardineiro no novo solo
    Solo &novoSolo = jardim->getSolo(nova_linha, coluna_atual);
    novoSolo.setJardineiro(true);

    // Se houver ferramenta no solo, o jardineiro apanha-a
    if (novoSolo.temFerramenta())
    {
        Ferramenta *ferramenta = novoSolo.removerFerramenta();
        jardineiro.adicionarFerramentaAoInventario(ferramenta);
        jardim->processaFerramentasAleatorias();
        cout << "[INFO] >> O jardineiro encontrou e apanhou uma ferramenta!" << endl;
    }

    // Mostra o Jardim
    jardim->mostraJardim();
    return true;
}

// ========================================================

bool Simulador::comandoEntra(stringstream &ss)
{
    if (!isJardimCriado())
    {
        return false;
    }

    // Nota: Não é preciso verificar se jardineiro já está cá dentro, pois
    // ele pode entrar para a posição que quiser mesmo já estando dentro do jardim

    string pos;
    if (!(ss >> pos) || !isLetraPequena(pos))
    {
        cout << string(111, '=') << "\n[ERRO] >> Formato invalido! Use: entra <letras> (ex: entra aa)" << endl;
        return false;
    }

    if (!jardineiro.podeEntrarSair())
    {
        return false;
    }

    // Conversão de letras minusculas para indices inteiros
    int linha = pos[0] - 'a';
    int coluna = pos[1] - 'a';

    if (isForaDosLimites(linha, coluna))
    {
        return false;
    }

    // Entra no jardim
    jardineiro.usaEntrar(linha, coluna);
    jardineiroNoJardim = true;

    Solo &solo = jardim->getSolo(linha, coluna);
    solo.setJardineiro(true);

    // Se houver ferramenta no solo, o jardineiro apanha-a
    if (solo.temFerramenta())
    {
        Ferramenta *ferramenta = solo.removerFerramenta();
        jardineiro.adicionarFerramentaAoInventario(ferramenta);
        jardim->processaFerramentasAleatorias();
        cout << "[INFO] >> O jardineiro encontrou e apanhou uma ferramenta!" << endl;
    }

    cout << "[INFO] >> O Jardineiro entrou na posicao " << pos << ".\n";
    jardim->mostraJardim();

    return true;
}

// ========================================================

bool Simulador::comandoSai()
{
    if (!isJardimCriado())
    {
        return false;
    }

    if (!isJardineiroNoJardim())
    {
        return false;
    }

    if (!jardineiro.podeEntrarSair())
    {
        return false;
    }

    int linha_atual = jardineiro.getLinha();
    int coluna_atual = jardineiro.getColuna();
    if (!isForaDosLimites(linha_atual, coluna_atual))
    {
        Solo &solo = jardim->getSolo(linha_atual, coluna_atual);
        solo.setJardineiro(false);
    }

    // Executa a saida do jardineiro. Feedback está neste comando.
    jardineiro.usaSair();
    jardineiroNoJardim = false;

    jardim->mostraJardim();
    return true;
}

// ========================================================
// ========================================================
// ========================================================

// Funções Auxiliares

// Verifica se uma ‘string’ contém duas letras minusculas
bool Simulador::isLetraPequena(const string &p)
{
    return p.size() == 2 && islower(static_cast<unsigned char>(p[0])) && islower(static_cast<unsigned char>(p[1]));
}

bool Simulador::isJardimCriado() const
{
    if (!jardimCriado)
    {
        cout << string(111, '=') << "\n[ERRO] >> É necessário criar um jardim primeiro!" << endl;
        return false;
    }
    return true;
}

bool Simulador::isJardineiroNoJardim() const
{
    if (!jardineiroNoJardim)
    {
        cout << string(111, '=') << "\n[ERRO] >> É necessário o jardineiro entrar no jardim primeiro!" << endl;
        return false;
    }
    return true;
}

bool Simulador::isForaDosLimites(int linhas, int colunas) const
{
    if (linhas < 0 || linhas >= jardim->getLinhas() || colunas < 0 || colunas >= jardim->getColunas())
    {
        cout << string(111, '=') << "\n[ERRO] >> Posição inválida! (fora dos limites).\n";
        return true;
    }
    return false;
}

// ================================================================
// ================================================================

// Funções para Serializer/Deserialization

void Simulador::criarPastaSeNaoExistir(const string &caminho)
{
#ifdef _WIN32
    mkdir(caminho.c_str());
#else
    mkdir(caminho.c_str(), 0755);
#endif
}

bool Simulador::apagarFicheiro(const string &nome)
{
    // Construir caminho do ficheiro
    string caminhoFicheiro = "saves/" + nome + ".garden";

    // Tentar apagar o ficheiro
    if (remove(caminhoFicheiro.c_str()) != 0) // c_str() converte a string (C++) para um const char* (C) para poder ser recebido em remove()
    {
        cout << "[ERRO] >> Ficheiro '" << caminhoFicheiro << "' não encontrado ou não foi possível apagar.\n";
        return false;
    }

    return true;
}

string Simulador::serializarPlanta(const Planta *p)
{
    if (p == nullptr)
        return "TIPO:VAZIO";

    char tipo = p->getSimboloPlanta();
    int agua = p->getAguaInterna();
    int nutrientes = p->getNutrientesInternos();

    ostringstream oss;
    oss << "TIPO:" << tipo << "|AGUA:" << agua << "|NUTRIENTES:" << nutrientes;

    return oss.str();
}

Planta *Simulador::deserializarPlanta(const string &dados)
{
    if (dados.find("TIPO:VAZIO") != string::npos)
        return nullptr;

    // Parse dos dados
    char tipo = 'C';
    int agua = 0;
    int nutrientes = 0;

    stringstream ss(dados);
    string token;

    while (getline(ss, token, '|'))
    {
        size_t pos = token.find(':');
        if (pos != string::npos)
        {
            string chave = token.substr(0, pos);
            string valor = token.substr(pos + 1);

            if (chave == "TIPO")
                tipo = valor[0];
            else if (chave == "AGUA")
                agua = stoi(valor);
            else if (chave == "NUTRIENTES")
                nutrientes = stoi(valor);
        }
    }

    // Criar planta apropriada
    Planta *planta = nullptr;
    switch (tipo)
    {
    case 'c':
        planta = new Cacto();
        break;
    case 'r':
        planta = new Roseira();
        break;
    case 'e':
        planta = new ErvaDaninha();
        break;
    case 'x':
        planta = new PlantaExotica();
        break;
    default:
        return nullptr;
    }

    planta->setAguaInterna(agua);
    planta->setNutrientesInternos(nutrientes);



    return planta;
}

string Simulador::serializarFerramenta(const Ferramenta *f)
{
    if (f == nullptr)
        return "TIPO:VAZIO";

    char tipo = f->getSimboloFerramenta();
    int serie = f->getNumeroSerieFerramenta();

    ostringstream oss;
    oss << "TIPO:" << tipo << "|SERIE:" << serie;

    return oss.str();
}

Ferramenta *Simulador::deserializarFerramenta(const string &dados)
{
    if (dados.find("TIPO:VAZIO") != string::npos)
        return nullptr;

    // Parse dos dados
    char tipo = 'g';
    int serie = 0;

    stringstream ss(dados);
    string token;

    while (getline(ss, token, '|'))
    {
        size_t pos = token.find(':');
        if (pos != string::npos)
        {
            string chave = token.substr(0, pos);
            string valor = token.substr(pos + 1);

            if (chave == "TIPO")
                tipo = valor[0];
            else if (chave == "SERIE")
                serie = stoi(valor);
        }
    }

    // Criar ferramenta apropriada
    Ferramenta *ferramenta = nullptr;
    switch (tipo)
    {
    case 'g':
        ferramenta = new Regador();
        break;
    case 'a':
        ferramenta = new Adubo();
        break;
    case 't':
        ferramenta = new Tesoura();
        break;
    case 'z':
        ferramenta = new FerramentaZ();
        break;
    default:
        ferramenta = nullptr;
    }

    // Restaurar o número de série original
    if (ferramenta != nullptr && serie > 0)
    {
        ferramenta->setNumeroSerie(serie);
    }

    return ferramenta;
}

string Simulador::serializarSolo(const Solo &s)
{
    int agua = s.getAgua();
    int nutrientes = s.getNutrientes();

    ostringstream oss;
    oss << "AGUA:" << agua << "|NUTRIENTES:" << nutrientes;
    oss << "|PLANTA:" << serializarPlanta(s.getPlanta());
    oss << "|FERRAMENTA:" << serializarFerramenta(s.getFerramenta());

    return oss.str();
}

bool Simulador::deserializarSolo(Solo &s, const string &dados)
{
    int agua = 0;
    int nutrientes = 0;
    string plantaStr = "TIPO:VAZIO";
    string ferramentaStr = "TIPO:VAZIO";

    stringstream ss(dados);
    string token;

    // Parse dos dados
    while (getline(ss, token, '|'))
    {
        size_t pos = token.find(':');
        if (pos != string::npos)
        {
            string chave = token.substr(0, pos);
            string valor = token.substr(pos + 1);

            // Validar e converter valores numéricos
            if (chave == "AGUA")
            {
                if (!eNumeroValido(valor))
                    return false;
                agua = stoi(valor);
            }
            else if (chave == "NUTRIENTES")
            {
                if (!eNumeroValido(valor))
                    return false;
                nutrientes = stoi(valor);
            }
            else if (chave == "PLANTA")
                plantaStr = valor;
            else if (chave == "FERRAMENTA")
                ferramentaStr = valor;
        }
    }

    // Verificar se os valores são válidos
    if (agua < 0 || nutrientes < 0)
        return false;

    // Aplicar os dados ao Solo
    s.setAgua(agua);
    s.setNutrientes(nutrientes);

    // Deserializer planta
    Planta *p = deserializarPlanta(plantaStr);
    if (p != nullptr)
        s.setPlanta(p);

    // Deserializer ferramenta
    Ferramenta *f = deserializarFerramenta(ferramentaStr);
    if (f != nullptr)
        s.setFerramenta(f);

    return true;
}

bool Simulador::salvarJardimEmFicheiro(const string &nome) const
{

    // Criar pasta "saves" se não existir
    criarPastaSeNaoExistir("saves");

    // Construir caminho do ficheiro
    string caminhoFicheiro = "saves/" + nome + ".garden";

    // Abrir ficheiro para escrita
    ofstream ficheiro(caminhoFicheiro);
    if (!ficheiro.is_open())
    {
        cout << "[ERRO] >> Não foi possível abrir o ficheiro '" << caminhoFicheiro << "'.\n";
        return false;
    }

    // Guardar dimensões do jardim
    ficheiro << jardim->getLinhas() << " " << jardim->getColunas() << "\n";

    // Guardar estado de cada posição do jardim
    for (int l = 0; l < jardim->getLinhas(); ++l)
    {
        for (int c = 0; c < jardim->getColunas(); ++c)
        {
            const Solo &s = jardim->getSolo(l, c);
            ficheiro << serializarSolo(s) << "\n";
        }
    }

    ficheiro.close();
    return true;
}

bool Simulador::carregarJardimDeFicheiro(const string &nome)
{
    // Construir caminho do ficheiro
    string caminhoFicheiro = "saves/" + nome + ".garden";

    // Abrir ficheiro para leitura
    ifstream ficheiro(caminhoFicheiro);
    if (!ficheiro.is_open())
    {
        cout << "[ERRO] >> Ficheiro '" << caminhoFicheiro << "' não encontrado.\n";
        return false;
    }

    // Ler dimensões do jardim
    int linhas, colunas;
    if (!(ficheiro >> linhas >> colunas))
    {
        cout << "[ERRO] >> Formato de ficheiro inválido (dimensões).\n";
        ficheiro.close();
        return false;
    }

    // Destruir jardim anterior se existir
    delete jardim;


    // Criar jardim com as dimensões carregadas
    jardim = new Jardim(linhas, colunas, false);
    jardimCriado = true;

    // Limpar o buffer de entrada
    ficheiro.ignore();

    // Carregar estado de cada posição do jardim
    for (int l = 0; l < linhas; ++l)
    {
        for (int c = 0; c < colunas; ++c)
        {
            string linhaCompleta;
            if (!getline(ficheiro, linhaCompleta))
            {
                cout << "[ERRO] >> Erro ao ler o estado do solo em (" << l << "," << c << ").\n";
                ficheiro.close();
                return false;
            }

            Solo &s = jardim->getSolo(l, c);
            if (!deserializarSolo(s, linhaCompleta))
            {
                cout << "[ERRO] >> Erro ao deserializar o solo em (" << l << "," << c << ").\n";
                ficheiro.close();
                return false;
            }
        }
    }

    ficheiro.close();

    // Apagar o ficheiro guardado após carregamento bem-sucedido
    if (remove(caminhoFicheiro.c_str()) != 0)
    {
        cout << "[AVISO] >> Não foi possível apagar o ficheiro de cópia após recuperação.\n";
    }

    return true;
}

bool Simulador::eNumeroValido(const string &str)
{
    if (str.empty())
        return false;

    size_t inicio = 0;
    if (str[0] == '-')  // Permite números negativos
        inicio = 1;

    if (inicio >= str.length())
        return false;

    for (size_t i = inicio; i < str.length(); ++i)
    {
        if (!isdigit(static_cast<unsigned char>(str[i])))
            return false;
    }

    return true;
}