//
//  filesystem_tile_reader.hpp
//  MapsPort
//
//  Created by Iskandar on 29.05.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#ifndef filesystem_tile_reader_hpp
#define filesystem_tile_reader_hpp

#include <stdio.h>
#include <stdio.h>
#include "file_data.hpp"
#include "tile_reader_base.hpp"
#include "file_loader.h"

class FileSystemTileReader : public TileReaderBase
{
public:
    TFileData* getTile(int z, int x, int y);
    FileLoader *fileLoader;
    
};
#endif /* filesystem_tile_reader_hpp */
