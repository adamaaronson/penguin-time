#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(ofColor(0x333333));
    player = Player(ofGetWidth()/2 - 25, ofGetHeight() - 150, 50, 100, ofColor::steelBlue);
    
    Block bottom = Block(0, ofGetHeight() - 50, ofGetWidth(), 50, ofColor::white);
    blocks.push_back(bottom);
}

//--------------------------------------------------------------
void ofApp::update(){
    player.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    player.draw();
    for (Block b : blocks) {
        b.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_LEFT) {
        player.movingLeft = true;
        player.xVel = -player.walkVel;
    } else if (key == OF_KEY_RIGHT) {
        player.movingRight = true;
        player.xVel = player.walkVel;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == OF_KEY_LEFT) {
        player.movingLeft = false;
        if (player.movingRight) {
            player.xVel = player.walkVel;
        } else {
            player.xVel = 0;
        }
    } else if (key == OF_KEY_RIGHT) {
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
