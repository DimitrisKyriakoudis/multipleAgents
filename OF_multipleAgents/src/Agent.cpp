#include "Agent.h"


//Agent::Agent(const std::vector<float>& newValues){
//	values = newValues;
//}

Agent::Agent(const vector<float>& vals) {
	fitness = 0;
	standardC = ofColor(200, 0, 0);
	bestC = ofColor(100, 200, 255);
	drawSize = 10;

	values = vals;
}

//void Agent::update(const Agent& bestNeighbor, const std::vector<float>& updateAmt) {
//	for (int i = 0; i < values.size(); i++) {
//		float current = values[i];
//		float neighbor = bestNeighbor.values[i];
//		float r = ofRandom(0, updateAmt[i]);
//		float newVal = neighbor + r*(neighbor - current);
//		newVal = ofClamp(newVal, 0, 1);
//		values[i] = newVal;
//	}
//}

void Agent::update(const Agent& bestNeighbor, const Agent& bestInSwarm, const std::vector<float>& updateAmt, bool elitist) {
	for (int i = 0; i < values.size(); i++) {
		float current = values[i];
		float neighbor = bestNeighbor.values[i];
		float best = bestInSwarm.values[i];
		float r = ofRandom(0, updateAmt[i]);

		float newVal;
		if (elitist) newVal = neighbor + r*(best - current);
		else newVal = neighbor + r*(neighbor - current);
		newVal = ofClamp(newVal, 0, 1);

		values[i] = newVal;
	}
}

void Agent::updateFitness(const std::vector<float>& goals) {
	fitness = 0;
	if (goals.size() == values.size()) {
		for (int i = 0; i < goals.size(); i++) {
			fitness += abs(goals[i] - values[i]);
		}
	}
	else std::cout << "Goal and value sizes don't match!" << std::endl;
}

float Agent::getFitness() {
	return fitness;
}


float Agent::calcDistance(const Agent& otherAgent) {
	float dist = 0;
	for (int i = 0; i < values.size(); i++) {
		dist += pow(values[i] - otherAgent.values[i], 2);
	}
	return sqrt(dist);
}

//const std::vector<float>& Agent::getValues() {
//	return values;
//}

void Agent::setValues(const std::vector<float>& newValues) {
	values = newValues;
}

void Agent::addDimension(float val) {
	values.push_back(val);
}

void Agent::removeDimension() {
	if (values.size() > 1)
		values.pop_back();
	else std::cout << "Can't remove dimension, only 1 left" << std::endl;
}

void Agent::draw(bool isBest) {
	/*float r = drawSize;
	if (isBest) {
		ofSetColor(bestC);
		r *= 2;
	}
	else
		ofSetColor(standardC);*/
	float r = drawSize * 3;
	ofSetColor(standardC);
	//ofFill();
	ofDrawCircle(values[0], values[1], r);
}