#include "ofApp.h"

#define LEFT OF_KEY_LEFT
#define RIGHT OF_KEY_RIGHT
#define JUMP OF_KEY_UP

#define PLAYER_COLOR ofColor::steelBlue
#define BLOCK_COLOR ofColor::black

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(ofColor(0x333333));
    
    player = Player(width/2 - 25, height - 120, 50, 50, PLAYER_COLOR);
    
    std::vector<Block> blocks;
    
    blocks.emplace_back(0, height - 50, width, 50, BLOCK_COLOR);
    
    int horizontalBoxes = width / 50;
    int verticalBoxes = height / 50;
    for (int i = 0; i < 50; i++) {
        blocks.emplace_back(50 * (int) ofRandom(horizontalBoxes), height - 50 * (int) ofRandom(verticalBoxes), 50, 50, BLOCK_COLOR);
    }
    
    /*
    blocks.emplace_back(1*width/5, height - 144, 50, 50, BLOCK_COLOR);
    blocks.emplace_back(2*width/5, height - 146, 50, 50, BLOCK_COLOR);
    blocks.emplace_back(3*width/5, height - 54, 50, 50, BLOCK_COLOR);
    blocks.emplace_back(4*width/5, height - 56, 50, 50, BLOCK_COLOR);
    */
    
    levels.emplace_back(player, blocks);
}

//--------------------------------------------------------------
void ofApp::update(){
    player.update();
    player.collideAll(levels[currentLevel].blocks);
    
    if (player.grounded) {
        player.setColor(ofColor::red);
    } else {
        player.setColor(PLAYER_COLOR);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    player.draw();
    for (Block b : levels[currentLevel].blocks) {
        b.draw();
    }
    ofSetColor(ofColor::white);
    ofDrawBitmapString("xVel: " + std::to_string(player.xVel) + "\n" +
                       "yVel: " + std::to_string(player.yVel) + "\n", 10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == LEFT) {
        player.movingLeft = true;
        player.xVel = -player.walkVel;
    } else if (key == RIGHT) {
        player.movingRight = true;
        player.xVel = player.walkVel;
    } else if (key == JUMP) {
        player.jump();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == LEFT) {
        player.movingLeft = false;
        if (player.movingRight) {
            player.xVel = player.walkVel;
        } else {
            player.xVel = 0;
        }
    } else if (key == RIGHT) {
        player.movingRight = false;
        if (player.movingLeft) {
            player.xVel = -player.walkVel;
        } else {
            player.xVel = 0;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
