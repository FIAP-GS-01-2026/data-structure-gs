/* =============================================================
 *  MISSION CONTROL AI
 *  Monitoramento de missao espacial - Global Solution 2026 (FIAP)
 *
 *  Conceitos: condicionais, repeticao, vetores e funcoes.
 *  Regras de alerta:
 *    Temperatura > 80 -> Alerta de superaquecimento
 *    Energia < 20 -> Economia de energia
 *    Comunicacao = 0 -> Falha de comunicacao
 *
 *  Opcionais implementados:
 *    - Historico das leituras (vetor)
 *    - Simulacao continua dos sensores (opcao 4)
 *    - Animacoes simples (spinner, barra, delays)
 * ============================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Delay em milissegundos 
#include <windows.h>
#define DORMIR_MS(ms) Sleep(ms)

#define MAX_LEITURAS 100

// Estrutura para leitura de telemetria
typedef struct
{
    float temperatura; // C
    float energia;     // % de 0 a 100
    int comunicacao;   // 0 = falha, 1 = ok
} Leitura;

// ---------- Prototipos ----------
void limparBuffer(void);
Leitura lerDados(void);
Leitura gerarLeituraAleatoria(void);
void exibirStatus(Leitura l);
void analisarAlertas(Leitura l);
void exibirHistorico(Leitura historico[], int total);
void simularSensores(Leitura historico[], int *total);
void animacaoSpinner(const char *msg, int ciclos);
void animacaoBarra(const char *msg, int ciclos);

/* =============================================================
 *  MAIN
 * ============================================================= */
