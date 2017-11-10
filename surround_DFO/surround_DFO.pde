import controlP5.*;
ControlP5 cp5;

//Global parameters
float DT = 0.1;
int number_of_tests = 150;
int population_size = 70;
boolean torus = true; //chooses between wrapping around the search space or not
boolean use_only_closest_neighbor = true; //chooses between using only the closest neighbor in the SS or the fittest between two neighbors
float[] gGoal = {0};
float currentGoal = 0;

float[] oldPos = new float[population_size];
float[] newPos = new float[population_size];


//Global variables
float randOffset = 0.9;

int nDimensions = 1;
float radius = 200;
int ssSize = 500; //size of Search Space
float[][] ss = new float[ssSize][ssSize];
float startTime;
Population pop;

/////////////////////////////////////////////////
void setup() {
  size(600, 600);
  //initGUI();

  for (int i = 0; i < population_size; i++) {
    oldPos[i] = 0;
    newPos[i] = 0;
  }


//fullScreen();
  startTime = second();

  frameRate(60);
  //textSize(30);

  //setImage(1);

  pop = new Population();
  pop.update();
}

/////////////////////////////////////////////////
void draw() {
  drawBackground();  //image(image, 0, 0);
  //drawText();

  //println("iteration ", frameCount - reference_frame);
  if (frameCount%20==0) {
    pop.update();
    save();
  }
  //interpolate();


  float f = frameCount%20;
  f = f/20;
  println("f is ", f);
  pop.drawAgents(f);
}

void save() {
  oldPos = newPos;
  for (int i = 0; i<population_size; i++) {
    newPos[i] = pop.grains.get(i).pos[0];
  }
}

/////////////////////////////////////////////////
void drawBackground() {
  background(51);
  translate(width/2, height/2);
  float r = radius;
  int n = 8;

  for (int i = 0; i < n; i++) {
    float a = (TWO_PI)*i/n;
    float x = r * cos(a);
    float y = r * sin(a);

    fill(255, 0, 0, 180);
    ellipse(x, y, 50, 50);
  }

  float a = gGoal[0];
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