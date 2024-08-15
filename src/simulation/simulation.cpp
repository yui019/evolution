#include "simulation.hpp"
#include "imgui.h"
#include "implot.h"
#include "src/camera/camera.hpp"
#include "raylib.h"
#include "rlImGui.h"
#include "src/simulation/stats/stats.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <ctime>
#include <cstdlib>

evo::Simulation::Simulation(uint32_t simulation_width,
                            uint32_t simulation_height, uint32_t window_width,
                            uint32_t window_height)
    : _world(simulation_width, simulation_height, window_width, window_height),
      simulation_width(simulation_width), simulation_height(simulation_height),
      window_width(window_width), window_height(window_height) {

	this->_selected_creature           = std::nullopt;
	this->_paused                      = false;
	this->_stats_last_measurement_time = 0;
	this->_stats_stride                = 0;
	this->_stats_shown                 = false;

	this->_camera = evo::create_camera();

	srand(time(0));
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(window_width, window_height, "Evolution");

	rlImGuiSetup(true);
	ImPlot::CreateContext();
}

evo::Simulation::~Simulation() {
	ImPlot::DestroyContext();
	rlImGuiShutdown();
	CloseWindow();
}

void evo::Simulation::run() {
	while (!WindowShouldClose()) {
		this->update();
		this->draw();
	}
}

void evo::Simulation::update() {
	ImGuiIO &io = ImGui::GetIO();

	// Measure stats
	uint64_t measurement_elapsed =
	    this->_world.current_time - this->_stats_last_measurement_time;
	if (this->_world.current_time == 0 ||
	    measurement_elapsed >= SIMULATION_STATS_MEASUREMENT_PERIOD) {
		this->_measure_stats();
	}

	// Handle mouse click
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !io.WantCaptureMouse) {
		Vector2 mouse_coords = this->_mouse_coords();

		// If the click was inside a creature, mark it as selected
		for (size_t i = 0; i < this->_world.creatures.size(); ++i) {
			Creature &creature = this->_world.creatures[i];

			if (creature.contains_point(mouse_coords)) {
				this->_selected_creature = i;
				break;
			}
		}
	}

	if (!io.WantCaptureMouse) {
		evo::update_camera(this->_camera);
	}

	// Only update if not paused
	if (!this->_paused) {
		this->_world.update(this->_selected_creature);
	}
}

void evo::Simulation::draw() {
	BeginDrawing();
	{
		ClearBackground(WHITE);

		BeginMode2D(this->_camera);
		this->_world.draw();
		EndMode2D();

		rlImGuiBegin();
		{
			this->_draw_ui_controls();
			this->_draw_ui_selected_creature();
			this->_draw_ui_stats();
		}
		rlImGuiEnd();

		DrawFPS(10, 10);
	}
	EndDrawing();
}

Vector2 evo::Simulation::_mouse_coords() const {
	// This offset is needed because the world is drawn in the center of the
	// screen when the simulation starts
	Vector2 offset =
	    Vector2{(float)(this->simulation_width - this->window_width) / 2.0f,
	            (float)(this->simulation_height - this->window_height) / 2.0f};

	// Get screen coordinates of the mouse
	Vector2 coords = GetMousePosition();

	// Get world coordinates
	Vector2 result = GetScreenToWorld2D(
	    Vector2{
	        coords.x,
	        coords.y,
	    },
	    this->_camera);

	// Apply offset to the world coordinates
	result.x += offset.x;
	result.y += offset.y;

	return result;
}

void evo::Simulation::_measure_stats() {
	size_t number_of_creatures = this->_world.creatures.size();
	this->_stats.number_of_creatures.push_back(number_of_creatures);

	float speed_sum  = 0.0;
	int speed_count  = 0;
	float radius_sum = 0.0;
	int radius_count = 0;
	for (Creature &creature : this->_world.creatures) {
		speed_sum += creature.dna.speed;
		radius_sum += creature.dna.plant_detection_radius;

		speed_count++;
		radius_count++;
	}

	float average_speed  = speed_sum / speed_count;
	float average_radius = radius_sum / radius_count;

	this->_stats.average_speed.push_back(average_speed);
	this->_stats.average_plant_detection_radius.push_back(average_radius);
}