#ifndef NETWORK_H_
#define NETWORK_H_
#include <random>
#include <vector>
#include <unordered_set>

class Network {
public:
	Network(int size, double p);
	virtual ~Network();
	void print_all_links();



private:
	int n_of_links;
	int size;
	std::unordered_set<int>* net;
	int* k;
	int* l_seg;
	double p;
    std::mt19937_64 mt;
	std::uniform_int_distribution<int> dist;
	void draw_links();
	bool insert_link(std::pair<std::unordered_set<int>::iterator,bool> ret);
};

#endif /* NETWORK_H_ */
