//
//  file_loader.h
//  MapsPort
//
//  Created by Iskandar on 14.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#ifndef file_loader_h
#define file_loader_h

#include <stdio.h>
#include <string>
#include "file_data.hpp"
#include "platform_gl.h"
#include "raw_image.hpp"
#include "png.h"
#include "FileLoaderPlatform.h"
class FileLoader{
    
public:
    FileLoader();
    TFileData* loadFile(std::string *path);
    TFileData* loadFileFromAssets(std::string *path);
    GLuint load_png_asset_into_texture(std::string *relative_path);
    TRawImageData* get_raw_image_data_from_png(void* png_data, int png_data_size);
    GLuint load_texture(const GLsizei width, const GLsizei height, const GLenum type, const GLvoid* pixels);
    void release_raw_image_data(const TRawImageData* data);
    void release_file_data(TFileData* file_data);
    //void read_png_data_callback(png_structp png_ptr, png_byte* raw_data, png_size_t read_length);
    GLuint build_program_from_assets(std::string *vertex_shader_path, std::string *fragment_shader_path);
    GLuint build_program(const GLchar * vertex_shader_source, const GLint vertex_shader_source_length,
                         const GLchar * fragment_shader_source, const GLint fragment_shader_source_length);
    GLuint compile_shader(const GLenum type, const GLchar* source, const GLint length);
    GLuint link_program(const GLuint vertex_shader, const GLuint fragment_shader);
    TRawImageData* readPng(char* pngData, png_size_t pngLength);
    TRawImageData* readPng2(char* pngData, png_size_t pngLength);
    GLuint load_texture2(
                                     const GLsizei width, const GLsizei height,
                         const GLenum type, const GLvoid* pixels);
};



#endif /* file_loader_h */
