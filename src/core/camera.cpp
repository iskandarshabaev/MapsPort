//
//  camera.cpp
//  MapsPort
//
//  Created by Iskandar on 08.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#include "camera.hpp"


Camera::Camera(){
    rect = new Rectangle();
    position = new Position(0,0,0);
}

void Camera::moveCamera(float x, float y, float z){
    position->x += x;
    position->y += y;
    position->z += z;
    vec3 eye = {position->x,position->y,(float) position->z+0.000001f};
    vec3 center = {position->x,position->y,(float) position->z};
    vec3 up = {0,1,0};
    mat4x4_look_at(view_matrix, eye, center, up);
    
    rect->left+=x;
    rect->right+=x;
    rect->bottom+=y;
    rect->top+=y;
    
}

void Camera::setPosition(float x, float y, float z){
    position->x = x;
    position->y = y;
    position->z = -z;
    vec3 eye = {position->x,position->y,(float) position->z+0.000001f};
    vec3 center = {position->x,position->y,(float) position->z};
    vec3 up = {0,1,0};
    mat4x4_look_at(view_matrix, eye, center, up);
    
    rect->left+=x;
    rect->right+=x;
    rect->bottom+=y;
    rect->top+=y;
}


void Camera::setZoom(float z){
    position->z = -z;
    vec3 eye = {position->x,position->y,(float) position->z+0.000001f};
    vec3 center = {position->x,position->y,(float) position->z};
    vec3 up = {0,1,0};
    mat4x4_look_at(view_matrix, eye, center, up);
}



void Camera::zoomIn(float z){
    position->z = -z;
    position->x += position->x;
    position->y += position->y;
    vec3 eye = {position->x,position->y,(float) position->z+0.000001f};
    vec3 center = {position->x,position->y,(float) position->z};
    vec3 up = {0,1,0};
    mat4x4_look_at(view_matrix, eye, center, up);
    
    
    rect->left+=position->x/2;
    rect->right+=position->x/2;
    rect->bottom+=position->y/2;
    rect->top+=position->y/2;
}

void Camera::zoomOut(float z){
    position->z = -z;
    position->x -= position->x/2;
    position->y -= position->y/2;
    vec3 eye = {position->x,position->y,(float) position->z+0.000001f};
    vec3 center = {position->x,position->y,(float) position->z};
    vec3 up = {0,1,0};
    mat4x4_look_at(view_matrix, eye, center, up);
    
    
    rect->left-=position->x;
    rect->right-=position->x;
    rect->bottom-=position->y;
    rect->top-=position->y;
}

void Camera::setProjectionMatrix(float width, float height){
    /*
    float ratio = 1.0f;
    float left = -1.0f;
    float right = 1.0f;
    float bottom = -1.0f;
    float top = 1.0f;
    float near = 1.0f;
    float far = 50.0f;
    if (width > height) {
        ratio = (float) width / height;
        left *= ratio;
        right *= ratio;
    } else {
        ratio = (float) height / width;
        bottom *= ratio;
        top *= ratio;
    }
    */
    float w = (float)width / 256/2;
    float h = (float)height / 256/2;
    mat4x4_frustum(projection_matrix, -w, w, -h, h, 1, 50);
    
    rect->left = -w;
    rect->right = w;
    rect->bottom = -h;
    rect->top = h;
}

Rectangle Camera::getRect(){
    return *rect;
}

mat4x4* Camera::getViewMatrix(){
    return &view_matrix;
}


mat4x4* Camera::getProjectionMatrix(){
    return &projection_matrix;
}

mat4x4* Camera::getViewProjectionMatrix(){
    return &view_projection_matrix;
}

Position* Camera::getPosition(){
    return position;
}