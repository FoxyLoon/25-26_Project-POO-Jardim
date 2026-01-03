#include "Simulador.h"

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
    // if (cmd == "avanca")
    //     return comandoAvanca(ss);

    // ========================================================

    // Comandos Gerais
    if (cmd == "fim")
        return comandoFim();
    if (cmd == "jardim")
        return comandoJardim(ss);
    // if (cmd == "grava")
    //     return comandoGrava(ss);
    // if (cmd == "recupera")
    //     return comandoRecupera(ss);
    // if (cmd == "apaga")
    //     return comandoApaga(ss);
    // if (cmd == "executa")
    //     return comandoExecuta(ss);

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

    // // ========================================================

    // // Comandos para ações
    if (cmd == "colhe")
        return comandoColhe(ss);
    if (cmd == "planta")
        return comandoPlanta(ss);
    // if (cmd == "larga")
    //     return comandoLarga();
    // if (cmd == "pega")
    //     return comandoPega(ss);
    // if (cmd == "compra")
    //     return comandoCompra(ss);

    // // ========================================================

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

// bool Simulador::comandoAvanca(stringstream &ss)
// {
//     if (!isJardimCriado(jardimCriado))
//         return false;

//     int n = 1;
//     if (!(ss >> n))
//     {
//         n = 1;
//         cout << "[INFO] Numero de instantes nao especificado. Avancando 1 instante por defeito.\n";
//     }
//     if (n <= 0)
//     {
//         cout << "[ERRO] O numero de instantes deve ser positivo.\n";
//         return false;
//     }

//     // Avançar N instantes
//     for (int i = 0; i < n; ++i)
//     {
//         cout << "\n"
//              << string(60, '=') << "\n"
//              << "[INSTANTE " << (i + 1) << "/" << n << "]\n"
//              << string(60, '=') << "\n";

//         // 1. Reiniciar contadores do jardineiro
//         jardineiro.reiniciarTurno();
//         cout << "[INFO] >> Contadores do jardineiro reiniciados...\n";

//         // 2. APLICAR AÇÃO DA FERRAMENTA (se no jardim e com ferramenta na mão)
//         if (jardineiro.getEstaNoJardim())
//         {
//             Ferramenta *ferramenta = jardineiro.getFerramentaNaMao();
//             if (ferramenta != nullptr)
//             {
//                 Solo &s = jardim->getSolo(jardineiro.getLinha(), jardineiro.getColuna());
//                 ferramenta->aplicarNoSolo(s);

//                 // Remover ferramenta se ficar gasta (ex: adubo/regador vazios)
//                 if (ferramenta->estaGasta())
//                 {
//                     jardineiro.removerFerramenta(ferramenta->getNumeroSerie());
//                 }
//             }
//         }

//         // 3. Avança instante Jardim
//         jardim->avancaInstante();
//     }

//     cout << "\n"
//          << string(60, '=') << "\n"
//          << "[RESULTADO FINAL]\n"
//          << string(60, '=') << "\n";

//     jardim->mostraJardim();

//     return true;
// }

bool Simulador::comandoFim()
{
    cout << "A encerrar o simulador...\n";
    exit(0);
    return true; // nunca alcançado, mas satisfaz o tipo
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

// bool Simulador::comandoGrava(stringstream &ss)
// {
//     cout << "[INFO] Gravar estado nao implementado (sem persistencia nesta fase).\n";
//     return true;
// }

// // ========================================================

// bool Simulador::comandoRecupera(stringstream &ss)
// {
//     cout << "[INFO] Recuperar estado nao implementado (sem persistencia nesta fase).\n";
//     return true;
// }

// // ========================================================

// bool Simulador::comandoApaga(stringstream &ss)
// {
//     cout << "[INFO] Apagar copia nao implementado (sem persistencia nesta fase).\n";
//     return true;
// }

// // ========================================================

// bool Simulador::comandoExecuta(stringstream &ss)
// {
//     cout << "[INFO] Executar ficheiro de comandos nao implementado (I/O de ficheiros nao disponivel nesta fase).\n";
//     return true;
// }

// // Não é suposto existir - necessário remover
// /* bool Simulador::comandoEstado() const
// {
//     if (!jardimCriado)
//     {
//         cout << "[ERRO] E necessario criar o jardim antes de ver o seu estado.\n";
//         return false;
//     }
//     jardim->mostrar();
//     return true;
// } */

// ========================================================
// ========================================================
// ========================================================

// Comandos para listar informação

// Lista todas as plantas
bool Simulador::comandoLplantas()
{
    if (!isJardimCriado())
    {
        return false;
    }

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
bool Simulador::comandoLplanta(stringstream &ss)
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
bool Simulador::comandoLarea()
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

    // Nota: Condição tecnicamente impossivel pois o jardim sempre terá 3 ferramentas
    if (!encontrouSoloOcupado)
    {
        cout << "[INFO] >> Não existem plantas ou ferramentas no jardim." << endl;
    }

    cout << string(111, '-') << "\n"
         << string(111, '=') << endl;

    return true;
}

// ========================================================

bool Simulador::comandoLsolo(stringstream &ss)
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
            // Esta condição é a mesma de isForaDosLimites() mas sem o cout para não spammar na consola
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

    // Nota: Condição tecnicamente impossivel pois o jardim sempre terá 3 ferramentas
    if (!encontrouSoloOcupado)
    {
        cout << "[INFO] >> Não existem plantas ou ferramentas na posição especificada ou na área indicada do jardim." << endl;
    }

    cout << string(111, '-') << "\n"
         << string(111, '=') << endl;
    return true;
}

// ========================================================

