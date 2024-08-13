#include "rlImGui.h"
#include "imgui.h"
#include "raylib.h"
#include "camera/camera.hpp"
#include "src/creature/creature.hpp"
#include "src/world/world.hpp"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <optional>

// #define SCREEN_WIDTH  1920
// #define SCREEN_HEIGHT 1080
#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

int main() {
	srand(time(0));
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Evolution");
	SetTargetFPS(60);
	// ToggleFullscreen();

	rlImGuiSetup(true);

	evo::World world(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SCREEN_WIDTH,
	                 SCREEN_HEIGHT);

	auto camera = evo::create_camera();

	std::optional<size_t> selected_creature = std::nullopt;

	bool paused = false;

	while (!WindowShouldClose()) {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			world.handle_mouse_left_pressed(selected_creature, camera);
		}

		evo::update_camera(camera);

		if (!paused) {
			world.update(selected_creature);
		}

		BeginDrawing();
		{
			ClearBackground(WHITE);

			BeginMode2D(camera);
			world.draw();
			EndMode2D();

			rlImGuiBegin();
			{
				ImGui::Begin("Controls");
				{
					ImGui::Text("Creatures: %zu", world.creatures.size());
					ImGui::Separator();

					if (ImGui::Button(paused ? "Play" : "Pause")) {
						paused = !paused;
					}
				}
				ImGui::End();

				ImGui::Begin("Selected creature");
				{
					if (selected_creature.has_value()) {
						evo::Creature creature =
						    world.creatures[*selected_creature];

						ImGui::Text("Position: (%f, %f)", creature.position.x,
						            creature.position.y);

						ImGui::Text("Direction: (%f, %f)", creature.direction.x,
						            creature.direction.y);

						ImGui::Text("Energy: %f", creature.energy);

						ImGui::Text("Lifetime: %zu", creature.lifetime);
					}
				}
				ImGui::End();
			}
			rlImGuiEnd();

			DrawFPS(10, 10);
		}
		EndDrawing();
	}

	rlImGuiShutdown();
	CloseWindow();
	return 0;
}