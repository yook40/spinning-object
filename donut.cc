#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

const float n = 10; // depth / distance_from_screen

const float pi = 3.14;

const float v = 200; // distance_between_viewer_and_screen

string luminance = ".,-~:;=!*#$@";

const int light_source[3] = {0, 0, -1};

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

class Donut {
  vector<Coordinates> donut;
  int r1; // cross section radius
  int r2; // distance between cross section center and donut center
  public:
  Donut(int, int);
  void spin(float, float, float);
};

Donut::Donut(int r1, int r2): r1{r1}, r2{r2} {
  for (float i = 0; i < 2 * pi; i += 0.01 * pi) {
    for (float j = 0; j < 2 * pi; j += 0.01 * pi) {
      // divide each component of surface normal by len to make sure the normal vector is length 1
      donut.emplace_back((r2 + r1 * cos(j)) * cos(i), r1 * sin(j), (r2 + r1 * cos(j)) * sin(i),
      cos(j) * cos(i), sin(j), cos(j) * sin(i));
    }
  }
}

void Donut::spin(float x, float y, float z) {
  while (1) {
    float zbuffer[50][218];
    char display[50][218];
    // initialize display and z-buffer
    for (int j = 0; j < 50; j++) {
      for (int i = 0; i < 218; i++) {
        display[j][i] = ' ';
        zbuffer[j][i] = 0;
      }
    }
    // compute the position on the screen
    for (auto &pixel:donut) {
      int horizontal = 109 + round(pixel.x * v / (pixel.z + n + v + r2 + r1));
      int vertical = 25 - round(pixel.y * v / (pixel.z + n + v + r2 + r1) / 2.09);
      // divide by the ratio of height and width of a character in the terminal so it looks like a cube

      // compute luminance
      float lum = pixel.norm_x * light_source[0] + pixel.norm_y * light_source[1] + pixel.norm_z * light_source[2];
      if (lum >= 0) {
        // only show pixels that are in the display range and points towards the viewer
        int lum_index = lum * (luminance.length() - 1) / sqrt(light_source[0] * light_source[0] + light_source[1] * light_source[1] +
                        light_source[2] * light_source[2]);
        if (horizontal <= 217 && horizontal >= 0 && vertical >= 0 && vertical <= 49) {
          if (!zbuffer[vertical][horizontal]) {
            zbuffer[vertical][horizontal] = pixel.z;
            display[vertical][horizontal] = luminance[lum_index];
          } else if (zbuffer[vertical][horizontal] > pixel.z) {
            zbuffer[vertical][horizontal] = pixel.z;
            display[vertical][horizontal] = luminance[lum_index];
          }
        }
      }
    }
    cout << "\x1b[H";
    for (int i = 0; i < 50; i++) {
      for (int j = 0; j < 218; j++) {
        cout << display[i][j];
      }
      cout << endl;
    }
    // compute and store the accurate coordinates of each pixel with type float
    for (auto &pixel:donut) {
      float old_x = pixel.x;
      float old_y = pixel.y;
      float old_z = pixel.z;
      float old_norm_x = pixel.norm_x;
      float old_norm_y = pixel.norm_y;
      float old_norm_z = pixel.norm_z;

      // rotation about y-axis:
      pixel.x = old_x * cos(x) - old_z * sin(x);
      pixel.norm_x = old_norm_x * cos(x) - old_norm_z * sin(x);
      pixel.z = old_x * sin(x) + old_z * cos(x);
      pixel.norm_z = old_norm_x * sin(x) + old_norm_z * cos(x);

      // rotation about z-axis:
      old_x = pixel.x;
      old_norm_x = pixel.norm_x;
      old_y = pixel.y;
      old_norm_y = pixel.norm_y;
      pixel.x = old_x * cos(y) - old_y * sin(y);
      pixel.norm_x = old_norm_x * cos(y) - old_norm_y * sin(y);
      pixel.y = old_x * sin(y) + old_y * cos(y);
      pixel.norm_y = old_norm_x * sin(y) + old_norm_y * cos(y);

      // rotation about x-axis:
      old_y = pixel.y;
      old_norm_y = pixel.norm_y;
      old_z = pixel.z;
      old_norm_z = pixel.norm_z;
      pixel.y = old_y * cos(z) - old_z * sin(z);
      pixel.norm_y = old_norm_y * cos(z) - old_norm_z * sin(z);
      pixel.z = old_y * sin(z) + old_z * cos(z);
      pixel.norm_z = old_norm_y * sin(z) + old_norm_z * cos(z);
    }
  }
}

int main(void) {
  Donut d{20, 40};
  d.spin(0, 0, 0.01);
}
