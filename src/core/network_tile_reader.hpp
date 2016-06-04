//
//  tile_reader.hpp
//  MapsPort
//
//  Created by Iskandar on 28.05.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#ifndef tile_reader_hpp
#define tile_reader_hpp

#include <stdio.h>
#include "file_data.hpp"
#include "tile_reader_base.hpp"

class NetworkTileReader : public TileReaderBase
{
public:
    TFileData* getTile(int z, int x, int y);
};

#endif /* tile_reader_hpp */
