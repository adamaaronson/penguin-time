#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.setSize(DEFAULT_BLOCK_WIDTH * DEFAULT_LEVEL_WIDTH,
                     DEFAULT_BLOCK_HEIGHT * DEFAULT_LEVEL_HEIGHT);
    settings.resizable = false;
    
    shared_ptr<ofAppBaseWindow> window = ofCreateWindow(settings);
    shared_ptr<ofApp> app(new ofApp());

    ofRunApp(window, app);
    ofRunMainLoop();
}
