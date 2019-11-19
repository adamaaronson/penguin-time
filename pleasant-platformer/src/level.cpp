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
