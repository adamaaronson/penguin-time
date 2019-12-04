//
//  level.cpp
//  pleasant-platformer
//
//  Created by Adam Aaronson on 11/17/19.
//

#include "level.hpp"

Level::Level(Player &player_, std::vector<Block> blocks_) {
    player = player_;
    blocks = blocks_;
}

Level::Level(Player &player_, std::vector<std::vector<BlockType>> blockTypes) {
    for (int row = 0; row < blockTypes.size(); row++) {
        for (int col = 0; col < blockTypes[0].size(); col++) {
            BlockType type = blockTypes[row][col];
            if (type != AIR) {
                bool isTop = row != 0 && blockTypes[row - 1][col] != type;
                blocks.emplace_back(col * DEFAULT_BLOCK_WIDTH,
                                    row * DEFAULT_BLOCK_HEIGHT,
                                    DEFAULT_BLOCK_WIDTH, DEFAULT_BLOCK_HEIGHT,
                                    type, isTop);
            }
            
       }
    }
}
