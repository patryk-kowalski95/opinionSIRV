#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <random>
#include <vector>
#include "Network.h"
#include <ctime>


class Simulation {
public:
	Simulation(double b, double w, double p, double q, Network& sirv, Network& opinion, int size);
	virtual ~Simulation();
	void print_feature_arrays();
	void print_groups();
	void iterate_sirv();
	void iterate_opinion();
	void print_state_counts();
	void print_opinion_counts();
	void print_for_charts(char* filename);

private:
    std::mt19937 mt;
	std::uniform_real_distribution<double> infection_dist;
	int dying_period = 6;
	double b; // bheta getting sick coefficient
	double w; // omega vax efficiency coefficient
	double p; // extremization coefficient;
	double q; // moderation coefficient
	double r; //personality ratio
	Network& sirv;
	Network& opinion;
	int size;
	int* sick_time;
	int* opinions;
	char* states;
	std::vector<int> vaxxers;

	void init_states();
	void init_opinions();
	void update_vaxxers();
	void vaccinate();
	void die(int i);
	void get_sick(int i);
	void infection_trial(int i);
	bool can_interact(int agent_opinion, int neighbor_index);
	void interact(int agent_index, int agent_opinion, int neighbor_opinion);

};

#endif /* SIMULATION_H_ */
