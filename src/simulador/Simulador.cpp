#include "Simulador.h"
#include <iostream>
#include <sstream>

using namespace std;

Simulador::Simulador() : jardim(nullptr), jardimCriado(false), jardineiroCriado(false) {}

Simulador::~Simulador()
{
    delete jardim;
}

// --- Função auxiliar ---
bool Simulador::isPosicaoValida(const string &p)
{
    return p.size() == 2 && islower(static_cast<unsigned char>(p[0])) && islower(static_cast<unsigned char>(p[1]));
}

// --- Processamento dos Comandos ---
bool Simulador::processaComando(const string &linha)
{
    stringstream ss(linha);
    string cmd;

    // lê até ao primeiro espaço (apenas a primeira palavra)
    // Nota: Os parametros depois do espaço ficam e são usados mais tarde
    ss >> cmd;

    if (cmd == "avanca")
        return comandoAvanca(ss);
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
    if (cmd == "fim")
        return comandoFim();

    // Retorna "false" caso o comando não for nenhum dos de cima
    cout << "[ERRO] Comando desconhecido: " << cmd << "\n";
    return false;
}

// ========================================================

// --- Implementação de cada comando ---

bool Simulador::comandoFim()
{
    cout << "A encerrar o simulador...\n";
    exit(0);
    return true; // nunca alcançado, mas satisfaz o tipo
}

bool Simulador::comandoJardim(stringstream &ss)
{
    int linhas, colunas;
    if (!(ss >> linhas >> colunas))
    {
        cout << "[ERRO] Faltam valores!\n";
        return false;
    }
    if (linhas < 1 || linhas > 26)
    {
        cout << "[ERRO] Número de Linhas Inválido!\n";
        return false;
    }
    if (colunas < 1 || colunas > 26)
    {
        cout << "[ERRO] Número de Colunas Inválido!\n";
        return false;
    }

    if (jardimCriado)
    {
        cout << "[INFO] Já existe um jardim criado!\n";
        return false;
    }

    jardim = new Jardim(linhas, colunas);
    jardimCriado = true;
    cout << "[INFO] O Jardim foi criado com "
         << linhas << " linhas e "
         << colunas << " colunas.\n";

    jardim->mostrar();
    return true;
}

bool Simulador::comandoEstado() const
{
    if (!jardimCriado)
    {
        cout << "[ERRO] E necessario criar o jardim antes de ver o seu estado.\n";
        return false;
    }
    jardim->mostrar();
    return true;
}

bool Simulador::comandoEntra(stringstream &ss)
{
    if (!jardimCriado)
    {
        cout << "[ERRO] Nao e possivel adicionar um Jardineiro sem ter um jardim criado primeiro!\n";
        return false;
    }

    string pos;
    if (!(ss >> pos) || !isPosicaoValida(pos))
    {
        cout << "[ERRO] Posicao invalida. Use duas letras minusculas.\n";
        return false;
    }

    jardineiroCriado = true;
    jardineiro.entrarNoJardim(pos[0] - 'a', pos[1] - 'a');
    cout << "Jardineiro entrou na posição " << pos << ".\n";
    jardim->mostrarComJardineiro(jardineiro);

    return true;
}

bool Simulador::comandoSai()
{
    if (!jardimCriado)
    {
        cout << "[ERRO] Não e possivel remover um Jardineiro sem ter um jardim criado primeiro!\n";
        return false;
    }

    if (!jardineiroCriado)
    {
        cout << "[ERRO] Nao e possivel remover um Jardineiro que nao existe!\n";
        return false;
    }

    jardineiroCriado = false;
    jardineiro.sairDoJardim();
    cout << "Jardineiro saiu do jardim.\n";
    jardim->mostrar();
    return true;
}

bool Simulador::comandoAvanca(stringstream &ss)
{
    if (!jardimCriado)
    {
        cout << "[ERRO] E necessario criar o jardim antes de avançar o tempo.\n";
        return false;
    }

    int n = 1;
    if (!(ss >> n))
    {
        n = 1; // padrão
    }
    if (n <= 0)
    {
        cout << "[ERRO] O numero de instantes deve ser positivo.\n";
        return false;
    }

    for (int i = 0; i < n; ++i)
    {
        cout << "[INFO] Avancando 1 instante (" << i + 1 << "/" << n << ")...\n";
        // Atualmente não existem plantas com estado a atualizar; se existissem,
        // aqui invocar-se-ia a sua atualização.
    }

    // Mostrar estado actual do jardim
    jardim->mostrar();
    return true;
}

bool Simulador::comandoLplantas()
{
    if (!jardimCriado)
    {
        cout << "[ERRO] E necessario criar o jardim antes de listar plantas.\n";
        return false;
    }

    // Nesta meta ainda não existem plantas armazenadas no solo (estrutura Solo não contem plantas).
    cout << "[INFO] Listagem de plantas nao implementada nesta fase.\n";
    jardim->mostrar();
    return true;
}

