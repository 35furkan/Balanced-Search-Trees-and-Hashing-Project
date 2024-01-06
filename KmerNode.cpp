#include <string>
#include "KmerNode.h"
using namespace std;
KmerNode::KmerNode(string kmer, int position) {
    this->kmer = kmer;
    positions.push_back(position);
    next = nullptr;
}
void KmerNode::addPosition(int position) {
    positions.push_back(position);
}
string KmerNode::getKmer()
{
    return kmer;
}
void KmerNode::setKmer(string kmer)
{
    this->kmer = kmer;
}
KmerNode::KmerNode() {
    next = nullptr;
}
void KmerNode::setNext(KmerNode* obj) {
    this->next = obj;
}
KmerNode* KmerNode::getNext() {
    return next;
}

