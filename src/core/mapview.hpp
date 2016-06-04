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
#include "platform_log.h"

//#define TEX_COORD_MAX   1
}
#include "camera.hpp"
#include <vector>
#include "tilelayer.hpp"

class MapView{
    
public:
    MapView();
    ~MapView();
    void on_surface_created();
    void on_surface_changed(int width, int height);
    void setScale(int scale);
    void on_render();
    void on_touch_press(float normalized_x, float normalized_y);
    void on_touches_ended(float normalized_x, float normalized_y);
    void on_touch_drag(float normalized_x, float normalized_y);
    void zoomIn();
    void zoomOut();
    void setZoom(int zoom);
    float x;
    float y;
    bool touch;
    FileLoader *fileLoader;
    HttpPlatform *httpPlatform;
private:
    Camera *camera;
    int scale = 1;
    GLuint _colorRenderBuffer;
    GLuint _textureUniform;
    GLuint _depthRenderBuffer;
    std::vector<TileLayer*> layers;
    int zoom;
};


#endif /* MapView_hpp */
