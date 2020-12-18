#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"

using namespace cv;
using namespace ofxCv;

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofVideoGrabber vidGrabber;
	ofImage im;
	Mat mat;

	Mat mat_HSV;

	Mat mat_HSV_Threshold;

	ofxPanel gui;
	ofxIntSlider minH;
	ofxIntSlider maxH;
	ofxIntSlider minS;
	ofxIntSlider maxS;
	ofxIntSlider minV;
	ofxIntSlider maxV;

	ofxIntSlider red_val;
	ofxIntSlider green_val;
	ofxIntSlider blue_val;
	ofxIntSlider wid;	//width of the line
	Mat result;

	ofxCvContourFinder contourFinder;
	bool start = false;
	std::vector<int> xc, yc,rv,gv,bv,wv;	//hisotry of the drawing lines
	std::vector<int> history;	//Breaking point where the new lines start
	bool exist = false;
	Vec3b color;

	ofxVec3Slider colors;
	ofxToggle dotteLineToggle;
	ofxButton saveButton;
};