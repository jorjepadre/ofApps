//
//  boxCV.cpp
//  oFapps
//
//  Created by Zhanaidar on 13/12/2022.
//

#include "boxCV.hpp"

void boxCV::setup() {
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(xVal, yVal);
    
    colorImg.allocate(xVal, yVal);
    
    grayImage.allocate(xVal, yVal);
    grayBg.allocate(xVal, yVal);
    grayDiff.allocate(xVal, yVal);
    
    ofSetVerticalSync(true);
    
    box2d.init();
    box2d.setGravity(0, 10);
    box2d.setFPS(30.0);
    
    bodyShape = NULL;
    
    bLearningBackground = true;
    threshold = 80;
    
    debugging = false;
    contours = false;
}

void boxCV::update() {
    ofBackground(100, 100, 100);
    float height = ofGetHeight();
    
    vector<ofxBox2dCircle>::iterator cit = circles.begin();
    while (cit != circles.end()) {
        if (cit->getPosition().y > height + 100) circles.erase(cit);
        ++cit;
    }
    
    if (circles.size() < 50) {
        ofxBox2dCircle circle;
        circle.setPhysics(1, 0.5, 0.1);
        float pos = ofRandom(1000) + 10;
        circle.setup(box2d.getWorld(), pos, -100, 10);
        circles.push_back(circle);
    }
    
    box2d.update();
    vidGrabber.update();
    bool newFrame = vidGrabber.isFrameNew();
    if (newFrame) {
//        colorImg.setFromPixels(vidGrabber.getPixels(), xVal, yVal);
        colorImg.setFromPixels(vidGrabber.getPixels());
        colorImg.mirror(false, true);
        
        grayImage = colorImg;
        if (bLearningBackground) {
            grayBg = grayImage;
            bLearningBackground = false;
        }
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
        contourFinder.findContours(grayDiff, 20, (xVal * yVal) / 3, 10, true);
    }
    checkBlobs();
}

void boxCV::draw() {
    ofSetColor(255, 255, 255);
    ofFill();
    
    vector<ofxBox2dCircle>::iterator cit = circles.begin();
    while (cit != circles.end()) {
        ofDrawCircle(cit->getPosition().x, cit->getPosition().y, 10);
        ++cit;
    }
    
    ofSetColor(0, 0, 255);
    
    vector<ofxCvBlob>::iterator c_it = contourFinder.blobs.begin();
    if (contours) {
        while (c_it != contourFinder.blobs.end()) {
            c_it->draw();
            ++c_it;
        }
    }
    
    if (bodyShape) {
        bodyShape->draw();
        
        ofSetColor(0, 0, 255);
        ofFill();
        vector<ofPoint>::iterator pit = bodyShape->getVertices().begin();
        while (pit != bodyShape->getVertices().end()) {
            ofDrawCircle(pit->x, pit->y, 5);
            ++pit;
        }
    }
}

void boxCV::checkBlobs() {
    contourFinder.findContours(grayDiff, 120, (grayDiff.getWidth() * grayDiff.getHeight()) / 2, 5, false);
    
    if (contourFinder.blobs.size() < 1) return;
    
    vector<ofxCvBlob>::iterator c_it = contourFinder.blobs.begin();
    ofxCvBlob largest = contourFinder.blobs[0];
    while (c_it != contourFinder.blobs.end()) {
        if (c_it->area > largest.area) largest = *c_it;
        ++c_it;
    }
    
    if (!debugging) {
        if (bodyShape) {
            bodyShape->destroy();
            delete bodyShape;
        }
        
        bodyShape = new ofxBox2dPolygon();
        ofVec2f scaleUp(ofGetWidth()/xVal, ofGetHeight()/yVal);
        
        vector<ofPoint>::iterator pit = largest.pts.begin();
        while (pit != largest.pts.end()) {
            bodyShape->addVertex(*pit * scaleUp);
            ++pit;
        }
        
        bodyShape->simplify(20);
        bodyShape->create(box2d.getWorld());
    }
}

void boxCV::mouseDragged(int x, int y, int button) {
    if (debugging) {
        if (bodyShape) {
            bodyShape->destroy();
            delete bodyShape;
        }
        bodyShape = new ofxBox2dPolygon();
        ofVec2f ul(x - 50.f, y - 50.f);
        ofVec2f ur(x + 50.f, y - 50.f);
        ofVec2f lr(x + 50.f, y + 50.f);
        ofVec2f ll(x - 50.f, y + 50.f);
        
        bodyShape->addVertex(ul);
        bodyShape->addVertex(ur);
        bodyShape->addVertex(lr);
        bodyShape->addVertex(ll);
        
        bodyShape->create(box2d.getWorld());
    }
}

void boxCV::mousePressed(int x, int y, int button) {
    if (debugging) {
        if (bodyShape) {
            bodyShape->destroy();
            delete bodyShape;
        }
        bodyShape = new ofxBox2dPolygon();
        ofVec2f ul(x - 50.f, y - 50.f);
        ofVec2f ur(x + 50.f, y - 50.f);
        ofVec2f lr(x + 50.f, y + 50.f);
        ofVec2f ll(x - 50.f, y + 50.f);
        
        bodyShape->addVertex(ul);
        bodyShape->addVertex(ur);
        bodyShape->addVertex(lr);
        bodyShape->addVertex(ll);
        
        bodyShape->create(box2d.getWorld());
    }
}

void boxCV::keyPressed(int key) {
    switch (key) {
        case ' ':
            bLearningBackground = true;
            break;
        case '+':
            threshold++;
            if (threshold > 255) threshold = 255;
            break;
        case '-':
            threshold--;
            if (threshold < 0) threshold = 0;
            break;
        case 'd':
            debugging = !debugging;
            break;
        case 'c':
            contours = !contours;
            break;
    }
}
