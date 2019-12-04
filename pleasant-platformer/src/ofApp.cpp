#include "ofApp.h"

#define LEFT OF_KEY_LEFT
#define RIGHT OF_KEY_RIGHT
#define JUMP OF_KEY_UP

#define PLAYER_COLOR ofColor::steelBlue
#define BLOCK_COLOR ofColor::black
#define WADDLE_SPEED 10

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(ofColor(160,205,220));
    
    // load sprites
    
    spritesheet = ofxTexturePackerPtr(new ofxTexturePacker());
    spritesheet->load("/Users/adamaaronson/Documents/UIUC/CS126/fantastic-finale-adamaaronson/pleasant-platformer/src/spritesheet.xml");
    
    groundTop = spritesheet->getSprite("GroundTop");
    groundBottom = spritesheet->getSprite("GroundBottom");
    deathTop = spritesheet->getSprite("DeathTop");
    deathBottom = spritesheet->getSprite("DeathBottom");
    
    playerRightStand = spritesheet->getSprite("PlayerRightStand");
    playerLeftStand = spritesheet->getSprite("PlayerLeftStand");
    playerRightJump = spritesheet->getSprite("PlayerRightJump");
    playerLeftJump = spritesheet->getSprite("PlayerLeftJump");
    
    playerRightWalk = spritesheet->getAnimatedSprite("PlayerRightWalk");
    if (playerRightWalk != NULL) {
        playerRightWalk->setSpeed(WADDLE_SPEED);
        playerRightWalk->play();
    } else {
        ofLog(OF_LOG_FATAL_ERROR, "ofApp::setup():: Could not load animated sprite");
    }
    playerLeftWalk = spritesheet->getAnimatedSprite("PlayerLeftWalk");
    if (playerLeftWalk != NULL) {
        playerLeftWalk->setSpeed(WADDLE_SPEED);
        playerLeftWalk->play();
    } else {
        ofLog(OF_LOG_FATAL_ERROR, "ofApp::setup():: Could not load animated sprite");
    }
    
    int gridSize = DEFAULT_BLOCK_WIDTH;
    double blockChance = 0.3;
    double deathChance = 0.1;
    
    std::vector<std::vector<BlockType>> blockTypes;
    for (int row = 0; row < DEFAULT_LEVEL_HEIGHT; row++) {
        blockTypes.emplace_back();
        for (int col = 0; col < DEFAULT_LEVEL_WIDTH; col++) {
            if (ofRandom(1) < deathChance) {
                blockTypes[row].push_back(DEATH);
            } else if (ofRandom(1) < blockChance) {
                blockTypes[row].push_back(GROUND);
            } else {
                blockTypes[row].push_back(AIR);
            }
        }
    }
    
    for (int col = 0; col < DEFAULT_LEVEL_WIDTH; col++) {
        blockTypes[DEFAULT_LEVEL_HEIGHT - 1][col] = GROUND;
    }
    
    player = Player(gridSize * (int) ofRandom(DEFAULT_LEVEL_WIDTH), height - gridSize * (1 + (int) ofRandom(DEFAULT_LEVEL_HEIGHT - 1)), gridSize, gridSize, PLAYER_COLOR);
    
    levels.emplace_back(player, blockTypes);
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
    
    if (player.movingRight) {
        if (playerRightWalk) {
            playerRightWalk->update();
        }
    } else if (player.movingLeft) {
        if (playerLeftWalk) {
            playerLeftWalk->update();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // draw player
    float playerX = player.getRect().x;
    float playerY = player.getRect().y;
    
    if (!player.grounded) {
        if (player.facingRight) {
            playerRightJump->draw(playerX, playerY);
        } else {
            playerLeftJump->draw(playerX, playerY);
        }
    } else if (player.movingRight) {
        playerRightWalk->draw(playerX, playerY);
    } else if (player.movingLeft) {
        playerLeftWalk->draw(playerX, playerY);
    } else {
        if (player.facingRight) {
            playerRightStand->draw(playerX, playerY);
        } else {
            playerLeftStand->draw(playerX, playerY);
        }
    }
    
    
    for (Block b : levels[currentLevel].blocks) {
        if (b.getType() == GROUND) {
            if (b.isTop()) {
                groundTop->draw(b.getRect().x, b.getRect().y);
            } else {
                groundBottom->draw(b.getRect().x, b.getRect().y);
            }
        } else if (b.getType() == DEATH) {
            if (b.isTop()) {
                deathTop->draw(b.getRect().x, b.getRect().y);
            } else {
                deathBottom->draw(b.getRect().x, b.getRect().y);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == LEFT) {
        player.movingLeft = true;
        player.facingRight = false;
        player.xVel = -player.walkVel;
    } else if (key == RIGHT) {
        player.movingRight = true;
        player.facingRight = true;
        player.xVel = player.walkVel;
    } else if (key == JUMP) {
        player.jump();
    } else if (key == 32) {
        setup();
        currentLevel++;
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
