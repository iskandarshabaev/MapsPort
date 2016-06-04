//
//  filesystem_tile_reader.cpp
//  MapsPort
//
//  Created by Iskandar on 29.05.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#include "filesystem_tile_reader.hpp"
#include <curl/curl.h>
#include <sstream>

TFileData* FileSystemTileReader::getTile(int z, int x, int y){
    std::string *str = new std::string(std::to_string(z) + "/" + std::to_string(x) + "/" + std::to_string(y));
    std::string *path = new std::string("tiles/osm/" + *str + ".png");
    TFileData *png_file = fileLoader->loadFile(path);
    
    if(png_file != NULL && png_file->data_length > 0){
        return png_file;
    }else{
        return NULL;
    }
}