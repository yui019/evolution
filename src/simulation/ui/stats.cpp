#include "../simulation.hpp"
#include "imgui.h"
#include "implot.h"
#include <climits>

void evo::Simulation::_draw_ui_stats() {
	ImGui::Begin("Statistics over time");

	if (ImPlot::BeginPlot("##stats", ImVec2(-1, -1), ImPlotFlags_NoTitle)) {
		ImPlot::PlotLine("Number of creatures",
		                 this->_stats.number_of_creatures.data(),
		                 this->_stats.number_of_creatures.size());

		ImPlot::PlotLine("Average speed", this->_stats.average_speed.data(),
		                 this->_stats.average_speed.size());

		ImPlot::PlotLine("Average plant detection radius",
		                 this->_stats.average_plant_detection_radius.data(),
		                 this->_stats.average_plant_detection_radius.size());

		ImPlot::EndPlot();
	}

	ImGui::End();
}