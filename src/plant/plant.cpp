#include "plant.hpp"
#include "raylib.h"
#include "src/util/util.hpp"
#include <cassert>
#include <cstdint>

evo::Plant evo::Plant::random(Vector2 world_size) {
	Plant plant;
	plant.grown              = true;
	plant.growing_start_time = 0;
	plant.position           = Vector2{
        evo::random_float(0.0f, world_size.x),
        evo::random_float(0.0f, world_size.y),
    };

	return plant;
}

void evo::Plant::eat(uint64_t current_time) {
	this->grown              = false;
	this->growing_start_time = current_time;
}

bool evo::Plant::finished_growing(uint64_t current_time) {
	assert(this->grown == false);

	uint64_t elapsed = current_time - this->growing_start_time;

	return elapsed >= PLANT_GROWING_TIME;
}

void evo::Plant::draw(Vector2 offset) const {
	Color color = this->grown ? GREEN : BLACK;

	DrawRectangle(this->position.x - (int)(PLANT_SIZE / 2) + offset.x,
	              this->position.y - (int)(PLANT_SIZE / 2) + offset.y,
	              PLANT_SIZE, PLANT_SIZE, color);
}