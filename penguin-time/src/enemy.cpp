//
//  enemy.cpp
//  penguin-time
//
//  Created by Adam Aaronson on 12/5/19.
//

#include "enemy.hpp"

Enemy::Enemy(double x, double y, double width, double height, double distance_)
: Block(x, y, width, height, ENEMY, false) {
    startingPoint = ofVec2f(x, y);
    distance = distance_;
    movingRight = true;
    xVel = DEFAULT_ENEMY_VEL;
}

double Enemy::getDistance() {
    return distance;
}

void Enemy::update() {
    if (movingRight) {
        rect.translate(xVel, 0);
    } else {
        rect.translate(-xVel, 0);
    }
    
    if (!movingRight && rect.x <= startingPoint.x) {
        movingRight = true;
    } else if (movingRight && rect.x >= startingPoint.x + distance) {
        movingRight = false;
    }
}
