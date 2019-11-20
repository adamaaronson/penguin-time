//
//  player.cpp
//  pleasant-platformer
//
//  Created by Adam Aaronson on 11/14/19.
//

#include "player.hpp"

Player::Player(double x, double y, double width, double height, ofColor color_) {
    rect = ofRectangle(x, y, width, height);
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
    yVel += gravity;
    if (!canJump()) {
        grounded = false;
    }
}

void Player::draw() {
    ofSetColor(color);
    ofDrawRectangle(rect);
}

bool Player::canJump() {
    return grounded && (yVel == 0 || yVel == gravity);
}

void Player::jump() {
    if (canJump()) {
        grounded = false;
        yVel = -jumpVel;
    }
}

Collision Player::getCollision(Block block) {
    ofRectangle bRect = block.getRect();
    double xDist = (rect.x + rect.width / 2) - (bRect.x + bRect.width / 2);
    double yDist = (rect.y + rect.height / 2) - (bRect.y + bRect.height / 2);
    
    double halfWidths = rect.width / 2 + bRect.width / 2;
    double halfHeights = rect.height / 2 + bRect.height / 2;
    Collision col = Collision::NONE;
    
    double xShift = 0;
    double yShift = 0;
    
    if (std::abs(xDist) < halfWidths && std::abs(yDist) < halfHeights) {
        double xOverlap = halfWidths - std::abs(xDist);
        double yOverlap = halfHeights - std::abs(yDist);

        if (xOverlap > yOverlap || (!(xDist > 0 && movingLeft) && !(xDist < 0 && movingRight))) {
            if (yDist > 0) {
                col = Collision::TOP;
                if (!grounded) {
                    yShift = yOverlap;
                }
                if (yVel < 0) {
                    yVel = 0;
                }
            } else {
                col = Collision::BOTTOM;
                if (!grounded) {
                    yShift = -yOverlap;
                }
                grounded = true;
                if (yVel > 0) {
                    yVel = 0;
                }
            }
        } else if (xDist > 0 && movingLeft) {
            col = Collision::LEFT;
            xShift = xOverlap;
        } else if (xDist < 0 && movingRight) {
            col = Collision::RIGHT;
            xShift = -xOverlap;
        }
    }
    rect.translate(xShift, yShift);
    return col;
}

void Player::collideAll(std::vector<Block> blocks) {
    double xShift = 0;
    double yShift = 0;
    for (Block block : blocks) {
        ofRectangle bRect = block.getRect();
        double xDist = (rect.x + rect.width / 2) - (bRect.x + bRect.width / 2);
        double yDist = (rect.y + rect.height / 2) - (bRect.y + bRect.height / 2);
        
        double halfWidths = rect.width / 2 + bRect.width / 2;
        double halfHeights = rect.height / 2 + bRect.height / 2;
        
        if (std::abs(xDist) < halfWidths && std::abs(yDist) < halfHeights) {
            double xOverlap = halfWidths - std::abs(xDist);
            double yOverlap = halfHeights - std::abs(yDist);

            if (xOverlap > yOverlap || (!(xDist > 0 && movingLeft) && !(xDist < 0 && movingRight))) {
                if (yDist > 0) {
                    if (!grounded && yShift <= 0) {
                        yShift += yOverlap;
                    }
                } else {
                    if (!grounded && yShift >= 0) {
                        yShift -= yOverlap;
                    }
                }
            } else if (xDist > 0 && movingLeft && xShift <= 0) {
                xShift += xOverlap;
            } else if (xDist < 0 && movingRight && xShift >= 0) {
                xShift -= xOverlap;
            }
        }
    }
    
    //std::cout << xShift << ", " << yShift << std::endl;
    if (xShift != 0 && yShift != 0) {
        rect.translate(xShift, 0);
        collideAll(blocks);
    } else {
        rect.translate(xShift, yShift);
        if (yShift > 0) {
            if (yVel < 0) {
                yVel = 0;
            }
        } else if (yShift < 0) {
            grounded = true;
            if (yVel > 0) {
                yVel = 0;
            }
        }
    }
}
