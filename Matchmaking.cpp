#include "Matchmaking.hpp"

// construtor
Matchmaking::Matchmaking(){
    // players já é inicializado pelo instanciamento de Matchmaking()
    this->size = 0; // size equivale ao número atual de jogadores? Ou é o índice?
}

// destrutor
Matchmaking::~Matchmaking(){
    // não há memória alocada dinamicamente
}


bool Matchmaking::insert(Player player){
    if(size != MAX_PLAYERS){
        // optei por size ser o número de jogadores atuais por pura tradução
        // como o índice do último cara é size - 1, o novo cara tem que estar no size
        players[size] = player;
        size += 1;
        return true;
    }
    
    return false;
}

// bool RemovePlayer(int id)
   // implementação


// void sortByScoreInsertion()
   // implementação


// funções auxiliares para merge

void Matchmaking::merge(int left, int mid, int right, Player* aux){
    // recebe duas metades já ordenadas
    // devemos ir comparando do início de cada array

    int i = left; // índice para percorrer a metade esquerda
    int j = mid + 1; // índice para percorrer a metade direita

    // a cada passo comparo players[i] com players[j] e copia o menor para o auxiliar 
    // aí avança o cursor de quem foi copiado

    int k = left; // índice do array auxiliar de players
    
    while((i <= mid) && (j <= right)){

        // scores diferentes
        if(players[i].getScore() < players[j].getScore()){
            aux[k] = players[i];
            i += 1;
            k += 1;
        }

        else if(players[i].getScore() > players[j].getScore()){
            aux[k] = players[j];
            j += 1;
            k += 1;
        }

        // scores iguais, compara timestamp
        else{
            if(players[i].getTimestamp() < players[j].getTimestamp()){
                aux[k] = players[i];
                i += 1;
                k += 1;
            }
            else{
                aux[k] = players[j];
                j += 1;
                k += 1;
            }
        }
    }

    while(i <= mid){
        aux[k] = players[i];
        k += 1;
        i += 1;
    }

    while(j <= right){
        aux[k] = players[j];
        k += 1;
        j += 1;
    }

    for(int p = left; p <= right; p++){
        players[p] = aux[p];
    }
}

void Matchmaking::merge_sort(int left, int right, Player* aux){
    // calcula o meio
    // ordena a parte esquerda
    // ordena a parte direita
    // junta as partes ordenadas

    // caso base, quando as listas consideradas tem exatamente 1 elemento 
    if(left >= right){
        return;
    }

    int mid = (left + right)/2;
    merge_sort(left, mid, aux);
    merge_sort(mid + 1, right, aux);
    merge(left, mid, right, aux);
}

void Matchmaking::sortByScoreMerge(){
    // responsável apenas por chamar os auxiliares
    Player* aux = new Player[MAX_PLAYERS];
    merge_sort(0, size -1, aux);
    delete[] aux;
}


Player* Matchmaking::formGroup(int groupSize, int delta, int* n){
    // ordena os jogadores com o sort (aqui ou fora?)
    // parte do princípio que tá ordenado
    // testa para todos os grupos de tamanho groupSize possíveis 
    // pega o score do primeiro (menor) e compara com o do último (maior)
    // se maior_score - menor_score <= delta:
        // copia do jogador de maior_score até o jogador de menor_score
        // remove da lista inicial players sobrescrevendo 
    // se não der certo então o método deve indicar que não foi possível

    // grupo que eu vou retornar
    Player* group = new Player[groupSize];

    int i = 0;

    // testa todos os grupos de tamanho groupSize possíveis
    while(i <= (size - groupSize)){
        if((players[i + groupSize - 1].getScore()) - players[i].getScore() <= delta){
            // copia os jogadores para o retorno
            for(int j = 0; j < groupSize; j++){
                group[j] = players[i + j];
            }

            // k < (size - groupSize) porque o novo players tem (size - groupSize) elementos
            // como é sempre cópia de elementos da esquerda não perco informação nem mexo nos iniciais
            for(int k = i; k < (size - groupSize); k++){
                players[k] = players[k + groupSize];
            }
            size -= groupSize;
            *n = groupSize;
            return group;
        }
        i += 1;
    }

    // se chegou aqui é por que não deu certo, não retornou nada ainda    
    delete[] group;
    *n = 0;
    std::cout << "Não foi possível realizar a formação de grupos" << std::endl;
    return nullptr;
}


