#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"

namespace evo {
Camera2D create_camera();
void update_camera(Camera2D &camera);
}; // namespace evo

#endif // CAMERA_H
