#pragma once

#include "vector"
#include "ofMain.h"
#include "math.h"

class Agent{
public:
	//Agent(const std::vector<float>& newValues);
	Agent(const vector<float>&);

	void draw(bool);
	//const std::vector<float>& getValues();
	std::vector<float> values;

	void setValues(const std::vector<float>&);
	void update(const Agent&, const Agent&, const std::vector<float>&, const std::vector<float>&, bool);

	float getFitness();
	void updateFitness(const std::vector<float>&);
	void disturb(const std::vector<float>&, const std::vector<float>&, const std::vector<float>&);

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

