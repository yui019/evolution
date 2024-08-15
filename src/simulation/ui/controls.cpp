#include "../simulation.hpp"
#include "imgui.h"

void evo::Simulation::_draw_ui_controls() {
	ImGui::Begin("Controls");

	ImGui::Text("Creatures: %zu", this->_world.creatures.size());

	ImGui::Separator();

	if (ImGui::Button(this->_paused ? "Play" : "Pause")) {
		this->_paused = !this->_paused;
	}

	ImGui::Separator();

	ImGui::Checkbox("Show stats", &this->_stats_shown);

	ImGui::End();
}