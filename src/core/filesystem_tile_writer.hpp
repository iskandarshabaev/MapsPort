//
//  filesystem_tile_writer.hpp
//  MapsPort
//
//  Created by Iskandar on 29.05.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#ifndef filesystem_tile_writer_hpp
#define filesystem_tile_writer_hpp

#include <stdio.h>
#include "tile_writer_base.hpp"
#include "FileLoaderPlatform.h"
#include "PlatformFileSystemTileWriter.h"

class FileSystemTileWriter : public TileWriterBase{
public:
    PlatformFileSystemTileWriter *tileWriter = new PlatformFileSystemTileWriter();
    virtual bool writeTile(int z, int x, int y, void* data, long length){
        return tileWriter->writeTile(z, x, y, data,length);
    }
};
#endif /* filesystem_tile_writer_hpp */
