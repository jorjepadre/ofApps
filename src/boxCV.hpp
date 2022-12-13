//
//  boxCV.hpp
//  oFapps
//
//  Created by Zhanaidar on 13/12/2022.
//

#ifndef boxCV_hpp
#define boxCV_hpp

#pragma once
#include <stdio.h>
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxBox2d.h"

class boxCV : public ofBaseApp {
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    
    void checkBlobs();
    
    ofVideoGrabber vidGrabber;
    ofxCvColorImage colorImg;
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage grayBg;
    ofxCvGrayscaleImage grayDiff;
    ofxCvContourFinder contourFinder;
    
    ofxBox2dPolygon *bodyShape;
    ofxBox2d box2d;
    
    vector<ofxBox2dCircle> circles;
    int waterfallEdge, waterfallREdge;
    float radius;
    
    bool debugging, contours;
    bool bLearningBackground;
    
    int threshold;
    float amount;
    
    int xVal = 640, yVal = 480;
    
};

#endif /* boxCV_hpp */
