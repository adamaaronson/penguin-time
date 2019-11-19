#include "ofApp.h"

#define LEFT OF_KEY_LEFT
#define RIGHT OF_KEY_RIGHT
#define JUMP OF_KEY_UP

#define PLAYER_COLOR ofColor::steelBlue
#define BLOCK_COLOR ofColor::black

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(ofColor(0x333333));
    
    player = Player(width/2 - 25, height - 140, 90, 50, PLAYER_COLOR);
    std::vector<Block> blocks;
    blocks.emplace_back(0, height - 50, width, 50, BLOCK_COLOR);
    blocks.emplace_back(width/3, height - 200, 50, 50, BLOCK_COLOR);
    blocks.emplace_back(2*width/3, height - 100, 50, 50, BLOCK_COLOR);

    
    levels.emplace_back(player, blocks);
}

//--------------------------------------------------------------
void ofApp::update(){
    player.update();
    for (Block b : levels[currentLevel].blocks) {
        player.getCollision(b);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    player.draw();
    for (Block b : levels[currentLevel].blocks) {
        b.draw();
    }
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
        if (player.grounded) {
            player.grounded = false;
            player.yVel = -player.jumpVel;
        }
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
