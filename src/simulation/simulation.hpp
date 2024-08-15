#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "raylib.h"
#include "stats/stats.hpp"
#include "src/world/world.hpp"
#include <cstdint>

namespace evo {
class Simulation {
  private:
	World _world;
	std::optional<size_t> _selected_creature;
	bool _paused;
	Camera2D _camera;
	SimulationStats _stats;
	uint64_t _stats_last_measurement_time;

  public:
	uint32_t simulation_width;
	uint32_t simulation_height;
	uint32_t window_width;
	uint32_t window_height;

	Simulation(uint32_t simulation_width, uint32_t simulation_height,
	           uint32_t window_width, uint32_t window_height);

	~Simulation();

	void run();

	void update();
	void draw();

  private:
	Vector2 _mouse_coords() const;

	void _measure_stats();

	void _draw_ui_controls();
	void _draw_ui_selected_creature();
	void _draw_ui_stats();
};
} // namespace evo

#endif // SIMULATION_HPP