int main(void)
{
    Leitura historico[MAX_LEITURAS];
    int total = 0;
    int opcao;

    srand((unsigned int)time(NULL));

    do
    {
        printf("\n==============================\n");
        printf("     MISSION CONTROL AI\n");
        printf("==============================\n");
        printf("1 - Inserir dados\n");
        printf("2 - Visualizar status\n");
        printf("3 - Executar analise\n");
        printf("4 - Simulacao continua dos sensores\n");
        printf("5 - Encerrar sistema\n");
        printf("------------------------------\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1)
        {
            limparBuffer();
            opcao = -1;
        }

        switch (opcao)
        {
        case 1:
            if (total >= MAX_LEITURAS)
            {
                printf("\n>> Historico cheio (%d leituras).\n", MAX_LEITURAS);
            }
            else
            {
                historico[total] = lerDados();
                total++;
                printf("\n>> Leitura %d registrada.\n", total);
            }
            break;

        case 2:
            if (total == 0)
            {
                printf("\n>> Nenhuma leitura registrada. Use a opcao 1.\n");
            }
            else
            {
                exibirStatus(historico[total - 1]);
            }
            break;

        case 3:
            if (total == 0)
            {
                printf("\n>> Nenhuma leitura para analisar.\n");
            }
            else
            {
                animacaoSpinner("Processando analise", 12);
                exibirHistorico(historico, total);
                printf("\n--- Analise da ultima leitura ---\n");
                analisarAlertas(historico[total - 1]);
            }
            break;

        case 4:
            simularSensores(historico, &total);
            break;

        case 5:
            printf("\nEncerrando Mission Control AI. Boa missao!\n");
            break;

        default:
            printf("\n>> Opcao invalida. Escolha entre 1 e 5.\n");
        }
    } while (opcao != 5);

    return 0;
}

/* =============================================================
 *  FUNCOES
 * ============================================================= */

// Descarta caracteres ate o fim da linha para evitar travar o menu.
void limparBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

// Le temperatura, energia e status de comunicacao do usuario.
Leitura lerDados(void)
{
    Leitura l;

    printf("\n-- Inserir dados --\n");

    printf("Temperatura (C): ");
    while (scanf("%f", &l.temperatura) != 1)
    {
        printf(">> Valor invalido. Digite um numero: ");
        limparBuffer();
    }

    printf("Energia (%% de 0 a 100): ");
    while (scanf("%f", &l.energia) != 1 || l.energia < 0.0f || l.energia > 100.0f)
    {
        printf(">> Valor invalido. Digite entre 0 e 100: ");
        limparBuffer();
    }

    printf("Comunicacao (0 = falha, 1 = ok): ");
    while (scanf("%d", &l.comunicacao) != 1 || (l.comunicacao != 0 && l.comunicacao != 1))
    {
        printf(">> Valor invalido. Digite 0 ou 1: ");
        limparBuffer();
    }

    return l;
}

// Gera valores aleatorios em faixas que produzem casos normais e criticos.
Leitura gerarLeituraAleatoria(void)
{
    Leitura l;
    l.temperatura = -10.0f + (float)(rand() % 1200) / 10.0f; // -10.0 a 109.9
    l.energia = (float)(rand() % 1001) / 10.0f;              //   0.0 a 100.0
    l.comunicacao = (rand() % 10 < 8) ? 1 : 0;               // 80% ok, 20% falha
    return l;
}

// Mostra os valores atuais da leitura.
void exibirStatus(Leitura l)
{
    printf("\n======== STATUS ATUAL ========\n");
    printf("Temperatura..: %.1f C\n", l.temperatura);
    printf("Energia......: %.1f %%\n", l.energia);
    printf("Comunicacao..: %s\n", l.comunicacao == 0 ? "FALHA" : "OK");
    printf("==============================\n");
}

// Aplica as 3 regras do enunciado e imprime os alertas.
void analisarAlertas(Leitura l)
{
    int algumAlerta = 0;

    if (l.temperatura > 80.0f)
    {
        printf("[ALERTA] Superaquecimento (%.1f C > 80)\n", l.temperatura);
        algumAlerta = 1;
    }
    if (l.energia < 20.0f)
    {
        printf("[ALERTA] Economia de energia (%.1f%% < 20%%)\n", l.energia);
        algumAlerta = 1;
    }
    if (l.comunicacao == 0)
    {
        printf("[ALERTA] Falha de comunicacao\n");
        algumAlerta = 1;
    }

    if (!algumAlerta)
    {
        printf("Todos os sistemas nominais.\n");
    }
}

// Varre o vetor de leituras e exibe um resumo de cada uma.
void exibirHistorico(Leitura historico[], int total)
{
    int i;
    printf("\n======== HISTORICO (%d leitura(s)) ========\n", total);
    printf("  #   Temp(C)   Energia(%%)   Comunicacao\n");
    for (i = 0; i < total; i++)
    {
        printf("  %-3d %7.1f  %10.1f      %s\n",
               i + 1,
               historico[i].temperatura,
               historico[i].energia,
               historico[i].comunicacao == 0 ? "FALHA" : "OK");
    }
    printf("===========================================\n");
}

/* Simulacao continua: pede quantos ciclos rodar, gera leituras aleatorias,
 * mostra cada uma com animacao e armazena no historico. */
void simularSensores(Leitura historico[], int *total)
{
    int n, i;
    int espacoLivre = MAX_LEITURAS - *total;

    if (espacoLivre <= 0)
    {
        printf("\n>> Historico cheio (%d leituras).\n", MAX_LEITURAS);
        return;
    }

    printf("\nQuantos ciclos simular (1 a %d)? ", espacoLivre);
    if (scanf("%d", &n) != 1 || n < 1 || n > espacoLivre)
    {
        printf(">> Valor invalido.\n");
        limparBuffer();
        return;
    }

    animacaoBarra("Inicializando sensores", 20);

    for (i = 0; i < n; i++)
    {
        Leitura l = gerarLeituraAleatoria();
        historico[*total] = l;
        (*total)++;

        printf("\n>>> Ciclo %d/%d <<<\n", i + 1, n);
        printf("Temp: %.1f C | Energia: %.1f%% | Com: %s\n",
               l.temperatura, l.energia,
               l.comunicacao == 0 ? "FALHA" : "OK");
        analisarAlertas(l);

        DORMIR_MS(500);
    }

    printf("\n>> Simulacao concluida. Total no historico: %d leitura(s).\n", *total);
}

// Animacao de spinner girando enquanto "processa".
void animacaoSpinner(const char *msg, int ciclos)
{
    const char frames[] = {'|', '/', '-', '\\'};
    int i;
    for (i = 0; i < ciclos; i++)
    {
        printf("\r%s... %c", msg, frames[i % 4]);
        fflush(stdout);
        DORMIR_MS(80);
    }
    printf("\r%s... OK\n", msg);
}

// Animacao de barra de progresso preenchendo.
void animacaoBarra(const char *msg, int ciclos)
{
    int i;
    printf("%s: [", msg);
    fflush(stdout);
    for (i = 0; i < ciclos; i++)
    {
        printf("#");
        fflush(stdout);
        DORMIR_MS(40);
    }
    printf("] OK\n");
}
