//
//  raw_image.hpp
//  MapsPort
//
//  Created by Iskandar on 15.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#ifndef raw_image_hpp
#define raw_image_hpp

#include <stdio.h>
#include "platform_gl.h"
#include <string>

class TRawImageData{
public:
    int x;
    int y;
    int z;
    int width;
    int height;
    int size;
    GLenum gl_color_format;
    void* data;
};
#endif /* raw_image_hpp */
