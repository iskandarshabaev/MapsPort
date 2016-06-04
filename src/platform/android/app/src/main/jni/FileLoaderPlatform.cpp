#include "FileLoaderPlatform.h"
#include <android/asset_manager_jni.h>
#include <stdio.h>
#include <android/log.h>
#include <jni.h>

AAssetManager *asset_manager;
JavaVM* gg_JavaVM;
const char* storage;
void Log(char* s);

JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_platform_PlatformFileUtils_init_1file_1manager(JNIEnv *env,
                                                                                               jclass myclass, jstring path){
    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "setting JavaVM start");
    env->GetJavaVM(&gg_JavaVM);
    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "setting JavaVM done");

    const jsize len = env->GetStringUTFLength(path);
    storage = env->GetStringUTFChars(path, (jboolean *)0);
}

JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_platform_PlatformFileUtils_init_1asset_1manager_1cpp(
        JNIEnv *env, jclass jclazz, jobject java_asset_manager) {
    //UNUSED(jclazz);
    asset_manager = AAssetManager_fromJava(env, java_asset_manager);
}


FileLoaderPlatform::FileLoaderPlatform(){

}


const char* FileLoaderPlatform::getAppPath(){
    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "getAppPath is called: %s", storage);
    return storage;
}

const char* FileLoaderPlatform::getAssetsPath(){
    //env->GetJavaVM(&g_JavaVM);
    //Log("trtrtr");
    return "";
}

TFileData* FileLoaderPlatform::getAsset(std::string *path){

    __android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "getAsset is called");
    TFileData *fileData = new TFileData();
    AAsset *asset = AAssetManager_open(asset_manager, path->c_str(), AASSET_MODE_STREAMING);
    assert(asset != NULL);

    fileData->data_length = AAsset_getLength(asset);
    fileData->data = (void*) AAsset_getBuffer(asset);

    //return (FileData) {, , asset};

    __android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "asset is loaded");

    return fileData;

}


void Log(char* s){
    __android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "Log is called");
    JNIEnv *env;
    gg_JavaVM->GetEnv((void**)&env, JNI_VERSION_1_6);

    jstring jstr1 = env->NewStringUTF(s);

    jclass clazz = env->FindClass("com/ishabaev/mapsport/platform/PlatformFileUtils");
    jmethodID mid = env->GetStaticMethodID(clazz, "log", "()V");

    __android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "CallStaticObjectMethod start");
    env->CallStaticVoidMethod(clazz, mid);
    __android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "CallStaticObjectMethod done");
}