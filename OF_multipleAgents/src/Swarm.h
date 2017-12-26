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
	void setGoals(float, float);
	void disturbAgents(const std::vector<float>&, const std::vector<float>&, const std::vector<float>&);
	void reset();
	void resetAllTo(float);
	void resizeSwarm(int);
	void resizeDimensions(int);
	void setElitist(bool);

	void setGoals(const std::vector<float>&);

	int numAgents;
	int numDimensions;

private:
	void updateSwarm();
	void updateFitnesses(const std::vector<float>&);
	void updateAgents(bool, const std::vector<float>&, const std::vector<float>&);
	int findBestNeighbor(int);
	void addDimParams();
	void removeDimParams();

	std::vector<Agent> agents;
	std::vector<float> dThreshs;
	std::vector<float> dAmts;
	std::vector<float> dExps;
	std::vector<float> updateAmts;
	std::vector<float> updateExps;

	std::vector<float> goals;

	///////////////////
	std::vector<ofParameter<float> > dts;

	int bestAgentIndx;
	bool boolElitist;
	bool boolDisturbBeforeUpdate;

	float initValue;
	float initDt;
	float initDamt;
	float initDexp;
	float initUpdateAmt;
	float initUpdateExp;
	float initGoals;

	ofxPanel gui;


};

