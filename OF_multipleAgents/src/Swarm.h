#pragma once

#include "vector"
#include "ofMain.h"
#include "math.h"
#include "Agent.h"
#include "ofxGui.h"

class Swarm{
public:
	Swarm();

	int size();

	void draw();
	void update();
	void reset();
	void resetAllTo(float);
	void resizeSwarm(int);
	void resizeDimensions(int);
	void setElitist(bool);

	void setGoals(const std::vector<float>&);

	int numAgents;
	int numDimensions;

private:

	void updateFitnesses(const std::vector<float>&);
	void Swarm::updateAgents(bool elitist, const std::vector<float>& updateAmt);
	int findBestNeighbor(int);

	std::vector<Agent> agents;
	std::vector<float> dThreshs;
	std::vector<float> dAmts;
	std::vector<float> dExps;
	std::vector<float> updateAmts;
	std::vector<float> goals;

	std::vector<ofParameter<float> > dts;

	int bestAgentIndx;
	bool boolElitist;
	bool disturbBefore;

	float initValue;
	float initDt;
	float initDamt;
	float initDexp;
	float initUpdateAmt;

	ofxPanel gui;


};

