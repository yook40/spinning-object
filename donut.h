#include "object.h"

extern const float pi;

class Donut: public Object {
  float r1; // cross section radius
  float r2; // distance between cross section center and donut center
  public:
  Donut(float, float);
};
