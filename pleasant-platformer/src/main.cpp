#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofSetupOpenGL(DEFAULT_BLOCK_WIDTH * DEFAULT_LEVEL_WIDTH,
                  DEFAULT_BLOCK_HEIGHT * DEFAULT_LEVEL_HEIGHT,
                  OF_WINDOW);            // <-------- setup the GL context

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());

}