// TODO: verificar se o inventario apresenta a ferramenta equipada
bool Simulador::comandoLferr()
{
    if (!isJardimCriado())
        return false;

    jardineiro.listarFerramentas();

    cout << string(51, '-') << endl;

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
    {
        return false;
    }

    // Verifica se o comando tem o formato correto
    string posicao;
    char tipoPlanta;
    if (!(ss >> posicao >> tipoPlanta) || !isLetraPequena(posicao))
    {
        cout << string(111, '=') << "\n[ERRO] >> O comando planta requer posicao e tipo (ex: planta aa C)." << endl;
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

    // Criação da planta de acordo com o tipo fornecido
    Planta *novaPlanta = nullptr;
    tipoPlanta = toupper(tipoPlanta);

    switch (tipoPlanta)
    {
    case 'C': // Cacto
        novaPlanta = new Cacto();
        break;
    case 'R': // Roseira
        novaPlanta = new Roseira();
        break;
    case 'E': // Erva-Daninha
        novaPlanta = new ErvaDaninha();
        break;
    case 'X': // Planta Exotica
        novaPlanta = new PlantaExotica();
        break;
    default:
        cout << string(111, '=') << "\n[ERRO] >> Tipo de planta desconhecido: " << tipoPlanta << endl;
        return false;
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

// bool Simulador::comandoLarga()
// {
//     if (!isJardimCriado(jardimCriado))
//         return false;

//     jardineiro.largarFerramenta();

//     return true;
// }

// // ========================================================

// bool Simulador::comandoPega(stringstream &ss)
// {
//     if (!isJardimCriado(jardimCriado))
//         return false;

//     int numeroSerie;
//     if (!(ss >> numeroSerie))
//     {
//         cout << "[ERRO] Uso: pega <numero_de_serie>.\n";
//         return false;
//     }

//     // Pegar ferramenta do inventário
//     jardineiro.pegarFerramenta(numeroSerie);

//     return true;
// }

// // ========================================================

// bool Simulador::comandoCompra(stringstream &ss)
// {
//     if (!isJardimCriado(jardimCriado))
//         return false;

//     char tipo;
//     if (!(ss >> tipo))
//     {
//         cout << "[ERRO] Uso: compra <tipo>. Tipos: g a t z.\n";
//         return false;
//     }

//     // Criar ferramenta usando factory method
//     Ferramenta *f = Ferramenta::criar(tipo);

//     if (!f)
//     {
//         cout << "[ERRO] >> Tipo de ferramenta invalido. Use g, a, t ou z.\n";
//         return false;
//     }

//     // Adicionar ao inventário do jardineiro
//     jardineiro.adicionarFerramenta(f);

//     return true;
// }

// // ========================================================
// // ========================================================
// // ========================================================

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

    // Apanha ferramenta se houver alguma no novo solo
    if (novoSolo.temFerramenta())
    {
        Ferramenta *ferramentaEncontrada = novoSolo.removerFerramenta();
        jardineiro.adicionarFerramenta(ferramentaEncontrada);
        cout << "[INFO] >> O Jardineiro apanhou uma ferramenta: " << ferramentaEncontrada->getNomeFerramenta() << "!\n";
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

    // Apanha ferramenta se houver alguma no novo solo
    if (novoSolo.temFerramenta())
    {
        Ferramenta *ferramentaEncontrada = novoSolo.removerFerramenta();
        jardineiro.adicionarFerramenta(ferramentaEncontrada);
        cout << "[INFO] >> O Jardineiro apanhou uma ferramenta: " << ferramentaEncontrada->getNomeFerramenta() << "!\n";
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

    // Apanha ferramenta se houver alguma no novo solo
    if (novoSolo.temFerramenta())
    {
        Ferramenta *ferramentaEncontrada = novoSolo.removerFerramenta();
        jardineiro.adicionarFerramenta(ferramentaEncontrada);
        cout << "[INFO] >> O Jardineiro apanhou uma ferramenta: " << ferramentaEncontrada->getNomeFerramenta() << "!\n";
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

    // Apanha ferramenta se houver alguma no novo solo
    if (novoSolo.temFerramenta())
    {
        Ferramenta *ferramentaEncontrada = novoSolo.removerFerramenta();
        jardineiro.adicionarFerramenta(ferramentaEncontrada);
        cout << "[INFO] >> O Jardineiro apanhou uma ferramenta: " << ferramentaEncontrada->getNomeFerramenta() << "!\n";
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

    // Nota: Não é preciso verificar se jardineiro já está cá dentro pois
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
        jardineiro.adicionarFerramenta(ferramenta);
        cout << "[INFO] >> O jardineiro encontrou e apanhou: " << ferramenta->getNomeFerramenta() << "!\n";
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

// Funões Auxiliares

// Verifica se uma string contém duas letras minusculas
bool Simulador::isLetraPequena(const string &p)
{
    return p.size() == 2 && islower(static_cast<unsigned char>(p[0])) && islower(static_cast<unsigned char>(p[1]));
}

bool Simulador::isJardimCriado()
{
    if (!jardimCriado)
    {
        cout << string(111, '=') << "\n[ERRO] >> É necessário criar um jardim primeiro!" << endl;
        return false;
    }
    return true;
}

bool Simulador::isJardineiroNoJardim()
{
    if (!jardineiroNoJardim)
    {
        cout << string(111, '=') << "\n[ERRO] >> É necessário o jardineiro entrar no jardim primeiro!" << endl;
        return false;
    }
    return true;
}

bool Simulador::isForaDosLimites(int linhas, int colunas)
{
    if (linhas < 0 || linhas >= jardim->getLinhas() || colunas < 0 || colunas >= jardim->getColunas())
    {
        cout << string(111, '=') << "\n[ERRO] >> Posição inválida! (fora dos limites).\n";
        return true;
    }
    return false;
}
