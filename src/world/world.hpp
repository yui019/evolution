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
	Vector2 size;

	std::vector<evo::Creature> creatures;
	std::vector<evo::Plant> plants;

	uint64_t current_time = 0;

	World(float width, float height, float window_width, float window_height);

	void handle_mouse_left_pressed(std::optional<size_t> &selected_creature,
	                               Camera2D camera);
	void update(std::optional<size_t> &selected_creature);
	void draw() const;

	Vector2 mouse_coords(Camera2D camera) const;
};
} // namespace evo

#endif // WORLD_HPP