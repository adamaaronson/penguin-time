#include "ofApp.h"

#define LEFT OF_KEY_LEFT
#define RIGHT OF_KEY_RIGHT
#define JUMP OF_KEY_UP

#define PLAYER_COLOR ofColor::steelBlue
#define BLOCK_COLOR ofColor::black
#define WADDLE_SPEED 10
#define PORTAL_SPEED 15

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(ofColor(160,205,220));
    
    // load sprites
    
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
    
    int gridSize = DEFAULT_BLOCK_WIDTH;
    double blockChance = 0.3;
    double deathChance = 0.1;
    double enemyChance = 0.04;
    
    std::vector<double> enemyDistances;
    std::vector<std::vector<BlockType>> blockTypes;
    for (int row = 0; row < DEFAULT_LEVEL_HEIGHT; row++) {
        blockTypes.emplace_back();
        for (int col = 0; col < DEFAULT_LEVEL_WIDTH; col++) {
            if (ofRandom(1) < enemyChance) {
                blockTypes[row].push_back(ENEMY);
                enemyDistances.push_back(3 * gridSize);
            } else if (ofRandom(1) < deathChance) {
                blockTypes[row].push_back(DEATH);
            } else if (ofRandom(1) < blockChance) {
                blockTypes[row].push_back(GROUND);
            } else {
                blockTypes[row].push_back(AIR);
            }
        }
    }
    blockTypes[1][1] = PORTAL;
    
    for (int col = 0; col < DEFAULT_LEVEL_WIDTH; col++) {
        blockTypes[DEFAULT_LEVEL_HEIGHT - 1][col] = GROUND;
    }
    
    float startingX = gridSize * (int) ofRandom(DEFAULT_LEVEL_WIDTH);
    float startingY = gridSize * (int) ofRandom(DEFAULT_LEVEL_HEIGHT - 2);
    
    player = Player(startingX, startingY, gridSize, gridSize, PLAYER_COLOR);
    
    levels.emplace_back(ofVec2f(startingX, startingY), blockTypes, enemyDistances);
}

//--------------------------------------------------------------
void ofApp::update(){
    Level thisLevel = levels[currentLevel];
    
    player.update();
    player.collideAll(thisLevel.blocks);
    
    if (player.kaput) {
        player.moveTo(thisLevel.startingPoint);
        player.yVel = 0;
        player.kaput = false;
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
    
    
    for (Block* b : levels[currentLevel].blocks) {
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
                deathTop->draw(bRect.x, bRect.y);
            } else {
                deathBottom->draw(bRect.x, bRect.y);
            }
        } else if (bType == ENEMY) {
            enemyWalk->draw(bRect.x, bRect.y);
        } else if (bType == PORTAL) {
            portal->draw(bRect.x, bRect.y);
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
