#include <cmath>
#include "donut.h"

const float pi = 3.1415926;

// r1: cross section radius
// r2: distance between cross section center and donut center

Donut::Donut(float r1, float r2): Object{r1 + r2} {
  for (float i = 0; i < 2 * pi; i += 0.003 * pi) { // i rotates cross section about y-axis
    for (float j = 0; j < 2 * pi; j += 0.02 * pi) { // j draws a cross section
      object.emplace_back((r2 + r1 * cos(j)) * cos(i), r1 * sin(j), (r2 + r1 * cos(j)) * sin(i),
      cos(j) * cos(i), sin(j), cos(j) * sin(i));
    }
  }
}

