//
//  PlatformFileSystemTileLoader.h
//  MapsPort
//
//  Created by Iskandar on 29.05.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#ifndef PlatformFileSystemTileWriter_h
#define PlatformFileSystemTileWriter_h

#include <stdio.h>
class PlatformFileSystemTileWriter{
    
public:
    
    bool writeTile(int z, int x, int y, void* data, long length);
    
private:
    
};

#endif
