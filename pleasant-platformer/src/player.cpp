//
//  player.cpp
//  pleasant-platformer
//
//  Created by Adam Aaronson on 11/14/19.
//

#include "player.hpp"
#include <ofMain.h>

Player::Player(ofRectangle rect) {
    rect = rect;
}

Player::Player(ofRectangle rect, int walkVel, int jumpVel) {
    rect = rect;
    walkVel = walkVel;
    jumpVel = jumpVel;
}

ofRectangle Player::getRect() const {
    return rect;
}

int Player::getXVel() const {
    return xVel;
}

int Player::getYVel() const {
    return yVel;
}

bool Player::isGrounded() const {
    return grounded;
}

int Player::getJumpVel() const {
    return jumpVel;
}

int Player::getWalkVel() const {
    return walkVel;
}

void Player::update() {
    rect.translate(xVel, yVel);
    if (grounded) {
        
    }
}
