#include "Swarm.h"

Swarm::Swarm() {
	//Initialise parameters to default values
	//---------------------------------------
	numAgents = 10;
	numDimensions = 2;
	//Used to update swarm sizes when sliders change
	currNumAgents = numAgents;
	currNumDimensions = numDimensions;

	boolElitist = true;
	boolDisturbBeforeUpdate = true;
	boolDisturbSeparately = true;

	initDt = 0.05;
	initDamt = 0.8;
	initDexp = 1.0;
	initUpdateAmt = 1.0;
	initUpdateExp = 1.0;
	initValue = 0.0;
	initGoals = 0.5;
	singleThresh = initDt;

	//Initialise general toggle panel
	initPanelX = 10;
	initPanelY = 10;
	controlTogglesPanel = new ofxDatGui(initPanelX, initPanelY);
	controlTogglesPanel->addHeader("Behavior Toggles");
	controlTogglesPanel->addSlider("Number of Agents", 2, 100)->bind(numAgents);
	controlTogglesPanel->addSlider("Number of Dimensions", 1, 20)->bind(numDimensions);
	controlTogglesPanel->addToggle("Elitist Approach", boolElitist);
	controlTogglesPanel->addToggle("Disturb Before Update", boolDisturbBeforeUpdate);
	controlTogglesPanel->addToggle("Separate Disturbance Thresholds", boolDisturbSeparately);
	std::cout << "first panel done" << std::endl;

	

	//Resize vector to hold the vectors of sliders for each panel/parameter
	for (int i = 0; i < numDimensions; i++) {
		addParamDimension();
	}

	std::cout << "dimensions done" << std::endl;


	initGuiPanels(numDimensions);
	std::cout << "init gui panels done" << std::endl;

	

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


void Swarm::initGuiPanels(int num) {
	if (distThreshs.size() != num) {
		std::cout << "initGuiPanels: sizes don't match" << std::endl;
		return;
	}

	std::vector<string> panelNames = {
		"Disturbance Thresholds",
		"Disturbance Amounts" ,
		"Disturbance Amount Exponents",
		"Update Amounts",
		"Update Amount Exponents",
		"Goals"
	};

	std::cout << "panelNames done" << std::endl;


	for (int i = 0; i < panelNames.size(); i++) {
		panels.push_back(new ofxDatGui());
		panels[i]->addHeader(panelNames[i]);
	}
	
	//panels[0]->addSlider(s.str(), 0, 1);

	std::cout << "panels size: " << panels.size() << std::endl;

	for (int i = 0; i < num; i++) {
		stringstream s;
		s << "Dimension " << i + 1;

		//Disturbance Thresholds
		panels[0]->addSlider(s.str(), 0, 1);
		panels[0]->getSlider(s.str())->bind(distThreshs[i]);
		//Disturbance Amounts
		panels[1]->addSlider(s.str(), 0, 1);
		panels[1]->getSlider(s.str())->bind(distAmts[i]);
		//Disturbance Exponents
		panels[2]->addSlider(s.str(), 0, 1);
		panels[2]->getSlider(s.str())->bind(distExps[i]);
		//Update Amounts
		panels[3]->addSlider(s.str(), 0, 1);
		panels[3]->getSlider(s.str())->bind(updateAmts[i]);
		//Update amount Exponents
		panels[4]->addSlider(s.str(), 0, 1);
		panels[4]->getSlider(s.str())->bind(updateExps[i]);
		//Goals
		panels[5]->addSlider(s.str(), 0, 1);
		panels[5]->getSlider(s.str())->bind(goals[i]);
	}

	std::cout << "panel sliders done" << std::endl;


	positionGuiPanels();
	std::cout << "positioning done" << std::endl;

}

void Swarm::deleteGuiPanels() {
	for (int i = 0; i < panels.size(); i++) {
		panels[i]->~ofxDatGui();
		delete panels[i];
	}

	panels.clear();
}
//void Swarm::bindGuiPanel(ofxDatGui *pGUI, const std::vector<float>& parameter) {
//
//}

void Swarm::checkForNumChanges() {
	if (currNumAgents != numAgents) {
		setNumAgents(numAgents);
	}
	if (currNumDimensions != numDimensions) {
		setNumDimensions(numDimensions);
	}
}

//--------------------------------------------------------------
void Swarm::setNumAgents(int num) {
	resizeSwarm(num);
	numAgents = num;
}

//--------------------------------------------------------------
void Swarm::setNumDimensions(int num) {
	deleteGuiPanels();
	resizeDimensions(num);
	initGuiPanels(num);

	numDimensions = num;
	currNumDimensions = num;
	std::cout << "Dimensions resized!" << std::endl;
}

//--------------------------------------------------------------
void Swarm::update() {
	//oscUpdateParameters();
	checkForNumChanges();
	updateSwarm();
	draw();
}

//--------------------------------------------------------------
//TODO: set all goals
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
		//Keep adding agents until size is as desired
		while(agents.size() != newSize){
			std::vector<float> temp;
			for (int j = 0; j < numDimensions; j++) {
				temp.push_back(ofRandom(0, 1));
			}
			Agent a = Agent(temp);
			agents.push_back(a);
		}
	}
	//Else we should decrease (only if there is more than one agent in the swarm)
	else if (diff < 0) {
		if (currentSize >= 2) {
			//Keep removing agents until size is as desired
			while (agents.size() != newSize)
				agents.pop_back();
		}
		else std::cout << "Not enough agents to remove" << std::endl;
	}
}

//--------------------------------------------------------------
void Swarm::resizeDimensions(int newNum) {
	int diff = newNum - numDimensions;

	//If we should increase:
	if (diff > 0) {
		//Add dimensions to all agents
		for (int i = 0; i < agents.size(); i++) {
			for (int k = 0; k < diff; k++) agents[i].addDimension(initValue);
		}

		//Add gui sliders and elements to the parameter vectors to match
		for (int k = 0; k < diff; k++) {
			addParamDimension();
		}
	}
	//If we should decrease:
	else if (diff < 0) {
		//Remove dimensions from all agents (only if there are at least 2 left)
		if (numDimensions + diff >= 2) {
			for (int i = 0; i < agents.size(); i++) {
				for (int k = 0; k < abs(diff); k++) agents[i].removeDimension();
			}
			//Remove dimension parameters to match
			for (int k = 0; k < abs(diff); k++) {
				removeDimParams();
			}
		}
		else std::cout << "Swarm::resizeDims -> can't remove dimensions" << std::endl;
	}
}

//--------------------------------------------------------------
void Swarm::positionGuiPanels() {
	for (int i = 0; i < panels.size(); i++) {
		if (i == 0) {
			panels[i]->setPosition(controlTogglesPanel->getPosition().x, controlTogglesPanel->getPosition().y + controlTogglesPanel->getHeight());
		}
		else {
			int newY = panels[i - 1]->getPosition().y + panels[i - 1]->getHeight();
			panels[i]->setPosition(initPanelX, newY);
		}
	}
}

void Swarm::addParamDimension() {
	distThreshs.push_back(initDt);
	distAmts.push_back(initDamt);
	distExps.push_back(initDexp);
	updateAmts.push_back(initUpdateAmt);
	updateExps.push_back(initUpdateExp);
	goals.push_back(initValue);
}

void Swarm::removeDimParams() {
	distThreshs.pop_back();
	distAmts.pop_back();
	distExps.pop_back();
	updateAmts.pop_back();
	updateExps.pop_back();
	goals.pop_back();
}