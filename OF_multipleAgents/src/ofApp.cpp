#include "ofApp.h"

int numDimensions = 2;

bool isRunning = true;
//--------------------------------------------------------------
void ofApp::setup() {
	//GUI = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
	//ofBackground(100, 50, 50);

	numAgents = 20;

	ofSetFrameRate(10);

	//swarm = Swarm();
	/*int numAgents = 10;
	int numDimensions = 2;

	for (int i = 0; i < numAgents; i++) {
		std::vector<float> temp;
		float x = ofRandomWidth();
		float y = ofRandomHeight();

		temp.push_back(x);
		temp.push_back(y);
		Agent a(temp);
		agents.push_back(a);
	}*/

	//swarm.draw();
	/*ofSetColor()
	ofDrawCircle(100, 100, 10);*/
	//std::cout << "Max float: " << FLT_MAX << std::endl;


}

//--------------------------------------------------------------
void ofApp::update() {
	swarm.setGoals((float)ofGetMouseX() / ofGetWidth(), (float)ofGetMouseY() / ofGetHeight());
	
	
	if (isRunning)
		swarm.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	if (isRunning) {
		ofBackground(100, 50, 50);
		swarm.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'a') {
		swarm.setNumAgents(25);
	}
	
	if (key == 'o') {
		swarm.setNumDimensions(3);
	}

	if(key == 'f')
		ofToggleFullscreen();

	if (key == ' ')
		isRunning = !isRunning;
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	//swarm.setGoals(ofGetMouseX() / ofGetWidth(), ofGetMouseY() / ofGetHeight());
	//std::cout << (float)ofGetMouseX() / ofGetWidth() << " " << (float)ofGetMouseY() / ofGetHeight() << std::endl;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
