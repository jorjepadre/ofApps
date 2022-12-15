//
//  gestureRec_v2.cpp
//  oFapps
//
//  Created by Zhanaidar on 15/12/2022.
//

#include "gestureRec_v2.hpp"

//--------------------------------------------------------------
void gestureRec_v2::setup() {
    
    ofBackground(0, 0, 88);
    
    // Initial mode is drawing and it creates a newGesture for name display
    // when submitting the drawing, the new gesture will be created again.
    currentMode = DRAW;
    createNewGesture();
    
    loaded = false;
    
    firstLineX = 20;
    firstLineY = 15;
    
    secondLineX = 20;
    secondLineY = 30;
    
    thirdLineX = 20;
    thirdLineY = 45;
}

//--------------------------------------------------------------
void gestureRec_v2::update() {
    // If the waiting timer passed and current mode is waiting, then switch to drawing mode
    if (currentMode == WAIT && ofGetElapsedTimeMillis() >= messageTimer) {
        currentMode = DRAW;
        matchedGesture.clear();
    }
}

//--------------------------------------------------------------
void gestureRec_v2::draw() {
    // If it is drawing mode, then display the drawings in live
    if (currentMode == DRAW) {
        ofSetColor(255, 215, 0);
        currentGesture.draw();
    } else { // If not in drawing mode, then display the message of the reason of wait on the third line
        ofSetColor(168, 11, 68);
        ofDrawBitmapString(message, thirdLineX, thirdLineY);
    }
    
    // Drawing Matched Gesture, but it is not shown the whole time, only until the waiting timer is up.
    ofSetColor(34, 139, 34);
    matchedGesture.draw();
    
    // First two lines show the common information about.
    ofSetColor(255,250,250);
    ofDrawBitmapString("Number of gestures: " + to_string(gestureRecognizer.gestures.size()), firstLineX, firstLineY);
    ofDrawBitmapString("Name of current gesture: " + gesture->name, secondLineX, secondLineY);
}

//--------------------------------------------------------------
void gestureRec_v2::keyPressed(int key) {
    switch (key) {
        
        // Adding current gesture to the gesture recognizer
        case 'a': {
            cmdAdd();
            break;
        }
        // Recognize Gesture
        case 'r': {
            cmdRecognize();
            break;
        }

        // Clear Current Gesture
        case 'c': {
            cmdClear();
            break;
        }
        
        // Save All Gestures from Gesture Recognizer into "gestures.txt" file
        case 's': {
            cmdSave();
            break;
        }
            
        // Load All Gestures from "gestures.txt" file into Gesture Recognizer
        case 'l': {
            cmdLoad();
            break;
        }
    }
}

//--------------------------------------------------------------
void gestureRec_v2::mouseDragged(int x, int y, int button) {
    // If in drawing mode, keep adding the points on the mouse position while dragging
    if (currentMode == DRAW) currentGesture.addVertex(x, y);
}

//--------------------------------------------------------------
void gestureRec_v2::updateMessage(string msg) {
    // Utility function for updating the message text and set the waiting timer
    message = msg;
    messageTimer = ofGetElapsedTimeMillis() + 3000;
    currentMode = WAIT;
}

//--------------------------------------------------------------
void gestureRec_v2::createNewGesture() {
    gesture = new ofxGesture();
    gesture->setName("Gesture_" + to_string(gestureRecognizer.gestures.size()));
}

//--------------------------------------------------------------
void gestureRec_v2::cmdAdd() {
    createNewGesture();
    for (int i = 0; i < currentGesture.size(); ++i) gesture->addPoint(currentGesture[i].x, currentGesture[i].y);
    
    // If the gesture is too small
    string msg;
    if (gesture->points.size() <= 20) msg = "Gesture is too small!";
    
    // If the gesture is okay
    else {
        gestureRecognizer.addGesture(gesture);
        currentGesture.clear();
        msg = gesture->name + " was added to the gesture recognizer";
        createNewGesture();
    }
    updateMessage(msg);
    currentGesture.clear();
}

//--------------------------------------------------------------
void gestureRec_v2::cmdRecognize() {
    // Create a placeholder for gesture match
    ofxGesture* match = new ofxGesture();
    // Add all points of current gesture to the match gesture
    // Notice that the point of this is that the currentGesture is ofPolyline
    // while match is of type ofxGesture
    // ofxGesture type is provided with ofxOneDollar AddOn
    for (int i = 0; i < currentGesture.size(); ++i) match->addPoint(currentGesture[i].x, currentGesture[i].y);
    currentGesture.clear();
    
    // Calculating the match of current gesture with all existing gestures
    double matchingScore = 0.0;
    match = gestureRecognizer.match(match, &matchingScore);
    if (matchingScore >= 0.77) {
        // In case of big matching score, repopulate the matched gesture
        matchedGesture.clear();
        for (int i = 0; i < match->resampled_points.size(); ++i) {
            int x = ofGetWidth()/2 + match->resampled_points[i].x;
            int y = ofGetHeight()/2 + match->resampled_points[i].y;
            matchedGesture.addVertex(x, y);
        }
        updateMessage("Matching score: " + to_string(matchingScore) + ", which matches with gesture: " + match->name);
    } else updateMessage("Did not match any existing gesture from gesture recognizer");
}

//--------------------------------------------------------------
void gestureRec_v2::cmdClear() {
    currentGesture.clear();
}

//--------------------------------------------------------------
void gestureRec_v2::cmdSave() {
    gestureRecognizer.save(ofToDataPath("gesture.txt", true));
    updateMessage("Gesture was saved into \"gesture.txt\"");
}

//--------------------------------------------------------------
void gestureRec_v2::cmdLoad() {
    if (!loaded) {
        gestureRecognizer.load(ofToDataPath("gesture.txt", true));
        updateMessage("Loaded gestures from \"gesture.txt\"");
        createNewGesture();
        loaded = true;
    } else updateMessage("Gestures already loaded");
}
