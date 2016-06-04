#include "MapView.hpp"
//#include <android/log.h>
MapView::MapView(){
    camera = new Camera();
}

MapView::~MapView(){
    
}


// Add texture coordinates to Vertex structure as follows
typedef struct {
    float Position[3];
    //float Color[4];
    float TexCoord[2];
} Vertex2;

/*
const Vertex Vertices[] = {
    {{1, -1, 0}, {1, 1, 1, 1},{1,1}},
    {{1, 1, 0}, {1, 1, 1, 1}, {1, 0}},
    {{-1, 1, 0}, {1, 1, 1, 1}, {0,0}},
    {{-1, -1, 0}, {1, 1, 1, 1}, {0, 1} },
    
};
*/

const Vertex2 Vertices[] = {
    {{1, -1, 0}, {1,1}},
    {{1, 1, 0}, {1, 0}},
    {{-1, 1, 0}, {0,0}},
    {{-1, -1, 0}, {0, 1} },
    
};

const GLubyte Indices[] = {
    0, 1, 2,
    2, 3, 0
};


void MapView::zoomIn(){
    zoom+=1;
    for(int i = 0; i < layers.size(); i++){
        layers[i]->zoomIn(zoom);
    }
}

void MapView::setZoom(int zoom){
    this->zoom = zoom;
    for(int i = 0; i < layers.size(); i++){
        layers[i]->setZoom(zoom);
    }
}

void MapView::zoomOut(){
    zoom-=1;
    for(int i = 0; i < layers.size(); i++){
        layers[i]->zoomOut(zoom);
    }
}

void MapView::on_surface_created(){
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    
    //glGenRenderbuffers(1, &_depthRenderBuffer);
    //glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderBuffer);
    //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, 320*2, 568*2);
    
    //glGenRenderbuffers(1, &_colorRenderBuffer);
    //glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
    /*
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorRenderBuffer);
    //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBuffer);
     */
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

    glClearColor(238.0/255.0, 238.0/255.0, 238.0/255.0, 1.0);
    
    fileLoader = new FileLoader();
    httpPlatform = new HttpPlatform();
    
    TileLayer *osmLayer = new TileLayer(camera);
    osmLayer->fileLoader = fileLoader;
    
    osmLayer->httpPlatform = httpPlatform;
   
    //osmLayer->putTiles();
    layers.push_back(osmLayer);
    
    
    _debug_log_v("trrr", "created !!!!");
    //tiles.push_back(*new Tile(3+4194304,0,-5));
    //tiles.push_back(*new Tile(0+4194304,2,-5));
    //tiles.push_back(*new Tile(2+4194304,2,-6));
    //glMatrixMode(GL_);
    zoom = 2;
}

void MapView::on_surface_changed(int width, int height){
    
    glViewport(0, 0, width*scale, height*scale);
    
    float camX = 0;
    float camY = 0;
    float camZ = 1;
    
    camera -> setPosition(camX, camY, camZ);
    camera -> setProjectionMatrix(width*scale, height*scale);
    setZoom(zoom);
    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "scale: %d", scale);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MapView::setScale(int scale){
    this->scale = scale;
}

float para_vertex[]=
{
    50,270,
    100,30,
    54,270,
    104,30
};
float para_color[]=
{
    1,1,1,    //white
    1,1,1,
    1,0,0,    //red
    1,0,0
};

void MapView::on_render(){
    glClearColor(238.0/255.0, 238.0/255.0, 238.0/255.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    
    for(int i = 0; i < layers.size(); i++){
        layers[i]->render(camera);
    }

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(para_vertex), 0);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(para_color), 0);
    glDrawArrays(GL_LINES, 0, 4);
}

void MapView::on_touch_press(float normalized_x, float normalized_y) {
    touch = true;
    x = normalized_x;
    y = normalized_y;
}

void MapView::on_touches_ended(float normalized_x, float normalized_y){
    touch = false;
    x = normalized_x;
    y = normalized_y;
    layers.at(0)->getTiles();
}

void MapView::on_touch_drag(float normalized_x, float normalized_y) {
    if (touch) {
        float mX = x - normalized_x;
        float mY = y - normalized_y;
        camera->moveCamera(mX, mY, 0);
        x = normalized_x;
        y = normalized_y;
    }
    
}