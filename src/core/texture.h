//
//  texture.hpp
//  MapsPort
//
//  Created by Iskandar on 06.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#ifndef texture_hpp
#define texture_hpp

#include <stdio.h>
#include "platform_gl.h"

GLuint load_texture(const GLsizei width, const GLsizei height,
                    const GLenum type, const GLvoid* pixels);
#endif /* texture_hpp */
