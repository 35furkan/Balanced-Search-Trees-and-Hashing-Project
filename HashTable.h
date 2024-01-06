#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include <string>
#include "KmerNode.h"
class HashTable {
private:
    const int chainSize = 7;
    const int quadSize = 71;

    KmerNode** chainTable;
    KmerNode* quadraticTable;



public:
    HashTable();
    ~HashTable();

    int seperateChainHash(string kmer, int size);

    int quadraticProbingHash(string kmer, int size,
        int oldhashValue, KmerNode* curNode);

    void addKmer_chain(string kmer, int position);
    void fillHashTable_chain(string filename, int k);
    KmerNode* findKmer_chain(string kmer);
   
    void addKmer_quadratic(string kmer, int position);
    void fillHashTable_quadratic(string filename, int k);
    KmerNode* findKmer_quadratic(string kmer);
    void printAllChain();
    void printAllQuadratic();
    void go_to_positions(string inputFileName, int range, KmerNode* found);
};

#endif 

