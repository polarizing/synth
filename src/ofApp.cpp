#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	bufferSize = 512;
	sampleRate = 44100;

	beatpad.setup();
	createFrequencies();

	soundStream.setup(this, 2, 0, sampleRate, bufferSize, 2);

	gui.setup();
	gui.add(attack.setup("Attack", 5, 4, 500));
	gui.add(decay.setup("Decay", 200, 0.1, 500));
	gui.add(sustain.setup("Sustain", 0.2, 0.1, 1));
	gui.add(release.setup("Release", 2000, 0, 5000));
	gui.add(beat.setup("Beat", 8, 1, 16));
	gui.add(freq.setup("Frequency", 55, 0, 600));
}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < 8; i++) {
		ADSR[i].setAttack(attack);
		ADSR[i].setDecay(decay);
		ADSR[i].setSustain(sustain);
		ADSR[i].setRelease(release);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	beatpad.draw();
	gui.draw();
}

void ofApp::createFrequencies() {
	double frequencies[] = {
		261.626, 293.665, 329.628, 349.228, 391.995, 440.000, 493.883, 523.251
	};
	for (int i = 0; i < 8; i++) {
		frequencyMap.insert(pair<int, double>(i, frequencies[7 - i]));
	}
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
	
	for (int i = 0; i < bufferSize; i++) {
		mix = 0;
		currentCount = (int)timer.phasor(beat);
		
		if (lastCount != currentCount) {//if we have a new timer int this sample, play the sound

			if (counter == 8) {
				counter = 0;
			}

			ADSR[counter].trigger = 1;//trigger the envelope from the start

			for (int i = 0; i < 8; i++)
			{
				if (beatpad.pattern[i] == -1)
				{
					ADSR[i].trigger = 0;
				}
			}

			counter++;
		}

		//and this is where we build the synth

		for (int i = 0; i<8; i++) {
			ADSRout[i] = ADSR[i].adsr(1., ADSR[i].trigger);//our ADSR env is passed a constant signal of 1 to generate the transient.
			
			if (beatpad.pattern[i] >= 0)
			{
				double frequency = frequencyMap.at(beatpad.pattern[i]);
				VCO1out[i] = VCO1[i].sinewave( frequency );
				mix += VCO1out[i] * ADSRout[i] / 8; //finally we add the ADSR as an amplitude modulator
			}
		}

		output[i * nChannels] = mix * 2;
		output[i * nChannels + 1] = mix * 2;

		// This just sends note-off messages.
		for (int i = 0; i<8; i++) {
			ADSR[i].trigger = 0;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	beatpad.toggleCell(ofVec2f(x, y));
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
