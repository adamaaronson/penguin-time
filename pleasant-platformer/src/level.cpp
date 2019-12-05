//
//  level.cpp
//  pleasant-platformer
//
//  Created by Adam Aaronson on 11/17/19.
//

#include "level.hpp"

Level::Level(ofVec2f startingPoint_, std::vector<Block*> blocks_) {
    startingPoint = startingPoint_;
    blocks = blocks_;
}

Level::Level(ofVec2f startingPoint_, std::vector<std::vector<BlockType>> blockTypes, std::vector<double> enemyDistances) {
    startingPoint = startingPoint_;
    int enemyIndex = 0;
    for (int row = 0; row < blockTypes.size(); row++) {
        for (int col = 0; col < blockTypes[0].size(); col++) {
            BlockType type = blockTypes[row][col];
            if (type == ENEMY) {
                blocks.push_back(new Enemy(col * DEFAULT_BLOCK_WIDTH,
                                           row * DEFAULT_BLOCK_HEIGHT,
                                           DEFAULT_BLOCK_WIDTH, DEFAULT_BLOCK_HEIGHT,
                                           enemyDistances[enemyIndex]));
                enemyIndex++;
            } else if (type != AIR) {
                bool isTop = row == 0 || blockTypes[row - 1][col] != type;
                blocks.push_back(new Block(col * DEFAULT_BLOCK_WIDTH,
                                           row * DEFAULT_BLOCK_HEIGHT,
                                           DEFAULT_BLOCK_WIDTH, DEFAULT_BLOCK_HEIGHT,
                                           type, isTop));
            }
            
       }
    }
}
