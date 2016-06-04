//
//  tile_writer_base.hpp
//  MapsPort
//
//  Created by Iskandar on 29.05.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#ifndef tile_writer_base_hpp
#define tile_writer_base_hpp

#include <stdio.h>
class TileWriterBase{
public:
    virtual bool writeTile(int z, int x, int y, void* data, long length){
        return false;
    }
};

#endif /* tile_writer_base_hpp */
