#ifndef PlatformFileSystemTileWriter_h
#define PlatformFileSystemTileWriter_h

#include <stdio.h>
#include <jni.h>


class PlatformFileSystemTileWriter{

public:

    bool writeTile(int z, int x, int y, void* data, long length);


private:

};

#endif