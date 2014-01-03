#include "ofMain.h"
#include "testApp.h"
#include "ofxFensterManager.h"

//========================================================================
int main( ){

    // Config o'Brother ------------------------------------------
	ofSetupOpenGL(ofxFensterManager::get(), 1600, 900, OF_WINDOW);			// <-------- setup the GL context
//	ofSetupOpenGL(&window, 1200, 1024, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunFensterApp(new testApp());
//	ofRunApp( new testApp());

}
