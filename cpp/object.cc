#include <iostream>
#include <cmath>
#include "object.h"
using namespace std;

const float n = 4; // depth / distance_from_screen

const float v = 200; // distance_between_viewer_and_screen

const string luminance = ".,-~:;=!*#$@"; // from dimmest to brightest

const int light_source[3] = {0, 1, -1};

Object::Object(float r): r{r} {}

void Object::spin(float a, float b, float c) {
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
    for (auto &pixel:object) {
      int horizontal = 109 + round(pixel.x * v / (pixel.z + n + v + r));
      int vertical = 25 - round(pixel.y * v / (pixel.z + n + v + r) / 2.09);
      // divide by the ratio of height to width of a character in the terminal so the object does not get stretched

      // compute luminance
      float lum = pixel.norm_x * light_source[0] + pixel.norm_y * light_source[1] + pixel.norm_z * light_source[2];

      if (lum >= 0) {
        // only show pixels that are in the display range and points towards the viewer
        int lum_index = round(lum * (luminance.length() - 1) / sqrt(light_source[0] * light_source[0] +
                        light_source[1] * light_source[1] + light_source[2] * light_source[2]));
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

    // compute and store the accurate coordinates and the surface normal of each
    // pixel after rotation with type float
    for (auto &pixel:object) {
      float old_x = pixel.x;
      float old_norm_x = pixel.norm_x;
      // rotation about y-axis:
      pixel.x = old_x * cos(a) - pixel.z * sin(a);
      pixel.z = old_x * sin(a) + pixel.z * cos(a);
      pixel.norm_x = old_norm_x * cos(a) - pixel.norm_z * sin(a);
      pixel.norm_z = old_norm_x * sin(a) + pixel.norm_z * cos(a);

      old_x = pixel.x;
      old_norm_x = pixel.norm_x;
      // rotation about z-axis:
      pixel.x = old_x * cos(b) - pixel.y * sin(b);
      pixel.y = old_x * sin(b) + pixel.y * cos(b);
      pixel.norm_x = old_norm_x * cos(b) - pixel.norm_y * sin(b);
      pixel.norm_y = old_norm_x * sin(b) + pixel.norm_y * cos(b);

      float old_y = pixel.y;
      float old_norm_y = pixel.norm_y;
      // rotation about x-axis:
      pixel.y = old_y * cos(c) - pixel.z * sin(c);
      pixel.z = old_y * sin(c) + pixel.z * cos(c);
      pixel.norm_y = old_norm_y * cos(c) - pixel.norm_z * sin(c);
      pixel.norm_z = old_norm_y * sin(c) + pixel.norm_z * cos(c);
    }
  }
}
