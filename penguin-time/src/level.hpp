//
//  level.hpp
//  penguin-time
//
//  Created by Adam Aaronson on 11/17/19.
//

#ifndef level_hpp
#define level_hpp

#include <stdio.h>
#include <ofMain.h>
#include "player.hpp"
#include "block.hpp"
#include "enemy.hpp"

#define DEFAULT_LEVEL_WIDTH 20
#define DEFAULT_LEVEL_HEIGHT 12

#define START_CHAR 'S'
#define GROUND_CHAR 'G'
#define DEATH_CHAR '#'
#define ENEMY_CHAR 'E'
#define PORTAL_CHAR 'P'
#define DISTANCE_DELIM ','

class Level {
    
public:
    Level() {};
    Level(ofVec2f startingPoint_, std::vector<Block*> blocks_);
    Level(ofVec2f startingPoint_, std::vector<std::vector<BlockType>> blockTypes, std::vector<double> enemyDistances);
    
    
    ofVec2f startingPoint;
    std::vector<Block*> blocks;
    
    static std::vector<std::string> ReadLines(const std::string &filepath);
    static Level GenerateLevel(std::vector<std::string> grid, std::vector<double> enemyDistances);
    static std::vector<Level> GenerateLevels(std::vector<std::string> grids);
};

#endif /* level_hpp */
