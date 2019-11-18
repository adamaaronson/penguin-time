//
//  block.cpp
//  pleasant-platformer
//
//  Created by Adam Aaronson on 11/17/19.
//

#include "block.hpp"

Block::Block(ofRectangle rect) {
    rect = rect;
}

ofRectangle Block::getRect() {
    return rect;
}
