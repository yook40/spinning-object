class Donut extends Object {
  public Donut(float r1, float r2) {
    super(r1 + r2);
    for (float i = 0; i < 2 * Math.PI; i += 0.003 * Math.PI) { // i rotates cross section about y-axis
      for (float j = 0; j < 2 * Math.PI; j += 0.02 * Math.PI) { // j draws a cross section
        Coordinate c = new Coordinate((r2 + r1 * Math.cos(j)) * Math.cos(i), r1 * Math.sin(j), (r2 + r1 * Math.cos(j)) * Math.sin(i),
            Math.cos(j) * Math.cos(i), Math.sin(j), Math.cos(j) * Math.sin(i));
        object.add(c);
      }
    }
  }
}
