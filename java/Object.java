import java.util.ArrayList;

class Const {
  static final float n = 4.0f; // depth / distance_from_screen

  static final float v = 200.0f; // distance between viewer and screen

  static final char[] luminance = {'.', ',', '-', '~', ':', ';', '=', '!', '*', '#', '$', '@'}; // from darkest to brightest

  static final int[] LightSource = {0, 0, -1};
}

class Object {
  protected ArrayList<Coordinate> object = new ArrayList<Coordinate>();
  protected float r;
  public Object(float r) { this.r = r; }
  public void spin(float x, float y, float z) {
    while (true) {
      final double[][] ZBuffer = new double[50][218];
      final char[][] display = new char[50][218];
      for (int j = 0; j < 50; j++) {
        for (int i = 0; i < 218; i++) {
          display[j][i] = ' ';
        }
      }
      for (Coordinate pixel : object) {
        int horizontal = 109 + (int) Math.round(pixel.x * Const.v / (pixel.z + Const.n + Const.v + r));
        int vertical = 25 - (int) Math.round(pixel.y * Const.v / (pixel.z + Const.n + Const.v + r) / 2.09);
        // divide by the ratio of height to width of a character in the terminal so the object does not get stretched

        // compute luminance
        double lum = pixel.norm_x * Const.LightSource[0] + pixel.norm_y * Const.LightSource[1] + pixel.norm_z * Const.LightSource[2];

        if (lum >= 0) {
          // only show pixels that are in the display range and points towards the viewer
          int lum_index = (int) Math.round(lum * (Const.luminance.length - 1) / Math.sqrt(Const.LightSource[0] * Const.LightSource[0] +
                          Const.LightSource[1] * Const.LightSource[1] + Const.LightSource[2] * Const.LightSource[2]));
          if (horizontal <= 217 && horizontal >= 0 && vertical >= 0 && vertical <= 49) {
            if (ZBuffer[vertical][horizontal] == 0) {
              ZBuffer[vertical][horizontal] = pixel.z;
              display[vertical][horizontal] = Const.luminance[lum_index];
            } else if (ZBuffer[vertical][horizontal] > pixel.z) {
              ZBuffer[vertical][horizontal] = pixel.z;
              display[vertical][horizontal] = Const.luminance[lum_index];
            }
          }
        }
      }
      System.out.print("\u001b[H");
      for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 218; j++) {
          System.out.print(display[i][j]);
        }
        System.out.print("\n");
      }

      // compute and store the accurate coordinates and the surface normal of each
      // pixel after rotation with type float
      for (Coordinate pixel : object) {
        double old_x = pixel.x;
        double old_norm_x = pixel.norm_x;
        // rotation about y-axis:
        pixel.x = old_x * Math.cos(x) - pixel.z * Math.sin(x);
        pixel.z = old_x * Math.sin(x) + pixel.z * Math.cos(x);
        pixel.norm_x = old_norm_x * Math.cos(x) - pixel.norm_z * Math.sin(x);
        pixel.norm_z = old_norm_x * Math.sin(x) + pixel.norm_z * Math.cos(x);

        old_x = pixel.x;
        old_norm_x = pixel.norm_x;
        // rotation about z-axis:
        pixel.x = old_x * Math.cos(y) - pixel.y * Math.sin(y);
        pixel.y = old_x * Math.sin(y) + pixel.y * Math.cos(y);
        pixel.norm_x = old_norm_x * Math.cos(y) - pixel.norm_y * Math.sin(y);
        pixel.norm_y = old_norm_x * Math.sin(y) + pixel.norm_y * Math.cos(y);

        double old_y = pixel.y;
        double old_norm_y = pixel.norm_y;
        // rotation about x-axis:
        pixel.y = old_y * Math.cos(z) - pixel.z * Math.sin(z);
        pixel.z = old_y * Math.sin(z) + pixel.z * Math.cos(z);
        pixel.norm_y = old_norm_y * Math.cos(z) - pixel.norm_z * Math.sin(z);
        pixel.norm_z = old_norm_y * Math.sin(z) + pixel.norm_z * Math.cos(z);
      }
    }
  }
}

