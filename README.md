# 🌿 Simulador de Jardim – Meta 1  
### Unidade Curricular: POO – 2526

**Autores:**
   - _Gabriel Dinis Paixão dos Santos | LEI-PL | 2024134576_
   - _Diogo Simões Martins | LEI | 2024120298_

**Ano:** _2025/2026_  
**Versão:** Meta 1 – Estrutura base e validação sintática  
**Linguagem:** C++ 20  
**Compilador:** CLion + CMake  
**Configuração:** `Settings.h` (uso obrigatório e não modificável)

---

## 🧩 Descrição Geral

Este projeto implementa a **estrutura base** do simulador de jardim descrito no enunciado oficial da UC **Programação Orientada a Objetos** (POO – 2526).  

A **Meta 1** foca-se em:
- Estruturar todas as classes principais (`Simulador`, `Jardim`, `Solo`, `Jardineiro`, `Planta`, `Ferramenta`, etc.);
- Validar **sintaticamente** todos os comandos introduzidos;
- Garantir total conformidade com o enunciado (sem coleções STL).

---

## ⚙️ Restrições Cumpridas

- 🚫 **Sem coleções STL** (`std::vector`, `std::list`, `std::map`, …)  
- ✅ Jardim implementado com **alocação dinâmica manual** (`new`/`delete`)  
- ✅ Uso de `std::stringstream` **justificado e permitido**, pois trata-se de um fluxo de texto, não de uma coleção  
- ✅ Uso obrigatório da classe `Settings` para parametrização inicial  

---

## 📜 Estado Atual dos Comandos

| Estado | Significado |
|:-------:|-------------|
| 🟢 | Implementado e funcional |
| 🟡 | Inativo (reconhecido, mas sem efeito real ainda) |
| 🔴 | TODO (planeado, não reconhecido nesta meta) |

---

### 🧭 **1. Comandos Gerais**

| Comando | Estado | Descrição |
|----------|:------:|------------|
| `fim` | 🟢 | Termina imediatamente o simulador. |
| `jardim <linhas> <colunas>` | 🟢 | Cria o jardim (1–26 linhas/colunas). Só pode ser criado uma vez. |
| `larea` | 🟢 | Mostra o estado atual do jardim (pontos e posição do jardineiro). |
| `entra <pos>` | 🟢 | Coloca o jardineiro dentro do jardim na posição (ex: `entra fb`). |
| `sai` | 🟢 | Retira o jardineiro do jardim. |

---

### ⏱️ **2. Comandos de Interação com o Tempo**

| Comando | Estado | Descrição |
|----------|:------:|------------|
| `avanca [n]` | 🟡 | Avança n instantes de tempo. Validação sintática concluída. (TODO: atualizar crescimento das plantas na Meta 2.) |

---

### 🌱 **3. Comandos de Plantas**

| Comando | Estado | Descrição |
|----------|:------:|------------|
| `planta <pos> <tipo>` | 🟡 | Planta um tipo (`c`, `r`, `e`, `x`). Apenas validação sintática. |
| `colhe <pos>` | 🟡 | Colhe a planta da posição indicada. Apenas reconhecido. |

---

### 🧰 **4. Comandos de Ferramentas**

| Comando | Estado | Descrição |
|----------|:------:|------------|
| `rega <pos>` | 🟡 | Usa o regador na posição indicada. (TODO: alterar nível de água na Meta 2.) |
| `aduba <pos>` | 🟡 | Usa o adubo. (TODO: alterar nutrientes na Meta 2.) |
| `podar <pos>` | 🟡 | Usa a tesoura de poda. (TODO: interação real na Meta 2.) |
| `pega <n>` | 🟡 | Seleciona ferramenta pelo ID. Apenas validado. |
| `larga <n>` | 🟡 | Larga ferramenta do inventário. Apenas validado. |
| `compra <c>` | 🟡 | Compra uma ferramenta (`r`, `a`, `t`, `z`). Validação sintática apenas. |
| `inv` | 🟡 | Lista o inventário. (TODO: preencher inventário na Meta 2.) |

