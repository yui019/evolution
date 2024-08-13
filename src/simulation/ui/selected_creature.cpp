#include "../simulation.hpp"
#include "imgui.h"

void evo::Simulation::_draw_ui_selected_creature() {
	ImGui::Begin("Selected creature");

	if (this->_selected_creature.has_value()) {
		evo::Creature creature =
		    this->_world.creatures[*this->_selected_creature];

		ImGui::Text("Position: (%f, %f)", creature.position.x,
		            creature.position.y);

		ImGui::Text("Direction: (%f, %f)", creature.direction.x,
		            creature.direction.y);

		ImGui::Text("Energy: %f", creature.energy);

		ImGui::Text("Lifetime: %zu", creature.lifetime);
	}

	ImGui::End();
}