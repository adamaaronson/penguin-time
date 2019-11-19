//
//  block.cpp
//  pleasant-platformer
//
//  Created by Adam Aaronson on 11/17/19.
//

#include "block.hpp"

Block::Block(double x, double y, double width, double height, ofColor color_) {
    rect = ofRectangle(x, y, width, height);
    color = color_;
}

ofRectangle Block::getRect() const {
    return rect;
}

ofColor Block::getColor() const {
    return color;
}

void Block::setColor(ofColor color_) {
    color = color_;
}

void Block::draw() {
    ofSetColor(color);
    ofDrawRectangle(rect);
}
