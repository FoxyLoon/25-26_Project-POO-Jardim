#include "ErvaDaninha.h"

/*
ERVA DANINHA
Beleza: FEIA

Comportamento:
- Absorve recursos fixos do solo a cada instante.
- Não tem perda metabólica (não morre por falta de recursos).
- Morre apenas por idade (instantes de vida).
- Multiplica-se por tempo e recursos.
*/

ErvaDaninha::ErvaDaninha() : Planta("Erva Daninha", Settings::ErvaDaninha::inicial_agua, Settings::ErvaDaninha::inicial_nutrientes, 'e', "FEIA"), idade(0), instantesDesdeUltimaMultiplicacao(0) {}

// ========================================================

// Informação da Planta
string ErvaDaninha::getInfoPlanta() const
{
    ostringstream oss;
    oss << "\t[" << getNomePlanta() << "]"
        << " | Simbolo: " << getSimboloPlanta()
        << " | Beleza: " << getBelezaPlanta()
        << " | Água: " << getAguaInterna()
        << " | Nutrientes: " << getNutrientesInternos()
        << " | Idade (Instantes): " << idade << "\n"
        << "\t\tInstantes desde ultima multiplicacao: " << instantesDesdeUltimaMultiplicacao << endl;

    string informacao = oss.str();
    return informacao;
}

// ========================================================

// Processamento de cada instante

void ErvaDaninha::removeRecursosSolo(Solo &s)
{
    int qtdAguaParaRemover = Settings::ErvaDaninha::absorcao_agua;
    int qtdNutrientesParaRemover = Settings::ErvaDaninha::absorcao_nutrientes;

    obterAgua(s, qtdAguaParaRemover);
    obterNutrientes(s, qtdNutrientesParaRemover);
}

void ErvaDaninha::adicionaRecursosPlanta(Solo &s)
{
    int qtdAguaParaAdicionar = Settings::ErvaDaninha::absorcao_agua;
    int qtdNutrientesParaAdicionar = Settings::ErvaDaninha::absorcao_nutrientes;

    adicionarAguaInterna(qtdAguaParaAdicionar);
    adicionarNutrientesInternos(qtdNutrientesParaAdicionar);
}

void ErvaDaninha::envelhecimento()
{
    idade++;
    instantesDesdeUltimaMultiplicacao++;
}

void ErvaDaninha::removeRecursosPlanta()
{
    // A erva daninha não perde recursos
}

void ErvaDaninha::adicionaRecursosSolo(Solo &s)
{
    // A Erva Daninha não fornece recursos ao solo enquanto está viva
}

// ========================================================

// Condições de Multiplicação

bool ErvaDaninha::podeMultiplicar() const
{
    // Condição: Houver nutrientes suficientes e passar o tempo necessário
    int nutrientesAtual = getNutrientesInternos();
    int limiteNutrientes = Settings::ErvaDaninha::multiplica_nutrientes_maior;
    int tempoNecessario = Settings::ErvaDaninha::multiplica_instantes;

    bool temNutrientes = (nutrientesAtual > limiteNutrientes);
    bool passouTempo = (instantesDesdeUltimaMultiplicacao >= tempoNecessario);

    bool resultado = (temNutrientes && passouTempo);
    return resultado;
}

Planta *ErvaDaninha::gerarSemente()
{
    // Reinicia o contador do tempo de multiplicação
    instantesDesdeUltimaMultiplicacao = 0;

    // Cria a nova planta
    // Nota 1: Usa os valores iniciais do Settings.h no construtor padrão
    // Nota 2: A planta original não perder nada
    Planta *semente = new ErvaDaninha();
    return semente;
}

// ========================================================

// Condições de Morte

bool ErvaDaninha::verificaMorte(const Solo &s)
{
    int limiteIdade = Settings::ErvaDaninha::morre_instantes;

    // Verifica Condição
    bool morreuPorVelhice = (idade >= limiteIdade);
    return morreuPorVelhice;
}

void ErvaDaninha::aoMorrer(Solo &s)
{
    // A Erva Daninha não deposita recursos ao solo após morte
}