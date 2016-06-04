//
//  tile.hpp
//  MapsPort
//
//  Created by Iskandar on 08.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#ifndef tile_hpp
#define tile_hpp

#include <stdio.h>
#include "vertex.hpp"
#include "camera.hpp"

extern "C" {
#include "platform_gl.h"
#include "asset_utils.h"
#include "linmath.h"
}
#include <stdlib.h>
class Tile{
    
public:
    
    Tile(int x, int y, int z);
    Tile(int x, int y, int z, GLuint texture, GLuint programm);
    ~Tile();
    void render(Camera *camera);
    bool interceptRect(Rectangle rect);
    float x;
    float y;
    float z;
private:
    GLuint texture;
    GLuint program;
    float width;
    float height;
    GLuint _positionSlot;
    GLuint _modelViewUniform;
    GLuint _texCoordSlot;
    GLuint _textureUniform;
    mat4x4 model_matrix;
    mat4x4 model_view_projection_matrix;
};

#endif /* tile_hpp */
