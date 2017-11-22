import controlP5.*;
import oscP5.*;
import netP5.*;
ControlP5 cp5;

OscP5 osc;
NetAddress supercollider;

//Global parameters
float DT = 0.1;
int number_of_tests = 150;
int population_size = 70;
boolean torus = true; //chooses between wrapping around the search space or not
boolean use_only_closest_neighbor = true; //chooses between using only the closest neighbor in the SS or the fittest between two neighbors
float[] gGoal = {0};
float currentGoal = 0;

//temp for interpolation
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

  osc = new OscP5(this, 12000);
  supercollider = new NetAddress("127.0.0.1", 57120);

  for (int i = 0; i < population_size; i++) {
    oldPos[i] = 0;
    newPos[i] = 0;
  }


  //fullScreen();
  startTime = millis();

  frameRate(60);
  //textSize(30);

  //setImage(1);

  pop = new Population();
  pop.update();
  saveState();
  message();
}

/////////////////////////////////////////////////
void draw() {
  float timer = 2*1000;
  float t = millis();
  println(startTime);


  if (t-startTime > timer) {
    message();
    println("HELLO");

    startTime = millis();
  }
  //drawBackground();  //image(image, 0, 0);
  ////drawText();

  ////println("iteration ", frameCount - reference_frame);
  //if (frameCount%20==0) {
  //  pop.update();
  //  save();
  //}
  ////interpolate();


  //float f = frameCount%20;
  //f = f/20;
  //println("f is ", f);
  //pop.drawAgents(f);
}
void message() {
  OscMessage arrayMsg = new OscMessage("/test");

  int n = 3;
  for (int i = 0; i < n; i++) {
    arrayMsg.add(random(-1, 1));
  }

  osc.send(arrayMsg, supercollider);
}

void saveState() {
  oldPos = newPos;
  for (int i = 0; i<population_size; i++) {
    newPos[i] = pop.grains.get(i).pos[0];
  }
}