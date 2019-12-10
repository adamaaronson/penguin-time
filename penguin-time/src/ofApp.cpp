#include "ofApp.h"
#include <sstream>

#define LEFT OF_KEY_LEFT
#define RIGHT OF_KEY_RIGHT
#define JUMP OF_KEY_UP
#define RESET 'r'

#define ALT_LEFT 'a'
#define ALT_RIGHT 'd'
#define ALT_JUMP 'w'

#define PLAYER_COLOR ofColor::steelBlue
#define BLOCK_COLOR ofColor::black
#define OVERLAY_COLOR ofColor(255, 255, 255, 150)
#define WADDLE_SPEED 10
#define PORTAL_SPEED 10

#define END_LEVEL 10

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Penguin Time");
    ofSetBackgroundColor(ofColor(160,205,220));
    
    // load sprites
    
    sky.load("../../src/resources/sky.png");
    intro.load("../../src/resources/intro.png");
    outro.load("../../src/resources/outro.png");
    
    littleFont.load("../../src/resources/din.ttf", 12);
    bigFont.load("../../src/resources/din.ttf", 24);
    
    music.load("../../src/resources/penguintime.mp3");
    
    spritesheet = ofxTexturePackerPtr(new ofxTexturePacker());
    spritesheet->load("../../src/resources/spritesheet.xml");
    
    groundTop = spritesheet->getSprite("GroundTop");
    groundBottom = spritesheet->getSprite("GroundBottom");
    deathTop = spritesheet->getSprite("DeathTop");
    deathBottom = spritesheet->getSprite("DeathBottom");
    endGroundTop = spritesheet->getSprite("EndGroundTop");
    endGroundBottom = spritesheet->getSprite("EndGroundBottom");
    
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
    if (!music.isPlaying()) {
        music.play();
    }
    if (gameStarted) {
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
            }
            if (currentLevel == END_LEVEL) {
                gameFinished = true;
                player.walkVel *= 2;
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
        
        if (!gameFinished) {
            if (ofGetFrameRate() > 1) {
                timer += 1 / ofGetFrameRate();
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // draw background
    int bgSize = 4;
    int offset = currentLevel % bgSize;
    for (int x = -1; x <= DEFAULT_LEVEL_WIDTH / bgSize; x++) {
        for (int y = -1; y <= DEFAULT_LEVEL_HEIGHT / bgSize; y++) {
            sky.draw(x * DEFAULT_BLOCK_WIDTH * bgSize + offset * DEFAULT_BLOCK_WIDTH,
                     y * DEFAULT_BLOCK_HEIGHT * bgSize + offset * DEFAULT_BLOCK_HEIGHT);
        }
    }
    
    if (!gameStarted) {
        // draw intro thing
        ofSetColor(OVERLAY_COLOR);
        ofDrawRectangle(width/8, height/8, 3*width/4, 3*height/4);
        ofSetColor(ofColor::white);
        intro.draw(width/8, height/8);
        
    } else {
        Level thisLevel = levels[currentLevel];
        
        // draw blocks
        for (Block* b : thisLevel.blocks) {
            BlockType bType = b->getType();
            bool bTop = b->isTop();
            ofRectangle bRect = b->getRect();
            if (bType == GROUND) {
                if (bTop) {
                    if (gameFinished) {
                        endGroundTop->draw(bRect.x, bRect.y);
                    } else {
                        groundTop->draw(bRect.x, bRect.y);
                    }
                } else {
                    if (gameFinished) {
                        endGroundBottom->draw(bRect.x, bRect.y);
                    } else {
                        groundBottom->draw(bRect.x, bRect.y);
                    }
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
        if (!gameFinished) {
            // draw data overlay
            ofSetColor(OVERLAY_COLOR);
            ofDrawRectangle(20, 20, 240, 56);
            
            ofSetColor(ofColor::black);
            bigFont.drawString("LEVEL " + std::to_string(currentLevel + 1), 32, 60);
            
            stringstream time;
            time << setprecision(floor(log10(timer)) + 3) << timer;
            
            littleFont.drawString("DEATHS: " + std::to_string(player.deaths) + "\nTIME: " + time.str(), 160, 44);
            
            ofSetColor(255, 255, 255);
        }
    }
    
    if (gameFinished) {
        // draw outro thing
        ofSetColor(OVERLAY_COLOR);
        ofDrawRectangle(width/8, height/8, 3*width/4, 3*height/5);
        ofSetColor(ofColor::black);
        outro.draw(width/8, height/8);
        
        bigFont.drawString("DEATHS: " + std::to_string(player.deaths), width * 0.3, height * 2/3);
        
        stringstream time;
        time << setprecision(floor(log10(timer)) + 3) << timer;
        
        bigFont.drawString("TIME: " + time.str(), width * 0.55, height * 2/3);
        ofSetColor(ofColor::white);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (!gameStarted) {
        gameStarted = true;
    } else {
        if (key == LEFT || key == ALT_LEFT) {
            player.movingLeft = true;
            player.facingRight = false;
            player.xVel = -player.walkVel;
        } else if (key == RIGHT || key == ALT_RIGHT) {
            player.movingRight = true;
            player.facingRight = true;
            player.xVel = player.walkVel;
        } else if (key == JUMP || key == ALT_JUMP) {
            player.jump();
        } else if (key == RESET && !gameFinished) {
            player.deaths++;
            player.kaput = true;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (gameStarted) {
        if (key == LEFT || key == ALT_LEFT) {
            player.movingLeft = false;
            if (player.movingRight) {
                player.xVel = player.walkVel;
            } else {
                player.xVel = 0;
            }
        } else if (key == RIGHT || key == ALT_RIGHT) {
            player.movingRight = false;
            if (player.movingLeft) {
                player.xVel = -player.walkVel;
            } else {
                player.xVel = 0;
            }
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
