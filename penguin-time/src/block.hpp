//
//  block.hpp
//  penguin-time
//
//  Created by Adam Aaronson on 11/17/19.
//

#ifndef block_hpp
#define block_hpp

#include <stdio.h>
#include <ofMain.h>

#define DEFAULT_BLOCK_WIDTH 48
#define DEFAULT_BLOCK_HEIGHT 48
#define BLOCK_PIXELS 16
#define PIXEL_SIZE DEFAULT_BLOCK_WIDTH / BLOCK_PIXELS

enum BlockType {
    AIR,
    GROUND,
    DEATH,
    ENEMY,
    PORTAL
};

class Block {
protected:
    ofRectangle rect;
    ofColor color;
    BlockType type;
    bool top;
    
public:
    Block() {};
    Block(double x, double y, double width, double height, ofColor color_);
    Block(double x, double y, double width, double height, BlockType type_, bool top_);
    
    void draw();
    virtual void update() {};
    
    ofRectangle getRect() const;
    ofColor getColor() const;
    BlockType getType() const;
    bool isTop() const;
    
    void setColor(ofColor color_);
};

#endif /* block_hpp */
