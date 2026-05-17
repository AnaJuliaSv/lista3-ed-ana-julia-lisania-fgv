#include "Matchmaking.hpp"
#include <iomanip>

// Construtor
Matchmaking::Matchmaking(){
    this->size = 0;
}

// Destrutor
Matchmaking::~Matchmaking(){
    // Não há memória alocada dinamicamente
}


bool Matchmaking::insert(Player player){
    if(size <= MAX_PLAYERS){
        players[size] = player;
        size += 1;
        return true;
    }
    return false;
}


bool Matchmaking::removePlayer(int id){
    for (int p = 0; p < size; p++){
        if (players[p].getId() == id){
            // Movemos todos os elementos uma poisção à esquerda
            for(int i = p; i < (size - 1); i++){ 
                players[i] = players[i+1]; 
            }
            size -= 1;
            return true;
        }
    }
    return false;
}


void Matchmaking::move_player(Player player, int id_from, int id_to){
    // Movemos os elementos do fim do array até id_to para evitar acessos inválidos de memória
    // fora do array
    for (int i = id_from; i > id_to; i --){
        players[i] = players[i - 1];
    }

    players[id_to] = player;
}
   

void Matchmaking::sortByScoreInsertion(){
    // Começamos do segundo elemento, pois o primeiro está
    // naturalmente ordenado
    for (int e = 1; e < size; e++){
        Player current_e = players[e];

        // Ordenando o array em partes
        for (int i = 0; i < e; i++){

            if(players[i].getScore() > current_e.getScore()){
                move_player(current_e, e, i);
                break;

            // Caso dê empate no score
            } else if (players[i].getScore() == current_e.getScore()){
                if(players[i].getTimestamp() > current_e.getTimestamp()){
                    move_player(current_e, e, i);
                    break;
                }
            }
        }
    }
}


void Matchmaking::merge(int left, int mid, int right, Player* aux){
    // Recebe duas metades já ordenadas e une em um array ordenado

    int i = left; // Cursor da metade esquerda
    int j = mid + 1; // Cursor da metade direita
    int k = left; // Cursor do array auxiliar
    
    while((i <= mid) && (j <= right)){
        // Scores diferentes
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

        // Empate no score, desempata pelo timestamp
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
    // Caso base, listas de 1 elemento 
    if(left >= right){
        return;
    }

    // Chama o algoritmo de ordenação recursivamente
    int mid = (left + right)/2;
    merge_sort(left, mid, aux);
    merge_sort(mid + 1, right, aux);
    merge(left, mid, right, aux);
}

void Matchmaking::sortByScoreMerge(){
    Player* aux = new Player[MAX_PLAYERS];
    merge_sort(0, size -1, aux);
    delete[] aux;
}


Player* Matchmaking::formGroup(int groupSize, int delta, int* n){
    Player* group = new Player[groupSize];

    int i = 0;

    // Testa todos os grupos de tamanho groupSize possíveis
    while(i <= (size - groupSize)){
        if((players[i + groupSize - 1].getScore()) - players[i].getScore() <= delta){
            // Copia o grupo que obedece às restrições
            for(int j = 0; j < groupSize; j++){
                group[j] = players[i + j];
            }

            // Remove os jogadores do grupo deslocando o restante à esquerda
            for(int k = i; k < (size - groupSize); k++){
                players[k] = players[k + groupSize];
            }

            size -= groupSize;
            *n = groupSize;
            printFormedGroup(group, n);
            return group;
        }
        i += 1;
    }
    delete[] group;
    *n = 0;
    std::cout << "Nao foi possivel realizar a formacao de grupos.\n" << std::endl;
    return nullptr;
}


Player* Matchmaking::getWaitingPlayers(int* n){
    // Se não existir jogadores na lista de espera
    if (size == 0){
        // Se o ponteiro passado para a função existir
        if (n != nullptr) *n = 0;
        return nullptr;
    }
    
    // Caso contrário
    Player* players_copy = new Player[size];
    // Se o ponteiro passado para a função existir
    if (n != nullptr) *n = size;

    for (int p = 0; p < size; p++){
        players_copy[p] = players[p];
    }

    return players_copy;
}


void Matchmaking::printWaitingPlayers(){
    std::cout << "Waiting Players:" << std::endl;

    if(size == 0){
        std::cout << "(empty)" << std::endl;

    } else{ 
        // Printamos todas as informações de forma organizada para cada player   
        for (int p = 0; p < size; p++){
            Player player = players[p];
            std::cout << "[" << std::left << std::setw(2) << player.getId() << 
                " | " << std::left << std::setw(12) << player.getName()<< " | " 
                << std::left << std::setw(6) << player.getScore() << " | " 
                << std::left << std::setw(2) << player.getTimestamp() << "]" << std::endl;
        }
    }
}

void Matchmaking::printFormedGroup(Player* group, int* n){
    std::cout << "Group:" << std::endl;
   
    for (int p = 0; p < *n; p++){
        Player player = group[p];
        std::cout << "[" << std::left << std::setw(2) << player.getId() << 
            " | " << std::left << std::setw(12) << player.getName()<< " | " 
            << std::left << std::setw(6) << player.getScore() << " | " 
            << std::left << std::setw(2) << player.getTimestamp() << "]" << std::endl;
    }
}