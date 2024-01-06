#include "HashTable.h"


HashTable::HashTable() {
    chainTable = new KmerNode*[chainSize];
    quadraticTable = new KmerNode[quadSize];
    for (int i = 0; i < chainSize; ++i) {
        chainTable[i] = nullptr;
    }
}

HashTable::~HashTable() {
    delete[] quadraticTable;
    for (int i = 0; i < chainSize; i++) {
        KmerNode* cur = chainTable[i];
        while (cur->getNext() != nullptr) {
            KmerNode* cur2 = cur->getNext();
            cur->setNext(cur2->getNext());
            delete cur2;
            cur = cur->getNext();
        }
        cur->setNext(nullptr);
        
    }
    delete[] chainTable;
}

int HashTable::seperateChainHash(string kmer, int size) {
    int hashValue = 0;
    for (char& c : kmer) {
        c = tolower(c); // Convert each character to lowercase
    }
    
    for (char c : kmer) {
        hashValue += static_cast<int>(c);
    }
    hashValue = hashValue % size;
    return hashValue;

}
int HashTable::quadraticProbingHash(string kmer, int size,int oldhashValue , KmerNode* curNode) {
    int newHashValue = oldhashValue;
    for (int i = 0; i < size; i++) {
        newHashValue = (oldhashValue + i * i) % size;
        if (quadraticTable[newHashValue].getKmer() == "") { // no collision
            break;
        }
    }
    return newHashValue;

}

void HashTable::addKmer_chain(string kmer, int position) {
    for (char& c : kmer) {
        c = tolower(c); // Convert each character to lowercase
    }
    int hashVal = seperateChainHash(kmer, chainSize);

    KmerNode* kmerObj = new KmerNode(kmer, position);
    KmerNode* tmpNode = nullptr;
    if (chainTable[hashVal]==nullptr) { // no collision
        chainTable[hashVal] = kmerObj;
    }
    else {
        KmerNode* node = chainTable[hashVal];
        while (node!=nullptr) {    //collision case
            
            if (node->getKmer() == kmer) { //collision with same object
                node->addPosition(position);
                return;
            }
            if (node->getNext() == nullptr) {
                 tmpNode = node;
               
            }
            node = node->getNext();
        }
        tmpNode->setNext(kmerObj);// collision with non same object which adds the new node to the end of the linked list
    }
}


void HashTable::fillHashTable_chain(string filename, int k) {
    ifstream file(filename);
    string text;

    if (file.is_open()) {
        // Read the entire text as a single string
        string fullText((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

        for (int i = 0; i <= fullText.length() - k; i=i+k) {
            string kmer = fullText.substr(i, k);
            addKmer_chain(kmer, i);
        }

        file.close();
    }
    else {
        cout << "Unable to open file." << endl;
    }
}


KmerNode* HashTable::findKmer_chain(string kmer)
{
    for (char& c : kmer) {
        c = tolower(c); // Convert each character to lowercase
    }
    int hashValue = seperateChainHash(kmer, chainSize);

   /*for (list<KmerNode*>::iterator i = chainTable[hashValue].begin(); i != chainTable[hashValue].end(); ++i) {    //collision case
        KmerNode* node = *i;
        if (node->getKmer() == kmer) {
            return node;
        }
    }*/
    KmerNode* node = chainTable[hashValue];
   
    while (node != nullptr) {    //collision case

        if (node->getKmer() == kmer) { //collision with same object
            return node;
        }
        node = node->getNext();
    }
    return nullptr;
}

void HashTable::addKmer_quadratic(string kmer, int position)
{
    for (char& c : kmer) {
        c = tolower(c); // Convert each character to lowercase
    }
    int hashValue = seperateChainHash(kmer, quadSize);

    
    KmerNode* kmerObj = new KmerNode(kmer, position);
    if (quadraticTable[hashValue].getKmer() == "") { // no collision
       
        quadraticTable[hashValue] = *kmerObj;
    }
    else if (kmerObj->getKmer() == quadraticTable[hashValue].getKmer()) {  //Collision but same kmer
        quadraticTable[hashValue].addPosition(position);
        return;
    }
    else { //Collision but not same kmer

        int newHashValue = hashValue;
        int count = 0;
        while (newHashValue == hashValue && count < quadSize) {
            count++;
            newHashValue = quadraticProbingHash(kmer, quadSize, hashValue, kmerObj);
        }
        if (quadraticTable[newHashValue].getKmer() == "") { // Ensure an empty slot
            quadraticTable[newHashValue] = *kmerObj;  // adds the new node 
        }
        else if (kmerObj->getKmer() == quadraticTable[newHashValue].getKmer()) {
            quadraticTable[newHashValue].addPosition(position);
            return;
        }
    }
}
void HashTable::fillHashTable_quadratic(string filename, int k) {
    ifstream file(filename);
    string text;

    if (file.is_open()) {
        // Read the entire text as a single string
        string fullText((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

        for (int i = 0; i <= fullText.length() - k; i = i + k) {
            string kmer = fullText.substr(i, k);
            addKmer_quadratic(kmer, i);
        }

        file.close();
    }
    else {
        cout << "Unable to open file." << endl;
    }
}

KmerNode* HashTable::findKmer_quadratic(string kmer) {
    for (char& c : kmer) {
        c = tolower(c); // Convert each character to lowercase
    }
    int hashValue = seperateChainHash(kmer, quadSize);

    for (int count = 0; count < quadSize; count++) {
        int newHashValue = (hashValue + count * count) % quadSize;
        if (quadraticTable[newHashValue].getKmer() == "") {
            break; 
        }
        if (quadraticTable[newHashValue].getKmer() != "") {
            if (quadraticTable[newHashValue].getKmer() == kmer) {
                return &quadraticTable[newHashValue]; //looking at kmers
            }
             
        }
    }

    return nullptr; // Kmer not found
}



void HashTable::printAllChain() {
    for (int i = 0; i < chainSize; ++i) {
        KmerNode* node = chainTable[i];
        while (node != nullptr) {
            cout << node->getKmer() << " (";
            for (int k = 0; k < node->positions.size(); ++k) {
                cout << node->positions[k] << ",";
            }
            cout << ")" << endl;
            node = node->getNext();
        }
    }
}
void HashTable::printAllQuadratic()
{
    for (int i = 0; i < quadSize; i++) {
        KmerNode  node = quadraticTable[i];
        if (node.getKmer() != "") {
            cout << node.getKmer() << " (";
            for (int k = 0; k < node.positions.size(); k++) {
                cout << node.positions[k] << ",";

            }
            cout << ")" << endl;
        }
    }
}

void HashTable::go_to_positions(string inputFileName, int range, KmerNode* found)
{
    ifstream file(inputFileName);

    if (file.is_open()) {
        string text;
        string fullText;

        // Read the entire file into a single string
        while (getline(file, text)) {
            fullText += text;
        }
        if (found != nullptr) {
            for (int pos : found->positions) {
                int start = pos;
                int end = pos + found->getKmer().length() + range;

                string excerpt = fullText.substr(start, end - start);
                cout << excerpt << " (Generated From Position: " << start << " )" << endl;
            }
            file.close();
        }
        file.close();
    }
    else {
        cout << "Unable to open file." << endl;
    }
}

