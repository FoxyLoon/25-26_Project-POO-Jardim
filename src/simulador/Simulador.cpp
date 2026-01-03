#include "Simulador.h"
#include <fstream>
#include <sys/stat.h>

using namespace std;

Simulador::Simulador() : jardim(nullptr), jardimCriado(false), jardineiroCriado(false) {}

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
    if (cmd == "grava")
        return comandoGrava(ss);
    if (cmd == "recupera")
        return comandoRecupera(ss);
    if (cmd == "apaga")
        return comandoApaga(ss);
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
    // if (cmd == "lferr")
    //     return comandoLferr();

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
    cout << "[ERRO] Comando desconhecido: " << cmd << "\n";
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
        cout << "[INFO] Já existe um jardim criado!\n";
        return false;
    }
    else if (!(ss >> linhas >> colunas))
    {
        cout << "[ERRO] >> Faltam valores!\n";
        return false;
    }
    else if (ss >> extra)
    {
        cout << "[ERRO] >> Existem parametros a mais!\n";
        return false;
    }
    else if (linhas < 1 || linhas > 26)
    {
        cout << "[ERRO] >> Número de LINHAS Inválido!\n";
        return false;
    }
    else if (colunas < 1 || colunas > 26)
    {
        cout << "[ERRO] >> Número de COLUNAS Inválido!\n";
        return false;
    }

    jardim = new Jardim(linhas, colunas);
    jardimCriado = true;
    cout << "[INFO] >> Foi criado um Jardim com "
         << linhas << " linhas e "
         << colunas << " colunas.\n";

    jardim->mostraJardim();
    return true;
}

// ========================================================

