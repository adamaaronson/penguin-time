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

#define DEFAULT_LEVEL_WIDTH 20
#define DEFAULT_LEVEL_HEIGHT 12

class Level {
    
public:
    Level() {};
    Level(Player &player_, std::vector<Block> blocks_);
    Level(Player &player_, std::vector<std::vector<BlockType>> blockTypes);
    
    Player player;
    std::vector<Block> blocks;
};

#endif /* level_hpp */
