#ifndef PLANT_HPP
#define PLANT_HPP

#include "raylib.h"
#include <cstdint>

namespace evo {
const uint64_t PLANT_GROWING_TIME = 300;
const uint64_t PLANT_SIZE         = 50;

struct Plant {
	Vector2 position;
	bool grown;
	uint64_t growing_start_time;

	static Plant random(Vector2 world_size);

	void eat(uint64_t current_time);

	// Only call if grown is false
	bool finished_growing(uint64_t current_time);

	void draw(Vector2 offset) const;
};
} // namespace evo

#endif // PLANT_HPP