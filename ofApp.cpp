#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	gui.setup();
	gui.add(minH.setup("min H", 2, 0, 180));
	gui.add(maxH.setup("max H", 52, 0, 180));
	gui.add(minS.setup("min S", 57, 0, 255));
	gui.add(maxS.setup("max S", 196, 0, 255));
	gui.add(minV.setup("min V", 158, 0, 255));
	gui.add(maxV.setup("max V", 230, 0, 255));
	gui.add(red_val.setup("R", 255, 0, 255));
	gui.add(green_val.setup("G", 255, 0, 255));
	gui.add(blue_val.setup("B", 255, 0, 255));
	gui.add(wid.setup("Width", 2, 1, 10));
	gui.add(dotteLineToggle.setup("dotted line",false));
	gui.add(saveButton.setup("Save Picture"));
	vidGrabber.initGrabber(640, 480);

}

//--------------------------------------------------------------
void ofApp::update() {
	vidGrabber.update();
	if (vidGrabber.isFrameNew()) {
		im.setFromPixels(vidGrabber.getPixels());
		mat = toCv(im);
		cvtColor(mat, mat_HSV, CV_BGR2HSV);
		inRange(mat_HSV, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), mat_HSV_Threshold);
		erode(mat_HSV_Threshold, mat_HSV_Threshold, Mat());
		dilate(mat_HSV_Threshold, mat_HSV_Threshold, Mat());

		ofImage im_temp;
		ofxCvGrayscaleImage im_temp_gray;

		toOf(mat_HSV_Threshold, im_temp);

		im_temp_gray.setFromPixels(im_temp.getPixels());

		contourFinder.findContours(im_temp_gray, 5, (680 * 480) / 4, 4, false, true);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofSetColor(255, 255, 255);
	drawMat(mat, 0, 0);
	for (int i = 0; i < contourFinder.nBlobs; i++) {
		ofRectangle r = contourFinder.blobs.at(i).boundingRect;
		if (r.getArea() > 1000) {	//threshold to filter out the noise countour

			if (start) {	//start drawing
				xc.push_back(contourFinder.blobs.at(i).centroid.x);
				yc.push_back(contourFinder.blobs.at(i).centroid.y);
				rv.push_back(red_val);
				gv.push_back(green_val);
				bv.push_back(blue_val);
				wv.push_back(wid);
			}
			//cout << r.getArea() << endl;

			ofSetColor(255, 0, 0);	//draw bounding box
			ofNoFill();
			ofSetLineWidth(1);
			ofDrawRectangle(r);

		}
	}
	ofSetColor(255, 255, 255);
	drawMat(mat_HSV_Threshold, mat.cols, 0);
	gui.draw();

	for (int i = 1; i < xc.size(); i++) {	//draw lines
		bool newLine = false;
		for (int j = 0; j < history.size(); j++) {
			if (i == history[j])
				newLine = true;
		}
		if (newLine)
			continue;
		if (!dotteLineToggle) {	//Drawing solid line

			ofSetColor(rv[i - 1], gv[i - 1], bv[i - 1]);
			ofSetLineWidth(wv[i - 1]);
			ofDrawLine(xc[i - 1], yc[i - 1], xc[i], yc[i]);
		}
		else {	//Drawing dotted line
			ofSetColor(rv[i - 1], gv[i - 1], bv[i - 1]);
			ofDrawCircle(xc[i], yc[i], wv[i - 1] / 2);
		}

	}
	// Help information
	if (start) {
		ofSetColor(255, 255, 255);
		ofDrawBitmapString("Press key s to stop the drawing mode. A new line will be generated", 10, 10);
	}
	else {
		ofSetColor(255, 255, 255);
		ofDrawBitmapString("Press key s to start the drawing mode.", 5, 10);
		ofDrawBitmapString("Press key c to clear the canvas.", 5, 20);
	}

	if (saveButton) {	//save the image and name it as screenshot
		imwrite("screenshot.jpg", mat); // A JPG FILE IS BEING SAVED
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 's') {	//start drawing
		if (start) {
			history.push_back(xc.size());
		}
		start = !start;
	}
	if (key == 'c') {	//clear canvas
		xc.clear();
		yc.clear();
		rv.clear();
		gv.clear();
		bv.clear();
		wv.clear();
		history.clear();
	}
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
