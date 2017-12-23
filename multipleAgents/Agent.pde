class Grain {
  float[] pos = new float[nDimensions];
  float fitness = 0;
  int drawSize = 5;
  color c = color(220, 220, 220, 80);
  color best = color(100, 200, 255);

  /////////////////////////////////////////////////
  Grain(float[] dim) {
    for (int i = 0; i < dim.length; i++) {
      pos[i] = dim[i];
    }
  }
  /////////////////////////////////////////////////
  void set(float[] dim) {
    for (int i = 0; i < dim.length; i++) {
      pos[i] = dim[i];
    }
  }

  /////////////////////////////////////////////////
  void update(Grain bestNeighbor, Grain bestInSwarm) {
    for (int i = 0; i < pos.length; i++) {
      float current = pos[i];
      float neighbor = bestNeighbor.pos[i];
      float best = bestInSwarm.pos[i];
      float r = random(1);
      //Xi = Xin + U(0, 1)*(Xs - Xi)
      pos[i] = constrain(neighbor + r*(best - current), 0, 499);
    }
  }
  /////////////////////////////////////////////////
  //get fitness of current fly
  float getFitness(float[] goal) {
    float fitness = 0;
    for (int i = 0; i < pos.length; i++) {
      ///////////absolute difference or euclidean distance?///////////
      fitness += abs(goal[i]-pos[i]);
    }    

    return fitness;
  }
  /////////////////////////////////////////////////
  float getDistance(Grain otherGrain) {
    float squaredSum = 0;
    for (int i = 0; i < pos.length; i++) {
      squaredSum += sq(pos[i] - otherGrain.pos[i]);
    }
    return sqrt(squaredSum);
  }
  /////////////////////////////////////////////////
  void draw(float x, float y, boolean isBest) {
    noStroke();
    

    if (isBest) {
      fill(best);
      ellipse(x, y, drawSize*4, drawSize*4);
    } else {
      fill(c);
      ellipse(x, y, drawSize, drawSize);
    }
  }
  /////////////////////////////////////////////////
  int torus(int pos) {
    int newPos = pos;
    if (pos < 0)
      newPos = ssSize + pos;
    if (pos >= ssSize)
      newPos = pos%ssSize;

    return newPos;
  }

  /////////////////////////////////////////////////
}