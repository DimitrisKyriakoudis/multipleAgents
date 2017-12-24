#pragma once

#include "vector"
#include "ofMain.h"
#include "math.h"
#include "Agent.h"

class Swarm{
public:
	Swarm();

	int size();

	void draw();
	void update();
	void reset();
	void resetAllTo(float);
	void resizeAgents(int);
	void resizeDimensions(int);

	int numAgents;
	int numDimensions;

private:
	std::vector<Agent> agents;
	std::vector<float> dThresh;
	std::vector<float> dAmt;
	std::vector<float> dExp;
	std::vector<float> goals;

	int bestAgentInd;
	bool elitist;

	float initValue;
	float initDt;
	float initDamt;
	float initDexp;


};

