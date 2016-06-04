//
//  tile_reader_abstract.hpp
//  MapsPort
//
//  Created by Iskandar on 29.05.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#ifndef tile_reader_abstract_hpp
#define tile_reader_abstract_hpp

#include <stdio.h>
#include "file_data.hpp"

class TileReaderBase{
public:
    virtual TFileData* getTile(int z,int x,int y);
};
#endif /* tile_reader_abstract_hpp */
