#include "simulation/simulation.hpp"

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

int main() {
	evo::Simulation simulation(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2,
	                           SCREEN_WIDTH, SCREEN_HEIGHT);

	simulation.run();

	return 0;
}