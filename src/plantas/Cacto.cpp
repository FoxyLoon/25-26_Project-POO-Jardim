#include "Cacto.h"

/*
CACTO
Beleza: NEUTRA

Comportamento:
- Absorve 25% da água do solo a cada instante
- Absorve até 5 unidades de nutrientes
- Morre se água do solo > 100 por 3 instantes seguidos
- Morre se nutrientes do solo = 0 por mais de 3 instantes seguidos
- Ao morrer: devolve TODOS os nutrientes absorvidos durante a vida
- Multiplica-se se nutrientes > 100 e água > 50
*/

Cacto::Cacto() : Planta(20, 20, 'c', "NEUTRA"), instantesAguaExcessiva(0), instantesSemNutrientes(0) {}

// ========================================================

// Informação da Planta
string Cacto::getInfo() const
{
    int agua = getAguaInterna();
    int nutrientes = getNutrientesInternos();

    ostringstream oss;
    oss << "[Cacto] " << "\n";
    oss << "Água: " << agua << "\n";
    oss << "Nutrientes: " << nutrientes << "\n";
    oss << "Idade (Instantes): " << idade << "\n";
    oss << "Instantes Água Excessiva: " << instantesAguaExcessiva << "\n";
    oss << "Instantes Sem Nutrientes: " << instantesSemNutrientes << "\n";

    string informacao = oss.str();
    return informacao;
}

// ========================================================

// Processamento de cada instante

void Cacto::removeRecursosSolo(Solo &s)
{
    // Obtem o valor de água do solo para calcular a percentagem a remover
    int aguaNoSolo = s.getAgua();
    int percentagem = Settings::Cacto::absorcao_agua_percentagem;

    int qtdAguaParaRemover = (aguaNoSolo * percentagem) / 100;
    int qtdNutrientesParaRemover = Settings::Cacto::absorcao_nutrientes;

    obterAgua(s, qtdAguaParaRemover);
    obterNutrientes(s, qtdNutrientesParaRemover);
}

void Cacto::adicionaRecursosPlanta(Solo &s)
{
    // Obtem o valor de água do solo para calcular a percentagem a adicionar
    int aguaNoSolo = s.getAgua();
    int percentagem = Settings::Cacto::absorcao_agua_percentagem;

    // Cálculo realizado antes
    int qtdAguaParaAdicionar = (aguaNoSolo * percentagem) / 100;
    int qtdNutrientesParaAdicionar = Settings::Cacto::absorcao_nutrientes;

    adicionarAguaInterna(qtdAguaParaAdicionar);
    adicionarNutrientesInternos(qtdNutrientesParaAdicionar);
}

void Cacto::envelhecimento()
{
    idade++;
}

void Cacto::removeRecursosPlanta()
{
    // O Cacto não perde recursos
}

void Cacto::adicionaRecursosSolo(Solo &s)
{
    // O Cacto não fornece recursos ao solo enquanto está vivo
}

// ========================================================

// Condições de Multiplicação

bool Cacto::podeMultiplicar() const
{
    // Condição: Houver nutrientes e água suficientes
    int nutrientesAtual = getNutrientesInternos();
    int aguaAtual = getAguaInterna();

    int limiteNutrientes = Settings::Cacto::multiplica_nutrientes_maior;
    int limiteAgua = Settings::Cacto::multiplica_agua_maior;

    bool temNutrientes = (nutrientesAtual > limiteNutrientes);
    bool temAgua = (aguaAtual > limiteAgua);

    bool resultado = (temNutrientes && temAgua);
    return resultado;
}

Planta *Cacto::gerarSemente()
{
    int aguaPlantaOriginal = getAguaInterna();
    int nutrientesPlantaOriginal = getNutrientesInternos();

    // Cálculo dos valores para a nova planta
    int aguaSemente = aguaPlantaOriginal / 2;
    int nutrientesSemente = nutrientesPlantaOriginal / 2;

    // Atualiza a planta original
    setAguaInterna(aguaSemente);
    setNutrientesInternos(nutrientesSemente);

    // Cria a nova planta
    // Nota: Como a Planta Original e Semente terâo os mesmos valores,
    // a água e nutrientes vão ser uma copia da Planta original após o calculo
    Planta *semente = new Cacto();
    return semente;
}

// ========================================================

// Condições de Morte

bool Cacto::verificaMorte(const Solo &s)
{
    int aguaSolo = s.getAgua();
    int nutriSolo = s.getNutrientes();

    int limiteAguaSolo = Settings::Cacto::morre_agua_solo_maior;
    int limiteNutriSolo = Settings::Cacto::morre_nutrientes_solo_menor;

    int maxInstantesAgua = Settings::Cacto::morre_agua_solo_instantes;
    int maxInstantesNutri = Settings::Cacto::morre_nutrientes_solo_instantes;

    // Verifica se tem Água em Excesso
    if (aguaSolo > limiteAguaSolo)
    {
        instantesAguaExcessiva++;
    }
    else
    {
        instantesAguaExcessiva = 0;
    }

    // Verifica se faltam Nutrientes
    if (nutriSolo <= limiteNutriSolo)
    {
        instantesSemNutrientes++;
    }
    else
    {
        instantesSemNutrientes = 0;
    }

    bool morreuPorAgua = (instantesAguaExcessiva >= maxInstantesAgua);
    bool morreuPorNutri = (instantesSemNutrientes > maxInstantesNutri);
    bool morreuPorSede = (getAguaInterna() <= 0);

    // Basta uma condição para morrer
    bool resultadoMorte = (morreuPorAgua || morreuPorNutri || morreuPorSede);
    return resultadoMorte;
}

void Cacto::aoMorrer(Solo &s)
{
    int nutrientesParaDevolver = getNutrientesInternos();

    // Devolve os nutrientes acumulados ao solo
    depositarNutrientes(s, nutrientesParaDevolver);
}