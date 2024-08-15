#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "raylib.h"
#include "src/plant/plant.hpp"
#include <cstddef>
#include <optional>
#include <cstdint>
#include <vector>

namespace evo {
const float CREATURE_EATING_DISTANCE             = 50;
const uint64_t CREATURE_EATING_TIME              = 100;
const uint64_t CREATURE_SIZE                     = 20;
const float CREATURE_ENERGY_DROP_SPEED           = 0.00005;
const uint64_t CREATURE_MAX_LIFETIME             = 2000;
const uint64_t CREATURE_REPLICATION_MIN_LIFETIME = 100;
const float CREATURE_MUTATION_PROBABILITY        = 0.1f;

struct CreatureDna {
	float speed;
	float plant_detection_radius;
};

enum class CreatureState {
	Aimless,
	MovingTowardsPlant,
	Eating
};

struct Creature {
  public:
	CreatureDna dna;
	float energy; // From 0.0 to 1.0
	Vector2 position;
	Vector2 direction; // Always a normalized vector

	CreatureState state;
	Vector2 plant_location;     // used if state is MovingTowardsPlant
	size_t plant_index;         // used if state is MovingTowardsPlant
	uint64_t eating_start_time; // used if state is Eating

	// Amount of simulation time that's passed since the creature was created
	uint64_t lifetime;

	static Creature random(Vector2 world_size);

	// Only call with mutation_probability from 0.0 to 1.0
	static Creature from_parent(Creature &parent, float mutation_probability);

	void update(uint64_t current_time, Vector2 world_size,
	            std::vector<evo::Plant> &plants);

	void draw(Vector2 offset) const;

	// Whether or not the creature has finished eating.
	// Only call if state is Eating.
	bool finished_eating(uint64_t current_time);

	// Whether or not the creature contains a certain point
	bool contains_point(Vector2 point);

  private:
	// Try to find the nearest plant in the creature's plant_detection_radius
	std::optional<size_t> _find_plant(std::vector<evo::Plant> &plants);
};

} // namespace evo

#endif // CREATURE_HPP