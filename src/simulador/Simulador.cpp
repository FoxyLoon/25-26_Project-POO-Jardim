#include "Simulador.h"

using namespace std;

Simulador::Simulador() : jardim(nullptr), jardimCriado(false), jardineiroCriado(false) {}

Simulador::~Simulador()
{
    delete jardim;
}

// ================================================================
// ================================================================
// ================================================================

// Funões Auxiliares

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

bool Simulador::isJardineiroCriado(const bool &jo_c)
{
    if (!jo_c)
    {
        cout << "[ERRO] >> É necesario criar um jardineiro primeiro\n";
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
    cout << "[ERRO] Comando desconhecido: " << cmd << "\n";
    return false;
}

// ========================================================

// Comandos Gerais

bool Simulador::comandoAvanca(stringstream &ss) {
    if (!isJardimCriado(jardimCriado))
        return false;

    int n = 1;
    if (!(ss >> n)) {
        n = 1;
        cout << "[INFO] Numero de instantes nao especificado. Avancando 1 instante por defeito.\n";
    }
    if (n <= 0) {
        cout << "[ERRO] O numero de instantes deve ser positivo.\n";
        return false;
    }

    // Avançar N instantes
    for (int i = 0; i < n; ++i) {
        cout << "\n";
        cout << string(60, '=') << "\n";
        cout << "[INSTANTE " << (i + 1) << "/" << n << "]\n";
        cout << string(60, '=') << "\n";

        // ========================================================
        // 1. RESETAR CONTADORES DO JARDINEIRO
        // ========================================================
        jardineiro.resetarContadores();
        cout << "[INFO] Contadores do jardineiro resetados.\n";

        // ========================================================
        // 2. APLICAR FERRAMENTA (se jardineiro tiver uma na mão E estiver no jardim)
        // ========================================================
        if (jardineiroCriado && jardineiro.getFerramentaNaMao()) {
            Solo* s = jardim->getSolo(jardineiro.getLinha(), jardineiro.getColuna());
            if (s) {
                cout << "[INFO] Aplicando " << jardineiro.getFerramentaNaMao()->nome()
                     << " em " << char('a' + jardineiro.getLinha())
                     << char('a' + jardineiro.getColuna()) << "...\n";

                jardineiro.aplicarFerramentaSeNaMao(*s);
            }
        }

        // ========================================================
        // 3. AVANÇAR INSTANTE DO JARDIM (plantas processam, morrem, multiplicam)
        // ========================================================
        jardim->avancarInstante();
    }

    cout << "\n";
    cout << string(60, '=') << "\n";
    cout << "[RESULTADO FINAL]\n";
    cout << string(60, '=') << "\n";

    jardim->mostraJardim(jardineiro);

    return true;
}

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

    jardim->mostraJardim(jardineiro);
    return true;
}

// ========================================================

bool Simulador::comandoGrava(stringstream &ss)
{
    cout << "[INFO] Gravar estado nao implementado (sem persistencia nesta fase).\n";
    return true;
}

// ========================================================

bool Simulador::comandoRecupera(stringstream &ss)
{
    cout << "[INFO] Recuperar estado nao implementado (sem persistencia nesta fase).\n";
    return true;
}

// ========================================================

bool Simulador::comandoApaga(stringstream &ss)
{
    cout << "[INFO] Apagar copia nao implementado (sem persistencia nesta fase).\n";
    return true;
}

// ========================================================

bool Simulador::comandoExecuta(stringstream &ss)
{
    cout << "[INFO] Executar ficheiro de comandos nao implementado (I/O de ficheiros nao disponivel nesta fase).\n";
    return true;
}

// Não é suposto existir - necessário remover
/* bool Simulador::comandoEstado() const
{
    if (!jardimCriado)
    {
        cout << "[ERRO] E necessario criar o jardim antes de ver o seu estado.\n";
        return false;
    }
    jardim->mostrar();
    return true;
} */

// ========================================================
// ========================================================
// ========================================================

// Comandos para listar informação