bool Simulador::comandoGrava(stringstream &ss)
{
    if (!isJardimCriado())
        return false;

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
         << string(39, '=') << "[ LISTAGEM DE PLANTAS NO JARDIM ]" << string(39, '=') << endl;

    // Percorre todas as linhas do jardim
    for (int linha_atual = 0; linha_atual < jardim->getLinhas(); ++linha_atual)
    {
        // Percorre todas as colunas do jardim
        for (int coluna_atual = 0; coluna_atual < jardim->getColunas(); ++coluna_atual)
        {
            Solo &soloAtual = jardim->getSolo(linha_atual, coluna_atual);

            // Verifica se este solo possui uma planta
            if (soloAtual.temPlanta())
            {
                encontrouPlantas = true;
                contadorPlantas++;
                Planta *plantaNoSolo = soloAtual.getPlanta();

                // Conversão de indices inteiros para letras
                char letraLinha = static_cast<char>('a' + linha_atual);
                char letraColuna = static_cast<char>('a' + coluna_atual);

                cout << string(111, '-') << "\n"
                     << contadorPlantas << "ª Planta - Posicao ( " << letraLinha << " , " << letraColuna << " )" << "\n"
                     << "{Planta}" << plantaNoSolo->getInfoPlanta() << "\n"
                     << "{Solo}" << soloAtual.getInfoSolo();
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
        cout << "[ERRO] >> Formato de posicao invalido! Use duas letras minusculas (ex: lplanta aa)." << endl;
        return false;
    }

    // Conversão de letras para índices inteiros
    int linha = posicao[0] - 'a';
    int coluna = posicao[1] - 'a';
    if (isForaDosLimites(linha, coluna))
    {
        return false;
    }

    Solo &soloAlvo = jardim->getSolo(linha, coluna);
    if (!soloAlvo.temPlanta())
    {
        cout << "[INFO] >> Nao existe nenhuma planta na posicao ( "
             << posicao[0] << " , " << posicao[1] << " )." << endl;
        return false;
    }

    // ========================================================

    Planta *plantaAlvo = soloAlvo.getPlanta();

    cout << "\n"
         << string(44, '=') << "[ DETALHE DA PLANTA ]" << string(44, '=') << "\n"
         << string(111, '-') << "\n"
         << "Posicao ( " << posicao[0] << " , " << posicao[1] << " )" << "\n"
         << "{Planta}" << plantaAlvo->getInfoPlanta()
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
         << string(39, '=') << "[ LISTAGEM DAS ÁREAS OCUPADAS ]" << string(39, '=') << endl;

    bool encontrouSoloOcupado = false;
    int contadorSolos = 0;

    // Percorre todas as linhas do jardim
    for (int linha_atual = 0; linha_atual < jardim->getLinhas(); ++linha_atual)
    {
        // Percorre todas as colunas do jardim
        for (int coluna_atual = 0; coluna_atual < jardim->getColunas(); ++coluna_atual)
        {
            Solo &soloAtual = jardim->getSolo(linha_atual, coluna_atual);

            // Verifica se este solo tem conteudo
            if (!soloAtual.estaVazio())
            {
                encontrouSoloOcupado = true;
                contadorSolos++;

                // Conversão de indices inteiros para letras
                char letraLinha = static_cast<char>('a' + linha_atual);
                char letraColuna = static_cast<char>('a' + coluna_atual);

                cout << string(111, '-') << "\n"
                     << contadorSolos << "ª Area Ocupada - Posicao ( " << letraLinha << " , " << letraColuna << " )" << "\n"
                     << "{Solo}" << soloAtual.getInfoSolo();
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
        cout << "[ERRO] >> O comando lsolo requer pelo menos uma posicao (ex: lsolo aa [numero_opcional])." << endl;
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
         << string(35, '=') << "[ INSPECAO DE SOLO ]" << string(35, '=') << endl;

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

            Solo &soloAtual = jardim->getSolo(linha_atual, coluna_atual);

            // Verifica se este solo tem conteudo
            if (!soloAtual.estaVazio())
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

                cout << string(111, '-') << "\n"
                     << contadorSolos << "ª Area Ocupada - Posicao ( " << letraLinha << " , " << letraColuna << " )" << "\n";

                // Propriedades do Solo
                cout << "{Solo} " << soloAtual.getInfoSolo();

                // Propriedades da Planta (se existir)
                if (soloAtual.temPlanta())
                {
                    cout << "\n{Planta} " << soloAtual.getPlanta()->getInfoPlanta();
                }

                // Propriedades da Ferramenta (se existir)
                if (soloAtual.temFerramenta())
                {
                    cout << "\n{Ferramenta} " << soloAtual.getFerramenta()->getInfoFerramenta();
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

// // ========================================================

// bool Simulador::comandoLferr()
// {
//     if (!isJardimCriado(jardimCriado))
//         return false;

//     jardineiro.listarFerramentas();

//     return true;
// }

// // ========================================================
// // ========================================================
// // ========================================================

// // Comandos para ações

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
        cout << "[ERRO] >> O comando colhe requer uma posição (ex: colhe aa)." << endl;
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
        cout << "[ERRO] >> Não existe nenhuma planta na posição " << posicao << "!" << endl;
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
        cout << "[ERRO] >> O comando planta requer posicao e tipo (ex: planta aa C)." << endl;
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
        cout << "[ERRO] >> Tipo de planta desconhecido: " << tipoPlanta << endl;
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
    if (!isJardineiroCriado())
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
        cout << "[ERRO] >> Movimento invalido (fora dos limites).\n";
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
    if (!isJardineiroCriado())
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
    if (!isJardineiroCriado())
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
    if (!isJardineiroCriado())
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
        cout << "[ERRO] >> Formato invalido! Use: entra <letras> (ex: entra aa)" << endl;
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
    jardineiroCriado = true;

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

    if (!isJardineiroCriado())
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
    jardineiroCriado = false;

    jardim->mostraJardim();
    return true;
}

// ========================================================
// ========================================================
// ========================================================

// Funções Auxiliares

// Verifica se uma string contém duas letras minusculas
bool Simulador::isLetraPequena(const string &p)
{
    return p.size() == 2 && islower(static_cast<unsigned char>(p[0])) && islower(static_cast<unsigned char>(p[1]));
}

bool Simulador::isJardimCriado()
{
    if (!jardimCriado)
    {
        cout << "[ERRO] >> É necessário criar um jardim primeiro!" << endl;
        return false;
    }
    return true;
}

bool Simulador::isJardineiroCriado()
{
    if (!jardineiroCriado)
    {
        cout << "[ERRO] >> É necessário o jardineiro entrar no jardim primeiro!" << endl;
        return false;
    }
    return true;
}

bool Simulador::isForaDosLimites(int linhas, int colunas)
{
    if (linhas < 0 || linhas >= jardim->getLinhas() || colunas < 0 || colunas >= jardim->getColunas())
    {
        cout << "[ERRO] >> Posição inválida! (fora dos limites).\n";
        return true;
    }
    return false;
}


// ========================================================
// ========================================================
// ========================================================


// ================================================================
// ================================================================
// ================================================================

// Funções para Serialização/Deserialização

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
    if (remove(caminhoFicheiro.c_str()) != 0) // c_str() converte a string (C++) para um const char* (C) para poder ser rercebido em remove()
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

Planta* Simulador::deserializarPlanta(const string &dados)
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

    if (planta)
    {
        planta->setAguaInterna(agua);
        planta->setNutrientesInternos(nutrientes);
    }

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

Ferramenta* Simulador::deserializarFerramenta(const string &dados)
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

    while (getline(ss, token, '|'))
    {
        size_t pos = token.find(':');
        if (pos != string::npos)
        {
            string chave = token.substr(0, pos);
            string valor = token.substr(pos + 1);

            if (chave == "AGUA")
                agua = stoi(valor);
            else if (chave == "NUTRIENTES")
                nutrientes = stoi(valor);
            else if (chave == "PLANTA")
                plantaStr = valor;
            else if (chave == "FERRAMENTA")
                ferramentaStr = valor;
        }
    }

    s.setAgua(agua);
    s.setNutrientes(nutrientes);

    Planta *p = deserializarPlanta(plantaStr);
    if (p != nullptr)
        s.setPlanta(p);

    Ferramenta *f = deserializarFerramenta(ferramentaStr);
    if (f != nullptr)
        s.setFerramenta(f);

    return true;
}

bool Simulador::salvarJardimEmFicheiro(const string &nome)
{
    if (!jardimCriado || jardim == nullptr)
    {
        cout << "[ERRO] >> Não existe um jardim para guardar.\n";
        return false;
    }

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
    if (jardim != nullptr)
    {
        delete jardim;
    }

    // Criar novo jardim com as dimensões carregadas
    jardim = new Jardim(linhas, colunas);
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