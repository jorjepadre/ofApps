//
//  contoursApp.cpp
//  oFapps
//
//  Created by Zhanaidar on 13/12/2022.
//

#include "contoursApp.hpp"

void contoursApp::setup() {
    learnBackground = false;
    vidGrabber.setVerbose(true);
    
    vidGrabber.initGrabber(xVal, yVal);
    colorImg.allocate(xVal, yVal);
    grayImage.allocate(xVal, yVal);
    grayBg.allocate(xVal, yVal);
    grayDiff.allocate(xVal, yVal);
}

void contoursApp::update() {
    vidGrabber.update();
    if (vidGrabber.isFrameNew()) {
        colorImg.setFromPixels(vidGrabber.getPixels());
        grayImage = colorImg;
        if (learnBackground) {
            grayBg = grayImage;
            learnBackground = false;
        }
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(30);
        
        
        // 10 : Minimum number of pixels in the object to be detected
        // (xVal * yVal) / 8 : Maximum number of pixels in the object to be detected
        // 1 : objects to be detected
        // bFindHoles = false : find holes in the object
        // bUseApproximation = true : tells contourFinder to use approximation
        contourFinder.findContours(grayDiff, 10, (xVal * yVal) / 8, 1, false, true);
    }
}

void contoursApp::draw() {
    ofSetHexColor(0xffffff);
    colorImg.draw(0, 0, xVal, yVal);
    grayDiff.draw(0, yVal, xVal, yVal);
    ofDrawRectangle(xVal, 0, xVal, yVal);
    contourFinder.draw(xVal, 0, xVal, yVal);
    ofColor c(255, 255, 255);
    
    for (int i = 0; i <contourFinder.nBlobs; ++i) {
        ofRectangle r = contourFinder.blobs.at(i).boundingRect;
        r.x += xVal ;
        r.y += yVal;
        c.setHsb(i * 64, 255, 255);
        ofSetColor(c);
        ofDrawRectangle(r);
    }
}


void contoursApp::keyPressed(int key){
    learnBackground = true;
}
