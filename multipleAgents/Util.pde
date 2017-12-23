/////////////////////////////////////////////////
void drawBackground() {
  background(51);
  translate(width/2, height/2);
  float r = radius;
  int n = 6;

  for (int i = 0; i < n; i++) {
    float a = (TWO_PI)*i/n;
    float x = r * cos(a);
    float y = r * sin(a);

    fill(255, 0, 0, 180);
    ellipse(x, y, 50, 50);
  }

  float a = gGoal[0]*TWO_PI;
  float x = r * cos(a);
  float y = r * sin(a);

  fill(255, 200, 205, 150);
  ellipse(x, y, 90, 90);
}

/////////////////////////////////////////////////