---

### 💾 **5. Comandos de Estados e Execução**

| Comando | Estado | Descrição |
|----------|:------:|------------|
| `grava <nome>` | 🟡 | Guarda o estado atual do simulador. (TODO: Meta 3 – persistência.) |
| `recupera <nome>` | 🟡 | Restaura um estado guardado. (TODO: Meta 3.) |
| `apaga <nome>` | 🟡 | Apaga um estado guardado. (TODO: Meta 3.) |
| `executa <ficheiro>` | 🟡 | Executa comandos a partir de um ficheiro. Validação feita; execução real na Meta 2. |

---

## 🧱 Estrutura do Projeto

```text
TP/
├── main.cpp
├── CMakeLists.txt
└── src/
    ├── Settings.h
    ├── simulador/
    │   ├── Simulador.h
    │   └── Simulador.cpp
    ├── jardim/
    │   ├── Jardim.h
    │   ├── Jardim.cpp
    │   ├── Solo.h
    │   └── Solo.cpp
    ├── jardineiro/
    │   ├── Jardineiro.h
    │   └── Jardineiro.cpp
    ├── plantas/
    │   ├── Planta.h
    │   ├── Cacto.h
    │   ├── Roseira.h
    │   ├── ErvaDaninha.h
    │   └── Exotica.h
    └── faramentas/
        ├── Ferramenta.h
        ├── Regador.h
        ├── Adubo.h
        ├── TesouraPoda.h
        └── FerramentaZ.h

```

---

## 🔬 Notas Técnicas

- As instâncias de `Solo` são criadas com valores aleatórios dentro dos intervalos definidos em `Settings.h`.  
- O `Jardineiro` tem posição e estado (`dentro` / `fora`).  
- O `Simulador` coordena todos os objetos e processa os comandos via `std::stringstream`.  
- Cada classe está separada em `.h` e `.cpp` e documentada.  
- Nenhuma coleção STL é utilizada em qualquer parte do projeto.

---

## 🧭 Plano de Desenvolvimento

| Meta | Objetivo | Estado |
|------|-----------|--------|
| **Meta 1** | Estrutura e validação sintática | ✅ Concluída |
| **Meta 2** | Lógica de plantas e ferramentas | 🔄 Em desenvolvimento |
| **Meta 3** | Persistência e gravação de estados | ⏳ Planeada |

---

## 👨‍💻 Execução (CLion)

Este projeto foi desenvolvido para ser executado diretamente no **CLion**.

### Passos para compilar e executar:

1. **Abrir o projeto**
   - Abre o CLion.
   - Seleciona **File → Open...** e escolhe a pasta principal do projeto  
     (`Project_POO_Jardim_25-26`).

2. **Construir o projeto**
   - Clica no botão 🛠️ **Build** (ou usa `Ctrl + F9`).
   - O CLion vai compilar automaticamente todos os ficheiros `.cpp`  
     definidos no `CMakeLists.txt`.

3. **Executar o simulador**
   - Seleciona a configuração **TP** no canto superior direito.
   - Clica em ▶️ **Run** (ou usa `Shift + F10`).
   - A consola integrada do CLion abrirá automaticamente.

4. **Interagir com o simulador**
   - Introduz os comandos diretamente na consola, por exemplo:
     ```
     jardim 10 10
     entra aa
     larea
     sai
     fim
     ```

7. **Parar o programa**
   - Usa o botão vermelho ⏹️ **Stop** na barra de execução do CLion.

---

### ℹ️ Nota importante
- Não é necessário criar pastas `build/` nem executar comandos no terminal.  
- Todas as compilações e execuções são geridas automaticamente pelo **CLion** através do **CMake**.  
- O executável gerado pode ser encontrado em:






