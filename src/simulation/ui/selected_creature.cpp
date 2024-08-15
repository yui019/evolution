#include "../simulation.hpp"
#include "imgui.h"

void evo::Simulation::_draw_ui_selected_creature() {
	if (this->_selected_creature.has_value()) {
		ImGui::Begin("Selected creature");

		evo::Creature creature =
		    this->_world.creatures[*this->_selected_creature];

		ImGui::Text("Position: (%f, %f)", creature.position.x,
		            creature.position.y);

		ImGui::Text("Direction: (%f, %f)", creature.direction.x,
		            creature.direction.y);

		ImGui::Text("Energy: %f", creature.energy);

		ImGui::Text("Lifetime: %zu", creature.lifetime);

		ImGui::End();
	}
}