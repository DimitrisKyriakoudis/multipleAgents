#include "ofApp.h"


bool guiMode = false;


//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	//ofToggleFullscreen();
	ofSetWindowShape(1920, 1920);


	framesLength = 500;
	currentFrame = 0;

	numAgents = 80;
	numDimensions = 2;

	if (guiMode) {
		swarm.setup(numAgents, numDimensions);
	}
	else {
		fboSwarm.setup(numAgents, numDimensions);

		fboSwarm.showGui(false);

		fboSwarm.setDistThreshs({ 0.1f, 0.1f });
		fboSwarm.setDistAmts({ 0.1f, 0.2f });
		fboSwarm.setDistExps({ 5.0f, 5.0f });

		fboSwarm.setUpdateAmts({ 1.0f, 1.0f });
		fboSwarm.setUpdateExps({ 1.0f, 1.0f });

		fboSwarm.setLoopEvery(10);
		fboSwarm.setUpdatesPerLoop(20);
		fboSwarm.resetAllTo(0.0);
		fboSwarm.setElitist(true);
	}

	
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofSetBackgroundAuto(false);
	ofBackground(0);
}


//--------------------------------------------------------------
void ofApp::update() {

	if (guiMode) {
		swarm.setGoals((float)ofGetMouseX() / ofGetWidth(), (float)ofGetMouseY() / ofGetHeight());

		if (isRunning)
			swarm.update();
	}
	else {
		currentFrame = ofGetFrameNum();
	}
	
}

//--------------------------------------------------------------
void ofApp::draw() {

	if (guiMode) {
		if (isRunning) {
			ofBackground(61);
			swarm.draw();
		}
	}
	else {
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
		
		if (currentFrame < framesLength) {
			int i = currentFrame;

			float dt = ofMap(sin((16 * TWO_PI * i / (float)framesLength)), -1, 1, 0.00, 0.9);
			float a = i / (float)framesLength;
			float r = i / (float)framesLength;
			float size = 8;
			fboSwarm.setDistThreshs({ 0.1f, dt });
			fboSwarm.setGoals(a, r);
			fboSwarm.update();

			vector<vector<float> > val = fboSwarm.getLerpedValues();

			hue = 255 * i / framesLength;

			for (int i = 0; i < val.size(); i++) {
				ofSetColor(ofColor::fromHsb(hue, 255, 255, ofRandom(100, 160)));

				float a_ = val[i][0] * (3 * TWO_PI);
				float r_ = val[i][1] * 500;
				ofDrawCircle(cos(a_)*r_, sin(a_)*r_, size, size);
			}
		}
	}

	

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	/*if (key == 'a') {
		swarm.setNumAgents(25);
	}
	
	if (key == 'o') {
		swarm.setNumDimensions(5);
	}*/
	
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
