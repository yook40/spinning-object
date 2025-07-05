#include "cube.h"
#include "donut.h"

int main(void) {
  int donut = 0;
  if (donut) {
    Donut d{16, 32};
    d.spin(0.02, 0.03, 0.01);
  } else {
    Cube c{37};
    c.spin(0.02, 0.03, 0.01);
  }
}
