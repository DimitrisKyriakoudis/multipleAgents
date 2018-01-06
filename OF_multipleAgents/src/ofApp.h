#pragma once


#include "vector"
#include "ofMain.h"
#include "ofxDatGui.h"
//#include "ofxGui.h"

//#include "Agent.h"
#include "Swarm.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		/*ofxDatGui* GUI;*/

		//Agent agent;
		//Swarm swarm;
		Swarm fboSwarm;

		int numAgents;
		int numDimensions;
		bool isRunning = true;

		int framesLength;
		int currentFrame;
		float hue;

		//Frame Buffer Object to draw the image on
		ofFbo fbo;
};
