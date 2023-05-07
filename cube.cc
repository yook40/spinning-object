#include "cube.h"

// constructor initializes coordinates of all surface pixels
Cube::Cube(float r): Object{r} {
  for (float i = -r; i <= r; i++) { // i and j must range from -r to r
    for (float j = -r; j <= r; j++) {
      object.emplace_back(j, i, -r, 0, 0, -1); // front
    }
    for (float j = -r; j <= r; j++) {
      object.emplace_back(j, i, r, 0, 0, 1); // back
    }
    for (float j = -r; j <= r; j++) {
      object.emplace_back(j, r, i, 0, 1, 0); // top
    }
    for (float j = -r; j <= r; j++) {
      object.emplace_back(j, -r, i, 0, -1, 0); // bottom
    }
    for (float j = -r; j <= r; j++) {
      object.emplace_back(-r, j, i, -1, 0, 0); // left
    }
    for (float j = -r; j <= r; j++) {
      object.emplace_back(r, j, i, 1, 0, 0); // right
    }
  }
}
