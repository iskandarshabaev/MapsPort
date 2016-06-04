//
//  tilelayer.hpp
//  MapsPort
//
//  Created by Iskandar on 10.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#ifndef tilelayer_hpp
#define tilelayer_hpp

#include <stdio.h>
#include <vector>
#include "tile.hpp"
#include <map>
#include "HtppPlatform.h"
#include <string>
#include "camera.hpp"
#include "file_loader.h"
#include "threadpool.h"
#include "raw_image.hpp"
#include <mutex>
#include <stdlib.h>
#include "lrucache.h"
#include <memory>
#include "network_tile_reader.hpp"
#include "filesystem_tile_reader.hpp"
#include "tile_reader_base.hpp"
#include "tile_writer_base.hpp"
#include "filesystem_tile_writer.hpp"

class TileLayer{
    
private:
    std::vector<std::shared_ptr<Tile>> renderTiles;
    std::vector<std::pair<std::string, std::shared_ptr<Tile>>> tileCache2;
    
    std::vector<TRawImageData*> images;
    //std::map<std::string, Tile*> tileCache;
    
    Camera *camera;
    GLuint program;
    int width;
    int height;
    int zoom;
    ThreadPool *thread_pool;
    std::mutex mutex_;
    bool findTile(int x, int y, int z);
public:
    TileLayer(Camera *camera);
    void render(Camera *camera);
    void putTiles();
    void refresh();
    void getTiles();
    FileLoader *fileLoader;
    HttpPlatform *httpPlatform;
    void setZoom(int zoom);
    void zoomIn(int zoom);
    void zoomOut(int zoom);
    void foo2(int x, int y, int z);
    TileReaderBase* networkTileReader = new NetworkTileReader();
    TileReaderBase* fileSystemTileReader = new FileSystemTileReader();
    TileWriterBase* tileWriter = new FileSystemTileWriter();
};

#endif /* tilelayer_hpp */
