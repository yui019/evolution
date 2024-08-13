#include "camera.hpp"
#include "raylib.h"
#include "raymath.h"

Camera2D evo::create_camera() {
	Camera2D camera;
	camera.zoom = 1.0f;

	return camera;
}

void evo::update_camera(Camera2D &camera) {
	// Translate based on mouse left click
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		Vector2 delta = GetMouseDelta();
		delta         = Vector2Scale(delta, -1.0f / camera.zoom);
		camera.target = Vector2Add(camera.target, delta);
	}

	float wheel = GetMouseWheelMove();
	if (wheel != 0) {
		Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

		camera.offset = GetMousePosition();

		camera.target = mouseWorldPos;

		float scaleFactor = 1.0f + (0.05f * fabsf(wheel));
		if (wheel < 0)
			scaleFactor = 1.0f / scaleFactor;

		camera.zoom = Clamp(camera.zoom * scaleFactor, 0.125f, 64.0f);
	}
}