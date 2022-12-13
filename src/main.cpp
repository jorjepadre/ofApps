#include "ofMain.h"
#include "ofApp.h"
#include "contoursApp.hpp"
#include "eyeFinder.hpp"
#include "gestureRec.hpp"

//========================================================================
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	// ofRunApp(new ofApp());
    
    // Run Object Detection App
    // ofRunApp(new contoursApp());
    
    // Run Feature (eyes) Detection App
    // ofRunApp(new eyeFinder());
    
    // Run Gesture Detection App
    ofRunApp(new gestureRec());

}
