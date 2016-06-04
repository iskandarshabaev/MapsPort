//
//  file_loader.cpp
//  MapsPort
//
//  Created by Iskandar on 14.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#include <stdio.h>
#include "file_loader.h"
#include <stdio.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
//#include <android/log.h>
FileLoaderPlatform *loader;

FileLoader::FileLoader(){
    loader = new FileLoaderPlatform();
}

TFileData* FileLoader::loadFile(std::string *path){
    std::string *basePath = new std::string(loader->getAppPath());
    *basePath += "/" + *path;
    FILE* stream = fopen(basePath->c_str(), "r");
    if (stream == NULL){
        return NULL;
    }
    
    fseek(stream, 0, SEEK_END);
    long stream_size = ftell(stream);
    fseek(stream, 0, SEEK_SET);
    
    void* buffer = malloc(stream_size);
    fread(buffer, stream_size, 1, stream);

    if (ferror(stream) != 0)return NULL;
    fclose(stream);
    
    TFileData *fileData = new TFileData();
    fileData->data_length = stream_size;
    fileData->data = buffer;
    return fileData;
}

TFileData* FileLoader::loadFileFromAssets(std::string *path){
    
    return loader->getAsset(path);
}

GLuint FileLoader::load_png_asset_into_texture(std::string *relative_path){
    TFileData *png_file = loadFile(relative_path);
    if(png_file==NULL) return 0;
    TRawImageData* raw_image_data = get_raw_image_data_from_png(png_file->data, png_file->data_length);
    GLuint texture_object_id = load_texture(
                                                  raw_image_data->width, raw_image_data->height,
                                                  raw_image_data->gl_color_format, raw_image_data->data);
    
    release_raw_image_data(raw_image_data);
    release_file_data(png_file);
    
    return texture_object_id;

}


GLuint FileLoader::build_program_from_assets(std::string *vertex_shader_path, std::string *fragment_shader_path) {
    assert(vertex_shader_path != NULL);
    assert(fragment_shader_path != NULL);
    
    TFileData *vertex_shader_source = loadFileFromAssets(vertex_shader_path);
    TFileData *fragment_shader_source = loadFileFromAssets(fragment_shader_path);
    GLuint program_object_id = build_program((GLchar*)vertex_shader_source->data, vertex_shader_source->data_length,
                                            (GLchar*)fragment_shader_source->data, fragment_shader_source->data_length);
    
    release_file_data(vertex_shader_source);
    release_file_data(fragment_shader_source);
    
    return program_object_id;
}

GLuint FileLoader::build_program(
                     const GLchar * vertex_shader_source, const GLint vertex_shader_source_length,
                     const GLchar * fragment_shader_source, const GLint fragment_shader_source_length) {
    assert(vertex_shader_source != NULL);
    assert(fragment_shader_source != NULL);
    
    GLuint vertex_shader = compile_shader(
                                          GL_VERTEX_SHADER, vertex_shader_source, vertex_shader_source_length);
    GLuint fragment_shader = compile_shader(
                                            GL_FRAGMENT_SHADER, fragment_shader_source, fragment_shader_source_length);
    return link_program(vertex_shader, fragment_shader);
}


GLuint FileLoader::compile_shader(const GLenum type, const GLchar* source, const GLint length) {
    assert(source != NULL);
    GLuint shader_object_id = glCreateShader(type);
    GLint compile_status;
    
    assert(shader_object_id != 0);
    
    glShaderSource(shader_object_id, 1, (const GLchar **)&source, &length);
    glCompileShader(shader_object_id);
    glGetShaderiv(shader_object_id, GL_COMPILE_STATUS, &compile_status);
    assert(compile_status != 0);
    return shader_object_id;
}


GLuint FileLoader::link_program(const GLuint vertex_shader, const GLuint fragment_shader) {
    GLuint program_object_id = glCreateProgram();
    GLint link_status;
    
    assert(program_object_id != 0);
    
    glAttachShader(program_object_id, vertex_shader);
    glAttachShader(program_object_id, fragment_shader);
    glLinkProgram(program_object_id);
    glGetProgramiv(program_object_id, GL_LINK_STATUS, &link_status);

    assert(link_status != 0);
    
    return program_object_id;
}

typedef struct {
    png_byte* data;
    png_size_t size;
} DataHandle;

typedef struct {
    DataHandle data;
    png_size_t offset;
} ReadDataHandle;

typedef struct {
    png_uint_32 width;
    png_uint_32 height;
    int color_type;
} PngInfo;

static void read_png_data_callback(
                                   png_structp png_ptr, png_byte* png_data, png_size_t read_length);
static PngInfo read_and_update_info(const png_structp png_ptr, const png_infop info_ptr);
static DataHandle read_entire_png_image(
                                        const png_structp png_ptr, const png_infop info_ptr, const png_uint_32 height);
static GLenum get_gl_color_format(const int png_color_format);

