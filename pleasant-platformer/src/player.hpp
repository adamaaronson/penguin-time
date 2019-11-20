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
#include "block.hpp"

#define DEFAULT_WALK_VEL 5.0
#define DEFAULT_JUMP_VEL 8.0
#define DEFAULT_GRAVITY 0.2

enum Collision {
    TOP,
    RIGHT,
    BOTTOM,
    LEFT,
    NONE
};

class Player {
    
private:
    ofRectangle rect;
    ofColor color;

public:
    Player() {};
    Player(double x, double y, double width, double height, ofColor color_);
    
    void setup();
    void update();
    void draw();
    
    ofRectangle getRect() const;
    ofColor getColor() const;
    void setColor(ofColor color_);
    
    double xVel = 0;
    double yVel = 0;
    
    bool movingLeft = false;
    bool movingRight = false;
    bool grounded = true;
    
    double walkVel = DEFAULT_WALK_VEL;
    double jumpVel = DEFAULT_JUMP_VEL;
    double gravity = DEFAULT_GRAVITY;
    
    
    bool canJump();
    void jump();
    
    void collideAll(std::vector<Block> blocks);
};

#endif /* player_hpp */
