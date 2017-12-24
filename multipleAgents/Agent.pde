class Agent {
  FloatList value; // = new float[nDimensions];
  float fitness = 0;
  int drawSize = 5;
  color c = color(220, 220, 220, 80);
  color best = color(100, 200, 255);

  /////////////////////////////////////////////////
  Agent(FloatList newValue) {
    for (int i = 0; i < newValue.size(); i++) {
      value.append(newValue.get(i));
    }
  }
  /////////////////////////////////////////////////
  void set(FloatList newValue) {
    int s = newValue.size();
    if (s == value.size())
    {
      for (int i = 0; i < s; i++) {
        value.set(i, newValue.get(i));
      }
    } else println("Cannot set values, FloatLists have different sizes");
  }

  /////////////////////////////////////////////////
  void update(Agent bestNeighbor, Agent bestInSwarm, boolean usingBest) {
    for (int i = 0; i < value.size(); i++) {
      float current = value.get(i);
      float neighbor = bestNeighbor.value.get(i);
      float best = bestInSwarm.value.get(i);
      float r = random(1);
      //Xi = Xin + U(0, 1)*(Xs - Xi)
      float newVal = constrain(neighbor + r*(best - current), 0.0, 1.0);
      value.set(i, newVal);
    }
  }
  /////////////////////////////////////////////////
  //get fitness of current fly
  float getFitness(float[] goal) {
    float fitness = 0;
    for (int i = 0; i < value.size(); i++) {
      ///////////absolute difference or euclidean distance?///////////
      fitness += abs(goal[i]-value.get(i));
    }    

    return fitness;
  }
  /////////////////////////////////////////////////
  float getDistance(Agent otherGrain) {
    float squaredSum = 0;
    for (int i = 0; i < value.size(); i++) {
      squaredSum += sq(value.get(i) - otherGrain.value.get(i));
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