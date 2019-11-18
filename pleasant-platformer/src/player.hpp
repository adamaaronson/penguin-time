//
//  player.hpp
//  pleasant-platformer
//
//  Created by Adam Aaronson on 11/14/19.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include <ofMain.h>

#define DEFAULT_WALK_VEL 5
#define DEFAULT_JUMP_VEL 5

class Player {
private:
    ofRectangle rect;
    ofColor color;

public:
    Player() {};
    Player(int x, int y, int width, int height, ofColor color_);
    Player(int x, int y, int width, int height, int walkVel_, int jumpVel_, ofColor color_);
    
    void setup();
    void update();
    void draw();
    
    ofRectangle getRect() const;
    ofColor getColor() const;
    
    void setColor(ofColor color_);
    
    int xVel = 0;
    int yVel = 0;
    
    bool movingLeft = false;
    bool movingRight = false;
    bool grounded = false;
    
    int walkVel = DEFAULT_WALK_VEL;
    int jumpVel = DEFAULT_JUMP_VEL;
};

#endif /* player_hpp */
