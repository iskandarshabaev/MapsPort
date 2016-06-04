//
//  tile.cpp
//  MapsPort
//
//  Created by Iskandar on 08.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#include "tile.hpp"
#ifdef __cplusplus
#include <string>
#endif
//#include <android/log.h>

const Vertex Vertices[]  = {
    {{0.5, -0.5, 0}, {1,1}},
    {{0.5, 0.5, 0}, {1, 0}},
    {{-0.5, 0.5, 0}, {0,0}},
    {{-0.5, -0.5, 0}, {0, 1}}
};

const GLubyte Indices[] = {
    0, 1, 2,
    2, 3, 0
};

#include "matrices.h"

Tile::Tile(int x, int y, int z){
    width = 2;
    height = 2;
    this->x = x*2 + width/2;
    this->y = -y*2 - height/2;
    this->z = z;
    std::string tileName = std::to_string(-1*z) + "/" + std::to_string(x) + "/" + std::to_string(y);
    std::string tilePath = "textures/" + tileName + ".png";
    texture = load_png_asset_into_texture(tilePath.c_str());
    program = build_program_from_assets("shaders/simple.vsh", "shaders/simple.fsh");
    
    glUseProgram(program);
    _positionSlot = glGetAttribLocation(program, "Position");
    _modelViewUniform = glGetUniformLocation(program, "Modelview");
    glEnableVertexAttribArray(_positionSlot);
    _texCoordSlot = glGetAttribLocation(program, "TexCoordIn");
    glEnableVertexAttribArray(_texCoordSlot);
    _textureUniform = glGetUniformLocation(program, "Texture");
}

Tile::Tile(int x, int y, int z, GLuint texture, GLuint programm){
    width = 2;
    height = 2;
    this->x = x*2 + width/2;
    this->y = -y*2 - height/2;
    this->z = -z;
    std::string tileName = std::to_string(z) + "/" + std::to_string(x) + "/" + std::to_string(y);
    this->texture = texture;
    this->program = programm;
    
    glUseProgram(program);
    _positionSlot = glGetAttribLocation(program, "Position");
    _modelViewUniform = glGetUniformLocation(program, "Modelview");
    glEnableVertexAttribArray(_positionSlot);
    _texCoordSlot = glGetAttribLocation(program, "TexCoordIn");
    glEnableVertexAttribArray(_texCoordSlot);
    _textureUniform = glGetUniformLocation(program, "Texture");
}

Tile::~Tile(){
    glDeleteTextures(1, &texture);
    //glDeleteProgram(program);
}
void Tile::render(Camera *camera){
    
    //if(interceptRect(camera->getRect())){
        mat4x4_mul(*camera->getViewProjectionMatrix(), *camera->getProjectionMatrix(), *camera->getViewMatrix());
        
        mat4x4_translate(model_matrix, (float)x, (float)y, (float)z);
        //mat4x4_translate_in_place(model_matrix, camX, camY, camZ);
        mat4x4_mul(model_view_projection_matrix, *camera->getViewProjectionMatrix(), model_matrix);
        
        glUniformMatrix4fv(_modelViewUniform, 1, 0, (GLfloat*)model_view_projection_matrix);
        
        glVertexAttribPointer(_positionSlot, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(_texCoordSlot, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) (sizeof(float) * 3));
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(_textureUniform, 0);
        
        glDrawElements(GL_TRIANGLES, sizeof(Indices)/sizeof(Indices[0]), GL_UNSIGNED_BYTE, 0);

    //}else{
        
    //}
    
    }

bool Tile::interceptRect(Rectangle rect){

    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "tile params: x: %g, y: %g, w: %g, h: %g", x, y, width, height);
    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "camera params: left: %g, right: %g, bottop: %g, top: %g", rect.left, rect.right, rect.bottom, rect.top);

    if(((float)x - (float)width/2 > rect.left &&
       (float)x + (float)width/2 < rect.right &&
       (float)y - (float)height/2 > rect.bottom&&
       (float)y + (float)height/2 < rect.top)||
       
       ((float)x - (float)width/2 < rect.right &&
        (float)x + (float)width/2 > rect.left &&
        (float)y - (float)height/2 < rect.top &&
        (float)y + (float)height/2 > rect.bottom
        )){
        return true;
    }else{
        //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "tile params: x: %g, y: %g deleted", x, y);
        return false;
    }
}