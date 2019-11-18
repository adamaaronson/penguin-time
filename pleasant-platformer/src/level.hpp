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
    Player player;
    std::vector<Block> blocks;
    
public:
    Player getPlayer();
    std::vector<Block> getBlocks();
    
};

#endif /* level_hpp */
