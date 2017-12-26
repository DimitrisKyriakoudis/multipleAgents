#include "Swarm.h"

Swarm::Swarm() {
	//Initialise parameters to default values
	//---------------------------------------
	numAgents = 10;
	numDimensions = 2;

	boolElitist = true;
	boolDisturbBeforeUpdate = false;
	boolDisturbSeparately = false;

	initDt = 0.05;
	initDamt = 0.8;
	initDexp = 1.0;
	initUpdateAmt = 1.0;
	initUpdateExp = 1.0;
	initValue = 0.0;
	initGoals = 0.5;
	singleThresh = initDt;

	//Names for the different panels
	std::vector<string> panelNames = {
		"Disturbance Thresholds",
		"Disturbance Amounts" ,
		"Disturbance Amount Exponents",
		"Update Amounts",
		"Update Amount Exponents"
	};

	/*dThreshsPanel = ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
	dAmtsPanel = ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
	dExpsPanel = ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
	uAmtsPanel = ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
	uExpsPanel = ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);

	dThreshsPanel.addHeader("Disturbance Thresholds");
	dAmtsPanel.addHeader("Disturbance Amounts");
	dExpsPanel.addHeader("Disturbance Amount Exponents");
	uAmtsPanel.addHeader("Update Amounts");
	uExpsPanel.addHeader("Update Amount Exponents");*/

	

	//Initialise panels and add the appropriate header
	for (int i = 0; i < panelNames.size(); i++) {
		panels.push_back(new ofxDatGui());
		panels[i]->addHeader(panelNames[i]);
	}

	//Resize vector to hold the vectors of sliders for each parameter
	guiParameterSliders.resize(panelNames.size());
	for (int i = 0; i < numDimensions; i++) {
		distThreshs.push_back(initDt);
		distAmts.push_back(initDamt);
		distExps.push_back(initDexp);
		updateAmts.push_back(initUpdateAmt);
		updateExps.push_back(initUpdateExp);
		goals.push_back(initGoals);
		//tempValues.push_back(initValue);

		//Name for each slider
		stringstream s;
		s << "Dimension " << i + 1;

		//Initialise a slider for each dimension and bind it to the corresponding
		//dimension value of the corresponding parameter

		//Disturbance Thresholds
		guiParameterSliders[0].push_back(panels[0]->addSlider(s.str(), 0, 1));
		guiParameterSliders[0][i]->bind(distThreshs[i]);
		//Disturbance Amounts
		guiParameterSliders[1].push_back(panels[1]->addSlider(s.str(), 0, 1));
		guiParameterSliders[1][i]->bind(distAmts[i]);
		//Disturbance Exponents
		guiParameterSliders[2].push_back(panels[2]->addSlider(s.str(), 0, 1));
		guiParameterSliders[2][i]->bind(distExps[i]);
		//Update Amounts
		guiParameterSliders[3].push_back(panels[3]->addSlider(s.str(), 0, 1));
		guiParameterSliders[3][i]->bind(updateAmts[i]);
		//Update Exponents
		guiParameterSliders[4].push_back(panels[4]->addSlider(s.str(), 0, 1));
		guiParameterSliders[4][i]->bind(updateExps[i]);
	}

	initPanelX = 10;
	initPanelY = 10;
	//Stack each panel vertically
	for (int i = 0; i < panels.size(); i++) {
		if (i == 0)
			panels[i]->setPosition(initPanelX, initPanelY);
		else {
			int newY = panels[i - 1]->getPosition().y + panels[i - 1]->getHeight();
			panels[i]->setPosition(initPanelX, newY);
		}
	}

	//Initialise agents with defaults
	//TODO: initialise at starting value instead of random
	//---------------------------------------
	for (int i = 0; i < numAgents; i++) {
		std::vector<float> tempValues;
		for (int i = 0; i < numDimensions; i++) {
			tempValues.push_back(ofRandom(0, 1));
		}

		Agent a = Agent(tempValues);
		agents.push_back(a);
	}

	//TODO: Initialise OSC (?)
	//---------------------------------------
}

