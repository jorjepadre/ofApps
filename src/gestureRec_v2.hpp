//
//  gestureRec_v2.hpp
//  oFapps
//
//  Created by Zhanaidar on 15/12/2022.
//

#ifndef gestureRec_v2_hpp
#define gestureRec_v2_hpp

#pragma once
#include <stdio.h>
#include "ofMain.h"
#include "ofxOneDollar.h"


enum mode { DRAW, WAIT };

class gestureRec_v2 : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void mouseDragged(int x, int y, int button);
    void updateMessage(string msg);
    
    void createNewGesture();
    
    // Commands on pressing keys
    void cmdAdd();
    void cmdRecognize();
    void cmdClear();
    void cmdSave();
    void cmdLoad();

    // Mode | Drawing or Recognizing/Saving/Loading (waiting)
    mode currentMode;
    
    // Storing current and matched gestures
    ofPolyline currentGesture;
    ofPolyline matchedGesture;
    
    // Using ofxOneDollar AddOn for the gesture creation, storage and matching functions
    ofxOneDollar gestureRecognizer;
    ofxGesture* gesture;
    
    // Boolean value to check if the gestures were already loaded
    // Needed for refusing loading same gestures many times
    bool loaded;
    
    // Timer for when to switch modes from waiting to drawing + message
    uint64_t messageTimer;
    string message;

    // Coordination of the text lines
    int firstLineX, firstLineY;
    int secondLineX, secondLineY;
    int thirdLineX, thirdLineY;

};

#endif /* gestureRec_v2_hpp */
