//
//  player.cpp
//  pleasant-platformer
//
//  Created by Adam Aaronson on 11/14/19.
//

#include "player.hpp"

Player::Player(int x, int y, int width, int height, ofColor color_) {
    rect = ofRectangle(x, y, width, height);
    color = color_;
}

Player::Player(int x, int y, int width, int height, int walkVel_, int jumpVel_, ofColor color_) {
    rect = ofRectangle(x, y, width, height);
    walkVel = walkVel_;
    jumpVel = jumpVel_;
    color = color_;
}

ofRectangle Player::getRect() const {
    return rect;
}

ofColor Player::getColor() const {
    return color;
}

void Player::setColor(ofColor color_) {
    color = color_;
}

void Player::setup() {
    
}

void Player::update() {
    rect.translate(xVel, yVel);
}

void Player::draw() {
    ofSetColor(color);
    ofDrawRectangle(rect);
}
