//
//  Rect.hpp
//  MapsPort
//
//  Created by Iskandar on 13.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#ifndef Rect_hpp
#define Rect_hpp

#include <stdio.h>

class Rectangle{
    
public:
    Rectangle();
    Rectangle(float left, float right, float bottom, float top);
    float left, right, bottom, top;
private:
    void init(float left, float right, float bottom, float top);
    
};

#endif /* Rect_hpp */
