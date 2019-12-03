#pragma once

#include "ofMain.h"
#include "player.hpp"
#include "block.hpp"
#include "level.hpp"
#include "ofxTexturePacker.h"

class ofApp : public ofBaseApp {
    Player player;
    std::vector<Level> levels;
    int currentLevel = 0;
    
    int width = ofGetWidth();
    int height = ofGetHeight();

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
    
    ofxTexturePackerPtr spritesheet;
    
    ofxTPSpritePtr groundBottom;
    ofxTPSpritePtr groundTop;
    ofxTPSpritePtr deathBottom;
    ofxTPSpritePtr deathTop;
    
    ofxTPSpritePtr playerLeftStand;
    ofxTPSpritePtr playerRightStand;
    ofxTPSpritePtr playerLeftJump;
    ofxTPSpritePtr playerRightJump;
    
    ofxTPAnimatedSpritePtr playerLeftWalk;
    ofxTPAnimatedSpritePtr playerRightWalk;
};
