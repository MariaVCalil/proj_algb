# 🧮 Sistema de Álgebra Linear

Projeto desenvolvido para a disciplina de Álgebra Linear do curso de Engenharia de Software.
O programa é um sistema interativo em C que reúne ferramentas para resolver problemas comuns da álgebra linear.

---

## Funcionalidades

- [x] Menu interativo com interface visual no terminal
- [x] Leitura de sistemas lineares
- [x] Leitura e impressão de matrizes
- [x] Resolução de sistemas lineares
- [x] Verificação de transformação linear
- [x] Determinação de bases
- [ ] Cálculo de autovalores e autovetores
- [ ] Diagonalização de matrizes
- [ ] Gerenciamento de arquivos

---

## Estrutura do Projeto

```
projeto/
│
├── main.c              # Ponto de entrada do programa
├── menu.c              # Lógica e exibição dos menus
├── sistemas.c          # Funções relacionadas a sistemas lineares
├── matrizes.c          # Funções de leitura e impressão de matrizes
├── arquivos.c          # Funções de leitura e escrita em arquivos
│
└── include/
    ├── menu.h          # Cabeçalho do menu
    ├── sistemas.h      # Cabeçalho dos sistemas lineares
    ├── matrizes.h      # Cabeçalho das matrizes
    ├── bases.h         # Cabeçalho das bases (em desenvolvimento)
    └── arquivos.h      # Cabeçalho dos arquivos
```

---

## Como Compilar e Executar

### Requisitos

- GCC instalado
- Sistema operacional Linux, macOS ou WSL (Windows Subsystem for Linux)

### Compilação

No terminal, dentro da pasta do projeto, execute:

```bash
gcc main.c menu.c sistemas.c transformacoes.c bases.c matrizes.c arquivos.c util.c -o algebra
```

### Execução

```bash
./algebra
```

---

## Como Usar

Ao iniciar o programa, um menu será exibido com as opções disponíveis.
Basta digitar o número da opção desejada e pressionar **Enter**.

```
╔══════════════════════════════╗
║    SISTEMA ALGEBRA LINEAR    ║
╚══════════════════════════════╝
    [1] Resolver um sistema linear
    [2] Verificar transformação linear
    [3] Determinar bases
    [4] Calcular autovalores e autovetores
    [5] Diagonalizar uma matriz
    [6] Arquivos
    [7] Sair
```

> ⚠️ As opções 2 a 6 ainda estão em desenvolvimento.

---

## Tecnologias

- Linguagem **C**
- Compilador **GCC**

---

## Autor

Desenvolvido como projeto da disciplina de Álgebra Linear — 3º Período de Engenharia de Software.