bool Simulador::comandoLplanta(stringstream &ss)
{
    if (!jardimCriado)
    {
        cout << "[ERRO] E necessario criar o jardim antes de listar uma planta.\n";
        return false;
    }

    string pos;
    if (!(ss >> pos) || !isPosicaoValida(pos))
    {
        cout << "[ERRO] Posicao invalida. Use duas letras minusculas.\n";
        return false;
    }

    int l = pos[0] - 'a';
    int c = pos[1] - 'a';
    Solo *s = jardim->getSolo(l, c);
    if (!s)
    {
        cout << "[ERRO] Posicao fora do jardim.\n";
        return false;
    }

    cout << "[INFO] Informacao da planta em " << pos << ": (nao implementado).\n";
    cout << "Solo - agua: " << s->agua << ", nutrientes: " << s->nutrientes << "\n";
    return true;
}

bool Simulador::comandoLarea()
{
    if (!jardimCriado)
    {
        cout << "[ERRO] E necessario criar o jardim antes de listar area.\n";
        return false;
    }
    // Mostrar toda a area com o estado actual
    jardim->mostrar();
    return true;
}

bool Simulador::comandoLsolo(stringstream &ss)
{
    if (!jardimCriado)
    {
        cout << "[ERRO] E necessario criar o jardim antes de listar solo.\n";
        return false;
    }

    string pos;
    if (!(ss >> pos) || !isPosicaoValida(pos))
    {
        cout << "[ERRO] Posicao invalida. Use duas letras minusculas.\n";
        return false;
    }

    int raio = 0;
    if (!(ss >> raio))
    {
        raio = 0; // se não fornecido, apenas a posição indicada
    }
    if (raio < 0)
        raio = 0;

    int li = pos[0] - 'a';
    int ci = pos[1] - 'a';

    for (int dl = -raio; dl <= raio; ++dl)
    {
        for (int dc = -raio; dc <= raio; ++dc)
        {
            int l = li + dl;
            int c = ci + dc;
            Solo *s = jardim->getSolo(l, c);
            if (s)
            {
                char pl = char('a' + l);
                char pc = char('a' + c);
                cout << "Posicao " << pl << pc << " -> agua: " << s->agua
                     << ", nutrientes: " << s->nutrientes << "\n";
            }
        }
    }

    return true;
}

bool Simulador::comandoLferr()
{
    if (!jardimCriado)
    {
        cout << "[ERRO] E necessario criar o jardim antes de listar ferramentas.\n";
        return false;
    }

    cout << "[INFO] Listagem de ferramentas nao implementada nesta fase.\n";
    return true;
}

bool Simulador::comandoColhe(stringstream &ss)
{
    if (!jardimCriado)
    {
        cout << "[ERRO] E necessario criar o jardim antes de colher.\n";
        return false;
    }

    string pos;
    if (!(ss >> pos) || !isPosicaoValida(pos))
    {
        cout << "[ERRO] Posicao invalida. Use duas letras minusculas.\n";
        return false;
    }

    // Nesta fase nao existe colecao de plantas por posicao, logo nao ha colheita real
    cout << "[INFO] Colhe nao implementado (sem plantas).\n";
    jardim->mostrar();
    return true;
}

bool Simulador::comandoPlanta(stringstream &ss)
{
    if (!jardimCriado)
    {
        cout << "[ERRO] E necessario criar o jardim antes de plantar.\n";
        return false;
    }

    string pos;
    char tipo;
    if (!(ss >> pos >> tipo) || !isPosicaoValida(pos))
    {
        cout << "[ERRO] Uso: planta <l><c> <tipo> (ex: planta ab C).\n";
        return false;
    }

    // Tipos aceites: C, R, E, X (aceita minusculas tambem)
    tipo = static_cast<char>(toupper(static_cast<unsigned char>(tipo)));
    if (tipo != 'C' && tipo != 'R' && tipo != 'E' && tipo != 'X')
    {
        cout << "[ERRO] Tipo de planta invalido. Use C, R, E ou X.\n";
        return false;
    }

    cout << "[INFO] Plantar nao implementado nesta fase. (Recebido: " << pos << " " << tipo << ")\n";
    jardim->mostrar();
    return true;
}

bool Simulador::comandoLarga()
{
    if (!jardimCriado)
    {
        cout << "[ERRO] E necessario criar o jardim antes de largar ferramentas.\n";
        return false;
    }

    cout << "[INFO] Largar ferramenta nao implementado nesta fase.\n";
    return true;
}

