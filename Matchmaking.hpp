#ifndef MATCHMAKING_HPP
#define MATCHMAKING_HPP

#include "Player.hpp"

const int MAX_PLAYERS = 100000;

class Matchmaking {

private:

    Player players[MAX_PLAYERS];
    int size;

public:

    Matchmaking();
    ~Matchmaking();

    bool insert(Player player);
    bool removePlayer(int id);

    void sortByScoreInsertion();
    void sortByScoreMerge();

    Player* formGroup(int groupSize, int delta, int* n);
    Player* getWaitingPlayers(int* n);

    void printWaitingPlayers();

    // Funções auxiliares para o insertion
    void move_player(Player player, int id_from, int id_to);

    // Funções auxiliares para merge
    void merge(int left, int mid, int right, Player* aux);
    void merge_sort(int left, int right, Player* aux);
};

#endif