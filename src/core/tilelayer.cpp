//
//  tilelayer.cpp
//  MapsPort
//
//  Created by Iskandar on 10.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#include "tilelayer.hpp"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
//#include <android/log.h>
#include <curl/curl.h>
#include <sstream>
#include <sstream>
struct comp
{
    comp(std::string const& s) : _s(s) { }
    
    bool operator () (std::pair<std::string, std::shared_ptr<Tile>> const& p)
    {
        return (p.first == _s);
    }
    
    std::string _s;
};

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


void TileLayer::foo2(int x, int y, int z)
{
    
    std::string *str = new std::string(std::to_string(z) + "/" + std::to_string(x) + "/" + std::to_string(y));
    std::vector<std::pair<std::string, std::shared_ptr<Tile>>>::iterator i = std::find_if(tileCache2.begin(), tileCache2.end(), comp(*str));
    if (i == tileCache2.end())
    {
        TFileData *png_file;
        if(fileSystemTileReader != NULL)
        {
            mutex_.lock();
            png_file = fileSystemTileReader->getTile(z, x, y);
            mutex_.unlock();
        }
        
        if(((png_file == NULL) || (png_file != NULL && png_file->data == NULL) ) && networkTileReader != NULL)
        {
            png_file = networkTileReader->getTile(z, x, y);
            if(png_file!= NULL && tileWriter != NULL && png_file->data != NULL && png_file->data_length > 8){
                mutex_.lock();
                tileWriter->writeTile(z, x, y, png_file->data,png_file->data_length);
                mutex_.unlock();
            }
        }
        
        if(png_file != NULL && png_file->data != NULL && png_file->data_length > 8)
        {
            TRawImageData* raw_image_data = fileLoader->get_raw_image_data_from_png(png_file->data, png_file->data_length);
            if(raw_image_data != NULL)
            {
                raw_image_data->x = x;
                raw_image_data->y = y;
                raw_image_data->z = z;
                mutex_.lock();
                images.push_back(raw_image_data);
                mutex_.unlock();
                
            }
            fileLoader->release_file_data(png_file);
        }
    }
    
}






TileLayer::TileLayer(Camera *camera){
    this->camera = camera;
    std::string *vertex = new std::string("shaders/simple.vsh");
    std::string *fragment = new std::string("shaders/simple.fsh");
    program = fileLoader->build_program_from_assets(vertex, fragment);
    thread_pool = new ThreadPool(4);
}



void TileLayer::setZoom(int zoom){
    camera->setZoom(zoom-1);
    width = pow(2,zoom);
    height = pow(2,zoom);
    this->zoom = zoom;
    //tileCache.clear();
    renderTiles.clear();
    tileCache2.clear();
    getTiles();
}



void TileLayer::zoomIn(int zoom){
    camera->zoomIn(zoom-1);
    width = pow(2,zoom);
    height = pow(2,zoom);
    this->zoom = zoom;
    //tileCache.clear();
    renderTiles.clear();
    tileCache2.clear();
    getTiles();
}

void TileLayer::zoomOut(int zoom){
    camera->zoomOut(zoom-1);
    width = pow(2,zoom);
    height = pow(2,zoom);
    this->zoom = zoom;
    //tileCache.clear();
    renderTiles.clear();
    tileCache2.clear();
    getTiles();
}


