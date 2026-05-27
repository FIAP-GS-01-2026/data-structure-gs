# Mission Control AI

Sistema de monitoramento de telemetria para uma missão espacial experimental, desenvolvido em linguagem C.

> **Global Solution 2026 — FIAP**
> Disciplina: Data Structures And Algorithms

---

## Visão geral

O **Mission Control AI** simula o monitoramento de uma sonda/estação espacial ao longo de vários *ciclos* de leitura de telemetria. A cada ciclo, o sistema recebe dados (gerados automaticamente ou inseridos manualmente) de três subsistemas críticos:

- **Energia** — nível de bateria, geração solar e consumo
- **Comunicação** — força do sinal, latência e estado do enlace (link)
- **Operacional** — temperatura interna e modo da missão

A partir desses dados, o sistema **classifica** o estado de cada subsistema, **dispara alertas automáticos** e **reage a situações críticas** alterando o comportamento da missão (ex.: ativar modo de economia de energia). Ao final, gera um **relatório consolidado** da missão.

---

## Objetivos

O projeto aplica, de forma prática, os conceitos fundamentais de C:

| Conceito | Onde aparece |
|---|---|
| **Estruturas condicionais** | Classificação de status (`if`/`else`, `switch`) |
| **Estruturas de repetição** | Laço de ciclos e menu (`for`, `while`, `do-while`) |
| **Vetores** | Histórico de telemetria de toda a missão |
| **Funções** | Geração, análise, alertas, relatório (responsabilidades separadas) |
| **Structs e enums** | Modelagem dos dados de telemetria |

---

## Funcionalidades

1. **Monitoramento automático** — simula uma sequência de ciclos com dados gerados aleatoriamente dentro de faixas realistas de sensores.
2. **Inserção manual** — permite ao operador inserir uma leitura à mão para testar cenários específicos.
3. **Motor de análise** — classifica cada grandeza em três níveis: `NOMINAL`, `ATENÇÃO` ou `CRÍTICO`.
4. **Alertas automáticos** — exibe avisos quando um subsistema sai do estado nominal.
5. **Resposta a situações críticas** — lógica reativa que altera o estado da missão:
   - Bateria crítica → ativa **modo economia** (reduz consumo nos próximos ciclos)
   - Temperatura crítica → ativa **modo seguro**
   - Sinal perdido por vários ciclos seguidos → **alerta de emergência** escalonado
6. **Relatório final** — estatísticas da missão: médias, mínimos/máximos e total de alertas por tipo.

---

## Limiares de classificação

Os limites usados pelo motor de análise (centralizados como `#define` no código):

| Grandeza | NOMINAL | ATENÇÃO | CRÍTICO |
|---|---|---|---|
| Bateria (%) | > 50 | 20 a 50 | < 20 |
| Temperatura (°C) | -20 a 50 | 50 a 60 / -40 a -20 | > 60 ou < -40 |
| Força do sinal (dB) | > -70 | -85 a -70 | < -85 |
| Saldo de energia (W) | ≥ 0 | -50 a 0 | < -50 |

---

## Como compilar e executar

Requer um compilador C (GCC recomendado).

```bash
# Compilar
gcc -o mission_control main.c -Wall

# Executar
./mission_control
```

No Windows (com GCC/MinGW):

```bash
gcc -o mission_control.exe main.c -Wall
mission_control.exe
```

---

## Menu principal

```
=== MISSION CONTROL AI ===
1. Iniciar monitoramento (simulação automática)
2. Inserir leitura manual
3. Ver relatório da missão
4. Configurar simulação
0. Encerrar
```

---

## Estrutura do código

O projeto é contido em um único arquivo `main.c`, organizado em seções:

1. Includes e definições de limiares (`#define`)
2. Enums e a `struct Telemetria`
3. Protótipos das funções
4. `main()` — menu e laço principal
5. Implementação das funções, agrupadas por responsabilidade (geração, análise, alertas, relatório, utilitários)

---

## Autor

Thiago Renatino — FIAP, Global Solution 2026.
