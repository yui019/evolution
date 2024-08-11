#include "rlImGui.h"
#include "imgui.h"
#include "raylib.h"
#include "camera/camera.hpp"

#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080

int main() {
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Evolution");
	ToggleFullscreen();

	rlImGuiSetup(true);

	auto camera = evo::create_camera();

	while (!WindowShouldClose()) {
		evo::update_camera(camera);

		BeginDrawing();
		{
			ClearBackground(WHITE);

			BeginMode2D(camera);
			{
				DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 50,
				           MAROON);
			}
			EndMode2D();

			rlImGuiBegin();
			{ ImGui::ShowDemoWindow(); }
			rlImGuiEnd();

			DrawFPS(10, 10);
		}
		EndDrawing();
	}

	rlImGuiShutdown();
	CloseWindow();
	return 0;
}