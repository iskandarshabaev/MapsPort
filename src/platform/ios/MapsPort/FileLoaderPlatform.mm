//
//  FileLoaderPlatform.m
//  MapsPort
//
//  Created by Iskandar on 14.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#include "FileLoaderPlatform.h"
#import <Foundation/Foundation.h>

FileLoaderPlatform::FileLoaderPlatform(){
    
}


const char* FileLoaderPlatform::getAppPath(){
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString*path = paths.firstObject;
    return [path UTF8String];
}

const char* FileLoaderPlatform::getAssetsPath(){
    NSMutableString* path = [[NSMutableString alloc] initWithString:@"/assets"];
    return [[[NSBundle mainBundle] pathForResource:path ofType:nil] cStringUsingEncoding:NSUTF8StringEncoding];
}

TFileData* FileLoaderPlatform::getAsset(std::string *path){
    
    std::string *basePath = new std::string(getAssetsPath());
    *basePath += "/" + *path;
    
    FILE* stream = fopen(basePath->c_str(), "r");
    assert (stream != NULL);
    
    fseek(stream, 0, SEEK_END);
    long stream_size = ftell(stream);
    fseek(stream, 0, SEEK_SET);
    
    void* buffer = malloc(stream_size);
    fread(buffer, stream_size, 1, stream);
    
    assert(ferror(stream) == 0);
    fclose(stream);
    
    TFileData *fileData = new TFileData();
    fileData->data_length = stream_size;
    fileData->data = buffer;
    return fileData;

}