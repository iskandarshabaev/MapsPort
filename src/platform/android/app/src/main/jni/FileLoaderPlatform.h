#include <jni.h>
#include <string>
#include "file_data.hpp"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_platform_PlatformFileUtils_init_1file_1manager(JNIEnv *env,
                                                                                               jclass myclass, jstring str);

JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_platform_PlatformFileUtils_init_1asset_1manager_1cpp(
        JNIEnv *env, jclass jclazz, jobject java_asset_manager);


#ifdef __cplusplus
}
#endif

#ifndef FileLoaderPlatform_h
#define FileLoaderPlatform_h
class FileLoaderPlatform{
public:

    FileLoaderPlatform();
    const char* getAppPath();
    const char* getAssetsPath();
    TFileData* getAsset(std::string *path);
    char* storagePath;
};
#endif