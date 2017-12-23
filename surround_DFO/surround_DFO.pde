import controlP5.*;
import oscP5.*;
import netP5.*;
ControlP5 cp5;

OscP5 osc;
NetAddress supercollider;

//Global parameters
float gDT = 0.1;
float gDamt = 0.1;
//float gDamt
int population_size = 12;
int nDimensions = 7;
float updateTime = 1;
int updateCounter = 0;
int msgEvery = 2;


boolean torus = true; //chooses between wrapping around the search space or not
boolean use_only_closest_neighbor = false; //chooses between using only the closest neighbor in the SS or the fittest between two neighbors
//[pan, density, index, ratio, amp]

float gPan, gDens, gInd, gRat, gDur, gAmp, gFreq;
float[] gGoal = new float[nDimensions];// = {0};




float radius = 200;
int ssSize = 500; //size of Search Space

float startTime;
Population pop;




/////////////////////////////////////////////////
void setup() {
  size(600, 600);
  //initGUI();

  //Initial values
  gPan = 0; 
  gDens = 0.2; 
  gInd = 0.1; 
  gRat = 0.1; 
  gDur = 0.3;
  gAmp = 0.05; 
  gFreq = 0.5;


  osc = new OscP5(this, 12000);
  supercollider = new NetAddress("127.0.0.1", 57120);


  //fullScreen();
  startTime = millis();

  frameRate(30);

  pop = new Population();
}

/////////////////////////////////////////////////
void draw() {
  update();
  pop.drawAgents();
}


void message() {
  OscMessage panMsg = new OscMessage("/pan");
  OscMessage densMsg = new OscMessage("/dens");
  OscMessage indMsg = new OscMessage("/ind");
  OscMessage ratMsg = new OscMessage("/rat");
  OscMessage ampMsg = new OscMessage("/amp");
  OscMessage durMsg = new OscMessage("/dur");
  OscMessage freqMsg = new OscMessage("/freq");

  for (int i = 0; i < population_size; i++) {
    panMsg.add(pop.grains.get(i).pos[0]);
    densMsg.add(pop.grains.get(i).pos[1]);
    indMsg.add(pop.grains.get(i).pos[2]);
    ratMsg.add(pop.grains.get(i).pos[3]);
    durMsg.add(pop.grains.get(i).pos[4]);
    ampMsg.add(pop.grains.get(i).pos[5]);
    freqMsg.add(pop.grains.get(i).pos[6]);
  }

  osc.send(panMsg, supercollider);
  osc.send(densMsg, supercollider);
  osc.send(indMsg, supercollider);
  osc.send(ratMsg, supercollider);
  osc.send(ampMsg, supercollider);
  osc.send(durMsg, supercollider);
  osc.send(freqMsg, supercollider);
}

void update() {
  drawBackground();

  float timer = updateTime*1000;
  float t = millis();

  if (t-startTime > timer) {
    //send update message every few updates
    if (updateCounter%msgEvery == 0)
      message();

    updateCounter += 1;
    pop.update();
    startTime = millis();
  }

  updateParams();
}

void updateParams() {
  gGoal[0] = gPan;
  gGoal[1] = gDens;
  gGoal[2] = gInd;
  gGoal[3] = gRat;
  gGoal[4] = gDur;
  gGoal[5] = gAmp;
  gGoal[6] = gFreq;
}

void oscEvent(OscMessage msg) {
  int num = msg.get(0).intValue();
  float val = msg.get(1).intValue()/127.0;

  if (num == 1)
    gPan = val;

  if (num == 2)
    gDens = val;

  if (num == 3)
    gInd = val;

  if (num == 4)
    gRat = val;

  if (num == 5)
    gDur = val;

  if (num == 6)
    gAmp = val;

  if (num == 7)
    gDT = val;

  if (num == 8)
    gDamt = val;

  if (num == 9)
    gFreq = val;
}