void TileLayer::render(Camera *camera){
    
    
    
    /*
     for (std::vector<TRawImageData*>::iterator it = images.begin() ; it != images.end(); ++it){
     GLuint texture = fileLoader.load_texture((*it)->width, (*it)->height,(*it)->gl_color_format, (*it)->data);
     Tile *tile = new Tile((*it)->x,(*it)->y,(*it)->z,texture,program);
     renderTiles.push_back(tile);
     std::string *str = new std::string(std::to_string((*it)->z) + "/" + std::to_string((*it)->x) + "/" + std::to_string((*it)->y));
     tileCache.insert(std::pair<std::string, Tile *>(*str,tile));
     fileLoader.release_raw_image_data((*it));
     images.erase(it);
     
     }
     */
    
    
    
    
    for(int i = 0; i < images.size(); i++){
        GLuint texture = fileLoader->load_texture(images[i]->width, images[i]->height,images[i]->gl_color_format, images[i]->data);
        
        std::shared_ptr<Tile> pointer (new Tile(images[i]->x,images[i]->y,images[i]->z,texture,program));
        //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "tile params: x: %d, y: %d", images[i]->x, images[i]->y);
        renderTiles.push_back(pointer);
        std::string str = std::to_string(images[i]->z) + "/" + std::to_string(images[i]->x) + "/" + std::to_string(images[i]->y);
        //tileCache.insert(std::pair<std::string, Tile *>(*str,tile));
        tileCache2.push_back((std::pair<std::string, std::shared_ptr<Tile>>(str, move(pointer))));
        fileLoader->release_raw_image_data(images[i]);
        images.erase(images.begin() + i);
    }
    
    
    /*
    std::vector<Tile*>::iterator it;
    for(it = renderTiles.begin() ; it != renderTiles.end() ; ++it)
    {
        if(!(*it)->interceptRect(camera->getRect())){
            std::string *str = new std::string(std::to_string((*it)->z) + "/" + std::to_string((*it)->x) + "/" + std::to_string((*it)->y));
            tileCache.insert(std::pair<std::string, Tile *>(*str,(*it)));
            renderTiles.erase(it);
        }
    }
    */
    
    for(int i = 0; i < renderTiles.size(); i++){
        //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "tile params: x: %g, y: %g", renderTiles[i]->x, renderTiles[i]->y);
        mutex_.lock();
        renderTiles[i]->render(camera);
        mutex_.unlock();
    }
}

void TileLayer::putTiles(){
    
    int z = 2;
    for(int x = 0; x < 4; x ++){
        for(int y = 0; y < 4; y++){
            std::string *str = new std::string("");
            *str+=std::to_string(z) + "/" + std::to_string(x) + "/" + std::to_string(y);
            //tileCache.insert(std::pair<std::string *, Tile*> (str, new Tile(x,y,-2)));
            //httpPlatform.makeRequest(x, y, -2);
        }
    }
}

void TileLayer::refresh(){
    for (int i = 0; i < renderTiles.size(); i++){
        if(!renderTiles.at(i)->interceptRect(camera->getRect())){
            Position *position = camera->getPosition();
            std::string str = std::to_string(position->z) + "/" + std::to_string(position->x) + "/" + std::to_string(position->y);
            //if(tileCache.find(*str) == tileCache.end()){
              //  tileCache.insert(std::pair<std::string, Tile *>(*str,renderTiles.at(i)));
            //}
            renderTiles.erase(renderTiles.begin() + i);
        }
    }
}

