#pragma once

#include "vector"
#include "ofMain.h"
#include "math.h"

using namespace std;

class Agent{
public:
	//Agent(const vector<float>& newValues);
	Agent(const vector<float>&);

	void draw(bool);
	//const vector<float>& getValues();
	vector<float> values;

	void setValues(const vector<float>&);
	void update(const Agent&, const Agent&, const vector<float>&, const vector<float>&, bool);

	float getFitness();
	void updateFitness(const vector<float>&);

	void disturb(const vector<float>&, const vector<float>&, const vector<float>&);
	void disturb(float, const vector<float>&, const vector<float>&);

	void removeDimension();
	void addDimension(float);
	float calcDistance(const Agent&);

private:
	float fitness;
	float drawSize;
	ofColor standardC;
	ofColor bestC;

	//float torus(float);
};

