#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxGui.h"
#include "grid.h"

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
		void createFrequencies();
		
		map<int, double>frequencyMap;
		ofSoundStream soundStream;
		int bufferSize;
		int sampleRate;

		Grid beatpad;

		maxiOsc VCO1[8];		
		maxiEnv ADSR[8];

		maxiOsc timer;

		int currentCount, lastCount, counter = 0;

		double VCO1out[8], ADSRout[8], mix;

		int trigger;

		void audioOut(float * input, int bufferSize, int nChannels);

		ofxFloatSlider attack;
		ofxFloatSlider decay;
		ofxFloatSlider release;
		ofxFloatSlider sustain;
		ofxIntSlider beat;
		ofxFloatSlider freq;
		ofxPanel gui;

};