// Lista todas as plantas
bool Simulador::comandoLplantas() {
    if (!isJardimCriado(jardimCriado))
        return false;

    cout << "\n";
    cout << string(60, '=') << "\n";
    cout << "       LISTAGEM DE TODAS AS PLANTAS NO JARDIM\n";
    cout << string(60, '=') << "\n\n";

    int contador = 0;

    for (int i = 0; i < jardim->getLinhas(); ++i) {
        for (int j = 0; j < jardim->getColunas(); ++j) {
            Solo* s = jardim->getSolo(i, j);
            if (s && s->temPlanta()) {
                contador++;

                // Posição
                cout << "[" << char('a' + i) << char('a' + j) << "] ";

                // Info da planta
                cout << s->getPlanta()->getInfo() << "\n";

                // Info do solo
                cout << "     Solo -> Agua: " << s->getAgua()
                     << " | Nutrientes: " << s->getNutrientes() << "\n\n";
            }
        }
    }

    cout << string(60, '=') << "\n";
    cout << "Total de plantas no jardim: " << contador << "\n";
    cout << string(60, '=') << "\n\n";

    return true;
}

// ========================================================

// Lista uma planta numa posição especifica
bool Simulador::comandoLplanta(stringstream &ss)
{
    if (!isJardimCriado(jardimCriado))
        return false;

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
    cout << "Solo - agua: " << s->getAgua() << ", nutrientes: " << s->getNutrientes() << "\n";
    return true;
}

// ========================================================

bool Simulador::comandoLarea()
{
    if (!isJardimCriado(jardimCriado))
        return false;

    // Mostrar toda a area com o estado actual
    jardim->mostraJardim(jardineiro);
    return true;
}

// ========================================================

bool Simulador::comandoLsolo(stringstream &ss)
{
    if (!isJardimCriado(jardimCriado))
        return false;

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

                cout << "Posicao " << pl << pc << " -> agua: " << s->getAgua()
                     << ", nutrientes: " << s->getNutrientes() << "\n";
            }
        }
    }

    return true;
}

// ========================================================

bool Simulador::comandoLferr() {
    if (!isJardimCriado(jardimCriado))
        return false;

    jardineiro.listarFerramentas();

    return true;
}

// ========================================================
// ========================================================
// ========================================================

// Comandos para ações

bool Simulador::comandoColhe(stringstream &ss) {
    if (!isJardimCriado(jardimCriado))
        return false;

    // VERIFICAR LIMITE
    if (!jardineiro.podeColher()) {
        cout << "[ERRO] >> Limite de colheitas atingido! ("
             << Settings::Jardineiro::max_colheitas << " por turno)\n";
        return false;
    }

    string pos;
    if (!(ss >> pos) || !isPosicaoValida(pos)) {
        cout << "[ERRO] Posicao invalida.\n";
        return false;
    }

    int l = pos[0] - 'a';
    int c = pos[1] - 'a';
    Solo* s = jardim->getSolo(l, c);

    if (!s) {
        cout << "[ERRO] Posicao fora do jardim.\n";
        return false;
    }
    if (!s->temPlanta()) {
        cout << "[ERRO] Nao existe planta nesta posicao.\n";
        return false;
    }

    Planta* p = s->removerPlanta();
    delete p;

    // GASTAR AÇÃO
    jardineiro.usarColheita();

    cout << "[INFO] >> Planta colhida em " << pos
         << ". Colheitas restantes: " << jardineiro.getColheitasRestantes() << "\n";

    jardim->mostraJardim(jardineiro);
    return true;
}

// ========================================================

bool Simulador::comandoPlanta(stringstream &ss) {
    if (!isJardimCriado(jardimCriado))
        return false;

    // VERIFICAR LIMITE
    if (!jardineiro.podePlantar()) {
        cout << "[ERRO] >> Limite de plantacoes atingido! ("
             << Settings::Jardineiro::max_plantacoes << " por turno)\n";
        return false;
    }

    string pos;
    char tipo;
    if (!(ss >> pos >> tipo) || !isPosicaoValida(pos)) {
        cout << "[ERRO] Uso: planta <l><c> <tipo> (ex: planta ab C).\n";
        return false;
    }

    tipo = static_cast<char>(toupper(static_cast<unsigned char>(tipo)));
    if (tipo != 'C' && tipo != 'R' && tipo != 'E' && tipo != 'X') {
        cout << "[ERRO] Tipo de planta invalido. Use C, R, E ou X.\n";
        return false;
    }

    int l = pos[0] - 'a';
    int c = pos[1] - 'a';

    Solo* s = jardim->getSolo(l, c);
    if (!s) {
        cout << "[ERRO] Posicao fora do jardim.\n";
        return false;
    }
    if (s->temPlanta()) {
        cout << "[ERRO] Ja existe uma planta nesta posicao.\n";
        return false;
    }

    // Criar planta
    Planta* nova = nullptr;
    switch(tipo) {
    case 'C': nova = new Cacto(); break;
    case 'R': nova = new Roseira(); break;
    case 'E': nova = new ErvaDaninha(); break;
    case 'X': nova = new PlantaExotica(); break;
    }

    s->setPlanta(nova);

    // GASTAR AÇÃO
    jardineiro.usarPlantacao();

    cout << "[INFO] >> Planta '" << tipo << "' adicionada em " << pos
         << ". Plantacoes restantes: " << jardineiro.getPlantacoesRestantes() << "\n";

    jardim->mostraJardim(jardineiro);
    return true;
}

