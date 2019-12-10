//
//  enemy.hpp
//  pleasant-platformer
//
//  Created by Adam Aaronson on 12/5/19.
//

#ifndef enemy_hpp
#define enemy_hpp

#include <stdio.h>
#include <ofMain.h>
#include "block.hpp"
#include "player.hpp"

#define DEFAULT_ENEMY_VEL DEFAULT_WALK_VEL / 2

class Enemy : public Block {
private:
    ofVec2f startingPoint;
    double distance;
    bool movingRight;
    double xVel;
public:
    Enemy(double x, double y, double width, double height, double distance_);
    
    double getDistance();
    
    void update() override;
};

#endif /* enemy_hpp */
