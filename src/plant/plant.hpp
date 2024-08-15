#ifndef PLANT_HPP
#define PLANT_HPP

#include "raylib.h"
#include <cstdint>

namespace evo {
const uint64_t PLANT_GROWING_TIME = 100;
const uint64_t PLANT_SIZE         = 20;

struct Plant {
	Vector2 position;

	// Whether the plant is grown or not
	bool grown;

	// Simulation time when the plant started growing (it starts growing
	// immediately after being eaten)
	uint64_t growing_start_time;

	static Plant random(Vector2 world_size);

	void eat(uint64_t current_time);

	// Whether or not the plant has finished growing.
	// Only call if grown is false
	bool finished_growing(uint64_t current_time);

	void draw(Vector2 offset) const;
};
} // namespace evo

#endif // PLANT_HPP