#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "raylib.h"
#include "src/plant/plant.hpp"
#include <cstddef>
#include <optional>
#include <cstdint>
#include <vector>

namespace evo {
const float CREATURE_EATING_DISTANCE                  = 50;
const uint64_t CREATURE_EATING_TIME                   = 100;
const uint64_t CREATURE_SIZE                          = 20;
const float CREATURE_ENERGY_DROP_PER_DISTANCE_SQUARED = 0.0001;
const uint64_t CREATURE_MAX_LIFETIME                  = 2000;
const uint64_t CREATURE_REPLICATION_MIN_LIFETIME      = 100;
const float CREATURE_MUTATION_PROBABILITY             = 0.1f;

struct CreatureDna {
	float speed;
	float food_detection_radius;
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
	uint64_t lifetime;

	static Creature random(Vector2 world_size);

	// mutation_probability is from 0.0 to 1.0
	static Creature from_parent(Creature &parent, float mutation_probability);

	void update(uint64_t current_time, Vector2 world_size,
	            std::vector<evo::Plant> &plants);
	void draw(Vector2 offset) const;

	// Only call if current state is Eating
	bool finished_eating(uint64_t current_time);

	bool contains_point(Vector2 point);

  private:
	std::optional<size_t> _find_plant(std::vector<evo::Plant> &plants);
};

} // namespace evo

#endif // CREATURE_HPP