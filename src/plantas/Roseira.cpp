#include "Roseira.h"

/*
ROSEIRA
Beleza: BONITA

Comportamento:
- Absorve valores fixos de água e nutrientes do solo
- Tem perda metabólica constante (respiração/transpiração)
- Morre se tiver pouca água, poucos nutrientes ou excesso de nutrientes
- Ao morrer: devolve metade dos seus recursos ao solo
- Multiplicação baseada em nutrientes
*/

Roseira::Roseira() : Planta("Roseira", Settings::Roseira::inicial_agua, Settings::Roseira::inicial_nutrientes, 'r', "BONITA"), idade(0) {}

// ========================================================

// Informação da Planta
string Roseira::getInfoPlanta() const
{
    ostringstream oss;
    oss << "\t[" << getNomePlanta() << "]"
        << " | Simbolo: " << getSimboloPlanta()
        << " | Beleza: " << getBelezaPlanta()
        << " | Água: " << getAguaInterna()
        << " | Nutrientes: " << getNutrientesInternos()
        << " | Idade (Instantes): " << idade << endl;

    string informacao = oss.str();
    return informacao;
}

// ========================================================

// Processamento de cada instante

void Roseira::removeRecursosSolo(Solo &s)
{
    int qtdAguaParaRemover = Settings::Roseira::absorcao_agua;
    int qtdNutrientesParaRemover = Settings::Roseira::absorcao_nutrientes;

    obterAgua(s, qtdAguaParaRemover);
    obterNutrientes(s, qtdNutrientesParaRemover);
}

void Roseira::adicionaRecursosPlanta(Solo &s)
{
    int qtdAguaParaAdicionar = Settings::Roseira::absorcao_agua;
    int qtdNutrientesParaAdicionar = Settings::Roseira::absorcao_nutrientes;

    adicionarAguaInterna(qtdAguaParaAdicionar);
    adicionarNutrientesInternos(qtdNutrientesParaAdicionar);
}

void Roseira::envelhecimento()
{
    idade++;
}

void Roseira::removeRecursosPlanta()
{
    int qtdAguaParaRemover = Settings::Roseira::perda_agua;
    int qtdNutrientesParaRemover = Settings::Roseira::perda_nutrientes;

    removerAguaInterna(qtdAguaParaRemover);
    removerNutrientesInternos(qtdNutrientesParaRemover);
}

void Roseira::adicionaRecursosSolo(Solo &s)
{
    // A Roseira não fornece recursos ao solo enquanto está viva
}

// ========================================================

// Condições de Multiplicação

bool Roseira::podeMultiplicar() const
{
    // Condição: Houver nutrientes suficientes
    int nutrientesAtual = getNutrientesInternos();
    int limiteNutrientes = Settings::Roseira::multiplica_nutrientes_maior;

    bool resultado = (nutrientesAtual > limiteNutrientes);
    return resultado;
}

Planta *Roseira::gerarSemente()
{
    int aguaPlantaOriginal = getAguaInterna();
    int nutrientesPlantaOriginal = Settings::Roseira::original_nutrientes;

    int percentagem_AguaSemente = Settings::Roseira::nova_agua_percentagem;
    int nutrientesSemente = Settings::Roseira::nova_nutrientes;

    // ================================================

    // ==== Planta Original ====

    // A Planta Original perde metade da água e reinicia os nutrientes
    int novaAguaPlantaOriginal = aguaPlantaOriginal / 2;

    // Atualiza a planta original
    setAguaInterna(novaAguaPlantaOriginal);
    setNutrientesInternos(nutrientesPlantaOriginal);

    // ================================================

    // ==== Nova Planta ====

    // Cálculo da água para a nova planta
    int aguaSemente = (aguaPlantaOriginal * percentagem_AguaSemente) / 100;

    // ================================================

    // Cria a nova planta
    Planta *semente = new Roseira();

    // Define os novos valores da nova planta após a criação
    semente->setAguaInterna(aguaSemente);
    semente->setNutrientesInternos(nutrientesSemente);

    return semente;
}

// ========================================================

// Condições de Morte

bool Roseira::verificaMorte(const Solo &s)
{
    int aguaInterna = getAguaInterna();
    int nutrientesInternos = getNutrientesInternos();

    int minAgua = Settings::Roseira::morre_agua_menor;
    int minNutrientes = Settings::Roseira::morre_nutrientes_menor;
    int maxNutrientes = Settings::Roseira::morre_nutrientes_maior;

    // Verifica Condições
    bool faltaAgua = (aguaInterna <= minAgua);
    bool faltaNutrientes = (nutrientesInternos <= minNutrientes);
    bool excessoNutrientes = (nutrientesInternos >= maxNutrientes);

    // Basta uma condição para morrer
    bool resultadoMorte = (faltaAgua || faltaNutrientes || excessoNutrientes);
    return resultadoMorte;
}

void Roseira::aoMorrer(Solo &s)
{
    int aguaParaDevolver = getAguaInterna() / 2;
    int nutrientesParaDevolver = getNutrientesInternos() / 2;

    depositarAgua(s, aguaParaDevolver);
    depositarNutrientes(s, nutrientesParaDevolver);
}