// ========================================================

bool Simulador::comandoLarga() {
    if (!isJardimCriado(jardimCriado))
        return false;

    jardineiro.largarFerramenta();

    return true;
}

// ========================================================

bool Simulador::comandoPega(stringstream &ss) {
    if (!isJardimCriado(jardimCriado))
        return false;

    int numeroSerie;
    if (!(ss >> numeroSerie)) {
        cout << "[ERRO] Uso: pega <numero_de_serie>.\n";
        return false;
    }

    // Pegar ferramenta do inventário
    jardineiro.pegarFerramenta(numeroSerie);

    return true;
}

// ========================================================

bool Simulador::comandoCompra(stringstream &ss) {
    if (!isJardimCriado(jardimCriado))
        return false;

    char tipo;
    if (!(ss >> tipo)) {
        cout << "[ERRO] Uso: compra <tipo>. Tipos: g a t z.\n";
        return false;
    }

    // Criar ferramenta usando factory method
    Ferramenta* f = Ferramenta::criar(tipo);

    if (!f) {
        cout << "[ERRO] >> Tipo de ferramenta invalido. Use g, a, t ou z.\n";
        return false;
    }

    // Adicionar ao inventário do jardineiro
    jardineiro.adicionarFerramenta(f);

    return true;
}

// ========================================================
// ========================================================
// ========================================================

// Comandos para controlar o jardineiro

bool Simulador::comandoE() {
    if (!isJardimCriado(jardimCriado))
        return false;
    else if (!isJardineiroCriado(jardineiroCriado))
        return false;

    // VERIFICAR LIMITE
    if (!jardineiro.podeMovimentar()) {
        cout << "[ERRO] >> Limite de movimentos atingido! ("
             << Settings::Jardineiro::max_movimentos << " por turno)\n";
        return false;
    }

    int l = jardineiro.getLinha();
    int c = jardineiro.getColuna();
    if (!jardim->getSolo(l, c - 1)) {
        cout << "[ERRO] >> Movimento invalido (fora dos limites).\n";
        return false;
    }

    jardineiro.moveNoJardim(l, c - 1);

    // GASTAR AÇÃO
    jardineiro.usarMovimento();

    cout << "[INFO] >> o Jardineiro deslocou-se para a ESQUERDA. "
         << "Movimentos restantes: " << jardineiro.getMovimentosRestantes() << "\n";

    jardim->mostraJardim(jardineiro);
    return true;
}

// ========================================================

bool Simulador::comandoD()
{
    if (!isJardimCriado(jardimCriado))
        return false;
    else if (!isJardineiroCriado(jardineiroCriado))
        return false;

    // VERIFICAR LIMITE
    if (!jardineiro.podeMovimentar()) {
        cout << "[ERRO] >> Limite de movimentos atingido! ("
             << Settings::Jardineiro::max_movimentos << " por turno)\n";
        return false;
    }

    int l = jardineiro.getLinha();
    int c = jardineiro.getColuna();
    if (!jardim->getSolo(l, c + 1)) {
        cout << "[ERRO] >> Movimento invalido (fora dos limites).\n";
        return false;
    }

    jardineiro.moveNoJardim(l, c + 1);

    // GASTAR AÇÃO
    jardineiro.usarMovimento();

    cout << "[INFO] >> o Jardineiro deslocou-se para a DIREITA. "
         << "Movimentos restantes: " << jardineiro.getMovimentosRestantes() << "\n";

    jardim->mostraJardim(jardineiro);
    return true;
}

// ========================================================

