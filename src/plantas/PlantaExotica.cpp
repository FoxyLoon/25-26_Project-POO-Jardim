#include "PlantaExotica.h"

/*
PLANTA EXÓTICA (x) - BAMBU LUNAR
Beleza: BONITA

Comportamento por Fases:
- Jovem (0-20): Absorve 3 água e 2 nutrientes.
- Adulta (21-40): Dormência (não absorve nem produz).
- Madura (41+): Produz 2 nutrientes para o solo, perde 2 água e 1 nutriente internos.

Morte:
- Água interna < 5 ou Nutrientes internos < 3.
- Idade >= 80 instantes.
- Ao morrer: Devolve 75% dos recursos ao solo.
*/

PlantaExotica::PlantaExotica() : Planta(Settings::PlantaExotica::inicial_agua, Settings::PlantaExotica::inicial_nutrientes, 'x', "BONITA"), idade(0) {}

// ========================================================

// Informação da Planta
string PlantaExotica::getInfo() const
{
    int agua = getAguaInterna();
    int nutri = getNutrientesInternos();
    char simbolo = getSimbolo();
    string beleza = getBeleza();

    ostringstream oss;
    oss << "[Planta Exótica] " << "\n";
    oss << "Simbolo: " << simbolo << "\n";
    oss << "Beleza: " << beleza << "\n";
    oss << "Água: " << agua << "\n";
    oss << "Nutrientes: " << nutri << "\n";
    oss << "Idade (Instantes): " << idade << "\n";

    // Identificação da fase atual de acordo com a idade
    if (idade <= Settings::PlantaExotica::fim_jovem)
        oss << "Fase: JOVEM" << "\n";
    else if (idade <= Settings::PlantaExotica::fim_adulta)
        oss << "Fase: ADULTA" << "\n";
    else
        oss << "Fase: MADURA" << "\n";

    string informacao = oss.str();
    return informacao;
}

// ========================================================

// Processamento de cada instante

void PlantaExotica::removeRecursosSolo(Solo &s)
{
    // Apenas ganha recursos na Fase JOVEM
    if (idade <= Settings::PlantaExotica::fim_jovem)
    {
        int qtdAguaParaRemover = Settings::PlantaExotica::jovem_abs_agua;
        int qtdNutrientesParaRemover = Settings::PlantaExotica::jovem_abs_nutrientes;

        obterAgua(s, qtdAguaParaRemover);
        obterNutrientes(s, qtdNutrientesParaRemover);
    }
}

void PlantaExotica::adicionaRecursosPlanta(Solo &s)
{
    // Apenas ganha recursos na Fase JOVEM
    if (idade <= Settings::PlantaExotica::fim_jovem)
    {
        int qtdAguaParaAdicionar = Settings::PlantaExotica::jovem_abs_agua;
        int qtdNutrientesParaAdicionar = Settings::PlantaExotica::jovem_abs_nutrientes;

        adicionarAguaInterna(qtdAguaParaAdicionar);
        adicionarNutrientesInternos(qtdNutrientesParaAdicionar);
    }
}

void PlantaExotica::envelhecimento()
{
    idade++;
}

void PlantaExotica::removeRecursosPlanta()
{

    // Apenas perde recursos na Fase MADURA
    if (idade > Settings::PlantaExotica::fim_adulta)
    {
        int qtdAguaParaRemover = Settings::PlantaExotica::madura_perda_agua;
        int qtdNutrientesParaRemover = Settings::PlantaExotica::madura_perda_nutrientes;

        removerAguaInterna(qtdAguaParaRemover);
        removerNutrientesInternos(qtdNutrientesParaRemover);
    }
}

void PlantaExotica::adicionaRecursosSolo(Solo &s)
{
    // Apenas produz para o solo na Fase Madura
    if (idade > Settings::PlantaExotica::fim_adulta)
    {
        int nutrientesProduzidos = Settings::PlantaExotica::madura_prod_nutrientes_solo;
        depositarNutrientes(s, nutrientesProduzidos);
    }
}

// ========================================================

// Condições de Multiplicação

bool PlantaExotica::podeMultiplicar() const
{
    // Condição: Houver nutrientes e agua suficientes
    int aguaAtual = getAguaInterna();
    int nutrientesAtual = getNutrientesInternos();

    int limiteAgua = Settings::PlantaExotica::multiplica_agua_maior;
    int limiteNutrientes = Settings::PlantaExotica::multiplica_nutrientes_maior;

    // Importante: A verificação das posições diagonais livres será verificada no Jardim
    bool temRecursos = (aguaAtual > limiteAgua && nutrientesAtual > limiteNutrientes);
    return temRecursos;
}

Planta *PlantaExotica::gerarSemente()
{
    int aguaPlantaOriginal = getAguaInterna();
    int nutrientesPlantaOriginal = getNutrientesInternos();

    // ================================================

    // ==== Planta Original ====

    // Planta Original fica com metade da agua e nutrientes
    int novaAguaPlantaOriginal = aguaPlantaOriginal / 2;
    int novosNutrientesPlantaOriginal = nutrientesPlantaOriginal / 2;

    setAguaInterna(novaAguaPlantaOriginal);
    setNutrientesInternos(novosNutrientesPlantaOriginal);

    // ================================================

    // ==== Nova Planta ====

    int aguaSemente = Settings::PlantaExotica::nova_agua;
    int nutrientesSemente = Settings::PlantaExotica::nova_nutrientes;

    // ================================================

    // Cria a nova planta
    Planta *semente = new PlantaExotica();

    // Define os novos valores da nova planta após a criação
    semente->setAguaInterna(aguaSemente);
    semente->setNutrientesInternos(nutrientesSemente);

    return semente;
}

// ========================================================

// Condições de Morte

bool PlantaExotica::verificaMorte(const Solo &s)
{
    int aguaInterna = getAguaInterna();
    int nutrientesInternos = getNutrientesInternos();

    int minAgua = Settings::PlantaExotica::morre_agua_menor;
    int minNutrientes = Settings::PlantaExotica::morre_nutrientes_menor;
    int tempoVidaMax = Settings::PlantaExotica::tempo_vida_max;

    // Verifica Condições
    bool faltaAgua = (aguaInterna < minAgua);
    bool faltaNutrientes = (nutrientesInternos < minNutrientes);
    bool morreuVelhice = (idade >= tempoVidaMax);

    // Basta uma condição para morrer
    bool resultado = (faltaAgua || faltaNutrientes || morreuVelhice);
    return resultado;
}

void PlantaExotica::aoMorrer(Solo &s)
{
    int aguaInterna = getAguaInterna();
    int nutrientesInternos = getNutrientesInternos();
    int percentagem = Settings::PlantaExotica::percentagem_recursos_pos_morte;

    // Cálculo a depositar de acordo com a percentagem
    int aguaParaDevolver = (aguaInterna * percentagem) / 100;
    int nutrientesParaDevolver = (nutrientesInternos * percentagem) / 100;

    depositarAgua(s, aguaParaDevolver);
    depositarNutrientes(s, nutrientesParaDevolver);
}