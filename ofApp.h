#pragma once

#include "ofMain.h"
#include "ofxCv.h"

#define Bericht 6

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	
	ofVideoGrabber cam;

	ofxCv::ObjectFinder finder;
	ofImage sunglasses;

	ofSoundPlayer Berichten;
	ofSoundPlayer BerichtPlayer[Bericht];

	bool isPlaying; 
};