bool Simulador::comandoC()
{
    if (!isJardimCriado(jardimCriado))
        return false;
    else if (!isJardineiroCriado(jardineiroCriado))
        return false;

    // VERIFICAR LIMITE
    if (!jardineiro.podeMovimentar()) {
        cout << "[ERRO] >> Limite de movimentos atingido! ("
             << Settings::Jardineiro::max_movimentos << " por turno)\n";
        return false;
    }

    int l = jardineiro.getLinha();
    int c = jardineiro.getColuna();
    if (!jardim->getSolo(l- 1, c)) {
        cout << "[ERRO] >> Movimento invalido (fora dos limites).\n";
        return false;
    }

    jardineiro.moveNoJardim(l -1, c);

    // GASTAR AÇÃO
    jardineiro.usarMovimento();

    cout << "[INFO] >> o Jardineiro deslocou-se para CIMA. "
         << "Movimentos restantes: " << jardineiro.getMovimentosRestantes() << "\n";

    jardim->mostraJardim(jardineiro);
    return true;
}

// ========================================================

bool Simulador::comandoB()
{
    if (!isJardimCriado(jardimCriado))
        return false;
    else if (!isJardineiroCriado(jardineiroCriado))
        return false;

    // VERIFICAR LIMITE
    if (!jardineiro.podeMovimentar()) {
        cout << "[ERRO] >> Limite de movimentos atingido! ("
             << Settings::Jardineiro::max_movimentos << " por turno)\n";
        return false;
    }

    int l = jardineiro.getLinha();
    int c = jardineiro.getColuna();
    if (!jardim->getSolo(l + 1, c)) {
        cout << "[ERRO] >> Movimento invalido (fora dos limites).\n";
        return false;
    }

    jardineiro.moveNoJardim(l + 1, c);

    // GASTAR AÇÃO
    jardineiro.usarMovimento();

    cout << "[INFO] >> o Jardineiro deslocou-se para BAIXO. "
         << "Movimentos restantes: " << jardineiro.getMovimentosRestantes() << "\n";

    jardim->mostraJardim(jardineiro);
    return true;
}

// ========================================================

bool Simulador::comandoEntra(stringstream &ss) {
    if (!isJardimCriado(jardimCriado))
        return false;
    else if (jardineiroCriado) {
        cout << "[ERRO] >> O Jardineiro ja esta no jardim.\n";
        return false;
    }

    if (!jardineiro.podeEntrarSair()) {
        cout << "[ERRO] >> Limite de entradas/saidas atingido! ("
             << Settings::Jardineiro::max_entradas_saidas << " por turno)\n";
        return false;
    }

    string pos;
    if (!(ss >> pos) || !isPosicaoValida(pos)) {
        cout << "[ERRO] Posicao invalida. Use duas letras minusculas.\n";
        return false;
    }

    int l = pos[0] - 'a';
    int c = pos[1] - 'a';

    Solo* s = jardim->getSolo(l, c);
    if (!s) {
        cout << "[ERRO] Posicao fora do jardim.\n";
        return false;
    }

    jardineiroCriado = true;
    jardineiro.entraNoJardim(l, c);
    jardineiro.usarEntradaSaida();

    // ✅ APANHAR FERRAMENTA + CRIAR NOVA "POR MAGIA"
    if (s->temFerramenta()) {
        Ferramenta* f = s->removerFerramenta();
        jardineiro.adicionarFerramenta(f);
        jardim->criarFerramentaAleatoria();  // ✅ MAGIA!
        cout << "[INFO] >> Apanhou " << f->nome() << " #"
             << f->getNumeroSerie() << " do chao!\n";

        // ✅ CRIAR NOVA FERRAMENTA ALEATÓRIA (ENUNCIADO)
        cout << "[INFO] >> Uma nova ferramenta apareceu noutro local...\n";
        // jardim->criarFerramentaAleatoria();  // Se for público
    }

    cout << "[INFO] >> O Jardineiro entrou na posicao " << pos << ".\n";
    jardim->mostraJardim(jardineiro);

    return true;
}

// ========================================================

bool Simulador::comandoSai() {
    if (!isJardimCriado(jardimCriado))
        return false;
    else if (!isJardineiroCriado(jardineiroCriado))
        return false;

    // VERIFICAR LIMITE
    if (!jardineiro.podeEntrarSair()) {
        cout << "[ERRO] >> Limite de entradas/saidas atingido! ("
             << Settings::Jardineiro::max_entradas_saidas << " por turno)\n";
        return false;
    }

    jardineiroCriado = false;
    jardineiro.saiDoJardim();

    // GASTAR AÇÃO
    jardineiro.usarEntradaSaida();

    cout << "[INFO] >> o Jardineiro SAIU do Jardim.\n";
    jardim->mostraJardim(jardineiro);
    return true;
}