TRawImageData* FileLoader::get_raw_image_data_from_png(void* png_data, int png_data_size) {
    assert(png_data != NULL && png_data_size > 8);
    //assert(png_check_sig((void*)png_data, 8));
    
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    assert(png_ptr != NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    assert(info_ptr != NULL);
    
    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "read raw");
    ReadDataHandle png_data_handle = (ReadDataHandle) {(DataHandle){(png_byte*)png_data, (png_size_t)(png_data_size)}, 0};
    png_set_read_fn(png_ptr, &png_data_handle, read_png_data_callback);
    
    if (setjmp(png_jmpbuf(png_ptr))) {
        //CRASH("Error reading PNG file!");
        //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "Error reading PNG file");
        //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "png_data_size: %d",png_data_size);
        return NULL;
    }
    
    const PngInfo png_info = read_and_update_info(png_ptr, info_ptr);
    const DataHandle raw_image = read_entire_png_image(png_ptr, info_ptr, png_info.height);
    
    png_read_end(png_ptr, info_ptr);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    
    TRawImageData* rawImageData = new TRawImageData();
    rawImageData->width = png_info.width;
    rawImageData->height = png_info.height;
    rawImageData->size = raw_image.size;
    rawImageData->gl_color_format = get_gl_color_format(png_info.color_type);
    rawImageData->data = raw_image.data;
    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "return raw");
    return rawImageData;
}

struct image {
    png_uint_32 imWidth, imHeight; //реальный размер картинки
    png_uint_32 glWidth, glHeight; //размер который подойдет для OpenGL
    int bit_depth, color_type;
    char* data; //данные RGB/RGBA
};

//ф-ция определяющая размер картинки который подойдет для OpenGL
static int reNpot(int w) {
    //поддерживает ли OpenGL текстуры размера не кратным двум
    //эту переменную конечно надо определять один раз при старте проги с помощью
    //String s = gl.glGetString(GL10.GL_EXTENSIONS);
    //NON_POWER_OF_TWO_SUPPORTED = s.contains("texture_2D_limited_npot") || s.contains("texture_npot") || s.contains("texture_non_power_of_two");
    bool NON_POWER_OF_TWO_SUPPORTED = false;
    if (NON_POWER_OF_TWO_SUPPORTED) {
        if (w % 2) w++;
    } else {
        if (w <= 4) w = 4;
        else if (w <= 8) w = 8;
        else if (w <= 16) w = 16;
        else if (w <= 32) w = 32;
        else if (w <= 64) w = 64;
        else if (w <= 128) w = 128;
        else if (w <= 256) w = 256;
        else if (w <= 512) w = 512;
        else if (w <= 1024) w = 1024;
        else if (w <= 2048) w = 2048;
        else if (w <= 4096) w = 4096;
    }
    return w;
}





struct mypng {
    unsigned int pos;//текущая позиция в массиве
    unsigned int length;//длинна массива
    const char* data;//массив содержащий сжатую картинку
};

static void userReadData(png_structp png_ptr, png_bytep data, png_size_t length) {
    //получаем ссылку на структуру
    mypng* png = (mypng*) png_get_io_ptr(png_ptr);
    //смотрим чтобы не вылезти за края массива
    if (png->pos + length > png->length) length += png->pos-png->length;
    if (length > 0) {
        //копируем данные из массива
        memcpy(data, png->data + png->pos, length);
        //двигаем текущую позицию
        png->pos += length;
    }
}

TRawImageData* FileLoader::readPng(char* pngData, png_size_t pngLength) {
    
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    mypng png = { 8, static_cast<unsigned int>(pngLength), pngData };
    png_init_io(png_ptr, (FILE*) &png);
    png_set_read_fn(png_ptr, png_get_io_ptr(png_ptr), userReadData);
    
    if (setjmp(png_jmpbuf(png_ptr))) {
        //CRASH("Error reading PNG file!");
        //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "Error reading PNG file");
    }
    
    //const PngInfo png_info = read_and_update_info(png_ptr, info_ptr);
    //const DataHandle raw_image = read_entire_png_image(png_ptr, info_ptr, png_info.height);
    
    //png_read_end(png_ptr, info_ptr);
    //png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    
    TRawImageData* rawImageData = new TRawImageData();
    rawImageData->width = 256;
    rawImageData->height = 256;
    rawImageData->size = png.length;
    rawImageData->gl_color_format = GL_RGBA;
    rawImageData->data = (void*)png.data;
    return rawImageData;
}




GLuint FileLoader::load_texture(
                    const GLsizei width, const GLsizei height,
                    const GLenum type, const GLvoid* pixels) {
    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "Loading texture");
    GLuint texture_object_id;
    glGenTextures(1, &texture_object_id);
    assert(texture_object_id != 0);
    
    glBindTexture(GL_TEXTURE_2D, texture_object_id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(
                 GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "Texture loaded");
    return texture_object_id;
}

GLuint FileLoader::load_texture2(
                                const GLsizei width, const GLsizei height,
                                const GLenum type, const GLvoid* pixels) {
    GLuint texture_object_id;
    glGenTextures(1, &texture_object_id);
    glBindTexture(GL_TEXTURE_2D, texture_object_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, im.glWidth, im.glHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, im.data);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    
    return texture_object_id;
}

void FileLoader::release_raw_image_data(const TRawImageData* data) {
    assert(data != NULL);
    free((void*)data->data);
}

