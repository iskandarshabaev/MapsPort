/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include "mapview.hpp"
/* Header for class my_mega_pack_NativeCallsClass */

#ifdef __cplusplus
extern "C" {
#endif

MapView *mapView;

JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_RendererWrapper_on_1surface_1created(JNIEnv *env,
                                                                                       jclass myclass);

JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_RendererWrapper_on_1surface_1changed(JNIEnv *env,
                                                                                       jclass myclass,
                                                                                       jint width,
                                                                                       jint height);

JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_RendererWrapper_on_1draw_1frame(JNIEnv *env,
                                                                                  jclass myclass);

JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_RendererWrapper_on_1touch_1press(JNIEnv *env,
                                                                                   jclass myclass,
                                                                                   jfloat normalizedX,
                                                                                   jfloat normalizedY);

JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_RendererWrapper_on_1touch_1drag(JNIEnv *env,
                                                                                  jclass myclass,
                                                                                  jfloat normalizedX,
                                                                                  jfloat normalizedY);

JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_RendererWrapper_on_1touches_1ended(JNIEnv *env,
                                                                                     jclass myclass,
                                                                                     jfloat normalizedX,
                                                                                     jfloat normalizedY);

JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_RendererWrapper_zoom_1in(JNIEnv *env,jclass myclass);

JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_RendererWrapper_zoom_1out(JNIEnv *env,jclass myclass);

#ifdef __cplusplus
}
#endif