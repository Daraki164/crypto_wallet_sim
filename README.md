# Crypto Wallet Sim

> Simulador de carteira de criptomoedas em linha de comando, escrito em C (C11), com foco didático em modularização, gerenciamento de memória e precisão financeira.

[![Linguagem](https://img.shields.io/badge/C-C11-blue.svg)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))
[![Build](https://img.shields.io/badge/build-make-green.svg)]()
[![Status](https://img.shields.io/badge/status-em%20desenvolvimento-yellow.svg)]()

## Sobre o Projeto

O **Crypto Wallet Sim** é um projeto de estudo que simula o funcionamento de uma carteira de criptomoedas. O objetivo é explorar, na prática, conceitos de software de baixo nível: separação entre interface e implementação, alocação dinâmica de memória, representação de valores monetários sem ponto flutuante e, futuramente, simulação de um livro-razão (*ledger*).

Atualmente o projeto implementa a criação de uma carteira em memória, com chaves pública/privada e saldos de quatro ativos (USD, BRL, BTC e ETH), além da leitura e exibição desses dados.

> **Aviso:** este é um projeto educacional. Não utilize para armazenar valores reais ou chaves reais.

## Funcionalidades

- Criação de carteira em memória com identificação de chave pública e privada.
- Suporte a múltiplos ativos: `USD`, `R$`, `BTC` e `ETH`.
- Saldos representados por inteiros de 64 bits (centavos e Satoshis).
- Exibição formatada dos dados da carteira no terminal.
- Build automatizado com `Makefile` e alvo dedicado para depuração com `GDB`.

## Conceitos Técnicos Aplicados

- **Modularização:** separação estrita entre interfaces (`include/*.h`) e implementações (`src/*.c`).
- **Gerenciamento de memória:** alocação dinâmica com `malloc`/`calloc` e liberação com `free`.
- **Precisão numérica:** uso de `uint64_t` / `int64_t` representando a menor fração de cada ativo para evitar erros de arredondamento de `float`/`double`.
- **Build & debug:** automação de compilação com `Makefile` e suporte a símbolos de depuração.

## Estrutura do Projeto

```text
crypto_wallet_sim/
├── include/            # Cabeçalhos (.h), structs e protótipos
│   └── wallet.h
├── src/                # Implementações (.c)
│   ├── wallet.c
│   └── main.c          # Ponto de entrada
├── docs/               # Documentação técnica
│   └── DOCUMENTATION.md
├── obj/                # Arquivos objeto gerados na compilação (ignorado no Git)
├── bin/                # Executável final (ignorado no Git)
├── Makefile            # Regras de compilação e debug
└── README.md
```

## Pré-requisitos

- `gcc` (com suporte a C11)
- `make`
- `gdb` (opcional, para depuração)

## Compilação

```bash
git clone <url-do-repositorio>
cd crypto_wallet_sim

# Build padrão (otimizado)
make

# Build com símbolos de depuração
make debug

# Limpar artefatos de compilação
make clean
```

O executável é gerado em `bin/main`.

## Uso

```bash
./bin/main
```

Saída esperada:

```text
Chave Publica: chavepubica111
Chave Privada: chaveprivada222
0 de USD
0 de R$
0 de BTC
0 de ETH
```

## Roadmap

- [x] **Fase 1:** Estrutura da carteira, gerenciamento de ativos e validação de saldos em memória
- [ ] **Fase 2:** Motor de transações (transferências, taxas e histórico em memória)
- [ ] **Fase 3:** Simulador de mercado e variação de cotações
- [ ] **Fase 4:** Geração de chaves, hashes SHA-256 e assinatura digital
- [ ] **Fase 5:** Persistência de dados e livro-razão em disco (`data/`)
- [ ] **Fase 6:** Interface interativa no terminal (CLI)

## Documentação

A documentação técnica detalhada (arquitetura, modelo de dados, referência das funções e decisões de projeto) está disponível em [`docs/DOCUMENTATION.md`](docs/DOCUMENTATION.md).

## Contribuição

Sugestões e correções são bem-vindas. Para contribuir:

1. Faça um fork do projeto.
2. Crie uma branch para sua feature (`git checkout -b feature/minha-feature`).
3. Faça commit das alterações (`git commit -m "feat: minha feature"`).
4. Envie para o seu fork (`git push origin feature/minha-feature`).
5. Abra um Pull Request.

## Licença

Projeto desenvolvido para fins de estudo. Nenhuma licença foi definida até o momento.
