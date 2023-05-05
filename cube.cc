#include <iostream>
#include <vector>
#include <unistd.h>
#include <cmath>
using namespace std;

struct Coordinates {
  float x;
  float y;
  float z;
  char c;
  Coordinates(float x, float y, float z, char c): x{x}, y{y}, z{z}, c{c} {}
};

class Cube {
	vector<Coordinates> cube[6];
  float distance_from_screen; // depth
  float radius; // half edge length
  float distance_between_viewer_and_screen;
	public:
		Cube(float, float, float);
		void spin(float, float, float);
};

void Cube::spin(float x, float y, float z) {
  float n = distance_from_screen;
  float r = radius;
  float v = distance_between_viewer_and_screen;
  while (1) {
    float zbuffer[33][144];
    char display[33][144];
    for (int j = 0; j < 33; j++) {
      for (int i = 0; i < 144; i++) {
        display[j][i] = ' ';
        zbuffer[j][i] = 0;
      }
    }
    int face_area = (2 * r + 1) * (2 * r + 1);
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < face_area; j++) {
        int horizontal = 72 + round(cube[i].at(j).x * v / (cube[i].at(j).z + n + r + v));
        int vertical = 16 - round(cube[i].at(j).y * v / (cube[i].at(j).z + n + r + v) / 2);
        if (!zbuffer[vertical][horizontal]) {
          zbuffer[vertical][horizontal] = cube[i].at(j).z;
          display[vertical][horizontal] = cube[i].at(j).c;
        } else if (zbuffer[vertical][horizontal] > cube[i].at(j).z) {
          zbuffer[vertical][horizontal] = cube[i].at(j).z;
          display[vertical][horizontal] = cube[i].at(j).c;
        }
      }
    }
    cout << "\x1b[H";
    for (int i = 0; i < 33; i++) {
      for (int j = 0; j < 144; j++) {
        cout << display[i][j];
      }
      cout << endl;
    }
    // compute and store the accurate coordinates of each pixel with type float
    for (int i = 0; i < face_area; i++) {
      for (int j = 0; j < 6; j++) {
        float old_x = cube[j].at(i).x;
        float old_y = cube[j].at(i).y;
        float old_z = cube[j].at(i).z;

        // rotation about y-axis:
        cube[j].at(i).x = old_x * cos(x) - old_z * sin(x);
        cube[j].at(i).z = old_x * sin(x) + old_z * cos(x);

        // rotation about z-axis:
        old_x = cube[j].at(i).x;
        old_y = cube[j].at(i).y;
        cube[j].at(i).x = old_x * cos(y) - old_y * sin(y);
        cube[j].at(i).y = old_x * sin(y) + old_y * cos(y);

        // rotation about x-axis:
        old_y = cube[j].at(i).y;
        old_z = cube[j].at(i).z;
        cube[j].at(i).y = old_y * cos(z) - old_z * sin(z);
        cube[j].at(i).z = old_y * sin(z) + old_z * cos(z);
      }
    }
    usleep(30000);
  }
}

Cube::Cube(float n, float r, float v):
  distance_from_screen{n}, radius{r}, distance_between_viewer_and_screen{v} {
  // constructor initializes coordinates of all surface pixels
  // assign each face a char so no need for luminance
  for (float i = -r; i <= r; i++) { // i and j must range from -r to r
    for (float j = -r; j <= r; j++) {
      cube[0].emplace_back(Coordinates{j, i, -r, '='}); // front
    }
    for (float j = -r; j <= r; j++) {
      cube[1].emplace_back(Coordinates{j, i, r, '+'}); // back
    }
    for (float j = -r; j <= r; j++) {
      cube[2].emplace_back(Coordinates{j, r, i, '!'}); // top
    }
    for (float j = -r; j <= r; j++) {
      cube[3].emplace_back(Coordinates{j, -r, i, '/'}); // bottom
    }
    for (float j = -r; j <= r; j++) {
      cube[4].emplace_back(Coordinates{-r, j, i, '-'}); // left
    }
    for (float j = -r; j <= r; j++) {
      cube[5].emplace_back(Coordinates{r, j, i, '~'}); // right
    }
  }
}

int main(void) {
  float pi = 3.1415926;
  Cube c{40, 40, 20};
  c.spin(-pi / 40, pi / 20, pi / 30);
}
