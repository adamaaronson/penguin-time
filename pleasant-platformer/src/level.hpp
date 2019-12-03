//
//  level.hpp
//  pleasant-platformer
//
//  Created by Adam Aaronson on 11/17/19.
//

#ifndef level_hpp
#define level_hpp

#include <stdio.h>
#include <ofMain.h>
#include "player.hpp"
#include "block.hpp"

class Level {
private:
    int levelWidth;
    int levelHeight;
    std::vector<std::vector<BlockType>> blockTypes;
    
public:
    Level() {};
    Level(Player &player_, std::vector<Block> blocks_);
    
    Player player;
    std::vector<Block> blocks;
    
};

#endif /* level_hpp */
