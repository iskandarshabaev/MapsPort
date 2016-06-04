//
//  buffer.hpp
//  MapsPort
//
//  Created by Iskandar on 06.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#ifndef buffer_hpp
#define buffer_hpp

#include <stdio.h>
#include "platform_gl.h"

#define BUFFER_OFFSET(i) ((void*)(i))

GLuint create_vbo(const GLsizeiptr size, const GLvoid* data, const GLenum usage);

#endif /* buffer_hpp */
