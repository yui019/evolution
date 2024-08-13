#include "creature.hpp"
#include "raylib.h"
#include "raymath.h"
#include "src/plant/plant.hpp"
#include "src/util/util.hpp"
#include <cassert>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <optional>

evo::Creature evo::Creature::random(Vector2 world_size) {
	Creature creature;
	creature.state     = CreatureState::Aimless;
	creature.energy    = 1.0f;
	creature.lifetime  = 0;
	creature.direction = Vector2{0.0f, 0.0f};
	creature.position  = Vector2{
        evo::random_float(0.0f, world_size.x),
        evo::random_float(0.0f, world_size.y),
    };

	CreatureDna dna;
	dna.food_detection_radius = evo::random_float(100.0f, 1000.0f);
	dna.speed                 = evo::random_float(1.0f, 50.0f);

	creature.dna = dna;

	return creature;
}

evo::Creature evo::Creature::from_parent(Creature &parent,
                                         float mutation_probability) {
	assert(mutation_probability >= 0.0 && mutation_probability <= 1.0);

	Creature creature;
	creature.state     = CreatureState::Aimless;
	creature.energy    = 1.0f;
	creature.lifetime  = 0;
	creature.direction = Vector2{0.0f, 0.0f};
	creature.position  = parent.position;
	creature.dna       = parent.dna;

	float r_speed = evo::random_float();
	if (r_speed <= mutation_probability) {
		creature.dna.speed += evo::random_float(0.0f, 5.0f);
	}

	float r_food_detection_radius = evo::random_float();
	if (r_food_detection_radius <= mutation_probability) {
		creature.dna.food_detection_radius += evo::random_float(0.0f, 20.0f);
	}

	return creature;
}

void evo::Creature::update(u_int64_t current_time, Vector2 world_size,
                           std::vector<evo::Plant> &plants) {
	printf("Incrementing lifetime %zu", this->lifetime);
	this->lifetime += 1;
	printf(" -> %zu\n", this->lifetime);

	if (this->state != CreatureState::Eating) {
		Vector2 prev_pos = this->position;

		this->position.x += this->dna.speed * this->direction.x;
		this->position.y += this->dna.speed * this->direction.y;

		Vector2 current_pos = this->position;

		float distance = abs(Vector2DistanceSqr(prev_pos, current_pos));
		this->energy -= CREATURE_ENERGY_DROP_PER_DISTANCE_SQUARED * distance;

		if (this->position.x < 0) {
			this->position.x = 0;
			this->direction.x *= -1;
		}
		if (this->position.x > world_size.x) {
			this->position.x = world_size.x;
			this->direction.x *= -1;
		}
		if (this->position.y < 0) {
			this->position.y = 0;
			this->direction.y *= -1;
		}
		if (this->position.y > world_size.y) {
			this->position.y = world_size.y;
			this->direction.y *= -1;
		}
	}

	if (this->state == CreatureState::Aimless) {
		this->direction.x = evo::random_float(-1.0, 1.0);
		this->direction.y = evo::random_float(-1.0, 1.0);

		auto found_plant = this->_find_plant(plants);
		if (found_plant.has_value()) {
			Vector2 found_plant_pos = plants[*found_plant].position;

			this->plant_location = found_plant_pos;
			this->plant_index    = *found_plant;

			this->state = CreatureState::MovingTowardsPlant;

			this->direction = Vector2Normalize(
			    Vector2Subtract(found_plant_pos, this->position));
		}
	} else if (this->state == CreatureState::MovingTowardsPlant) {
		float distance =
		    Vector2DistanceSqr(this->plant_location, this->position);

		if (distance <= pow(CREATURE_EATING_DISTANCE, 2)) {
			this->state             = CreatureState::Eating;
			this->eating_start_time = current_time;
		}
	}
}

bool evo::Creature::finished_eating(uint64_t current_time) {
	assert(this->state == CreatureState::Eating);

	uint64_t elapsed = current_time - this->eating_start_time;

	return elapsed >= CREATURE_EATING_TIME;
}

void evo::Creature::draw(Vector2 offset) const {
	Color color = BLUE;

	if (this->state == CreatureState::Aimless) {
		color = RED;
	} else if (this->state == CreatureState::Eating) {
		color = ORANGE;
	}

	DrawRectangle(this->position.x - (int)(CREATURE_SIZE / 2) + offset.x,
	              this->position.y - (int)(CREATURE_SIZE / 2) + offset.y,
	              CREATURE_SIZE, CREATURE_SIZE, color);
}

bool evo::Creature::contains_point(Vector2 point) {
	return (this->position.x - (int)(PLANT_SIZE / 2) < point.x &&
	        this->position.x + (int)(PLANT_SIZE / 2) > point.x &&
	        this->position.y - (int)(PLANT_SIZE / 2) < point.y &&
	        this->position.y + (int)(PLANT_SIZE / 2) > point.y);
}

std::optional<size_t>
evo::Creature::_find_plant(std::vector<evo::Plant> &plants) {
	float found_plant_distance_squared = INT_MAX;
	size_t found_plant_index;

	bool plant_found = false;
	for (size_t i = 0; i < plants.size(); ++i) {
		evo::Plant plant = plants[i];

		if (!plant.grown) {
			continue;
		}

		float distance_squared = pow(this->position.x - plant.position.x, 2) +
		                         pow(this->position.y - plant.position.y, 2);

		if (distance_squared >= pow(this->dna.food_detection_radius, 2)) {
			continue;
		}

		if (distance_squared < found_plant_distance_squared) {
			plant_found = true;

			found_plant_distance_squared = distance_squared;
			found_plant_index            = i;
		}
	}

	if (plant_found) {
		return found_plant_index;
	} else {
		return std::nullopt;
	}
}