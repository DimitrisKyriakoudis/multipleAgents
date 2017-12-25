#include "Swarm.h"

Swarm::Swarm() {
	//Initialise parameters to default values
	//---------------------------------------
	numAgents = 10;
	numDimensions = 2;

	boolElitist = true;

	initDt = 0.05;
	initDamt = 0.1;
	initDexp = 1;
	initUpdateAmt = 1;
	initValue = 0.0;

	for (int i = 0; i < numDimensions; i++) {
		dThreshs.push_back(initDt);
		dAmts.push_back(initDamt);
		dExps.push_back(initDexp);
		updateAmts.push_back(initUpdateAmt);
		goals.push_back(initValue);
		//tempValues.push_back(initValue);
	}

	//Initialise agents with defaults
	//TODO: initialise at starting value instead of random
	//---------------------------------------
	for (int i = 0; i < numAgents; i++) {
		std::vector<float> tempValues;
		for (int i = 0; i < numDimensions; i++) {
			tempValues.push_back(ofRandomHeight());
		}

		Agent a = Agent(tempValues);
		agents.push_back(a);
	}

	//Initialise GUI
	//---------------------------------------
	gui.setup("Parameters");
	for (int i = 0; i < numDimensions; i++) {
		ofParameter<float> temp;
		dts.push_back(temp);
		gui.add(dts[i].set("test", 0.5, 0, 1));
	}

	//TODO: Initialise OSC (?)
	//---------------------------------------




}

//--------------------------------------------------------------
void Swarm::update() {
	updateFitnesses(goals);
	updateAgents(boolElitist, updateAmts);
	draw();
}

//--------------------------------------------------------------
void Swarm::updateAgents(bool elitist, const std::vector<float>& updateAmt) {
	for (int i = 0; i < agents.size(); i++) {
		int bestNeighborIndx = findBestNeighbor(i);
		agents[i].update(agents[bestNeighborIndx], agents[bestAgentIndx], updateAmt, elitist);
	}
}

//--------------------------------------------------------------
int Swarm::findBestNeighbor(int currentAgent) {
	float minDist = FLT_MAX;
	int firstNeighbor = 0;
	int secondNeighbor = 0;

	//Find first neighbor
	for (int i = 0; i < agents.size(); i++) {
		//Skip if we're testing against itself
		if (i == currentAgent)
			continue;

		float d = agents[currentAgent].calcDistance(agents[i]);
		if (d < minDist) {
			firstNeighbor = i;
			minDist = d;
		}
	}
	//Find second neighbor
	minDist = FLT_MAX; // reset minDist
	for (int i = 0; i < agents.size(); i++) {
		//Skip if we're testing against itself or the first neighbor
		if (i == currentAgent || i == firstNeighbor)
			continue;

		float d = agents[currentAgent].calcDistance(agents[i]);
		if (d < minDist) {
			secondNeighbor = i;
			minDist = d;
		}
	}

	if (agents[firstNeighbor].getFitness() < agents[secondNeighbor].getFitness())
		return firstNeighbor;
	else return secondNeighbor;
}

//--------------------------------------------------------------
void Swarm::updateFitnesses(const std::vector<float>& goals) {
	float minScore = FLT_MAX;
	//int indexOfBest = 0;

	for (int i = 0; i < agents.size(); i++) {
		agents[i].updateFitness(goals);

		float f = agents[i].getFitness();
		if (f < minScore) {
			bestAgentIndx = i; //update index of globally best agent
			minScore = f;
		}
	}
}

//--------------------------------------------------------------
int Swarm::size() {
	return agents.size();
}

//--------------------------------------------------------------
void Swarm::draw() {
	for (int i = 0; i < agents.size(); i++) {
		if (i == bestAgentIndx)
			agents[i].draw(true);
		else agents[i].draw(false);
	}

	gui.draw();
}

//--------------------------------------------------------------
void Swarm::resizeSwarm(int newSize) {
	int currentSize = agents.size();
	int diff = newSize - currentSize;
	//If we should increase
	if (diff > 0) {
		for (int i = 0; i < diff; i++) {
			std::vector<float> temp;
			for (int j = 0; j < numDimensions; j++) {
				temp.push_back(ofRandomHeight());
			}
			Agent a = Agent(temp);
			agents.push_back(a);
		}
	}
	//Else we should decrease (only if there is more than one agent in the swarm)
	else if (diff < 0) {
		if (currentSize > 1) {
			for (int i = 0; i < abs(diff); i++)	agents.pop_back();
		}
		else std::cout << "Not enough agents to remove" << std::endl;
	}
}

//--------------------------------------------------------------
void Swarm::resizeDimensions(int newNum) {
	int diff = newNum - numDimensions;

	//If we should increase:
	if (diff > 0) {
		//for every agent..
		for (int i = 0; i < agents.size(); i++) {
			//add as many dimensions as needed
			for (int k = 0; k < diff; k++) agents[i].addDimension(initValue);
		}

		//add more parameters
	/*	for (int k = 0; k < diff; k++) {
			ofParameter<float> temp;
			dts.push_back(temp);
			gui.add(dts[dts.size()-1].set("test", 0.5, 0, 1));
		}*/

		numDimensions += diff; //update global number of dimensions
	}

	//If we should decrease:
	else if (diff < 0) {
		//for every agent..
		if (numDimensions + diff >= 2) {
			for (int i = 0; i < agents.size(); i++) {
				//remove as many dimensions as needed (only if there is at least 2 left)
				for (int k = 0; k < abs(diff); k++) {
					agents[i].removeDimension();
				}
			}
			numDimensions += diff; //update global number of dimensions
		}
	}
}