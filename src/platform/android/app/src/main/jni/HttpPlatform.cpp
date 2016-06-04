#include "HtppPlatform.h"
#include <android/log.h>
#include "file_data.hpp"
#include <stdio.h>
#include <string.h>
#include "file_loader.h"

JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_platform_PlatformFileUtils_init_1http_1platform(JNIEnv *env,
                                                                                                 jclass myclass){
    //env->GetJavaVM(&g_JavaVM);
    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "http platform is initialized");
}


void HttpPlatform::setJV(JavaVM* g_JavaVM){
    __android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "setJV is called");
    this->g_JavaVM = g_JavaVM;

    JNIEnv *env;
    g_JavaVM->GetEnv((void**)&env, JNI_VERSION_1_6);
    jclass localClass = env->FindClass("com/ishabaev/mapsport/HttpRequest");
    globalHttpRequestClass = (jclass) env->NewGlobalRef(localClass);
}

void* HttpPlatform::makeRequest(int x, int y, int z){

    JNIEnv *env;
    g_JavaVM->GetEnv((void**)&env, JNI_VERSION_1_6);
    g_JavaVM->AttachCurrentThread(&env, NULL);

    jmethodID ctor = env->GetMethodID(globalHttpRequestClass, "<init>", "()V");
    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "makeRequest params: z: %d, x: %d, y: %d", z, x, y);
    jobject myo = env->NewObject(globalHttpRequestClass, ctor);
    //env->MonitorEnter(myo);

    //jmethodID send = env->GetMethodID(globalHttpRequestClass, "send", "(III)[B");
    //jbyteArray array = (jbyteArray) env->CallObjectMethod(myo, send,(jint)x, (jint)y, (jint)z);
    //jbyteArray array = (jbyteArray)
    jmethodID send = env->GetMethodID(globalHttpRequestClass, "send", "(III)[B");
    jbyteArray array = (jbyteArray)env->CallObjectMethod(myo, send,(jint)x, (jint)y, (jint)z);

    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "get test string");
    //jmethodID getStringMethod = env->GetMethodID(globalHttpRequestClass, "getString", "(I)[B");
    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "CallObjectMethod test string");
    //jbyteArray array = (jbyteArray)env->CallObjectMethod(myo, getStringMethod,(jint)x);


    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "CallObjectMethod called");


    //jbyte* bufferPtr = env->GetByteArrayElements(array, 0);

    //jbyte * data = new jbyte();
    jint length = env->GetArrayLength(array);
    //env->GetByteArrayRegion(array, 0, length, data);

    //void* buffer = malloc(length);
    unsigned char* buffer = new unsigned char[length];
    env->GetByteArrayRegion(array, 0, length, reinterpret_cast<jbyte*>(buffer));
    //process_buffer(buffer);
    //jbyte *bd = (jbyte *) malloc(length);
    //memcpy(bd, buffer, length);
    //free(buffer);

    //memcpy(bufferPtr, data, size*sizeof(jbyte));

    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "byte copied");
    TFileData *pngTile = new TFileData();
    pngTile->data = (void*)buffer;
    pngTile->data_length = length;

    //FileLoader *fileLoader = new FileLoader();
    //fileLoader->readPng((char*)buffer, length);
    //env->ReleaseByteArrayElements(array,bufferPtr,0);

    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "GetByteArrayElements called");


    //const char *strReturn = env->GetStringUTFChars((jstring)rv, (jboolean*) true);
    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "GetArrayLength: %d", (int)lengthOfArray);


    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort",  "%s", *strReturn);


    //env->MonitorExit(myo);
    env->DeleteLocalRef(myo);
    g_JavaVM->DetachCurrentThread();
    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "return tile png");
    return pngTile;
    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "request is done");

    //jclass clazz = env->FindClass("com/ishabaev/opengles/platform/PlatformFileUtils");
    //jmethodID mid = env->GetStaticMethodID(clazz, "log", "()V");

    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "CallStaticObjectMethod start");
    //env->CallStaticVoidMethod(clazz, mid);
    //__android_log_print(ANDROID_LOG_VERBOSE, "MapsPort", "CallStaticObjectMethod done");
}