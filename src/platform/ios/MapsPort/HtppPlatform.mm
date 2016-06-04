//
//  HtppPlatform.cpp
//  MapsPort
//
//  Created by Iskandar on 11.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#include "HtppPlatform.h"
#include "HttpRequest.h"
#include "file_data.hpp"

void* HttpPlatform::makeRequest(int x, int y, int z){
    HttpRequest *httpRequest = [[HttpRequest alloc]init];
    NSData *data = [httpRequest send:x :y :z];
    TFileData *pngTile = new TFileData();
    pngTile->data = (void*)[data bytes];
    pngTile->data_length = data.length;
    return pngTile;
}