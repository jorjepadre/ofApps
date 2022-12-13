//
//  gestureRec.cpp
//  oFapps
//
//  Created by Zhanaidar on 13/12/2022.
//

#include "gestureRec.hpp"

void gestureRec::setup() {
    numCreatedGestures = 0;
    ofBackground(0, 0, 0);
    createNewGesture();
    mode = 0;
}

void gestureRec::update() {
    if (mode == 1 && ofGetElapsedTimeMillis() >= hideMessageOn) {
        mode = 0;
        foundGesture.clear();
    }
}

void gestureRec::draw() {
    if (mode == 0) {
        ofSetColor(255, 255, 0);
        line.draw();
    } else if (mode == 1) {
        ofSetColor(255, 0, 140);
        ofDrawBitmapString(message, 10, ofGetHeight() - 40);
    }
    
    ofSetColor(0, 255, 140);
    foundGesture.draw();
    
    ofColor(255, 255, 0.0f);
    ofDrawBitmapString("Number of gestrues: " + ofToString(dollar.gestures.size()), 10, ofGetHeight() - 25);
    ofDrawBitmapString("Name of current gesture: " + gesture->name, 10, ofGetHeight() - 10);
}

void gestureRec::keyPressed(int key) {
    switch (key) {
        case 'c':
            line.clear();
            break;
        case 'm':
            gesture->reset();
            for (int i = 0; i < line.size(); ++i) gesture->addPoint(line[i].x, line[i].y);
            
            if (gesture->points.size() <= 10) message = "Please add a line first";
            else {
                dollar.addGesture(gesture);
                message = "Added gesture to recognizer";
                line.clear();
                createNewGesture();
            }
            showMessage(message, 800);
            line.clear();
            break;
        case 's':
            dollar.save(ofToDataPath("gesture.txt", true));
            showMessage("Saved!");
            break;
        case 'l':
            dollar.load(ofToDataPath("gesture.txt", true));
            showMessage("Loaded!", 4000);
            break;
        case 'f':
            ofxGesture* tmp = new ofxGesture();
            for (int i = 0; i < line.size(); ++i) tmp->addPoint(line[i].x, line[i].y);
            line.clear();
            double score = 0.0;
            
            ofxGesture* match = dollar.match(tmp, &score);
            if (score >= 0.66) {
                string result = "Matching score: " + ofToString(score);
                if (match ) {
                    result += ", which matches with gesture: " + match->name;
                    foundGesture.clear();
                    float dx = ofGetWidth()/2;
                    float dy = ofGetHeight()/2;
                    
                    for (int i = 0; i < match->resampled_points.size(); ++i) {
                        foundGesture.addVertex(ofVec3f(dx + match->resampled_points[i].x, dy + match->resampled_points[i].y));
                    }
                }
                showMessage(result, 7000);
            } else {
                string result = "Too small matching score with any of the gestures";
                showMessage(result, 7000);
            }
            delete tmp;
            break;
    }
}

void gestureRec::mouseDragged(int x, int y, int button) {
    if (mode == 0) line.addVertex(ofVec3f(x, y));
}

void gestureRec::showMessage(string sMessage) {
    message = sMessage;
    mode = 1;
    hideMessageOn = ofGetElapsedTimeMillis() + 1000;
}

void gestureRec::showMessage(string sMessage, int nDelay) {
    message = sMessage;
    mode = 1;
    hideMessageOn = ofGetElapsedTimeMillis() + nDelay;
}

void gestureRec::createNewGesture() {
    ++numCreatedGestures;
    gesture = new ofxGesture();
    gesture->setName("Gesture#" + ofToString(numCreatedGestures));
}
