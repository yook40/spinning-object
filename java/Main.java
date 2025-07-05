
public class Main {
  public static void main(String[] args) {
    boolean donut = false;
    if (donut) {
      Donut d = new Donut(16, 32);
      d.spin(0.02f, 0.03f, 0.01f);
    } else {
      Cube c = new Cube(36);
      c.spin(0.02f, 0.03f, 0.01f);
    }
  }
}

