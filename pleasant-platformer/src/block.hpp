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
    
public:
    Block(ofRectangle rect);
    ofRectangle getRect();
    
};

#endif /* block_hpp */
