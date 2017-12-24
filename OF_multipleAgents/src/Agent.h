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
	void update(const Agent&);
	void update(const Agent&, const Agent&);


	float getFitness();
	void updateFitness(const std::vector<float>&);

	void removeDimension();
	void addDimension(float);

private:
	float fitness;
	float drawSize;
	ofColor standardC;
	ofColor bestC;

	float calcDistance(const Agent&);
	//float torus(float);
};

