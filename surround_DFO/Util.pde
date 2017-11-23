/////////////////////////////////////////////////
void mousePressed() {
  OscMessage myMessage = new OscMessage("/test");

  for (int i = 0; i < 5; i++) {

    for (int j = 0; j < 10; j++) {
      myMessage.add(new int[] {i, j});
    }
  }

  /* send the message */
  osc.send(myMessage, supercollider);
  println("done");
}

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
void keyPressed() {
  float[] goals = {0, 0.5, 1.7, 0, PI, PI*0.9, PI*1.5, PI*1.9, TWO_PI};


  if (key == '1')
    gGoal[0] = goals[1];
  if (key == '2')
    gGoal[0] = goals[2];
  if (key == '3')
    gGoal[0] = goals[3];
  if (key == '4')
    gGoal[0] = goals[4];
  if (key == '5')
    gGoal[0] = goals[5];
  if (key == '6')
    gGoal[0] = goals[6];
  if (key == '7')
    gGoal[0] = goals[7];
  if (key == '8')
    gGoal[0] = goals[8];
  //if (key == '9')
  //  gGoal[0] = goals[9];
}

//void reInit() {
//  pop = new Population();
//  reference_frame = frameCount;
//  println("population re-initialized!");
//}

//void setImage(int n) {
//  String s1 = "image";
//  String s2 = nf(n);
//  String name = s1 + s2 + ".png";
//  image = loadImage(name);
//  image.resize(ssSize, ssSize);

//  initializeSS();
//  reInit();
//}