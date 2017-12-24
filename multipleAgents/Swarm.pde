class Swarm {
  ArrayList<Agent> agents;//= new ArrayList<Agent>();
  //ArrayList of FloatLists (numAgents x numDimensions)
  ArrayList<FloatList> values;
  int numAgents;
  int numDimensions;
  FloatList dThresh;
  FloatList dAmt; 
  FloatList dExp;


  boolean usingBestInSwarm;
  boolean isTorus = torus;
  //holds index of the best fly
  int bestFly;
  float dimRange = 1;

  //Constructor
  Swarm() {
    //Initialize to default values
    numAgents = 20;
    numDimensions = 2;

    float initDT = 0.05;
    float initDAmt = 0.1;
    float initDExp = 1;
    dThresh = new FloatList();
    dAmt = new FloatList();
    dExp = new FloatList();

    //Initialize disturbance thresholds, amounts, and exponents for each dimension
    for (int i = 0; i < numDimensions; i++) {
      dThresh.append(initDT);
      dAmt.append(initDAmt);
      dExp.append(initDExp);
    }

    float startingValue = 0.0;
    //For every agent:
    for (int i = 0; i < numAgents; i ++) {
      //Add a FloatList to the total values
      values.add(new FloatList());
      //Initialize every dimension of that list to a starting value
      for (int j = 0; j < numDimensions; j++) {
        values.get(i).append(startingValue);
      }
      //Make an agent with those values and add it to the ArrayList
      Agent a = new Agent(values.get(i));
      agents.add(a);
    }
    println("Population Initialized.");
  }

  /////////////////////////////////////////////////
  float[] randomDims() {
    //for every agent
    float[] dims = new float[nDimensions];
    //for every dimension
    for (int i = 0; i < dims.length; i++) 
      dims[i] = random(dimRange);

    return dims;
  }

  /////////////////////////////////////////////////
  //void scatter() {
  //  for (Agent grain : agents) {
  //    float[] dims = randomDims();
  //    grain.set(dims);
  //  } 
  //  println("population scattered!");
  //}

  /////////////////////////////////////////////////
  //update all flies
  void update() {
    bestFly = findBestFly();
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    for (int i = 0; i < agents.size(); i++) {
      //don't update best fly
      if (i != bestFly) {

        for (int d = 0; d < numDimensions; d++) {
          float r = random(1);
          if (r < dThresh.get(d)) {
            //Calculate offset for current dimension
            float offset = random(0, dAmt.get(d));
            //offset = pow(offset, dExp.get(d));
            if(random(1) < 0.5)
              offset *= -1;
            agents.get(i).value.add(d, offset);
          } else {
            //update
          }
        }

aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

        int neighbor = findBestNeighbor(i);
        agents.get(i).update(agents.get(neighbor), agents.get(bestFly), usingBestInSwarm);



        //DISTURBANCE
        if (f < gDT) {
          float[] dims = agents.get(i).pos;
          for (int dim = 0; dim < nDimensions; dim++) {
            float ofst = pow(random(0, gDamt), 2.5);
            if (random(1)<0.5)
              ofst *= -1;

            dims[dim] += ofst;
          }

          agents.get(i).set(dims);
        }

        pos[i] = agents.get(i).pos;
      }
    }
  }

  /////////////////////////////////////////////////
  int findBestFly() {
    float minScore = 100000;
    int index = 0;

    for (int i = 0; i < agents.size(); i++) {
      float score = agents.get(i).getFitness(gGoal);
      if (score < minScore) {
        minScore = score;
        index = i;
      }
    }
    return index;
  }

  /////////////////////////////////////////////////
  //returns the closest neighbor to any given fly
  int findBestNeighbor(int currentFly) {
    float minDist = 1000000;
    int neighborIndexL = 0;
    int neighborIndexR = 0;


    //get left (1st closest) neighbor
    for (int i = 0; i < agents.size(); i++) {
      if (i == currentFly)
        continue;

      //distance between current fly and every other
      float dist = agents.get(currentFly).getDistance(agents.get(i));
      if (dist < minDist) {
        minDist = dist;
        neighborIndexL = i;
      }
    }

    //if we're not only using the closest neighbor, then find the second closest too
    if (!use_only_closest_neighbor) {
      //get right (2nd closest) neighbor
      for (int i = 0; i < agents.size(); i++) {
        if (i == currentFly)
          continue;
        if (i == neighborIndexL)
          continue;

        //distance between current fly and every other
        float dist = agents.get(currentFly).getDistance(agents.get(i));
        if (dist < minDist) {
          minDist = dist;
          neighborIndexR = i;
        }
      }
    }

    // flies.get(currentFly).bestNeighborL = neighborIndexL;
    if (use_only_closest_neighbor)
      return neighborIndexL;
    else {
      if (agents.get(neighborIndexL).fitness < agents.get(neighborIndexR).fitness)
        return neighborIndexL;
      else
        return neighborIndexR;
    }
  }

  /////////////////////////////////////////////////
  void drawAgents() {
    for (int i = 0; i < agents.size(); i++) {
      float r = radius;
      float a = agents.get(i).pos[0]*TWO_PI;
      float x = r * cos(a);
      float y = r * sin(a);

      if (i != bestFly)
        agents.get(i).draw(x, y, false);
      else {
        agents.get(i).draw(x, y, true);
      }
    }
    //draw the best fly last so it's on top
    //FIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIXXXXXXXXXXXX IIIIIIIIIIIIIITTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT

    //grains.get(bestFly).draw(, y, true);
  }
}