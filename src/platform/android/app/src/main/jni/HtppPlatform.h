#ifndef HtppPlatform_hpp
#define HtppPlatform_hpp

#include <stdio.h>

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_platform_PlatformFileUtils_init_1http_1platform(JNIEnv *env,
                                                                                                 jclass myclass);


#ifdef __cplusplus
}
#endif

class HttpPlatform{

public:

    void* makeRequest(int x, int y, int z);
    void setJV(JavaVM* g_JavaVM);

    JavaVM* g_JavaVM;
    jclass globalHttpRequestClass;
private:

};

#endif /* HtppPlatform_hpp */