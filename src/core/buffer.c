//
//  buffer.cpp
//  MapsPort
//
//  Created by Iskandar on 06.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#include "buffer.h"
#include "platform_gl.h"
#include <assert.h>
#include <stdlib.h>

GLuint create_vbo(const GLsizeiptr size, const GLvoid* data, const GLenum usage) {
    assert(data != NULL);
    GLuint vbo_object;
    glGenBuffers(1, &vbo_object);
    assert(vbo_object != 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo_object);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    return vbo_object;
}