//void Swarm::bindGuiPanel(ofxDatGui *pGUI, const std::vector<float>& parameter) {
//
//}

//--------------------------------------------------------------
void Swarm::addGuiDimension(int num) {

}

//--------------------------------------------------------------
void Swarm::update() {
	//oscUpdateParameters();
	updateSwarm();

	draw();
}

void Swarm::setGoals(float x, float y) {
	goals[0] = x;
	goals[1] = y;
}

//--------------------------------------------------------------
void Swarm::updateSwarm() {

	if (boolDisturbBeforeUpdate) {
		//Supply either a vector of thresholds or a single threshold for all dimensions
		if (boolDisturbSeparately)
			disturbAgents(distThreshs, distExps, distAmts);
		else disturbAgents(singleThresh, distExps, distAmts);

		updateFitnesses(goals);
		updateAgents(boolElitist, updateAmts, updateExps);
	}
	else {
		updateFitnesses(goals);
		updateAgents(boolElitist, updateAmts, updateExps);

		if (boolDisturbSeparately)
			disturbAgents(distThreshs, distExps, distAmts);
		else disturbAgents(singleThresh, distExps, distAmts);
	}
}

//--------------------------------------------------------------
void Swarm::updateAgents(bool elitist, const std::vector<float>& updateAmt, const std::vector<float>& updateExp) {
	for (int i = 0; i < agents.size(); i++) {
		int bestNeighborIndx = findBestNeighbor(i);
		agents[i].update(agents[bestNeighborIndx], agents[bestAgentIndx], updateAmt, updateExp, elitist);
	}
}

//--------------------------------------------------------------
void Swarm::disturbAgents(const std::vector<float>& thresholds, const std::vector<float>& exponents, const std::vector<float>& amounts) {
	if (thresholds.size() != numDimensions || exponents.size() != numDimensions || amounts.size() != numDimensions) {
		std::cout << "Swarm::disturbAgents -> vector sizes don't match" << std::endl;
		return;
	}
	else {
		for (int i = 0; i < agents.size(); i++) {
			if (i != bestAgentIndx) //Don't disturb the best agent
				agents[i].disturb(thresholds, exponents, amounts);
		}
	}
}
//-------------------overloaded-------------------
void Swarm::disturbAgents(float threshold, const std::vector<float>& exponents, const std::vector<float>& amounts) {
	if (exponents.size() != numDimensions || amounts.size() != numDimensions) {
		std::cout << "Swarm::disturbAgents -> vector sizes don't match" << std::endl;
		return;
	}
	else {
		for (int i = 0; i < agents.size(); i++) {
			if (i != bestAgentIndx) //Don't disturb the best agent
				agents[i].disturb(threshold, exponents, amounts);
		}
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
			continue;
		else agents[i].draw(false);
	}
	agents[bestAgentIndx].draw(true);
	//gui.draw();
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

		//Add as many dimension parameters to match
		for (int k = 0; k < diff; k++) addDimParams();

		//add more GUI parameters
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
			//Remove dimension parameters to match
			for (int k = 0; k < abs(diff); k++) removeDimParams();

			numDimensions += diff; //update global number of dimensions
		}
		else std::cout << "Swarm::resizeDims -> can't remove dimensions" << std::endl;
	}
}

void Swarm::addDimParams() {
	distThreshs.push_back(initDt);
	distAmts.push_back(initDamt);
	distExps.push_back(initDexp);
	updateAmts.push_back(initUpdateAmt);
	goals.push_back(initValue);
}

void Swarm::removeDimParams() {
	distThreshs.pop_back();
	distAmts.pop_back();
	distExps.pop_back();
	updateAmts.pop_back();
	goals.pop_back();
}