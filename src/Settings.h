#ifndef SETTINGS_H
#define SETTINGS_H

/**
 * Classe Settings - Centraliza todas as configurações do simulador
 *
 * IMPORTANTE: Estes valores podem ser alterados para testes,
 * mas devem ser repostos na versão final de entrega.
 */
class Settings
{
public:
    // ========================================================
    // JARDIM
    // ========================================================
    class Jardim
    {
    public:
        static constexpr int agua_min = 80;
        static constexpr int agua_max = 100;
        static constexpr int nutrientes_min = 40;
        static constexpr int nutrientes_max = 50;
        static constexpr int probabilidade_planta = 10;     // em %
        static constexpr int probabilidade_ferramenta = 10; // em %
    };

    // ========================================================
    // JARDINEIRO
    // ========================================================
    class Jardineiro
    {
    public:
        static constexpr int max_movimentos = 10;
        static constexpr int max_entradas_saidas = 1;
        static constexpr int max_plantacoes = 2;
        static constexpr int max_colheitas = 5;
    };

    // ========================================================
    // FERRAMENTAS
    // ========================================================
    class Regador
    {
    public:
        static constexpr int capacidade = 200;
        static constexpr int dose = 10;
    };

    class Adubo
    {
    public:
        static constexpr int capacidade = 100;
        static constexpr int dose = 10;
    };

    class FerramentaZ
    {
    public:
        static constexpr int capacidade = 50;
        static constexpr int otimo_agua = 90;
        static constexpr int otimo_nutrientes = 45;
        static constexpr int max_ajuste_agua = 15;
        static constexpr int max_ajuste_nutrientes = 10;
    };

    // ========================================================
    // PLANTAS
    // ========================================================

    class Cacto
    {
    public:
        static constexpr int absorcao_agua_percentagem = 25; // 25% da água do solo
        static constexpr int absorcao_nutrientes = 5;

        // Condições de morte
        static constexpr int morre_agua_solo_maior = 100;
        static constexpr int morre_agua_solo_instantes = 3;
        static constexpr int morre_nutrientes_solo_menor = 1;
        static constexpr int morre_nutrientes_solo_instantes = 3;

        // Multiplicação
        static constexpr int multiplica_nutrientes_maior = 100;
        static constexpr int multiplica_agua_maior = 50;
    };

    class Roseira
    {
    public:
        static constexpr int inicial_agua = 25;
        static constexpr int inicial_nutrientes = 25;

        // Metabolismo
        static constexpr int perda_agua = 4;
        static constexpr int perda_nutrientes = 4;
        static constexpr int absorcao_agua = 5;
        static constexpr int absorcao_nutrientes = 8;

        // Condições de morte
        static constexpr int morre_agua_menor = 1;
        static constexpr int morre_nutrientes_menor = 1;
        static constexpr int morre_nutrientes_maior = 199; // Morre se >= 200

        // Multiplicação
        static constexpr int multiplica_nutrientes_maior = 100;
        static constexpr int nova_nutrientes = 25;
        static constexpr int nova_agua_percentagem = 50; // 50% da água da mãe
        static constexpr int original_nutrientes = 100;
        static constexpr int original_agua_percentagem = 50; // 50% da água original
    };

    class ErvaDaninha
    {
    public:
        static constexpr int inicial_agua = 5;
        static constexpr int inicial_nutrientes = 5;

        // Absorção
        static constexpr int absorcao_agua = 1;
        static constexpr int absorcao_nutrientes = 1;

        // Morte
        static constexpr int morre_instantes = 60;

        // Multiplicação
        static constexpr int multiplica_nutrientes_maior = 30;
        static constexpr int multiplica_instantes = 5;
        static constexpr int nova_nutrientes = 5;
        static constexpr int original_nutrientes = 5;
    };

    class PlantaExotica
    {
    public:
        // Valores iniciais
        static constexpr int inicial_agua = 30;
        static constexpr int inicial_nutrientes = 30;

        // Fases de crescimento
        static constexpr int fim_jovem = 20;  // 0-20: JOVEM
        static constexpr int fim_adulta = 40; // 21-40: ADULTA (dormência)
                                          // 41+: MADURA (produção)

        // Absorção (fases JOVEM e MADURA)
        static constexpr int jovem_abs_agua = 3;
        static constexpr int jovem_abs_nutrientes = 2;

        // Metabolismo (todas as fases)
        static constexpr int madura_perda_agua = 2;
        static constexpr int madura_perda_nutrientes = 1;

        // Produção (fase MADURA)
        static constexpr int madura_prod_nutrientes_solo = 2;

        // Morte
        static constexpr int morre_agua_menor = 5;
        static constexpr int morre_nutrientes_menor = 3;
        static constexpr int tempo_vida_max = 80;
        static constexpr int percentagem_recursos_pos_morte = 75; // Devolve 75%

        // Multiplicação
        static constexpr int multiplica_nutrientes_maior = 70;
        static constexpr int multiplica_agua_maior = 60;
        static constexpr int nova_agua = 30;
        static constexpr int nova_nutrientes = 30;
    };
};

#endif