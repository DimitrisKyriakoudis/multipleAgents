#pragma once

#include <string>
#include <sstream>
#include <vector>
#include "math.h"

#include "ofMain.h"
#include "Agent.h"
//#include "ofxGui.h"
#include "ofxDatGui.h"
#include "ofxXmlSettings.h"

using namespace std;

class Swarm{
public:
	Swarm();

	void setup(int, int);

	int size();
	void draw();
	void update();
	void setGoals(float, float);
	void setDisturbSeparately(bool);
	void setNumAgents(int);
	void setNumDimensions(int);

	vector<vector<float> >& getLerpedValues();

	//frames until next update
	void setLoopEvery(int);
	void setUpdatesPerLoop(int);

	//Overloaded disturbance functions that use either a single or an individual threshold for every dimension
	void disturbAgents(const vector<float>&, const vector<float>&, const vector<float>&);
	void disturbAgents(float, const vector<float>&, const vector<float>&);

	void setDistThreshs(const vector<float>&);
	void setDistAmts(const vector<float>&);
	void setDistExps(const vector<float>&);

	void setUpdateAmts(const vector<float>&);
	void setUpdateExps(const vector<float>&);


	void showGui(bool);

	void reset();
	void resetAllTo(float);
	void resizeSwarm(int);
	void resizeDimensions(int);
	void setElitist(bool);
	void setGoals(const vector<float>&);
	void setDrawColour(ofColor);
	void setBestColour(ofColor);

	int numAgents;
	int currNumAgents;
	int numDimensions;
	int currNumDimensions;

	void deleteGuiPanels();


private:
	void updateSwarm();
	void updateFitnesses(const vector<float>&);
	void updateAgents(bool, const vector<float>&, const vector<float>&);
	int  findBestNeighbor(int);
	void addParamDimension();
	void removeDimParams();
	void positionGuiPanels();
	void checkForNumChanges();
	void lerpValues();

	ofColor drawColour;
	ofColor bestColour;

	//draw phase -> where in the interpolation cycle we are (0 to 1)
	//loopEvery -> how many frames does one update cycle loop over
	//updatesPerLoop -> how many times we update at once
	float interpPhase = 0;
	int loopEvery = 15;
	int updatesPerLoop = 5;



	//double time, timer, updateEvery;

	vector<Agent> agents;

	float		  singleThresh; //Single threshold for all dimensions
	vector<float> distThreshs; //individual thresholds for each dimension
	vector<float> distAmts;
	vector<float> distExps;
	vector<float> updateAmts;
	vector<float> updateExps;

	vector<float> goals;


	//Vectors for interpolation
	vector<vector<float> > previousValues;
	vector<vector<float> > nextValues;
	vector<vector<float> > lerpedValues;

	///////////////////
	vector<ofParameter<float> > dts;
	void onToggleEvent(ofxDatGuiToggleEvent);

	int bestAgentIndx;
	bool boolElitist;
	bool boolDisturbBeforeUpdate;
	bool boolDisturbSeparately;

	float initValue;
	float initDt;
	float initDamt;
	float initDexp;
	float initUpdateAmt;
	float initUpdateExp;
	float initGoals;


	//ofxPanel gui;
	ofxDatGui* controlTogglesPanel;
	vector<ofxDatGui*> panels;
	int initPanelX;
	int initPanelY;
	//vector<vector<float> > swarmParameters;
	void initGuiPanels(int);
	vector<vector<ofxDatGuiSlider*> > guiPanelSliders;

	ofxXmlSettings settings;
};

