class GUI {
  ControlP5 gui;
  //int 

    void init() {
    gui = new ControlP5(sketch);
    noStroke();

    int start = 10;
    int spacing = 35;


    gui.addSlider("DT")
      .setPosition(505, start)
      .setRange(0.001, 0.5)
      .setSize(100, 30)
      .setValue(gDT);

    gui.addSlider("population_size")
      .setPosition(505, start+2*spacing)
      .setRange(3, 200)
      .setSize(100, 30)
      .setValue(population_size);

    gui.addToggle("torus")
      .setPosition(505, start+3*spacing)
      .setSize(50, 30)
      .setValue(torus)
      .setMode(ControlP5.SWITCH);

    gui.addToggle("use_only_closest_neighbor")
      .setPosition(565, start+3*spacing)
      .setSize(50, 30)
      .setValue(use_only_closest_neighbor)
      .setMode(ControlP5.SWITCH);
  }

  void drawText() {
    fill(255);

    text("Press SPACE to re-initialize population,", 505, 170, 240, 200);
    text("'a' to scatter,", 505, 320, 240, 200);
    text("1-4 to change image.", 505, 380, 240, 200);
  }
}