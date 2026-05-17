#include <iostream>
#include "Matchmaking.hpp"
#include "Player.hpp"
#include <iomanip>
using namespace std;


void printSeparator(const string& title) {
    cout << "\n========================================" << endl;
    cout << " " << title << endl;
    cout << "========================================\n" << endl;
};

void printGroup(Player* group, int* n){
    std::cout << "Group:" << std::endl;
   
    for (int p = 0; p < *n; p++){
        Player player = group[p];
        std::cout << "[" << std::left << std::setw(2) << player.getId() << 
            " | " << std::left << std::setw(12) << player.getName()<< " | " 
            << std::left << std::setw(6) << player.getScore() << " | " 
            << std::left << std::setw(2) << player.getTimestamp() << "]" << std::endl;
    }
}


int main(void){
    Matchmaking* matchmaking = new Matchmaking();   
    
    // Criação de jogadores
    Player player_1 = Player(1, "Ana Julia", 1400, 1);
    Player player_2 = Player(2, "Lisania", 1307, 2);
    Player player_3 = Player(3, "Roberta", 1150, 3);
    Player player_4 = Player(4, "Alaerte", 1000, 4);
    Player player_5 = Player(5, "Joao", 1000, 1);
    Player player_6 = Player(6, "Joao Victor", 1300, 2);
    Player player_7 = Player(7, "Larissa", 900, 8);
    Player player_8 = Player(8, "Maria Julia", 600, 10);
    Player player_9 = Player(9, "Bianca", 1100, 9);
    Player player_10 = Player(10, "Andre", 1050, 11);

    // 1. Inserção dos Jogadores
    printSeparator("Insercao de Jogadores");

    matchmaking->insert(player_1);
    matchmaking->insert(player_2);
    matchmaking->insert(player_3);
    matchmaking->insert(player_4);
    matchmaking->insert(player_5);
    matchmaking->insert(player_6);
    matchmaking->insert(player_7);
    matchmaking->insert(player_8);
    matchmaking->insert(player_9);
    matchmaking->insert(player_10);

    matchmaking->printWaitingPlayers();


    // 2. Remoção de Jogadores
    printSeparator("Remocao de Jogadores");

    matchmaking->removePlayer(7);
    matchmaking->removePlayer(3);
    matchmaking->removePlayer(8);
 
    matchmaking->printWaitingPlayers();


    // 3. Ordenação com Insertion Sort
    printSeparator("Ordenacao com Insertion Sort");

    matchmaking->sortByScoreInsertion();
    matchmaking->printWaitingPlayers();
 
    Player player_11 = Player(11, "Cleo", 1100, 12);
    matchmaking->insert(player_11);


    // 4. Ordenação com Merge Sort
    printSeparator("Ordenacao com Merge Sort");

    cout << "Antes da Ordenacao:\n" << endl;
    matchmaking->printWaitingPlayers();

    // Ordenação com empate de Score
    cout << "\nDepois da ordenacao:\n" << endl;
    matchmaking->sortByScoreMerge();
    matchmaking->printWaitingPlayers();


    // 5. Formação bem-sucedida de grupo
    printSeparator("Formacao de Grupo (bem sucedida)");
    int n_1 = 0;
    Player* group_1 = matchmaking->formGroup(3, 50, &n_1);

    if(group_1 != nullptr){
        printGroup(group_1, &n_1);
        delete[] group_1;
    }


    // 6. Formação de grupo sem sucesso
    printSeparator("Formacao de Grupo (sem sucesso)");
    int n_2 = 0;
    Player* group_2 = matchmaking->formGroup(3, 30, &n_2);

    if(group_2 != nullptr){
        printGroup(group_2, &n_2);
        delete[] group_2;
    }


    // 7. Recuperação dos dados
    printSeparator("Recuperacao dos dados");
    int n = 0;
    Player* actual_players = matchmaking->getWaitingPlayers(&n);

    cout << "Atualmente temos " << n << " jogadores.\n" << endl;
    delete[] actual_players;


    // 8. Exibição do estado do sistema
    printSeparator("Exibicao do Estado do Sistema");

    matchmaking->printWaitingPlayers();
    cout << "\n" << endl;

    delete matchmaking;
    return 0;
}