bool Simulador::comandoPega(stringstream &ss)
{
    if (!jardimCriado)
    {
        cout << "[ERRO] E necessario criar o jardim antes de pegar uma ferramenta.\n";
        return false;
    }

    int id;
    if (!(ss >> id))
    {
        cout << "[ERRO] Uso: pega <numero_de_serie>.\n";
        return false;
    }

    cout << "[INFO] Pegar ferramenta nao implementado nesta fase (id=" << id << ").\n";
    return true;
}

bool Simulador::comandoCompra(stringstream &ss)
{
    if (!jardimCriado)
    {
        cout << "[ERRO] E necessario criar o jardim antes de comprar ferramentas.\n";
        return false;
    }

    char tipo;
    if (!(ss >> tipo))
    {
        cout << "[ERRO] Uso: compra <tipo>. Tipos: g a t z.\n";
        return false;
    }
    cout << "[INFO] Compra de ferramenta nao implementada nesta fase (tipo=" << tipo << ").\n";
    return true;
}

bool Simulador::comandoE()
{
    if (!jardimCriado)
    {
        cout << "[ERRO] E necessario criar o jardim antes de mover o jardineiro.\n";
        return false;
    }
    if (!jardineiroCriado)
    {
        cout << "[ERRO] O jardineiro nao foi colocado no jardim.\n";
        return false;
    }

    int l = jardineiro.getLinha();
    int c = jardineiro.getColuna();
    Solo *dest = jardim->getSolo(l, c - 1);
    if (!dest)
    {
        cout << "[ERRO] Movimento invalido (fora dos limites).\n";
        return false;
    }

    jardineiro.entrarNoJardim(l, c - 1);
    cout << "Jardineiro deslocou-se para a esquerda.\n";
    jardim->mostrarComJardineiro(jardineiro);
    return true;
}

bool Simulador::comandoD()
{
    if (!jardimCriado)
    {
        cout << "[ERRO] E necessario criar o jardim antes de mover o jardineiro.\n";
        return false;
    }
    if (!jardineiroCriado)
    {
        cout << "[ERRO] O jardineiro nao foi colocado no jardim.\n";
        return false;
    }

    int l = jardineiro.getLinha();
    int c = jardineiro.getColuna();
    Solo *dest = jardim->getSolo(l, c + 1);
    if (!dest)
    {
        cout << "[ERRO] Movimento invalido (fora dos limites).\n";
        return false;
    }

    jardineiro.entrarNoJardim(l, c + 1);
    cout << "Jardineiro deslocou-se para a direita.\n";
    jardim->mostrarComJardineiro(jardineiro);
    return true;
}

bool Simulador::comandoC()
{
    if (!jardimCriado)
    {
        cout << "[ERRO] E necessario criar o jardim antes de mover o jardineiro.\n";
        return false;
    }
    if (!jardineiroCriado)
    {
        cout << "[ERRO] O jardineiro nao foi colocado no jardim.\n";
        return false;
    }

    int l = jardineiro.getLinha();
    int c = jardineiro.getColuna();
    Solo *dest = jardim->getSolo(l - 1, c);
    if (!dest)
    {
        cout << "[ERRO] Movimento invalido (fora dos limites).\n";
        return false;
    }

    jardineiro.entrarNoJardim(l - 1, c);
    cout << "Jardineiro deslocou-se para cima.\n";
    jardim->mostrarComJardineiro(jardineiro);
    return true;
}

bool Simulador::comandoB()
{
    if (!jardimCriado)
    {
        cout << "[ERRO] E necessario criar o jardim antes de mover o jardineiro.\n";
        return false;
    }
    if (!jardineiroCriado)
    {
        cout << "[ERRO] O jardineiro nao foi colocado no jardim.\n";
        return false;
    }

    int l = jardineiro.getLinha();
    int c = jardineiro.getColuna();
    Solo *dest = jardim->getSolo(l + 1, c);
    if (!dest)
    {
        cout << "[ERRO] Movimento invalido (fora dos limites).\n";
        return false;
    }

    jardineiro.entrarNoJardim(l + 1, c);
    cout << "Jardineiro deslocou-se para baixo.\n";
    jardim->mostrarComJardineiro(jardineiro);
    return true;
}

bool Simulador::comandoGrava(stringstream &ss)
{
    cout << "[INFO] Gravar estado nao implementado (sem persistencia nesta fase).\n";
    return true;
}

bool Simulador::comandoRecupera(stringstream &ss)
{
    cout << "[INFO] Recuperar estado nao implementado (sem persistencia nesta fase).\n";
    return true;
}

bool Simulador::comandoApaga(stringstream &ss)
{
    cout << "[INFO] Apagar copia nao implementado (sem persistencia nesta fase).\n";
    return true;
}

bool Simulador::comandoExecuta(stringstream &ss)
{
    cout << "[INFO] Executar ficheiro de comandos nao implementado (I/O de ficheiros nao disponivel nesta fase).\n";
    return true;
}
