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

#define DEFAULT_WALK_VEL 10
#define DEFAULT_JUMP_VEL 10

class Player {
private:
    ofRectangle rect;
    int xVel = 0;
    int yVel = 0;
    
    bool movingLeft = false;
    bool movingRight = false;
    bool grounded = false;
    
    int walkVel = DEFAULT_WALK_VEL;
    int jumpVel = DEFAULT_JUMP_VEL;
    
public:
    Player(ofRectangle rect);
    Player(ofRectangle rect, int walkVel, int jumpVel);
    
    ofRectangle getRect() const;
    int getXVel() const;
    int getYVel() const;
    bool isGrounded() const;
    
    int getWalkVel() const;
    int getJumpVel() const;
    
    void update();
};

#endif /* player_hpp */
