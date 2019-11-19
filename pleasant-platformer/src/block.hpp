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
    Block(double x, double y, double width, double height, ofColor color_);
    
    void draw();
    
    ofRectangle getRect() const;
    ofColor getColor() const;
    
    void setColor(ofColor color_);
};

#endif /* block_hpp */
