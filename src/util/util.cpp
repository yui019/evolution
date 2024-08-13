#include "util.hpp"
#include <cstdlib>

float evo::random_float() {
	return evo::random_float(0.0, 1.0);
}

float evo::random_float(float min, float max) {
	return min + rand() / (RAND_MAX / (max - min));
}

int evo::random_int(int min, int max) {
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}