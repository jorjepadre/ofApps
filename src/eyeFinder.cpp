//
//  eyeFinder.cpp
//  featureDetection
//
//  Created by Zhanaidar on 13/12/2022.
//

#include "eyeFinder.hpp"

//--------------------------------------------------------------
void eyeFinder::setup(){
    faceFinder.setup("haarcascade_frontalface_default.xml");
    eyeFinder.setup("haarcascade_eye.xml");
    
    grab.setVerbose(true);
    grab.initGrabber(xVal, yVal);
}

//--------------------------------------------------------------
void eyeFinder::update(){
    grab.update();
    
    if (grab.isFrameNew()) {
        img.setFromPixels(grab.getPixels());
        faceFinder.findHaarObjects(img);
        
        for (int i = 0; i < faceFinder.blobs.size(); ++i) {
            ofRectangle cur = faceFinder.blobs[i].boundingRect;
            origin.x = cur.x;
            origin.y = cur.y;
            faceImg.cropFrom(img, cur.x, cur.y, cur.width, cur.height);
            eyeFinder.findHaarObjects(faceImg);
        }
    }
}

//--------------------------------------------------------------
void eyeFinder::draw(){
    img.draw(0, 0);
    ofNoFill();
    for (int i = 0; i < eyeFinder.blobs.size(); ++i) {
        ofRectangle cur = eyeFinder.blobs[i].boundingRect;
        ofDrawRectangle(cur.x + origin.x, cur.y + origin.y, cur.width, cur.height);
    }
}
