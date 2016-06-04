//
//  FileLoaderPlatform.h
//  MapsPort
//
//  Created by Iskandar on 14.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#ifndef FileLoaderPlatform_h
#define FileLoaderPlatform_h

#include <string>
#include "file_data.hpp"

class FileLoaderPlatform{

public:
    FileLoaderPlatform();
    const char* getAppPath();
    const char* getAssetsPath();
    TFileData* getAsset(std::string *path);
};
#endif