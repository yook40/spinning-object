#include "cube.h"

// constructor initializes coordinates of all surface pixels
Cube::Cube(float radius): Object{radius} {
  for (float i = -radius; i <= radius; i += 0.5f) {
    for (float j = -radius; j <= radius; j += 0.5f) {
      object.emplace_back(j, i, -radius, 0, 0, -1); // front
      object.emplace_back(j, i, radius, 0, 0, 1);   // back
      object.emplace_back(j, radius, i, 0, 1, 0); // top
      object.emplace_back(j, -radius, i, 0, -1, 0); // bottom
      object.emplace_back(-radius, j, i, -1, 0, 0); // left
      object.emplace_back(radius, j, i, 1, 0, 0); // right
    }
  }
}
