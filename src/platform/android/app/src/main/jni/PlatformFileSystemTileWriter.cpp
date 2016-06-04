#include "PlatformFileSystemTileWriter.h"
#include "FileLoaderPlatform.h"
#include <android/log.h>
#include <sys/stat.h>

bool PlatformFileSystemTileWriter:: writeTile(int z, int x, int y, void* data, long length){


/*
    FileLoaderPlatform *loader;
    JNIEnv *env;
    JavaVM* g_JavaVM = dddd;

    if(dddd == NULL){
        __android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "daddasdsa");
    }
    g_JavaVM->GetEnv((void**)&env, JNI_VERSION_1_6);
    g_JavaVM->AttachCurrentThread(&env, NULL);
    jmethodID ctor = env->GetMethodID(uuuu, "<init>", "()V");
    jobject myo = env->NewObject(uuuu, ctor);
    jmethodID send = env->GetMethodID(uuuu, "writeFile", "(BJ)Z");


    jbyteArray bArray=env->NewByteArray(length);
    env->SetByteArrayRegion(bArray, 0, length, (jbyte *)data);


    env->CallObjectMethod(myo, send, bArray, (jlong)length);

    std::string *str = new std::string(std::to_string(z) + "/" + std::to_string(x) + "/" + std::to_string(y) + ".png");


    std::string *basePath = new std::string(loader->getAppPath());
    *basePath += "/tiles/osm/" + *str;
    __android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "%s", basePath->c_str());

    env->DeleteLocalRef(bArray);
    */


    FileLoaderPlatform *loader;
    std::string *basePath = new std::string(loader->getAppPath());
    *basePath += "/tiles";
    mkdir(basePath->c_str(), 0770);
    *basePath += "/osm";
    mkdir(basePath->c_str(), 0770);
    *basePath += "/" + std::to_string(z);
    mkdir(basePath->c_str(), 0770);
    *basePath += "/" + std::to_string(x);
    mkdir(basePath->c_str(), 0770);
    *basePath += "/" + std::to_string(y) + ".png";
    __android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "%s", basePath->c_str());

    //*basePath += "/tiles/osm/" + std::to_string(y)  + ".png";
    FILE *output = fopen(basePath->c_str(), "w+");
    if(output != NULL){
        fwrite(data, sizeof(unsigned char*), length, output);
        fflush(output);
        fclose (output);
    }
    delete basePath;
    return true;
}