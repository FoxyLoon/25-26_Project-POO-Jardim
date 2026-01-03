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

// Funções Auxiliares

// Verifica se uma string contém duas letras minusculas
bool Simulador::isPosicaoValida(const string &p)
{
    return p.size() == 2 && islower(static_cast<unsigned char>(p[0])) && islower(static_cast<unsigned char>(p[1]));
}

bool Simulador::isJardimCriado(const bool &jm_c)
{
    if (!jm_c)
    {
        cout << "[ERRO] >> É necessário criar um jardim primeiro\n";
        return false;
    }

    return true;
}

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
    // if (cmd == "apaga")
    //     return comandoApaga(ss);
    // if (cmd == "executa")
    //     return comandoExecuta(ss);

    // // ========================================================

    // // Comandos para listar informação
    // if (cmd == "lplantas")
    //     return comandoLplantas();
    // if (cmd == "lplanta")
    //     return comandoLplanta(ss);
    // if (cmd == "larea")
    //     return comandoLarea();
    // if (cmd == "lsolo")
    //     return comandoLsolo(ss);
    // if (cmd == "lferr")
    //     return comandoLferr();

    // // ========================================================

    // // Comandos para ações
    // if (cmd == "colhe")
    //     return comandoColhe(ss);
    // if (cmd == "planta")
    //     return comandoPlanta(ss);
    // if (cmd == "larga")
    //     return comandoLarga();
    // if (cmd == "pega")
    //     return comandoPega(ss);
    // if (cmd == "compra")
    //     return comandoCompra(ss);

    // // ========================================================

    // // Comandos para controlar o jardineiro
    // if (cmd == "e")
    //     return comandoE();
    // if (cmd == "d")
    //     return comandoD();
    // if (cmd == "c")
    //     return comandoC();
    // if (cmd == "b")
    //     return comandoB();
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
    if (!isJardimCriado(jardimCriado))
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

// ========================================================

bool Simulador::comandoEntra(stringstream &ss)
{
    if (!isJardimCriado(jardimCriado))
        return false;

    string pos;
    if (!(ss >> pos) || pos.length() != 2)
    {
        cout << "[ERRO] >> Formato invalido! Use: entra <letras> (ex: entra aa)" << endl;
        return false;
    }

    if (!jardineiro.podeEntrarSair())
    {
        cout << "[ERRO] >> Limite de entradas/saidas atingido! (" << Settings::Jardineiro::max_entradas_saidas << " por turno)\n";
        return false;
    }

    // Conversão de letras minusculas para indices inteiros
    int linhas = pos[0] - 'a';
    int colunas = pos[1] - 'a';

    if (linhas < 0 || linhas >= jardim->getLinhas() || colunas < 0 || colunas >= jardim->getColunas())
    {
        cout << "[ERRO] >> Posição " << pos << " fora dos limites!\n";
        return false;
    }

    // Entra no jardim
    jardineiro.usaEntrar(linhas, colunas);
    jardineiroCriado = true;

    Solo &s = jardim->getSolo(linhas, colunas);
    s.setJardineiro(true);

    // Se houver ferramenta no solo, o jardineiro apanha-a
    if (s.temFerramenta())
    {
        Ferramenta *f = s.removerFerramenta();
        jardineiro.adicionarFerramenta(f);
        cout << "[INFO] >> O jardineiro encontrou e apanhou: " << f->getNome() << "!\n";
    }

    cout << "[INFO] >> O Jardineiro entrou na posicao " << pos << ".\n";
    jardim->mostraJardim();

    return true;
}

// ========================================================

bool Simulador::comandoSai()
{
    if (!isJardimCriado(jardimCriado))
        return false;

    if (!jardineiroCriado)
    {
        cout << "[AVISO] >> O jardineiro nao esta no jardim." << endl;
        return false;
    }

    if (!jardineiro.podeEntrarSair())
    {
        cout << "[ERRO] >> Limite de entradas/saidas atingido! ("
             << Settings::Jardineiro::max_entradas_saidas << " por turno)\n";
        return false;
    }

    int l = jardineiro.getLinha();
    int c = jardineiro.getColuna();
    if (l >= 0 && c >= 0)
    {
        jardim->getSolo(l, c).setJardineiro(false);
    }

    jardineiro.usaSair();
    jardineiroCriado = false;

    cout << "[INFO] >> o Jardineiro SAIU do Jardim.\n";
    jardim->mostraJardim();
    return true;
}

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

    char tipo = p->getSimbolo();
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

    char tipo = f->getSimbolo();
    int serie = f->getNumeroSerie();

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