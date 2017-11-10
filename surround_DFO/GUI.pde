void initGUI() {
  cp5 = new ControlP5(this);
  noStroke();

  int start = 10;
  int spacing = 35;


  cp5.addSlider("DT")
    .setPosition(505, start)
    .setRange(0.001, 0.5)
    .setSize(100, 30)
    .setValue(DT);

  cp5.addSlider("number_of_tests")
    .setPosition(505, start+spacing)
    .setRange(1, 500)
    .setSize(100, 30)
    .setValue(number_of_tests);

  cp5.addSlider("population_size")
    .setPosition(505, start+2*spacing)
    .setRange(3, 200)
    .setSize(100, 30)
    .setValue(population_size);

  cp5.addToggle("torus")
    .setPosition(505, start+3*spacing)
    .setSize(50, 30)
    .setValue(torus)
    .setMode(ControlP5.SWITCH);

  cp5.addToggle("use_only_closest_neighbor")
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