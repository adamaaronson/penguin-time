//
//  platformer-tests.cpp
//  pleasant-platformer-tests
//
//  Created by Adam Aaronson on 12/7/19.
//

#include <stdio.h>
#include "player.hpp"
#include "block.hpp"
#include "enemy.hpp"
#include "level.hpp"
#include "catch.hpp"

TEST_CASE("Test test") {
    REQUIRE(1 == 1);
}

TEST_CASE("Level building test") {
    std::vector<std::vector<BlockType>> blockTypes;
    blockTypes.emplace_back();
    blockTypes.emplace_back();
    blockTypes.emplace_back();
    blockTypes[0].push_back(AIR);
    blockTypes[0].push_back(AIR);
    blockTypes[1].push_back(DEATH);
    blockTypes[1].push_back(GROUND);
    blockTypes[2].push_back(GROUND);
    blockTypes[2].push_back(GROUND);
    Level level = Level(ofVec2f(0, 0), blockTypes, std::vector<double>());
    REQUIRE(level.blocks.size() == 4);
    REQUIRE(level.blocks[0]->getType() == DEATH);
    REQUIRE(level.blocks[1]->getType() == GROUND);
    REQUIRE(level.blocks[1]->isTop());
    REQUIRE(level.blocks[2]->isTop());
    REQUIRE(!level.blocks[3]->isTop());
}

TEST_CASE("Text-based level generation test") {
    std::vector<std::string> lines = Level::ReadLines("/Users/adamaaronson/Documents/UIUC/CS126/fantastic-finale-adamaaronson/pleasant-platformer/tests/testlevels.txt");
    std::vector<Level> levels = Level::GenerateLevels(lines);
    REQUIRE(levels.size() == 2);
    REQUIRE(levels[0].blocks.size() == 9);
    REQUIRE(levels[0].startingPoint == ofVec2f(4, 3));
    REQUIRE(levels[0].blocks[0]->getType() == ENEMY);
    REQUIRE(levels[0].blocks[1]->getType() == ENEMY);
    REQUIRE(levels[0].blocks[2]->getType() == GROUND);
    REQUIRE(levels[1].blocks.size() == 10);
}
