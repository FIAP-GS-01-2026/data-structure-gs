# Mission Control AI

Sistema em C de arquivo único para monitoramento de uma missão espacial experimental.
O operador insere temperatura, energia e status de comunicação; o programa aplica regras
de verificação automática, exibe alertas e mantém um histórico das leituras.

> **Global Solution 2026.1 — FIAP** · Disciplina: Data Structures and Algorithms · Arquivo principal: `mission_control.c`

---

## Conceitos de C aplicados

| Conceito | Onde aparece |
| --- | --- |
| Estruturas condicionais (`if`) | As 3 regras de alerta em `analisarAlertas()` |
| `switch` | Despacho do menu no `main()` |
| Laço `do-while` | Loop principal do menu |
| Laço `while` | Validação de entrada em `lerDados()` |
| Laço `for` | Varredura do histórico e ciclos da simulação |
| Vetores | `Leitura historico[MAX_LEITURAS]` (estático, tamanho fixo) |
| Structs e `typedef` | Tipo `Leitura` |
| Funções e passagem por referência | `simularSensores(historico, &total)` |
| Macros (`#define`) | `MAX_LEITURAS`, `DORMIR_MS`, cores ANSI |

---

## Estrutura de dados

```c
typedef struct {
    float temperatura;  // C
    float energia;      // % de 0 a 100
    int   comunicacao;  // 0 = falha, 1 = ok
} Leitura;
```

As leituras são guardadas em um vetor estático `historico[MAX_LEITURAS]` (100), com um
contador `int total` indicando quantas posições já foram preenchidas.

---

## Regras de alerta

| Condição | Alerta emitido |
| --- | --- |
| `temperatura > 80` | Superaquecimento |
| `energia < 20` | Economia de energia |
| `comunicacao == 0` | Falha de comunicação |

As três condições são `if` independentes — mais de um alerta pode disparar para a mesma
leitura. Valores no limite (80, 20, 1) não disparam. Quando nenhuma é verdadeira, exibe
"Todos os sistemas nominais.".

---

## Menu

```
1 - Inserir dados
2 - Visualizar status
3 - Executar analise
4 - Simulacao continua dos sensores
5 - Encerrar sistema
```

Entrada não numérica é tratada (opção inválida cai no `default` sem travar).

## Funcionalidades opcionais implementadas

- **Histórico** — todas as leituras (manuais e simuladas) são gravadas no vetor e listadas na análise (opção 3).
- **Simulação contínua** — opção 4 gera N ciclos com leituras aleatórias (casos nominais e críticos).
- **Animações** — spinner e barra de progresso no terminal (cores ANSI).

---

## Compilação e execução

> ⚠️ **Windows apenas.** O código usa `windows.h` (`Sleep`, cores ANSI via console do Windows),
> portanto **não compila em Linux/Mac** sem adaptação. Requer MinGW/GCC no Windows.

```bash
gcc -Wall -Wextra -o mission_control.exe mission_control.c
mission_control.exe
```

---

## Grupo

- Thiago Renatino — RM569073
- Glauco Kelly — RM572840
- Gabriel Fagundes — RM569074
