//
//  block.cpp
//  pleasant-platformer
//
//  Created by Adam Aaronson on 11/17/19.
//

#include "block.hpp"

Block::Block(int x, int y, int width, int height, ofColor color_) {
    rect = ofRectangle(x, y, width, height);
    color = color_;
}

ofRectangle Block::getRect() {
    return rect;
}

ofColor Block::getColor() {
    return color;
}

void Block::setColor(ofColor color_) {
    color = color_;
}

void Block::draw() {
    ofSetColor(color);
    ofDrawRectangle(rect);
}
