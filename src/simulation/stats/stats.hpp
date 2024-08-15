#ifndef SIMULATION_STATS_HPP
#define SIMULATION_STATS_HPP

#include <cstdint>
#include <vector>

namespace evo {
const uint32_t SIMULATION_STATS_MEASUREMENT_PERIOD = 1000;

// These are all stats gathered every SIMULATION_STATS_MEASUREMENT_PERIOD frames
struct SimulationStats {
	std::vector<float> number_of_creatures;
	std::vector<float> average_speed;
	std::vector<float> average_plant_detection_radius;
};
} // namespace evo

#endif // SIMULATION_STATS_HPP