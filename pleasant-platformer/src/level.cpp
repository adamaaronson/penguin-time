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
            if (type == PORTAL) {
                blocks.push_back(new Block(col * DEFAULT_BLOCK_WIDTH + DEFAULT_BLOCK_WIDTH / 3,
                                           row * DEFAULT_BLOCK_HEIGHT + DEFAULT_BLOCK_HEIGHT / 3,
                                           DEFAULT_BLOCK_WIDTH / 3, DEFAULT_BLOCK_HEIGHT / 3,
                                           type, false));
            } else if (type == ENEMY) {
                blocks.push_back(new Enemy(col * DEFAULT_BLOCK_WIDTH + PIXEL_SIZE,
                                           row * DEFAULT_BLOCK_HEIGHT + PIXEL_SIZE,
                                           DEFAULT_BLOCK_WIDTH - 2 * PIXEL_SIZE, DEFAULT_BLOCK_HEIGHT - 5 * PIXEL_SIZE,
                                           enemyDistances[enemyIndex]));
                enemyIndex++;
            } else if (type == GROUND) {
                bool isTop = row == 0 || blockTypes[row - 1][col] != type;
                blocks.push_back(new Block(col * DEFAULT_BLOCK_WIDTH,
                                           row * DEFAULT_BLOCK_HEIGHT,
                                           DEFAULT_BLOCK_WIDTH, DEFAULT_BLOCK_HEIGHT,
                                           type, isTop));
            } else if (type == DEATH) {
                bool isTop = row == 0 || blockTypes[row - 1][col] != type;
                blocks.push_back(new Block(col * DEFAULT_BLOCK_WIDTH + PIXEL_SIZE,
                                           row * DEFAULT_BLOCK_HEIGHT + PIXEL_SIZE,
                                           DEFAULT_BLOCK_WIDTH - 2 * PIXEL_SIZE, DEFAULT_BLOCK_HEIGHT - 5 * PIXEL_SIZE,
                                           type, isTop));
            }
            
       }
    }
}
