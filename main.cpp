/**
* Title: Hash Tables
* Author: Emre Furkan Akyol
* ID: 22103352
* Section:1
* Homework: 4
* Description: main.cpp includes timer and tests of all functions
*/
#include <iostream>
#include <fstream>
#include <chrono>
#include "HashTable.h" 
using namespace std;
int main(int argc, char* argv[]) {
    
    HashTable* separateChainingTable = new HashTable();
    HashTable* quadraticProbingTable= new HashTable();

    string filename = argv[2];
    int kSize = stoi(argv[1]);
    separateChainingTable->fillHashTable_chain(filename, kSize);
    quadraticProbingTable->fillHashTable_quadratic(filename, kSize);

    string targetKmer = "fuz"; 

    
    auto startSeparateChaining = chrono::high_resolution_clock::now();
    KmerNode* foundSeparateChaining = separateChainingTable->findKmer_chain(targetKmer);
    auto endSeparateChaining = chrono::high_resolution_clock::now();
    if (foundSeparateChaining) {
        cout << "K-mer found using separate chaining.\n";
    }
    else {
        cout << "K-mer not found using separate chaining.\n";
    }
    chrono::duration<double> timeSeparateChaining = endSeparateChaining - startSeparateChaining;
    cout << "Time taken for retrieval using separate chaining: " << timeSeparateChaining.count() << " seconds.\n";

    
    auto startQuadraticProbing = chrono::high_resolution_clock::now();
    KmerNode* foundQuadraticProbing = quadraticProbingTable->findKmer_quadratic(targetKmer);
    auto endQuadraticProbing = chrono::high_resolution_clock::now();
    if (foundQuadraticProbing) {
        cout << "K-mer found using quadratic probing.\n";
    }
    else {
        cout << "K-mer not found using quadratic probing.\n";
    }
    chrono::duration<double> timeQuadraticProbing = endQuadraticProbing - startQuadraticProbing;
    cout << "Time taken for retrieval using quadratic probing: " << timeQuadraticProbing.count() << " seconds.\n";
    separateChainingTable->printAllChain();
    KmerNode* temp = separateChainingTable->findKmer_chain("xwh");
    separateChainingTable->go_to_positions(filename, 5, temp);
    quadraticProbingTable->printAllQuadratic();
    KmerNode* temp2 = quadraticProbingTable->findKmer_quadratic("xwh");
    quadraticProbingTable->go_to_positions(filename, 5, temp2);
    return 0;
}