void FileLoader::release_file_data(TFileData* file_data) {
    assert(file_data != NULL);
    assert(file_data->data != NULL);
    
    free((void*)file_data->data);
}




void static read_png_data_callback(png_structp png_ptr, png_byte* raw_data, png_size_t read_length) {
    ReadDataHandle* handle = (ReadDataHandle*)png_get_io_ptr(png_ptr);
    const png_byte* png_src = handle->data.data + handle->offset;
    
    memcpy(raw_data, png_src, read_length);
    handle->offset += read_length;
}


static PngInfo read_and_update_info(const png_structp png_ptr, const png_infop info_ptr) {
    png_uint_32 width, height;
    int bit_depth, color_type;
    
    png_read_info(png_ptr, info_ptr);
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL);
    
    // Convert transparency to full alpha
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png_ptr);
    
    // Convert grayscale, if needed.
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png_ptr);
    
    // Convert paletted images, if needed.
    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_ptr);
    
    // Add alpha channel, if there is none (rationale: GL_RGBA is faster than GL_RGB on many GPUs)
    if (color_type == PNG_COLOR_TYPE_PALETTE || color_type == PNG_COLOR_TYPE_RGB)
        png_set_add_alpha(png_ptr, 0xFF, PNG_FILLER_AFTER);
    
    // Ensure 8-bit packing
    if (bit_depth < 8)
        png_set_packing(png_ptr);
    else if (bit_depth == 16)
        png_set_scale_16(png_ptr);
    
    png_read_update_info(png_ptr, info_ptr);
    
    // Read the new color type after updates have been made.
    color_type = png_get_color_type(png_ptr, info_ptr);
    
    return (PngInfo) {width, height, color_type};
}

static DataHandle read_entire_png_image(const png_structp png_ptr, const png_infop info_ptr, const png_uint_32 height) {
    png_size_t row_size = png_get_rowbytes(png_ptr, info_ptr);
    int data_length = row_size * height;
    assert(row_size > 0);
    
    png_byte* raw_image = (png_byte*)malloc(data_length);
    assert(raw_image != NULL);
    
    png_byte* row_ptrs[height];
    
    png_uint_32 i;
    for (i = 0; i < height; i++) {
        row_ptrs[i] = raw_image + i * row_size;
    }
    
    png_read_image(png_ptr, &row_ptrs[0]);
    
    return (DataHandle) {raw_image, (png_size_t)data_length};
}

static GLenum get_gl_color_format(const int png_color_format) {
    assert(png_color_format == PNG_COLOR_TYPE_GRAY
           || png_color_format == PNG_COLOR_TYPE_RGB_ALPHA
           || png_color_format == PNG_COLOR_TYPE_GRAY_ALPHA);
    
    switch (png_color_format) {
        case PNG_COLOR_TYPE_GRAY:
            return GL_LUMINANCE;
        case PNG_COLOR_TYPE_RGB_ALPHA:
            return GL_RGBA;
        case PNG_COLOR_TYPE_GRAY_ALPHA:
            return GL_LUMINANCE_ALPHA;
    }
    
    return 0;
}

TRawImageData* FileLoader::readPng2(char* pngData, png_size_t pngLength) {
    image im;
    //FILE* file = fopen(fileName, "rb");
    //пропускаем заголовок, хотя именно сюда можно добавить проверку PNG это или JPEG, чтобы ф-ция сама определяла как грузить картинку
    //fseek(file, 8, SEEK_CUR);
    
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    
    mypng png = { 8, static_cast<unsigned int>(pngLength), pngData };
    png_init_io(png_ptr, (FILE*) &png);
    png_set_read_fn(png_ptr, png_get_io_ptr(png_ptr), userReadData);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);
    
    //читаем данные о картинке
    png_get_IHDR(png_ptr, info_ptr, &im.imWidth, &im.imHeight, &im.bit_depth, &im.color_type, NULL, NULL, NULL);
    
    //определяем размер картинки подходящий для OpenGL
    im.glWidth = reNpot(im.imWidth);
    im.glHeight = reNpot(im.imHeight);
    
    //если картинка содержит прозрачность то на каждый пиксель 4 байта (RGBA), иначе 3 (RGB)
    int row = im.glWidth * (im.color_type == PNG_COLOR_TYPE_RGBA ? 4 : 3);
    im.data = new char[row * im.glHeight];
    
    //в этом массиве содержатся указатели на начало каждой строки
    png_bytep * row_pointers = new png_bytep[im.imHeight];
    for(int i = 0; i < im.imHeight; ++i)
        row_pointers[i] = (png_bytep) (im.data + i * row);
    
    //читаем картинку
    png_read_image(png_ptr, row_pointers);
    png_destroy_read_struct(&png_ptr, &info_ptr, 0);
    delete[] row_pointers;
    
    

    TRawImageData* rawImageData = new TRawImageData();
    rawImageData->width = im.glWidth;
    rawImageData->height = im.glHeight;
    rawImageData->size = row * im.glHeight;
    rawImageData->gl_color_format = GL_RGB;
    rawImageData->data = (void*)im.data;
    return rawImageData;

}

