#include "Agent.h"

//--------------------------------------------------------------
Agent::Agent(const vector<float>& vals) {
	fitness = 0;
	standardC = ofColor(200, 0, 0, 150);
	bestC = ofColor(100, 200, 255, 255);
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

//--------------------------------------------------------------
void Agent::update(const Agent& bestNeighbor, const Agent& bestInSwarm, const std::vector<float>& updateAmt, const std::vector<float>& updateExp, bool elitist) {
	for (int i = 0; i < values.size(); i++) {
		float current = values[i];
		float neighbor = bestNeighbor.values[i];
		float best = bestInSwarm.values[i];
		//random number from 0 to 1, raised to an exponent (to change the distribution curve) and scaled by the amount between 0 and 1
		float r = pow(ofRandom(0, 1), updateExp[i]) * updateAmt[i];

		float newVal;
		if (elitist) newVal = neighbor + r*(best - current);
		else newVal = neighbor + r*(neighbor - current);
		newVal = ofClamp(newVal, 0, 1);

		values[i] = newVal;
	}
}

//--------------------------------------------------------------
void Agent::updateFitness(const std::vector<float>& goals) {
	if (goals.size() == values.size()) {
		fitness = 0;
		for (int i = 0; i < goals.size(); i++) {
			fitness += abs(goals[i] - values[i]);
		}
	}
	else std::cout << "Agent::updateFitness -> Goal and value sizes don't match!" << std::endl;
}

//--------------------------------------------------------------
float Agent::getFitness() {
	return fitness;
}

//--------------------------------------------------------------
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

//--------------------------------------------------------------
void Agent::disturb(const std::vector<float>& thresholds, const std::vector<float>& exponents, const std::vector<float>& amounts) {
	//Make sure sizes match
	if(thresholds.size() != values.size() || amounts.size() != values.size()) {
		std::cout << "Agent::disturb -> vector sizes don't match" << std::endl;
		return;
	}
	
	//For every dimension:
	for (int i = 0; i < values.size(); i++) {
		float r = ofRandom(0, 1); //calculate a probability
		if (r < thresholds[i]) { //and if less than that dimension's threshold
			float offset = pow(ofRandom(0, 1), exponents[i]) * amounts[i]; //Exponent shapes the distribution curve, amount scales 
			if (ofRandom(0, 1) < 0.5) //50% chance it's negative
				offset *= -1;
			values[i] = ofClamp(values[i] + offset, 0, 1);
		}
	}
}

//--------------------------------------------------------------
void Agent::setValues(const std::vector<float>& newValues) {
	values = newValues;
}

//--------------------------------------------------------------
void Agent::addDimension(float val) {
	values.push_back(val);
}

//--------------------------------------------------------------
void Agent::removeDimension() {
	if (values.size() > 1)
		values.pop_back();
	else std::cout << "Can't remove dimension, only 1 left" << std::endl;
}

//--------------------------------------------------------------
void Agent::draw(bool isBest) {
	float r = drawSize;
	if (isBest) {
		ofSetColor(bestC);
		r *= 2;
	}
	else
		ofSetColor(standardC);
	//ofSetColor(standardC);
	ofFill();
	ofDrawCircle(values[0]*ofGetWidth(), values[1]*ofGetHeight(), r);
}