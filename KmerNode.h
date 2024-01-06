#ifndef KmerNode_
#define KmerNode_
#include <string>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class KmerNode {
private:
	string kmer;
	
	KmerNode* next;
	
public:
	KmerNode* getNext();
	vector<int> positions;
	KmerNode();
	void setNext(KmerNode* obj);
	KmerNode(string kmer, int position);
	void addPosition(int position);
	string getKmer();
	void setKmer(string kmer);
};
#endif
