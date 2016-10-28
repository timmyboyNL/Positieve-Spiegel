#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
	ofSetLogLevel(OF_LOG_VERBOSE);

	//kijken welke cams ik heb, en de webcam logitec kiezen
	cam.listDevices();
	cam.setDeviceID(1);
	cam.setup(640, 480);

	//Geluiden laden, preppen om af te spelen en daarna op pauze om later af te spelen stuk voor stuk
	for (int i = 0; i < Bericht; i++) {
		ofLogNotice() << "Loading sound  " << i << endl;
		BerichtPlayer[i].load("PM" + ofToString(i + 1) + ".mp3");

		BerichtPlayer[i].play();
		BerichtPlayer[i].setPaused(true); // Als ik deze uit zet speelt hij ze wel allemaal af, nu nog random 1 vvoor 1
	}

	ofSoundSetVolume(0.2);

	//Set up uit example voor Oog herkenning
	ofSetVerticalSync(true);
	ofSetFrameRate(120);
	finder.setup("haarcascade_frontalface_default.xml");
	finder.setPreset(ObjectFinder::Fast);
	finder.getTracker().setSmoothingRate(.3);
	ofEnableAlphaBlending();
}

void ofApp::update() {
	//Cam klaarzetten en sounds klaarzetten om later te activeren
	cam.update();
	if(cam.isFrameNew()) {
		finder.update(cam);
	}
	ofSoundUpdate();

}


void ofApp::draw() {
	cam.draw(0, 0);
	//Als de ogen gevonden worden, speel random bericht af. 

for (int i = 0; i < finder.size(); i++) {
	ofRectangle object = finder.getObjectSmoothed(i);
	sunglasses.setAnchorPercent(.5, .5);
	float scaleAmount = .85 * object.width / sunglasses.getWidth();
	ofPushMatrix();
	ofTranslate(object.x + object.width / 2., object.y + object.height * .42);
	ofScale(scaleAmount, scaleAmount);
	sunglasses.draw(0, 0);
	ofPopMatrix();
	ofPushMatrix();
	ofTranslate(object.getPosition());
	ofDrawBitmapStringHighlight(ofToString(finder.getLabel(i)), 0, 0);
	ofDrawLine(ofVec2f(), toOf(finder.getVelocity(i)) * 10);
	ofPopMatrix();
	//Berichten.play(); //hij speelt hem nu elke seconde af fuck xD
}

	if (finder.size() > 0) {
		for (int i = 0; i < finder.size(); i++) {
			if (!isPlaying) {
				BerichtPlayer[(int)ofRandom(0, 5)].setPaused(false);
				isPlaying = true;
				cout << "" << endl;
			}
		}
	}
	//Als er al een bericht speelt dan geen ander bericht afspelen
	else {
		//ofLog() << "1" << (!BerichtPlayer[0].isPlaying()) << endl;
		//ofLog() << "2" << (!BerichtPlayer[1].isPlaying()) << endl;
		//ofLog() << "3" << (!BerichtPlayer[2].isPlaying()) << endl;
		//ofLog() << "4" << (!BerichtPlayer[3].isPlaying()) << endl;
		//ofLog() << "5" << (!BerichtPlayer[4].isPlaying()) << endl;
		//ofLog() << "6" << (!BerichtPlayer[5].isPlaying()) << endl;
		if (
			!BerichtPlayer[0].isPlaying() &&
			!BerichtPlayer[1].isPlaying() &&
			!BerichtPlayer[2].isPlaying() &&
			!BerichtPlayer[3].isPlaying() &&
			!BerichtPlayer[4].isPlaying() &&
			!BerichtPlayer[5].isPlaying())
		{
			isPlaying = false;

		}
	}
}

void ofApp::keyPressed(int key) {
	ofLogVerbose() << "Key:" << key << endl;
	
	if (key == ' ') { 
		isPlaying = false;
	}
	// afhankelijk van de toets, zet een bericht aan of uit
/*	if (key == '1') { //als ik op 1 druk krijg ik 49 dus heb dat maar ingevoerd
		BerichtPlayer[0].setPaused(BerichtPlayer[0].isPlaying());
	}
	else if (key == '2') {
		BerichtPlayer[1].setPaused(BerichtPlayer[1].isPlaying());
	}
	else if (key == '3') {
		BerichtPlayer[2].setPaused(BerichtPlayer[2].isPlaying());
	}
	else if (key == '4') {
		BerichtPlayer[3].setPaused(BerichtPlayer[3].isPlaying());
	}
	else if (key == '5') {
		BerichtPlayer[4].setPaused(BerichtPlayer[4].isPlaying());
	}
	else if (key == '6') {
		BerichtPlayer[5].setPaused(BerichtPlayer[5].isPlaying());
	}*/
}

