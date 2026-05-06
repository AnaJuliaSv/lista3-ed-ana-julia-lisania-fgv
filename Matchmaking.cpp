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
