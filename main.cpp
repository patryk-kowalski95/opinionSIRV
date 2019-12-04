//============================================================================
// Name        : Simulation.cpp
// Author      : pk
// Version     :
// Copyright   : praca mgr, wydzia� Fizyki PW
//============================================================================

#include <iostream>
#include <random>
#include <ctime>
#include "Network.h"
#include "zerowanie.h"
#include "Simulation.h"
#include <string>


using namespace std;
void run(int size, double p, int cutoff, std::mt19937 mt, std::uniform_int_distribution<int> seeds,
		std::string filename_base, double p_, double q, double b, double z){

	std::uniform_int_distribution<int> neighbor_dist[18];

	std::string filename(filename_base + "b" + std::to_string(b) + "_z"+std::to_string(z)+"w1_r1");

	for(int i = 0; i < 18; i++){
		neighbor_dist[i] = std::uniform_int_distribution<int>(0,i+1);
	}
	for(unsigned int rep = 0; rep < 1; rep++){
		Network* sirv = new Network(size, p, mt);
		Network* opinion = new Network(size, p, mt);
			clock_t iter_begin = clock();
			Simulation* sim;
			int counter = 0;
			int days = 0;
			do {
				if (counter > 0) delete sim;
				if(counter > 50){
					delete sirv; delete opinion;
					sirv = new Network(size, p, mt);
					opinion = new Network(size, p, mt);
					std::cout<<"swapping networks"<<std::endl;
					counter = 1;
				}
				sim = new Simulation(b, z, p_, q, *sirv, *opinion, size, mt, neighbor_dist, filename);
				days = sim->iterate_until_end_of_epidemy();
				counter++;
			}
			while (sim->get_recovered_number() <= cutoff);

			delete sim;
			clock_t iter_end = clock();
			std::cout << "iteration time " << double(iter_end - iter_begin) / CLOCKS_PER_SEC << std::endl;

	}
}
int main() {
	void run(int size, double p, int cutoff, std::mt19937 mt, std::uniform_int_distribution<int> seeds,
			std::string filename_base, double p_, double q, double b, double z);

	int size = 100000;
	double p = (double)4/size;
	int cutoff = 30;
	std::mt19937 mt(time(0)); std::uniform_int_distribution<int> seeds(0, RAND_MAX);
	time_t begin = clock();
	run(size, p, cutoff, mt, seeds, std::string("var4_snap_"), (double)1/2, (double)1/2, 0.1, 0.7);
	run(size, p, cutoff, mt, seeds, std::string("var4_snap_"), (double)1/2, (double)1/2, 0.1, 0.8);
	run(size, p, cutoff, mt, seeds, std::string("var4_snap_"), (double)1/2, (double)1/2, 0.1, 0.9);
	run(size, p, cutoff, mt, seeds, std::string("var4_snap_"), (double)1/2, (double)1/2, 0.2, 0.7);
	run(size, p, cutoff, mt, seeds, std::string("var4_snap_"), (double)1/2, (double)1/2, 0.2, 0.8);
	run(size, p, cutoff, mt, seeds, std::string("var4_snap_"), (double)1/2, (double)1/2, 0.2, 0.9);

	time_t end = clock();
	double time_elapsed = double(end - begin)/CLOCKS_PER_SEC;
	std::cout<<"both iters "<<time_elapsed<<std::endl;
	return 0;
}


