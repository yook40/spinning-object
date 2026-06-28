#include <cmath>
#include "donut.h"

const float pi = 3.1415926;

// r1: cross section radius
// r2: distance between cross section center and donut center

Donut::Donut(float r1, float r2): Object{r1 + r2} {
  for (float i = 0; i < 2 * pi; i += 0.003 * pi) { // i rotates cross section about y-axis
    for (float j = 0; j < 2 * pi; j += 0.02 * pi) { // j draws a cross section
      float x = (r2 + r1 * cos(j)) * cos(i);
      float y = r1 * sin(j);
      float z = (r2 + r1 * cos(j)) * sin(i);
      float normX = cos(j) * cos(i);
      float normY = sin(j);
      float normZ = cos(j) * sin(i);
      object.emplace_back(x, y, z, normX, normY, normZ);
    }
  }
}

