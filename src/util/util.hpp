#ifndef UTIL_HPP
#define UTIL_HPP

namespace evo {
// Returns random float from 0.0 to 1.0.
float random_float();

// Returns random float from min to max.
// Works on both positive and negative values.
float random_float(float min, float max);

// Returns random int from min to max (inclusive on both).
// Works on both positive and negative values.
int random_int(int min, int max);
} // namespace evo

#endif // UTIL_HPP