void TileLayer::getTiles(){

    int left = camera->getRect().left/2;
    int right = camera->getRect().right/2;
    int bottom = -camera->getRect().bottom/2;
    int top = -camera->getRect().top/2;
    
    //if(right>width) right = width;
    if(top<0) top = 0;
    
    if(left<0) left = 0;
    if(bottom>=height) bottom = height-1;
    
    if(right>=width) right = width-1;
    if(top>height) top = height;
    
    if(left>width) left = width;
    if(bottom<0) bottom = 0;
    
    //httpPlatform->makeRequest(0, 0, -2);
    
    /*
    std::vector<Tile*>::iterator iteration = renderTiles.begin();
    while (iteration != renderTiles.end())
    {
        bool isActive =  (*iteration)->interceptRect(camera->getRect());
        if (!isActive)
        {
            renderTiles.erase(iteration++);  // alternatively, i = items.erase(i);
        }
        else
        {
            ++iteration;
        }
    }
    /*
    std::vector<Tile*>::iterator it;
    for(it = renderTiles.begin() ; it != renderTiles.end() ; ++it)
    {
        if(!(*it)->interceptRect(camera->getRect())){
            std::string *str = new std::string(std::to_string((*it)->z) + "/" + std::to_string((*it)->x) + "/" + std::to_string((*it)->y));
            tileCache2.push_back(std::pair<std::string, Tile *>(*str,(*it)));
            renderTiles.erase(it);
        }
    }
     */

    int size = renderTiles.size();
    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "renderTiles.size: %d", size);

    
    for(auto i = renderTiles.begin(); i != renderTiles.end();)
    {
        if(!(*i)->interceptRect(camera->getRect())){
            i = renderTiles.erase(i);
        }
        else{
            ++i;
        }
    }
    
    //size = renderTiles.size();
    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "renderTiles.size: %d", size);
    
    if(tileCache2.size() > 40){
        
        /*
    std::vector<std::pair<std::string, Tile*>>::iterator itt;
    for(itt = tileCache2.begin() ; itt != tileCache2.end() ; ++itt)
    {
        //std::vector<Tile*>::iterator iter;
        //iter=find(renderTiles.begin(),renderTiles.end(),(*itt).second);
        //if(iter==renderTiles.end()){
            //renderTiles.erase(iter);
            tileCache2.erase(itt);
          //  glDeleteTextures(1, &(*itt).second->texture);
            free ((*itt).second);
        //}

    }
         */
        
        
        
        for(auto i = tileCache2.begin(); i != tileCache2.end();)
        {
            std::vector<std::shared_ptr<Tile>>::iterator iter;
            iter=find(renderTiles.begin(),renderTiles.end(),(*i).second);
            if(iter==renderTiles.end()){
                //glDeleteTextures(1, &(*i).second->texture);
                //glDeleteProgram((*i).second->program);
                //delete ((*i).second);
                i = tileCache2.erase(i);
            }
            else{
                ++i;
            }
            if(tileCache2.size()<40){
                break;
            }
        }
    }
    
    mutex_.lock();
    /*
    if(tileCache2.size() > 12){
        while(tileCache2.size() > 12){
            Tile *tile = (tileCache2.begin()->second);
        
            std::vector<Tile*>::iterator it;
            it=find(renderTiles.begin(),renderTiles.end(),tile);
            if(it!=renderTiles.end()){
                renderTiles.erase(it);
                tileCache2.erase(tileCache2.begin());
                glDeleteTextures(1, &tile->texture);
                free (tile);
            }
        }
    }
     */
    mutex_.unlock();
    
    for(int x = left; x <= right; x ++){
        for(int y = top; y <= bottom; y++){
            std::string str = std::to_string(zoom) + "/" + std::to_string(x) + "/" + std::to_string(y);
            std::vector<std::pair<std::string, std::shared_ptr<Tile>>>::iterator i = std::find_if(tileCache2.begin(), tileCache2.end(), comp(str));
            if (i == tileCache2.end() && !findTile(x, y, zoom))
            {
                thread_pool->runAsync(&TileLayer::foo2,this,x,y,zoom);
                /*
                std::string *path = new std::string("tiles/osm/" + *str + ".png");
                GLuint texture = fileLoader.load_png_asset_into_texture(path);
                if(texture != 0){
                    Tile *tile = new Tile(x,y,zoom,texture,program);
                    //renderTiles.push_back(tile);
                    tileCache.insert(std::pair<std::string, Tile *>(*str,tile));
                    renderTiles.push_back(tileCache.at(*str));
                }
                 */
            }else{
                if(std::find(renderTiles.begin(), renderTiles.end(), i->second) != renderTiles.end()) {
                    /* v contains x */
                } else {
                    renderTiles.push_back(i->second);
                }
            }
            
            /*
            for(unsigned i=0; i< renderTiles.size();i++){
                if(!renderTiles[i]->interceptRect(camera->getRect())){
                    renderTiles.erase(renderTiles.begin() + i);
                }
            }
            */
            //httpPlatform.makeRequest(x, y, -2);
        }
    }
}

bool TileLayer::findTile(int x, int y, int z){
    for (int i = 0; i < renderTiles.size(); i++) {
        if(renderTiles[i]->x == x &&
           renderTiles[i]->y == y &&
           renderTiles[i]->z){
            return true;
        }
    }
    return false;
}