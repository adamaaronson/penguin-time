//
//  level.cpp
//  penguin-time
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
                bool isTop = row != 0 && blockTypes[row - 1][col] != type;
                blocks.push_back(new Block(col * DEFAULT_BLOCK_WIDTH,
                                           row * DEFAULT_BLOCK_HEIGHT,
                                           DEFAULT_BLOCK_WIDTH, DEFAULT_BLOCK_HEIGHT,
                                           type, isTop));
            } else if (type == DEATH) {
                bool isTop = row != 0 && blockTypes[row - 1][col] != type;
                blocks.push_back(new Block(col * DEFAULT_BLOCK_WIDTH + PIXEL_SIZE,
                                           row * DEFAULT_BLOCK_HEIGHT + PIXEL_SIZE,
                                           DEFAULT_BLOCK_WIDTH - 2 * PIXEL_SIZE, DEFAULT_BLOCK_HEIGHT - 5 * PIXEL_SIZE,
                                           type, isTop));
            }
            
       }
    }
    
    blocks.push_back(new Block(-DEFAULT_BLOCK_WIDTH,
                               -DEFAULT_LEVEL_HEIGHT * DEFAULT_BLOCK_HEIGHT,
                               DEFAULT_BLOCK_WIDTH,
                               2 * DEFAULT_LEVEL_HEIGHT * DEFAULT_BLOCK_HEIGHT,
                               GROUND, false));
    blocks.push_back(new Block(DEFAULT_LEVEL_WIDTH * DEFAULT_BLOCK_WIDTH,
                               -DEFAULT_LEVEL_HEIGHT * DEFAULT_BLOCK_HEIGHT,
                               DEFAULT_BLOCK_WIDTH,
                               2 * DEFAULT_LEVEL_HEIGHT * DEFAULT_BLOCK_HEIGHT,
                               GROUND, false));
}

Level Level::GenerateLevel(std::vector<std::string> grid, std::vector<double> enemyDistances) {
    ofVec2f startingPoint = ofVec2f(0, 0);
    std::vector<std::vector<BlockType>> blockTypes;
    for (int row = 0; row < grid.size(); row++) {
        blockTypes.emplace_back();
        for (int col = 0; col < grid[row].size(); col++) {
            char c = grid[row][col];
            if (c == START_CHAR) {
                startingPoint = ofVec2f(DEFAULT_BLOCK_HEIGHT * col, DEFAULT_BLOCK_WIDTH * row);
                blockTypes.back().push_back(AIR);
            } else if (c == GROUND_CHAR) {
                blockTypes.back().push_back(GROUND);
            } else if (c == DEATH_CHAR) {
                blockTypes.back().push_back(DEATH);
            } else if (c == ENEMY_CHAR) {
                blockTypes.back().push_back(ENEMY);
            } else if (c == PORTAL_CHAR) {
                blockTypes.back().push_back(PORTAL);
            } else {
                blockTypes.back().push_back(AIR);
            }
        }
    }
    return Level(startingPoint, blockTypes, enemyDistances);
}

// split helper method courtesy of StackOverflow
// https://stackoverflow.com/a/236803
template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

std::vector<Level> Level::GenerateLevels(std::vector<std::string> grids) {
    int levelLines = DEFAULT_LEVEL_HEIGHT + 1;
    if (grids.size() % levelLines != 0) {
        ofLog(OF_LOG_FATAL_ERROR, "Level::GenerateLevels: Improper input, invalid number of rows");
    }
    
    std::vector<Level> levels;
    
    for (int level = 0; level < grids.size() / levelLines; level++) {
        std::vector<std::string>::const_iterator first = grids.begin() + level * levelLines;
        std::vector<std::string>::const_iterator last = grids.begin() + (level + 1) * levelLines - 1;
        std::vector<std::string> grid(first, last);
        
        std::vector<std::string> enemyDistanceStrings = split(grids[(level + 1) * levelLines - 1], DISTANCE_DELIM);
        std::vector<double> enemyDistances;
        for (std::string s : enemyDistanceStrings) {
            enemyDistances.push_back(stod(s) * DEFAULT_BLOCK_WIDTH);
        }
        levels.push_back(GenerateLevel(grid, enemyDistances));
    }
    
    return levels;
}

std::vector<std::string> Level::ReadLines(const std::string &filepath) {
    std::vector<std::string> lines;
    ofBuffer buffer = ofBufferFromFile(filepath);
    for (auto line : buffer.getLines()) {
        lines.push_back(line);
    }
    return lines;
}


