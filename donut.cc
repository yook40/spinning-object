#include <cmath>
#include "donut.h"

const float pi = 3.1415926;

Donut::Donut(float r1, float r2): Object{r1 + r2}, r1{r1}, r2{r2} {
  for (float i = 0; i < 2 * pi; i += 0.01 * pi) {
    for (float j = 0; j < 2 * pi; j += 0.01 * pi) {
      // divide each component of surface normal by len to make sure the normal vector is length 1
      object.emplace_back((r2 + r1 * cos(j)) * cos(i), r1 * sin(j), (r2 + r1 * cos(j)) * sin(i),
      cos(j) * cos(i), sin(j), cos(j) * sin(i));
    }
  }
}
