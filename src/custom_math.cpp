#include "./custom_math.hpp"

float bezier_blend(float x) {
  return x * x * (3.0f - 2.0f * x);
}

float sigmoid(float x) {
  return 1.0f / (1.0f + std::exp(-x));
}

float parametric_blend(float x) {
  float sqr = x * x;
  return sqr / (2.0f * (sqr - x) + 1.0f);
}
