#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include <vector>
#include "coordinates.h"

extern const float n; // depth / distance_from_screen

extern const float v; // distance_between_viewer_and_screen

extern const std::string luminance;

extern const int light_source[3];

class Object {
  protected:
  std::vector<Coordinates> object;
  float r; // radius
  public:
  Object(float r);
  void spin(float x, float y, float z);
};
#endif