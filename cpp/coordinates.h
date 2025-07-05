struct Coordinates {
  float x;
  float y;
  float z;
  float norm_x;
  float norm_y;
  float norm_z;
  Coordinates(float x, float y, float z, float a, float b, float c):
  x{x}, y{y}, z{z}, norm_x{a}, norm_y{b}, norm_z{c} {}
};
