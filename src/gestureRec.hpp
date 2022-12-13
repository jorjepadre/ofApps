//
//  gestureRec.hpp
//  oFapps
//
//  Created by Zhanaidar on 13/12/2022.
//

#ifndef gestureRec_hpp
#define gestureRec_hpp

#pragma once
#include <stdio.h>
#include "ofMain.h"
#include "ofxOneDollar.h"

enum action { SAVE, LOAD, MAKE, FIND, CLEAR };

class gestureRec : public ofBaseApp {
public:
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void mouseDragged(int x, int y, int button);
    void showMessage(string sMessage, int nDelay);
    void showMessage(string sMessage);
    
    void createNewGesture();
    
    ofPolyline line;
    ofPolyline foundGesture;
    
    ofxOneDollar dollar;
    ofxGesture* gesture;
    
    int numCreatedGestures;
    
    int mode;
    action command;
    string message;
    uint64_t hideMessageOn;
    
};

#endif /* gestureRec_hpp */
