#include "Matchmaking.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <string>

// Gera um sistema de matchmaking com n jogadores aleatórios
void generateMatchmaking(Matchmaking& m, int n) {
    for (int i = 0; i < n; i++) {
        int score = rand() % 10000;
        Player p(i, "Player" + std::to_string(i), score, i);
        m.insert(p);
    }
}

int main() { 
    // Tamanhos de entrada: de 50 até 100000
    int sizes[] = {50, 100, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    std::ofstream file("benchmark.csv");
    file << "tamanho,insertion_sort_ms,merge_sort_ms\n";

    std::cout << "tamanho | insertion_sort (ms) | merge_sort (ms)" << std::endl;
    std::cout << "--------|---------------------|----------------" << std::endl;

    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];

        // Aloca no heap — evita stack overflow
        Matchmaking* m1 = new Matchmaking();
        Matchmaking* m2 = new Matchmaking();

        srand(42);
        generateMatchmaking(*m1, n);

        // Mede o tempo para o Insertion
        auto start1 = std::chrono::high_resolution_clock::now();
        m1->sortByScoreInsertion();
        auto end1 = std::chrono::high_resolution_clock::now();
        double time_insertion = std::chrono::duration<double, std::milli>(end1 - start1).count();
        
        // Reinicia a seed para garantir geração de mesmos jogadores para m1 e m2
        srand(42);
        generateMatchmaking(*m2, n);

        // Mede o tempo para o Merge
        auto start2 = std::chrono::high_resolution_clock::now();
        m2->sortByScoreMerge();
        auto end2 = std::chrono::high_resolution_clock::now();
        double time_merge = std::chrono::duration<double, std::milli>(end2 - start2).count();

        std::cout << n << " | " << time_insertion << " | " << time_merge << std::endl;
        file << n << "," << time_insertion << "," << time_merge << "\n";

        delete m1;
        delete m2;
    }
    file.close();
    std::cout << "\nResultados salvos em benchmark.csv" << std::endl;
    return 0;
}