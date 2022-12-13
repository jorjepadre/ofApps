//
//  contoursApp.hpp
//  oFapps
//
//  Created by Zhanaidar on 13/12/2022.
//

#ifndef contoursApp_hpp
#define contoursApp_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxOpenCv.h"
#pragma once

class contoursApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    
    
    ofxCvContourFinder contourFinder;
    ofxCvColorImage colorImg;
    ofVideoGrabber vidGrabber;
     
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage grayBg;
    ofxCvGrayscaleImage grayDiff;
    
    int threshold;
    bool learnBackground;
    
    int xVal = 640;
    int yVal = 480;
};

#endif /* contoursApp_hpp */
