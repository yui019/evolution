#include "world.hpp"
#include "raylib.h"
#include "src/creature/creature.hpp"
#include "src/util/util.hpp"
#include <climits>
#include <cstddef>
#include <cstdio>
#include <optional>
#include <vector>

evo::World::World(float width, float height, float window_width,
                  float window_height) {
	this->world_size  = Vector2{width, height};
	this->window_size = Vector2{window_width, window_height};

	for (size_t i = 0; i < WORLD_CREATURES_COUNT; ++i) {
		Creature creature = Creature::random(this->world_size);

		this->creatures.push_back(creature);
	}

	this->plants.reserve(WORLD_PLANTS_COUNT);
	for (size_t i = 0; i < WORLD_PLANTS_COUNT; ++i) {
		Plant plant = Plant::random(this->world_size);

		this->plants.push_back(plant);
	}
}

void evo::World::update(std::optional<size_t> &selected_creature) {
	this->current_time++;

	size_t i = 0;
	for (Creature &creature : this->creatures) {
		creature.update(this->current_time, this->world_size, this->plants);

		if (creature.lifetime >= CREATURE_MAX_LIFETIME ||
		    creature.energy <= 0.0f) {
			this->creatures.erase(this->creatures.begin() + i);

			if (selected_creature.has_value()) {
				if (*selected_creature == i) {
					selected_creature = std::nullopt;
				} else if (*selected_creature > i) {
					selected_creature = *selected_creature - 1;
				}
			}

			continue;
		}

		if (creature.state == CreatureState::Eating) {
			if (!this->plants[creature.plant_index].grown) {
				creature.state = CreatureState::Aimless;
			} else {
				if (creature.finished_eating(this->current_time)) {
					size_t plant_index = creature.plant_index;
					creature.state     = CreatureState::Aimless;
					creature.energy    = 1.0f;

					this->plants[plant_index].eat(this->current_time);
				}
			}
		}

		if (creature.energy == 1.0f) {
			if (creature.lifetime >= CREATURE_REPLICATION_MIN_LIFETIME) {
				Creature child = Creature::from_parent(
				    creature, CREATURE_MUTATION_PROBABILITY);

				this->creatures.push_back(child);
				creature.energy = 0.5f;
			}
		}

		i++;
	}

	for (auto &plant : this->plants) {
		if (!plant.grown && plant.finished_growing(this->current_time)) {
			plant.position = Vector2{
			    evo::random_float(0.0f, this->world_size.x),
			    evo::random_float(0.0f, this->world_size.y),
			};
			plant.grown = true;
		}
	}
}

void evo::World::draw() const {
	Vector2 offset = Vector2{-(this->world_size.x - this->window_size.x) / 2,
	                         -(this->world_size.y - this->window_size.y) / 2};

	DrawRectangle(offset.x, offset.y, this->world_size.x, this->world_size.y,
	              RAYWHITE);

	for (auto plant : this->plants) {
		plant.draw(offset);
	}

	for (auto creature : this->creatures) {
		creature.draw(offset);
	}
}

Vector2 evo::World::mouse_coords(Camera2D camera) const {
	Vector2 offset = Vector2{(this->world_size.x - this->window_size.x) / 2,
	                         (this->world_size.y - this->window_size.y) / 2};

	Vector2 coords = GetMousePosition();

	Vector2 result = GetScreenToWorld2D(
	    Vector2{
	        coords.x,
	        coords.y,
	    },
	    camera);

	result.x += offset.x;
	result.y += offset.y;

	printf("MOUSE POSITION: %f, %f\n", result.x, result.y);

	return result;
}