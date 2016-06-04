//
//  MapView.hpp
//  MapsPort
//
//  Created by Iskandar on 06.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#ifndef MapView_hpp
#define MapView_hpp
extern "C" {
#include "platform_gl.h"
#include "linmath.h"
#include <stdio.h>
#include "asset_utils.h"
#include "buffer.h"
#include "image.h"
#include "platform_gl.h"
#include "platform_asset_utils.h"
#include "shader.h"
#include "texture.h"
#include "tile.hpp"
//#define TEX_COORD_MAX   1
}
#include <vector>
#include "camera.hpp"

class MapView{
    
public:
    MapView();
    ~MapView();
    void on_surface_created();
    void on_surface_changed(int width, int height);
    void setScale(int scale);
    void on_render();
    
private:
    Camera *camera;
    int scale = 1;
    GLuint _colorRenderBuffer;
    GLuint _textureUniform;
    std::vector<Tile> tiles;
    GLuint _depthRenderBuffer;
};


#endif /* MapView_hpp */
