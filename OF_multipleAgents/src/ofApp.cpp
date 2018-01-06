#include "ofApp.h"


ofImage img;

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	//ofToggleFullscreen();
	ofSetWindowShape(1000, 1000);


	framesLength = 1000;
	currentFrame = 0;

	numAgents = 50;
	numDimensions = 2;
	fboSwarm.setup(numAgents, numDimensions);
	//swarm.setup(numAgents, numDimensions);


	fbo.allocate(1920, 1980, GL_RGBA);
	fbo.begin();
	ofClear(255, 255, 255, 255);
	fbo.end();

	fboSwarm.showGui(false);

	fboSwarm.setDistThreshs({ 0.01f, 0.01f });
	fboSwarm.setDistAmts({ 0.1f, 0.1f });
	fboSwarm.setDistExps({ 1.0f, 1.0f });

	fboSwarm.setUpdateAmts({ 1.0f, 1.0f });
	fboSwarm.setUpdateExps({ 1.0f, 1.0f });

	fboSwarm.setLoopEvery(15);
	fboSwarm.setUpdatesPerLoop(2);
	fboSwarm.resetAllTo(0.0);

	//ofBackground(255);

	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofSetBackgroundAuto(false);
	ofBackground(0, 0, 0);

	//ofSetFullscreen(true);
}


//--------------------------------------------------------------
void ofApp::update() {
	currentFrame = ofGetFrameNum();

	//std::cout << ofGetFrameRate() << std::endl;
	//swarm.setGoals((float)ofGetMouseX() / ofGetWidth(), (float)ofGetMouseY() / ofGetHeight());
	//
	//if (isRunning)
	//	swarm.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	//if (isRunning) {
	//	ofBackground(61);
	//	swarm.draw();
	//}

	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	//ofSetColor(ofColor::fromHsb(100, 255, 255));
	
	//ofDrawCircle(ofRandomWidth(), ofRandomHeight(), 10, 10);
	
	if(currentFrame < framesLength){
		int i = currentFrame;

		float dt = ofMap(sin((2*TWO_PI * i / (float)framesLength)), -1, 1, 0.00, 0.2);
		float a = i / (float)framesLength;
		float r = i / (float)framesLength;
		float size = 5;
		fboSwarm.setDistThreshs({ dt, dt });
		fboSwarm.setGoals(a, r);
		fboSwarm.update();

		vector<vector<float> > val = fboSwarm.getLerpedValues();

		hue = 255 * i / framesLength;
		ofSetColor(ofColor::fromHsb(hue, 255, 255, 255));

		for (int i = 0; i < val.size(); i++) {
			float a_ = val[i][0] * (3 * TWO_PI);
			float r_ = val[i][1] * 500;
			ofDrawCircle(cos(a_)*r_, sin(a_)*r_, size, size);
		}
	}

	//img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	//img.save("screenshot.png");


	////ofSaveFrame("screenshot.png");	
	//ofExit();
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	/*if (key == 'a') {
		swarm.setNumAgents(25);
	}
	
	if (key == 'o') {
		swarm.setNumDimensions(5);
	}*/
	if (key == 's') {
		img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		img.save("IMAGE.png");
	}
		
		//ofSaveFrame();



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
