#include "Player.hpp"

// construtor padrão
Player::Player() {
    this->id = 0;
    this->name = "";
    this->score = 0;
    this->timestamp = 0;
}

// construtor com argumentos específicos
Player::Player(int id, std::string name, int score, int timestamp){
    this->id = id;
    this->name = name;
    this->score = score;
    this->timestamp = timestamp;
}

// destrutor
Player::~Player(){
    // não há memória alocada dinamicamente
}