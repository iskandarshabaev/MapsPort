//
//  Rect.cpp
//  MapsPort
//
//  Created by Iskandar on 13.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#include "rect.hpp"

Rectangle::Rectangle(float left, float right, float bottom, float top){
    init(left, right, bottom, top);
}

Rectangle::Rectangle(){
   init(0, 0, 0, 0);
}

void Rectangle::init(float left, float right, float bottom, float top){
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->top = top;
}
