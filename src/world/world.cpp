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

	// Initialize all creatures randomly
	for (size_t i = 0; i < WORLD_CREATURES_COUNT; ++i) {
		Creature creature = Creature::random(this->world_size);

		this->creatures.push_back(creature);
	}

	// Initialize all plants randomly
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

		// If the creature is on 0 energy or too old, it should die
		if (creature.lifetime >= CREATURE_MAX_LIFETIME ||
		    creature.energy <= 0.0f) {
			// Completely erase creature
			this->creatures.erase(this->creatures.begin() + i);

			// Update selected_creature now that the indices have changed
			if (selected_creature.has_value()) {
				if (*selected_creature == i) {
					selected_creature = std::nullopt;
				} else if (*selected_creature > i) {
					selected_creature = *selected_creature - 1;
				}
			}

			continue;
		}

		// If the creature is eating, check if it's finished amd mark the plant
		// as eaten if so
		if (creature.state == CreatureState::Eating) {
			if (!this->plants[creature.plant_index].grown) {
				// Update the creature state to Aimless if it's eating an
				// ungrown plant (this is here to handle the case of multiple
				// creatures eating the same plant)
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

		// If the creature is on full energy and old enough, it should
		// self-replicate (and lose some energy doing so)
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
		// If the plant has finished growing, move it to a random position
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

	// Draw a lightgray background behind the world so its limits are visible
	DrawRectangle(offset.x, offset.y, this->world_size.x, this->world_size.y,
	              RAYWHITE);

	for (auto plant : this->plants) {
		plant.draw(offset);
	}

	for (auto creature : this->creatures) {
		creature.draw(offset);
	}
}