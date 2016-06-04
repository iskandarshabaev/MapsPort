//
//  camera.hpp
//  MapsPort
//
//  Created by Iskandar on 08.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include <stdio.h>
#include "linmath.h"
#include "rect.hpp"
#include "position.hpp"

class Camera{

public:
    Camera();
    ~Camera();
    void moveCamera(float x, float y, float z);
    void setPosition(float x, float y, float z);
    void setZoom(float z);
    void zoomIn(float z);
    void zoomOut(float z);
    void setProjectionMatrix(float w, float h);
    mat4x4* getViewMatrix();
    mat4x4* getProjectionMatrix();
    mat4x4* getViewProjectionMatrix();
    Rectangle getRect();
    Position* getPosition();
private:
    Position *position;
    Rectangle *rect;
    mat4x4 view_matrix;
    mat4x4 projection_matrix;
    mat4x4 view_projection_matrix;
};

#endif /* camera_hpp */
