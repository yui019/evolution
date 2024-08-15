#include "../simulation.hpp"
#include "imgui.h"
#include "implot.h"
#include <climits>

void evo::Simulation::_draw_ui_stats() {
	if (!this->_stats_shown) {
		return;
	}

	ImGui::Begin("Statistics over time");

	ImGui::DragInt("Stride", &this->_stats_stride, sizeof(float));

	ImGui::Separator();

	if (ImPlot::BeginPlot("##stats", ImVec2(-1, -1), ImPlotFlags_NoTitle)) {
		ImPlot::PlotLine("Number of creatures",
		                 this->_stats.number_of_creatures.data(),
		                 this->_stats.number_of_creatures.size(), 1, 0, 0, 0,
		                 this->_stats_stride);

		ImPlot::PlotLine("Average speed", this->_stats.average_speed.data(),
		                 this->_stats.average_speed.size(), 1, 0, 0, 0,
		                 this->_stats_stride);

		ImPlot::PlotLine("Average plant detection radius",
		                 this->_stats.average_plant_detection_radius.data(),
		                 this->_stats.average_plant_detection_radius.size(), 1,
		                 0, 0, 0, this->_stats_stride);

		ImPlot::EndPlot();
	}

	ImGui::End();
}