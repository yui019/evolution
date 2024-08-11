#include "rlImGui.h"
#include "imgui.h"
#include "raylib.h"

#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080

int main() {
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Evolution");
	ToggleFullscreen();

	rlImGuiSetup(true);

	while (!WindowShouldClose()) {
		BeginDrawing();
		{
			ClearBackground(WHITE);

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