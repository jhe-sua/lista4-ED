# Sistema de Autocomplete de Jogos com Trie

Este projeto consiste em um sistema simples de autocomplete de jogos utilizando a estrutura de dados **Trie**. Os resultados """""encontrados são ordenados pela popularidade e, para desempates, pela ordem alfabética dos títulos usando o algoritmo *Merge Sort*.


## Descrição do Projeto

O sistema armazena um catálogo de jogos, cada um possuindo um título, uma breve descrição e um valor de popularidade. As verificações e sugestões são buscadas seguindo as seguintes condições:
* **Busca Case-Insensitive:** Não há distinção entre letras maiúsculas e minúsculas.
* **Espaços Ignorados:** Espaços em branco são removidos na busca (ex: `"Half Life"` e `"halflife"` geram a mesma chave).
* **Alfabeto Restrito:** Tamanho fixo de **36 caracteres** (letras de A-Z e números de 0-9).
* **Critério de Ordenação:** Os resultados do autocomplete são exibidos em ordem decrescente de popularidade. Em caso de empate, o desempate é feito por ordem alfabética da chave de busca interna.


## Organização dos Arquivos

A estrutura do projeto está modularizada da seguinte forma:

| Arquivo | Tipo | Descrição |
| :--- | :--- | :--- |
| **`Game.hpp`** / **`Game.cpp`** |  Definição de Classe | Representação do objeto `Game` (título, descrição, popularidade) e adaptação do operador de saída. |
| **`Trie.hpp`** / **`Trie.cpp`** | Definição de Classe | Implementação dos nós (`TrieNode`) e da árvore (`Trie`). Contém a lógica de normalização de chaves, inserção, busca e o algoritmo *Merge Sort*. |
| **`GamesDatabase.hpp`** / **`GamesDatabase.cpp`** | Base de Dados | Base de dados contendo o array inicial de jogos fornecido pelo professor. |
| **`main.cpp`** | Principal | Trata os argumentos de linha de comando, alimenta a Trie e exibe os resultados do autocomplete. |


## Compilação

Para compilar o projeto, certifique-se de ter o compilador `g++` instalado. Execute o comando abaixo no terminal de sua preferência (todos os arquivos devem estar no mesmo diretório):

```bash
g++ main.cpp Game.cpp Trie.cpp GamesDatabase.cpp -o app
```

## Instruções de Execução
O programa deve ser executado obrigatoriamente via linha de comando, passando dois argumentos:

1. **`k`**: A quantidade máxima de sugestões que você deseja visualizar.

2. **`prefixo`**: A string correspondente ao início do título do jogo que deseja buscar.

Formato padrão:

```Bash
./app <k> <prefixo>
```

Atenção: Se o prefixo da sua busca possuir espaços (ex: Half Life), ele deve ser passado entre aspas duplas no terminal, caso contrário o sistema entenderá como múltiplos argumentos. Exemplo: ./app 3 "half l".

## Exemplos de Uso
Abaixo estão listados os principais cenários de execução, demonstrando o comportamento do sistema com base nas regras estabelecidas. Considere que os comandos estão rodando sobre a base de jogos inicial do projeto.

1. Busca padrão por prefixo
    - Ao buscar pelo prefixo "ha" limitando a 3 resultados, o sistema recupera os jogos, ordena pela popularidade e exibe o limite solicitado.  
    Comando:
    ```Bash
    ./app 3 ha
    ```
    Saída:
    ```
    [Hades | Defy the god of the dead as you hack and slash out of the Underworld in this rogue like dungeon crawler from the creators of Bastion Transistor and Pyre | 213542]
    [Halo The Master Chief Collection | The Master Chief s iconic journey includes six games built for PC and collected in a single integrated experience Whether you re a long time fan or meeting Spartan 117 for the first time The Master Chief Collection is the definitive Halo gaming experience | 192219]
    [Halo Infinite | The legendary Halo series returns with the most expansive Master Chief campaign yet and a ground breaking free to play multiplayer experience | 160647]
    ```
2. Tratamento de espaços e Case-Insensitive
    - A busca ignora espaços e o tamanho da caixa das letras. O prefixo "HALF lIFE deat  H" é convertido internamente para a chave HALFLIFEDEATH, trazendo exatamente o jogo esperado.

    Comando:
    ```Bash
    ./app 5 "HALF lIFE deat  H"
    ```
    Saída:
    ```
    [Half Life Deathmatch Source | Half Life Deathmatch Source is a recreation of the first multiplayer game set in the Half Life universe Features all the classic weapons and most played maps now running on the Source engine | 3083]
    ```
3. Cenário de desempate por ordem alfabética
    - O critério principal é a popularidade (ordem decrescente). Se dois jogos tiverem a mesma popularidade, o sistema utiliza a ordem alfabética da chave de busca para desempatar. Vamos supor que os jogos "Half Life" e "Halo" tivessem o mesmo valor de popularidade, a saída do programa apresentaria "Half Life" primeiro, uma vez que em ordem alfabética a letra "f" é anterior a letra "o".  
    
    Comando:
    ```Bash
    ./app 2 ha
    ```
    Saída:
    ```
    [Half Life | FPS classico de ficcao cientifica | 90]
    [Halo | FPS futurista com campanha e multiplayer | 90]
    ```

4. Prefixo não encontrado na Trie
    - Se o usuário buscar por um prefixo que não corresponda a nenhum título cadastrado na base de dados, o sistema o avisará.
    Comando:
    ```Bash
    ./app 3 zelda
    ```
    Saída:
    ```
    No results found
    ```
5. Execução com argumentos inválidos
    - O programa possui validação para garantir que está sendo chamado da forma correta. Se os parâmetros não forem passados, o sistema exibe o manual de uso.
    Comando:
    ```Bash
    ./app 5
    ```
    Saída:
    ```
    Usage: ./app k prefix
    ```