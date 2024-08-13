#ifndef WORLD_HPP
#define WORLD_HPP

#include "raylib.h"
#include "src/creature/creature.hpp"
#include <vector>

namespace evo {
const uint32_t WORLD_CREATURES_COUNT = 100;
const uint32_t WORLD_PLANTS_COUNT    = 400;

class World {
  public:
	Vector2 window_size;
	Vector2 world_size;

	std::vector<evo::Creature> creatures;
	std::vector<evo::Plant> plants;

	uint64_t current_time = 0;

	World(float width, float height, float window_width, float window_height);

	void update(std::optional<size_t> &selected_creature);
	void draw() const;
};
} // namespace evo

#endif // WORLD_HPP