#include "ofApp.h"

#define LEFT OF_KEY_LEFT
#define RIGHT OF_KEY_RIGHT
#define JUMP OF_KEY_UP

#define PLAYER_COLOR ofColor::steelBlue
#define BLOCK_COLOR ofColor::black

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(ofColor(0x333333));
    
    int gridSize = 40;
    int numBlocks = 100;
    
    std::vector<Block> blocks;
    blocks.emplace_back(0, height - gridSize, width, gridSize, BLOCK_COLOR);
    
    int horizontalBoxes = width / gridSize;
    int verticalBoxes = height / gridSize;
    for (int i = 0; i < numBlocks; i++) {
        blocks.emplace_back(gridSize * (int) ofRandom(horizontalBoxes), height - gridSize * (int) ofRandom(verticalBoxes), gridSize, gridSize, BLOCK_COLOR);
    }
    player = Player(gridSize * (int) ofRandom(horizontalBoxes), height - gridSize * (1 + (int) ofRandom(verticalBoxes - 1)), gridSize, gridSize, PLAYER_COLOR);
    player.gravity = DEFAULT_GRAVITY * 50 / gridSize;
    
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
