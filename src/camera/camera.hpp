#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "raylib.h"

namespace evo {
Camera2D create_camera();
void update_camera(Camera2D &camera);
} // namespace evo

#endif // CAMERA_HPP
