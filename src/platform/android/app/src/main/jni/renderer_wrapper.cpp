#include "mapview.hpp"
#include <jni.h>
#include <iostream>
#include "renderer_wrapper.h"


JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_RendererWrapper_on_1surface_1created(JNIEnv *env,
																					   jclass myclass){
 mapView = new MapView();
	mapView->setScale(1);
	mapView->on_surface_created();
	JavaVM* g_JavaVM;
	env->GetJavaVM(&g_JavaVM);
	mapView->httpPlatform->setJV(g_JavaVM);
}

JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_RendererWrapper_on_1surface_1changed(JNIEnv *env,
																					   jclass myclass,
																					   jint width,
																					   jint height){
	mapView->on_surface_changed(width, height);
}

JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_RendererWrapper_on_1draw_1frame(JNIEnv *, jclass){
	mapView -> on_render();
}


JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_RendererWrapper_on_1touch_1press(JNIEnv *env,
																				   jclass myclass,
																				   jfloat normalizedX,
																				   jfloat normalizedY){
	mapView->on_touch_press(normalizedX, normalizedY);
}

JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_RendererWrapper_on_1touch_1drag(JNIEnv *env,
																				  jclass myclass,
																				  jfloat normalizedX,
																				  jfloat normalizedY){
	mapView->on_touch_drag(normalizedX, normalizedY);
}

JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_RendererWrapper_on_1touches_1ended(JNIEnv *env,
																				  jclass myclass,
																				  jfloat normalizedX,
																				  jfloat normalizedY){
	mapView->on_touches_ended(normalizedX, normalizedY);
}


JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_RendererWrapper_zoom_1in(JNIEnv *env,jclass myclass){
	mapView->zoomIn();
}


JNIEXPORT void JNICALL Java_com_ishabaev_mapsport_RendererWrapper_zoom_1out(JNIEnv *env,jclass myclass){
	mapView->zoomOut();
}