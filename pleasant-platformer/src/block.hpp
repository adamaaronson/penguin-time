//
//  block.hpp
//  pleasant-platformer
//
//  Created by Adam Aaronson on 11/17/19.
//

#ifndef block_hpp
#define block_hpp

#include <stdio.h>
#include <ofMain.h>

class Block {
private:
    ofRectangle rect;
    ofColor color;
    
public:
    Block() {};
    Block(int x, int y, int width, int height, ofColor color_);
    
    void draw();
    
    ofRectangle getRect();
    ofColor getColor();
    
    void setColor(ofColor color_);
};

#endif /* block_hpp */
