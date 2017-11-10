class Population {
  ArrayList<Grain> grains = new ArrayList<Grain>();
  float[][] pos = new float[population_size][nDimensions];
  float dt = DT;
  int nTests = number_of_tests;
  boolean isTorus = torus;
  //holds index of the best fly
  int bestFly;
  float dimRange = TWO_PI;

  //Constructor
  Population() {
    //for every agent
    for (int i = 0; i < population_size; i++) {
      float[] dim = randomDims();
      Grain f = new Grain(dim);
      grains.add(f);
    }
    println("Torus is ", torus);
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
  void scatter() {
    for (Grain grain : grains) {
      float[] dims = randomDims();
      grain.set(dims);
    } 
    println("population scattered!");
  }

  /////////////////////////////////////////////////
  //update all flies
  void update() {
    bestFly = findBestFly();

    for (int i = 0; i < grains.size(); i++) {
      //don't update best fly
      if (i != bestFly) {
        int neighbor = findBestNeighbor(i);
        grains.get(i).update(grains.get(neighbor), grains.get(bestFly));

        float f = random(1);
        if (f < dt) {
          float[] dims = grains.get(i).pos;
          float ofst = pow(random(0, randOffset), 2.5)*TWO_PI;
          if (random(1)<0.5)
            ofst *= -1;

          dims[0] += ofst;
          grains.get(i).set(dims);
        }

        pos[i] = grains.get(i).pos;
      }
    }
  }

  /////////////////////////////////////////////////
  int findBestFly() {
    float minScore = 100000;
    int index = 0;

    for (int i = 0; i < grains.size(); i++) {
      float score = grains.get(i).getFitness(gGoal);
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
    for (int i = 0; i < grains.size(); i++) {
      if (i == currentFly)
        continue;

      //distance between current fly and every other
      float dist = grains.get(currentFly).getDistance(grains.get(i));
      if (dist < minDist) {
        minDist = dist;
        neighborIndexL = i;
      }
    }

    //if we're not only using the closest neighbor, then find the second closest too
    if (!use_only_closest_neighbor) {
      //get right (2nd closest) neighbor
      for (int i = 0; i < grains.size(); i++) {
        if (i == currentFly)
          continue;
        if (i == neighborIndexL)
          continue;

        //distance between current fly and every other
        float dist = grains.get(currentFly).getDistance(grains.get(i));
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
      if (grains.get(neighborIndexL).fitness < grains.get(neighborIndexR).fitness)
        return neighborIndexL;
      else
        return neighborIndexR;
    }
  }

  /////////////////////////////////////////////////
  void drawAgents(float f) {
    for (int i = 0; i < grains.size(); i++) {
      float r = radius;
      float a = lerp(oldPos[i], newPos[i], f);
      float x = r * cos(a);
      float y = r * sin(a);

      if (i != bestFly)
        grains.get(i).draw(x, y, false);
      else {
        grains.get(i).draw(x, y, true);
      }
    }
    //draw the best fly last so it's on top
    //FIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIXXXXXXXXXXXX IIIIIIIIIIIIIITTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT

    //grains.get(bestFly).draw(, y, true);
  }
}