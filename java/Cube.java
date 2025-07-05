// constructor initializes coordinates of all surface pixels
class Cube extends Object {
  public Cube(float r) {
    super(r);
    for (double i = -r; i <= r; ++i) { // i and j must range from -r to r
      for (double j = -r; j <= r; ++j) {
        Coordinate c = new Coordinate(j, i, -r, 0, 0, -1); // front
        object.add(c);
      }
      for (double j = -r; j <= r; ++j) {
        Coordinate c = new Coordinate(j, i, r, 0, 0, 1); // back
        object.add(c);
      }
      for (double j = -r; j <= r; ++j) {
        Coordinate c = new Coordinate(j, r, i, 0, 1, 0); // top
        object.add(c);
      }
      for (double j = -r; j <= r; ++j) {
        Coordinate c = new Coordinate(j, -r, i, 0, -1, 0); // bottom
        object.add(c);
      }
      for (double j = -r; j <= r; ++j) {
        Coordinate c = new Coordinate(-r, j, i, -1, 0, 0); // left
        object.add(c);
      }
      for (double j = -r; j <= r; ++j) {
        Coordinate c = new Coordinate(r, j, i, 1, 0, 0); // right
        object.add(c);
      }
    }
  }
}
