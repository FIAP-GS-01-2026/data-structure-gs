# Mission Control AI

Sistema de monitoramento de telemetria para uma missão espacial experimental, desenvolvido em linguagem C.

> **Global Solution 2026 — FIAP**
> Disciplina: Data Structures And Algorithms

---

## Visão geral

O **Mission Control AI** simula o monitoramento de uma sonda/estação espacial ao longo de vários *ciclos* de leitura de telemetria. A cada ciclo, o sistema recebe dados de três subsistemas críticos, classifica cada um, dispara alertas automáticos e reage a situações críticas.

---

## Conceitos de C aplicados

| Conceito | Onde aparece |
| --- | --- |
| **Estruturas condicionais** | Classificação de status (`if`/`else`, `switch`) |
| **Estruturas de repetição** | Menu (`do-while`), ciclos de simulação e relatório (`for`) |
| **Vetores** | Histórico completo da missão (`historico[MAX_CICLOS]`) |
| **Funções** | ~15 funções com responsabilidade única |
| **Structs e enums** | Modelagem dos dados de telemetria (`Telemetria`, `NivelStatus`, etc.) |

---

## Funcionalidades

1. **Inserir dados** — o usuário fornece temperatura, energia (%) e status de comunicação (0/1/2).
2. **Verificação automática** — o sistema analisa cada leitura e emite alertas:

| Condição | Alerta emitido |
| --- | --- |
| Temperatura > 80 °C | `[CRITICO] SUPERAQUECIMENTO` |
| Energia < 20 % | `[CRITICO] ECONOMIA DE ENERGIA` |
| Comunicação = 0 (link perdido) | `[CRITICO] FALHA DE COMUNICACAO` |

1. **Menu interativo com `switch()`** — quatro opções principais + extras.

### Bônus implementados

- **Histórico das leituras** — vetor de até 100 ciclos (`historico[MAX_CICLOS]`).
- **Simulação contínua dos sensores** — opção 4 do menu, gera N ciclos automaticamente.
- **Relatório estatístico** — médias, mínimos/máximos, % de ciclos críticos, distribuição de modos.

---

## Menu principal

```text
==============================
     MISSION CONTROL AI
==============================
1. Inserir dados
2. Visualizar status atual
3. Executar analise completa
4. Simulacao automatica
5. Configurar simulacao (N ciclos)
0. Encerrar sistema
```

---

## Limiares de classificação

Todos os limites estão centralizados como `#define` no topo do código:

| Grandeza | NOMINAL | ATENÇÃO | CRÍTICO |
| --- | --- | --- | --- |
| Bateria (%) | > 50 | 20 a 50 | < 20 |
| Temperatura (°C) | -20 a 50 | 50 a 80 / -40 a -20 | **> 80** ou < -40 |
| Status comunicação | OK | INSTÁVEL | **PERDIDO (= 0)** |
| Saldo de energia (W) | ≥ 0 | -50 a 0 | < -50 |

---

## Como compilar e executar

Requer GCC (Linux/Mac) ou MinGW (Windows).

```bash
# Compilar
gcc -o mission_control mission_control.c -Wall

# Executar — Linux/Mac
./mission_control

# Executar — Windows
./mission_control.exe
```

---

## Estrutura do código

Arquivo único `mission_control.c`, organizado em seções:

1. `#include` e `#define` — limiares centralizados
2. Enums e `struct Telemetria` — tipos de dados
3. Protótipos — todas as funções declaradas antes de `main`
4. `main()` — menu `do-while` + `switch`
5. Implementações agrupadas por responsabilidade:
   - Utilitários (`limparBuffer`, `aleatorioEmFaixa`)
   - Geração/entrada (`gerarLeitura`, `lerLeituraManual`)
   - Análise (`avaliarBateria`, `avaliarTemperatura`, `avaliarSinal`, `avaliarEnergia`)
   - Alertas e resposta (`emitirAlertas`, `responderCritico`)
   - Exibição (`exibirPainel`, `exibirUltimaLeitura`, `gerarRelatorio`)
   - Fluxos de menu (`iniciarMonitoramento`, `inserirLeituraManual`)

---

## Grupo

Thiago Renatino — RM569073
Glauco Kelly — RM572840
Gabriel Fagundes — RM569074
