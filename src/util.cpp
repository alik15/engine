#include "util.hpp"

float ResolveVelocity2D(float v1, float v2, float m1, float m2, float e) {
  return ((m1 - e * m2) * v1 + (1 + e) * m2 * v2) / (m1 + m2);
};