#include "ofApp.h"

#define LEFT OF_KEY_LEFT
#define RIGHT OF_KEY_RIGHT
#define JUMP OF_KEY_UP
#define RESET 'r'

#define PLAYER_COLOR ofColor::steelBlue
#define BLOCK_COLOR ofColor::black
#define WADDLE_SPEED 10
#define PORTAL_SPEED 10

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Penguin Time");
    ofSetBackgroundColor(ofColor(160,205,220));
    
    // load sprites
    
    sky.load("../../src/sky.png");
    bigFont.load("../../src/din.ttf", 24);
    littleFont.load("../../src/din.ttf", 12);
    
    spritesheet = ofxTexturePackerPtr(new ofxTexturePacker());
    spritesheet->load("../../src/spritesheet.xml");
    
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
    enemyWalk = spritesheet->getAnimatedSprite("EnemyWalk");
    if (enemyWalk != NULL) {
        enemyWalk->setSpeed(WADDLE_SPEED);
        enemyWalk->play();
    } else {
        ofLog(OF_LOG_FATAL_ERROR, "ofApp::setup():: Could not load animated sprite");
    }
    portal = spritesheet->getAnimatedSprite("Portal");
    if (portal != NULL) {
        portal->setSpeed(PORTAL_SPEED);
        portal->play();
    } else {
        ofLog(OF_LOG_FATAL_ERROR, "ofApp::setup():: Could not load animated sprite");
    }
    
    // create levels
    
    std::string levelFile = "../../src/levels.txt";
    
    levels = Level::GenerateLevels(Level::ReadLines(levelFile));
    double startingX = levels[currentLevel].startingPoint.x;
    double startingY = levels[currentLevel].startingPoint.y;
    player = Player(startingX, startingY, DEFAULT_BLOCK_WIDTH, DEFAULT_BLOCK_WIDTH, PLAYER_COLOR);
}

//--------------------------------------------------------------
void ofApp::update(){
    Level thisLevel = levels[currentLevel];
    
    if (player.kaput) {
        player.moveTo(thisLevel.startingPoint);
        player.yVel = 0;
        player.kaput = false;
    }
    
    player.update();
    player.collideAll(thisLevel.blocks);
    
    if (player.atPortal) {
        if (currentLevel < levels.size() - 1) {
            currentLevel++;
        } else {
            gameFinished = true;
        }
        player.kaput = true;
        player.atPortal = false;
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
    
    if (enemyWalk) {
        enemyWalk->update();
    }
    
    if (portal) {
        portal->update();
    }
    
    for (Block* b : thisLevel.blocks) {
        b->update();
    }
    
    if (ofGetFrameRate() > 1) {
        timer += 1/ofGetFrameRate();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    Level thisLevel = levels[currentLevel];
    
    // draw background
    int bgSize = 4;
    int offset = currentLevel % bgSize;
    for (int x = -1; x <= DEFAULT_LEVEL_WIDTH / bgSize; x++) {
        for (int y = -1; y <= DEFAULT_LEVEL_HEIGHT / bgSize; y++) {
            sky.draw(x * DEFAULT_BLOCK_WIDTH * bgSize + offset * DEFAULT_BLOCK_WIDTH,
                     y * DEFAULT_BLOCK_HEIGHT * bgSize + offset * DEFAULT_BLOCK_HEIGHT);
        }
    }
    
    // draw blocks
    for (Block* b : thisLevel.blocks) {
        BlockType bType = b->getType();
        bool bTop = b->isTop();
        ofRectangle bRect = b->getRect();
        if (bType == GROUND) {
            if (bTop) {
                groundTop->draw(bRect.x, bRect.y);
            } else {
                groundBottom->draw(bRect.x, bRect.y);
            }
        } else if (bType == DEATH) {
            if (bTop) {
                deathTop->draw(bRect.x - PIXEL_SIZE, bRect.y - PIXEL_SIZE);
            } else {
                deathBottom->draw(bRect.x - PIXEL_SIZE, bRect.y - PIXEL_SIZE);
            }
        } else if (bType == ENEMY) {
            enemyWalk->draw(bRect.x - PIXEL_SIZE, bRect.y - PIXEL_SIZE);
        } else if (bType == PORTAL) {
            portal->draw(bRect.x - DEFAULT_BLOCK_WIDTH / 3, bRect.y - DEFAULT_BLOCK_WIDTH / 3);
        }
    }
    
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
    
    // draw data overlay
    ofSetColor(255, 255, 255, 150);
    ofDrawRectangle(20, 20, 300, 56);
    
    ofSetColor(ofColor::black);
    bigFont.drawString("LEVEL " + std::to_string(currentLevel + 1), 32, 60);
    littleFont.drawString(("DEATHS: " + std::to_string(player.deaths) + "\nTIME: " + std::to_string(round(timer * 100.0) / 100.0)), 150, 42);
    
    ofSetColor(255, 255, 255);
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
    } else if (key == RESET) {
        player.kaput = true;
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
