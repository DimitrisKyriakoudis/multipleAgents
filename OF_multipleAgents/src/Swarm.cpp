#include "Swarm.h"

Swarm::Swarm() {
	numAgents = 10;
	numDimensions = 2;
	initDt = 0.05;
	initDamt = 0.1;
	initDexp = 1;
	initValue = 0.0;

	for (int i = 0; i < numDimensions; i++) {
		dThresh.push_back(initDt);
		dAmt.push_back(initDamt);
		dExp.push_back(initDexp);
		goals.push_back(initValue);
		//tempValues.push_back(initValue);
	}

	for (int i = 0; i < numAgents; i++) {
		std::vector<float> tempValues;
		for (int i = 0; i < numDimensions; i++) {
			tempValues.push_back(ofRandomHeight());
		}

		Agent a = Agent(tempValues);
		agents.push_back(a);
	}
}

//--------------------------------------------------------------
int Swarm::size() {
	return agents.size();
}

//--------------------------------------------------------------
void Swarm::draw() {
	for (int i = 0; i < agents.size(); i++) {
		agents[i].draw(false);
	}
}

//--------------------------------------------------------------
void Swarm::resizeAgents(int newSize) {
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