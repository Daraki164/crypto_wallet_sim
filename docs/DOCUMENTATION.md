# Documentação Técnica — Crypto Wallet Sim

Documento de referência do projeto **Crypto Wallet Sim**: arquitetura, modelo de dados, API pública, fluxo de execução, build e limitações conhecidas.

## Sumário

1. [Visão Geral](#1-visão-geral)
2. [Arquitetura](#2-arquitetura)
3. [Modelo de Dados](#3-modelo-de-dados)
4. [Referência da API](#4-referência-da-api)
5. [Fluxo de Execução](#5-fluxo-de-execução)
6. [Representação de Valores](#6-representação-de-valores)
7. [Gerenciamento de Memória](#7-gerenciamento-de-memória)
8. [Build e Depuração](#8-build-e-depuração)
9. [Estado Atual e Limitações](#9-estado-atual-e-limitações)
10. [Roadmap](#10-roadmap)
11. [Convenções de Código](#11-convenções-de-código)

---

## 1. Visão Geral

O Crypto Wallet Sim é um simulador de carteira de criptomoedas executado em linha de comando. O código é escrito em C (C11) e organizado em módulos, com o objetivo de demonstrar boas práticas de programação de sistemas em um domínio financeiro.

A versão atual cobre a **Fase 1** do roadmap: criação da carteira em memória, inicialização dos ativos e leitura dos dados.

### Objetivos de aprendizado

- Projetar interfaces estáveis (`wallet.h`) desacopladas da implementação (`wallet.c`).
- Modelar valores monetários sem ponto flutuante.
- Gerenciar memória dinâmica com responsabilidade.
- Automatizar o ciclo de build com `Makefile`.

---

## 2. Arquitetura

```text
┌────────────────┐     inclui      ┌────────────────┐
│    src/main.c   │ ──────────────▶ │ include/wallet.h │
│  (ponto de      │                 │ (tipos + API)    │
│   entrada)      │                 └────────┬─────────┘
└───────┬─────────┘                          │ implementa
        │ usa                                 ▼
        │                            ┌────────────────┐
        └───────────────────────────▶│   src/wallet.c  │
                                     │ (implementação) │
                                     └────────────────┘
```

### Camadas

| Camada | Arquivo | Responsabilidade |
|--------|---------|------------------|
| Interface | `include/wallet.h` | Define constantes, enumerações, structs e protótipos. |
| Implementação | `src/wallet.c` | Implementa criação, inicialização e leitura da carteira. |
| Aplicação | `src/main.c` | Instancia a carteira e dispara a leitura dos dados. |

Essa separação permite recompilar apenas a implementação quando o cabeçalho não muda e facilita a substituição de implementações no futuro.

---

## 3. Modelo de Dados

### 3.1 Enumeração `Coins`

Identifica os ativos suportados pela carteira.

```c
typedef enum {
    DOLAR = 0,
    REAL,
    BTC,
    ETH
} Coins;
```

| Valor | Posição | Constante de sigla |
|-------|---------|--------------------|
| `DOLAR` | 0 | `USD_S` (`"USD"`) |
| `REAL`  | 1 | `RS_S` (`"R$"`)  |
| `BTC`   | 2 | `BTC_S` (`"BTC"`) |
| `ETH`   | 3 | `ETH_S` (`"ETH"`) |

> A posição do enum é usada como índice em `astAtivos[]`, portanto a ordem é relevante.

### 3.2 Struct `STRUCT_BALANCE`

Representa o saldo de um ativo.

```c
typedef struct {
    uint8_t  iCoin;       // identificador do ativo (Coins)
    uint64_t iQuant;      // saldo na menor fração do ativo
    char     szSigla[8];  // sigla textual (ex.: "USD")
} STRUCT_BALANCE, *PSTRUCT_BALANCE;
```

| Campo | Tipo | Descrição |
|-------|------|-----------|
| `iCoin` | `uint8_t` | Código do ativo (`Coins`). |
| `iQuant` | `uint64_t` | Quantidade inteira na menor unidade (centavos / Satoshis). |
| `szSigla` | `char[8]` | Sigla exibida ao usuário. |

### 3.3 Struct `STRUCT_WALLET`

Estrutura principal da carteira.

```c
typedef struct {
    char           szIdPbc[65];  // chave pública (até 64 caracteres + '\0')
    char           szIdPvd[65];  // chave privada (até 64 caracteres + '\0')
    STRUCT_BALANCE astAtivos[4];  // um saldo por ativo
} STRUCT_WALLET, *PSTRUCT_WALLET;
```

| Campo | Tipo | Descrição |
|-------|------|-----------|
| `szIdPbc` | `char[65]` | Identificador/chave pública. |
| `szIdPvd` | `char[65]` | Identificador/chave privada. |
| `astAtivos` | `STRUCT_BALANCE[4]` | Vetor fixo de saldos, indexado por `Coins`. |

O nome `astAtivos` usa o prefixo `ast` (array de struct) por convenção de nomenclatura húngara.

---

## 4. Referência da API

### 4.1 `pstCreateWallet`

```c
PSTRUCT_WALLET pstCreateWallet(char szIdPbc[65], char szIdPvd[65]);
```

Cria e inicializa uma carteira em memória.

**Parâmetros**

| Nome | Descrição |
|------|-----------|
| `szIdPbc` | Chave pública a ser copiada (máx. 64 caracteres). |
| `szIdPvd` | Chave privada a ser copiada (máx. 64 caracteres). |

**Retorno**

- Ponteiro para `STRUCT_WALLET` alocada dinamicamente em caso de sucesso.
- `NULL` em caso de falha de alocação (comportamento desejado; ver [Limitações](#9-estado-atual-e-limitações)).

**Comportamento**

1. Aloca `sizeof(STRUCT_WALLET)` com `malloc`.
2. Copia as chaves com `strncpy`, limitando ao tamanho do buffer menos um.
3. Percorre `MAX_COINS` posições e inicializa cada ativo com sigla, código e saldo zero.

**Observações**

- O chamador é responsável por liberar a memória com `free`.
- As strings são truncadas em 64 caracteres, mas o terminador nulo não é garantido explicitamente em todos os caminhos.

### 4.2 `vLerDados`

```c
void vLerDados(const PSTRUCT_WALLET Dono);
```

Exibe no `stdout` as chaves e os saldos de todos os ativos da carteira.

**Parâmetros**

| Nome | Descrição |
|------|-----------|
| `Dono` | Ponteiro constante para a carteira a ser lida. |

**Retorno**

- Nenhum (`void`).

**Formato de saída**

```text
Chave Publica: <szIdPbc>
Chave Privada: <szIdPvd>
<saldo> de <sigla>
...
```

O saldo é impresso com `%ld` sobre um campo `uint64_t` — ponto de atenção detalhado na seção de limitações.

---

## 5. Fluxo de Execução

```text
main()
  │
  ├─▶ pstCreateWallet("chavepubica111", "chaveprivada222")
  │     ├─ malloc(STRUCT_WALLET)
  │     ├─ copia chaves
  │     └─ inicializa astAtivos[0..3]
  │
  └─▶ vLerDados(wallet)
        └─ printf das chaves e dos saldos
```

O programa encerra sem liberar a carteira, pois o processo termina logo em seguida. Em uma aplicação de longa duração, `free` seria obrigatório.

---

## 6. Representação de Valores

Valores monetários **não** usam `float`/`double`. Em vez disso, cada saldo é um inteiro de 64 bits na menor unidade do ativo:

| Ativo | Menor unidade | Exemplo: 1 unidade |
|-------|---------------|--------------------|
| USD | centavo | `100` |
| BRL | centavo | `100` |
| BTC | Satoshi (1e-8) | `100000000` |
| ETH | Wei (1e-18) | `1000000000000000000` |

### Por que inteiros?

- Evita erros de arredondamento binário inerentes a ponto flutuante.
- Torna somas e comparações exatas e determinísticas.
- `uint64_t` cobre a faixa necessária para BTC e ETH na menor unidade.

A conversão para exibição (dividir pela escala e formatar) deverá ser feita na camada de apresentação nas próximas fases.

---

## 7. Gerenciamento de Memória

### Alocação

A carteira é alocada dinamicamente em `pstCreateWallet`:

```c
PSTRUCT_WALLET wallet = (PSTRUCT_WALLET)malloc(sizeof(STRUCT_WALLET));
```

### Propriedade

- Quem chama `pstCreateWallet` torna-se dono do ponteiro.
- A liberação deve ser feita com `free` quando a carteira não for mais necessária.

### Riscos atuais

1. **Retorno de `malloc` não verificado:** se a alocação falhar, o código desreferencia `NULL`.
2. **Vazamento no `main`:** a carteira não é liberada antes do `return` (inofensivo no encerramento, mas didaticamente incorreto).
3. **`strncpy` e terminador nulo:** quando a origem é maior ou igual ao destino, `strncpy` não adiciona `'\0'`.

### Recomendações

- Verificar `wallet == NULL` e retornar `NULL`.
- Garantir `wallet->szIdPbc[64] = '\0';` e equivalentes após a cópia.
- Adicionar uma função `void vFreeWallet(PSTRUCT_WALLET w)` para encapsular a liberação.

---

## 8. Build e Depuração

### Variáveis do `Makefile`

| Variável | Valor padrão | Uso |
|----------|--------------|-----|
| `CC` | `gcc` | Compilador. |
| `CFLAGS` | `-Wall -Wextra -O2` | Flags de compilação otimizada. |
| `DEBUG_FLAGS` | `-Wall -Wextra -g -O0` | Flags para depuração. |
| `INC_DIR` | `include` | Diretório de cabeçalhos. |
| `SRC_DIR` | `src` | Diretório de fontes. |
| `OBJ_DIR` | `obj` | Diretório de objetos. |
| `BIN_DIR` | `bin` | Diretório do executável. |

### Alvos

| Alvo | Descrição |
|------|-----------|
| `all` | Limpa, cria diretórios e compila `bin/main`. |
| `debug` | Recompila com `DEBUG_FLAGS` (símbolos de depuração). |
| `clean` | Remove `bin/` e `obj/`. |
| `diretorio` | Cria `bin/` e `obj/`. |

### Comandos

```bash
make            # build otimizado
make debug      # build com -g -O0
make clean      # limpeza
```

### Depuração com GDB

```bash
make debug
gdb ./bin/main
```

Sugestões de uso:

```gdb
break pstCreateWallet
run
next
print *wallet
continue
```

### Verificação de memória

```bash
valgrind --leak-check=full ./bin/main
```

---

## 9. Estado Atual e Limitações

Esta seção documenta o comportamento real do código na Fase 1.

| # | Item | Descrição | Impacto |
|---|------|-----------|---------|
| 1 | `malloc` sem verificação | `pstCreateWallet` não trata falha de alocação. | Potencial *segfault* em memória insuficiente. |
| 2 | Incompatibilidade de assinatura | Protótipo usa `char[65]`, definição usa `char[64]`. | Aviso `-Warray-parameter`; contrato ambíguo. |
| 3 | `printf` com tipo incorreto | `%ld` para `uint64_t` (ideal: `PRIu64`). | Comportamento indefinido em plataformas onde `long` ≠ 64 bits. |
| 4 | Terminador nulo | `strncpy` não garante `'\0'`. | Risco de leitura fora do buffer em `printf`. |
| 5 | Vazamento no `main` | Carteira não é liberada. | Vazamento trivial no encerramento. |
| 6 | Chaves em texto puro | Chaves são strings fixas no código. | Inadequado para uso real (projeto didático). |

### Melhorias sugeridas

- Validar `malloc` e retornar `NULL`.
- Unificar o tamanho dos buffers entre protótipo e definição.
- Usar `#include <inttypes.h>` e `PRIu64`.
- Garantir terminação explícita das strings.
- Adicionar `vFreeWallet`.
- Separar a lógica de exibição da lógica de domínio.

---

## 10. Roadmap

- [x] **Fase 1:** Estrutura da carteira, gerenciamento de ativos e validação de saldos em memória
- [ ] **Fase 2:** Motor de transações (transferências, taxas e histórico em memória)
- [ ] **Fase 3:** Simulador de mercado e variação de cotações
- [ ] **Fase 4:** Geração de chaves, hashes SHA-256 e assinatura digital
- [ ] **Fase 5:** Persistência de dados e livro-razão em disco (`data/`)
- [ ] **Fase 6:** Interface interativa no terminal (CLI)

### Detalhamento das próximas fases

**Fase 2 — Motor de transações**

- Estrutura de transação (origem, destino, ativo, valor, timestamp).
- Validação de saldo antes de debitar.
- Histórico em memória (lista encadeada ou vetor dinâmico).

**Fase 3 — Simulador de mercado**

- Tabela de cotações por ativo.
- Conversão entre ativos e cálculo de valor total da carteira.

**Fase 4 — Criptografia**

- Geração de pares de chaves.
- Hash SHA-256 para integridade.
- Assinatura e verificação de transações.

**Fase 5 — Persistência**

- Serialização da carteira e do ledger em `data/`.
- Carregamento na inicialização.

**Fase 6 — CLI interativa**

- Menu de operações: consultar saldo, transferir, histórico, cotações.

---

## 11. Convenções de Código

| Elemento | Convenção | Exemplo |
|----------|-----------|---------|
| Structs | `ST` + nome em PascalCase | `STRUCT_WALLET` |
| Ponteiros para struct | `PS` + nome | `PSTRUCT_WALLET` |
| Funções | prefixo de tipo (`v`, `ps`, `i`, `b`) + CamelCase | `pstCreateWallet` |
| Variáveis locais | prefixo húngaro + CamelCase | `szIdPbc`, `iQuant`, `ii` |
| Constantes | `UPPER_SNAKE_CASE` | `MAX_COINS` |
| Cabeçalhos | guardas `#ifndef` | `WALLET_H` |

### Regras gerais

- Manter protótipos em `include/` e implementações em `src/`.
- Compilar sempre com `-Wall -Wextra` e tratar os avisos.
- Não introduzir ponto flutuante para valores monetários.
- Liberar toda memória alocada dinamicamente.
