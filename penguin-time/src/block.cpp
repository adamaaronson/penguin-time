//
//  block.cpp
//  penguin-time
//
//  Created by Adam Aaronson on 11/17/19.
//

#include "block.hpp"

Block::Block(double x, double y, double width, double height, ofColor color_) {
    rect = ofRectangle(x, y, width, height);
    color = color_;
    type = GROUND;
    top = false;
}

Block::Block(double x, double y, double width, double height, BlockType type_, bool top_) {
    rect = ofRectangle(x, y, width, height);
    color = ofColor::white;
    type = type_;
    top = top_;
}

ofRectangle Block::getRect() const {
    return rect;
}

ofColor Block::getColor() const {
    return color;
}

BlockType Block::getType() const {
    return type;
}

bool Block::isTop() const {
    return top;
}

void Block::setColor(ofColor color_) {
    color = color_;
}

void Block::draw() {
    ofSetColor(color);
    ofDrawRectangle(rect);
}
