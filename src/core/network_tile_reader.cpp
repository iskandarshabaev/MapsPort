//
//  tile_reader.cpp
//  MapsPort
//
//  Created by Iskandar on 28.05.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#include "network_tile_reader.hpp"
#include <curl/curl.h>
#include <sstream>

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t curlCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    
    
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;
    
    mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
    if(mem->memory == NULL) {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }
    
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

TFileData* NetworkTileReader::getTile(int z, int x, int y){
    struct MemoryStruct chunk;
    
    chunk.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */
    chunk.size = 0;
    
    
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        
        std::ostringstream os;
        os << "http://tile.openstreetmap.org/" << z << "/" << x << "/" << y << ".png";
        std::string s = os.str();
        
        
        curl_easy_setopt(curl, CURLOPT_URL, s.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
        curl_easy_setopt(curl, CURLOPT_FAILONERROR, true);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &curlCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    
    TFileData * file = new TFileData();
    file->data = chunk.memory;
    file->data_length = chunk.size;
    return file;
}