
Repositório destinado a entrega da lista 3 da disciplina de Estrutura de Dados.

# Descrição do Sistema

O repositório implementa um sistema de matchmaking simples para jogos online. Cada jogador possui um ID, nome, score (pontuação) e um timestamp (registro de tempo). Quando um jogador entra no sistema, ele é adicionado ao final de uma fila de espera armazenada em memória pelo programa.

Para a formação de grupos de jogadores, a fila é primeiramente ordenada pelo score, com o timestamp como critério de desempate. Em seguida, o sistema busca o primeiro subgrupo consecutivamente ordenado que atenda ao tamanho solicitado e ao limite de diferença de score (delta). Por exemplo, se um grupo deve ter três jogadores com o máximo de diferença entre os scores igual a 50, o sistema selecionará os três primeiros jogadores que satisfizerem essa condição. Caso nenhum grupo atenda aos requisitos, nenhum grupo será formado.

Quando um grupo é formado com sucesso, esses jogadores são removidos da lista de espera, simulando o seu envio para a partida.

Existem duas classes principais no sistema:

1. **Player**: classe que modela os jogadores e seus atributos.
```cpp
Player(int id, std::string name, int score, int timestamp)
```

2. **Matchmaking**: classe correspondente ao sistema de matchmaking. Implementa todas as ações básicas do sistema, tais como: inserir um jogador, remover um jogador pelo id, formar grupos, buscar os jogadores que estão na fila de espera, ordená-los e printar no console a fila de espera.
```cpp
Matchmaking()
```


# Instruções de Compilação

O repositório foi inteiramente programado em **C++**, portanto, é necessário compilar os arquivos antes de executar o programa. As instruções abaixo compilam todos os arquivos `.cpp` de uma vez:

1. Certifique-se de que todos os arquivos `.hpp` e `.cpp` estejam na mesma pasta.
2. Certifique-se de ter o `g++` instalado na sua máquina.
3. Em seu terminal, dentro da pasta onde estão os arquivos, execute:

```bash
g++ main.cpp Matchmaking.cpp Player.cpp -o matchmaking
```

Após o comando, um arquivo executável será criado na mesma pasta.



# Instruções de Execução

Após compilar, execute o programa de acordo com o seu sistema operacional:
 
- **Windows**
 
```bash
.\matchmaking.exe
```
 
- **Linux / macOS**
 
```bash
./matchmaking
```

# Estrutura de Dados do Sistema

Internamente, o sistema mantém apenas um **array estático** fixo de tamanho `MAX_PLAYERS` para gerenciar a fila de espera. O array é do tipo Player, uma vez que é uma fila de jogadores. Como o tamanho do array é fixo, cada posição já contém um objeto instanciado com seus atributos próprios.

Quando um novo jogador vai para a fila de espera, sua inserção é feita pelo método `insert(player)`. Utilizando o atributo `size` - que rastreia a quantidade atual de jogadores ativos na fila - o sistema o coloca diretamente no final da fila. Dessa forma, o array não está necessariamente ordenado a todo momento. Para remover um jogador a partir do método `removePlayer(id)`, o sistema percorre todo o array buscando o id do jogador especificado, e, após encontrá-lo, remove-o da fila e move todos os outros elementos à direita do jogador removido uma posição à esquerda, garantindo que não fiquem "buracos" na memória. Caso o id não seja encontrado, a fila não é alterada.